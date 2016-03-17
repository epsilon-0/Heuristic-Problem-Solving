// 
// Copyright (c) 2010, Benjamin Kaufmann
// 
// This file is part of Clasp. See http://www.cs.uni-potsdam.de/clasp/ 
// 
// Clasp is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Clasp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Clasp; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
#ifndef CLASP_PARALLEL_SOLVE_H_INCLUDED
#define CLASP_PARALLEL_SOLVE_H_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef DISABLE_MULTI_THREADING

#include <clasp/solve_algorithms.h>
#include <clasp/constraint.h>
#include <clasp/solver_types.h>
#include <clasp/util/multi_queue.h>

/*!
 * \file 
 * Defines classes controlling multi-threaded parallel solving
 * 
 */
namespace Clasp { 

//! A parallel algorithm for multi-threaded solving with and without search-space splitting
/*!
 * The class adapts clasp's basic solve algorithm
 * to a parallel solve algorithm that solves
 * a problem using a given number of threads.
 * It supports guiding path based solving, portfolio based solving, as well
 * as a combination these two approaches.
 */
class ParallelSolve : public SolveAlgorithm {
public:
	ParallelSolve();
	~ParallelSolve();
	// "setup" interface
	static uint32 hardwareThreads();
	bool   integrateUseHeuristic() const { return intHeuristic_; }
	uint32 integrateGrace()        const { return intGrace_; }
	uint32 integrateFlags()        const { return intFlags_; }
	uint32 numThreads()            const { return static_cast<uint32>(numThreads_); }
	SharedContext* init(int numThreads, SharedContext& ctx);
	void   setForceGP(bool gp);
	void   setIntegrate(uint32 grace, uint8 filter);
	void   setRestarts(uint32 maxR, const ScheduleStrategy& rs);
	
	// solve interface 
	
	//! must be called once for each solver except the master
	void   addThread(Solver& s, SharedContext* ctx, SolveParams& p);
	//! terminates current solving process
	bool   terminate();
	
	// interface for controlling the solve process
	struct Message_t {
		enum Type {
			  /* control */ quit_message = 0, terminate_message = 1, unsat_message = 2, restart_message = 3
			, /* other */   not_a_control_message = 4, split_message, update_message 
		};
	};
	typedef Message_t::Type MessageType;	
	bool   handleMessages(Solver& s);
	void   pushWork(LitVec& gp);
	void   postMessage(MessageType);
	bool   validModel(Solver& s, bool forceUpdate, bool disjointPath);
	Enumerator* enumerator() const { return enumerator_; }
private:
	ParallelSolve(const ParallelSolve&);
	ParallelSolve& operator=(const ParallelSolve&);
	typedef SingleOwnerPtr<const LitVec> PathPtr;
	typedef std::pair<SharedContext*, uint32> ThreadParams;
	// -------------------------------------------------------------------------------------------
	// Thread setup 
	void releaseThreads();
	void initThreads();
	void initThread(Solver& s, const SolveParams& p);
	void runThread(ThreadParams params);
	// -------------------------------------------------------------------------------------------
	// Algorithm steps
	bool   doSolve(Solver& s, const SolveParams& p, const LitVec& assume);
	void   startSolve(Solver& s, const SolveParams& p, const LitVec& assume);
	bool   endSolve(Solver& s); 
	void   initQueue();
	bool   requestWork(Solver& s, PathPtr& out);
	bool   backtrackFromModel(Solver& s);
	void   terminateUnsat(Solver& s, bool complete);
	void   terminateComplete(bool complete);
	bool   waitOnRestart(Solver& s);
	void   requestRestart();
	// -------------------------------------------------------------------------------------------
	struct SharedData;
	struct ThreadInfo;
	SharedData*         shared_;            // Shared control data
	ThreadInfo**        thread_;            // Thread-locl control data
	Enumerator*         enumerator_;        // Shared enumerator
	const LitVec*       initialPath_;       // initial guiding path - typically empty
	struct ThreadControlFlags {
	  ThreadControlFlags();
		enum Flag { 
			  quit_flag = 1, terminate_flag = 2, unsat_flag = 4, restart_flag = 8
			, ctrl_message = quit_flag|terminate_flag|unsat_flag|restart_flag
			, inhibit_restart_flag = 16, complete_flag = 32, allow_gp_flag = 64 
		};
		void reset();
		bool quit()         const { return (control & uint32(quit_flag)) != 0; }
		bool terminate()    const { return (control & uint32(quit_flag|terminate_flag)) != 0; }
		bool restart()      const { return (control & uint32(unsat_flag|restart_flag))  != 0; }
		bool unsatRestart() const { return (control & uint32(unsat_flag)) != 0; }
		bool hasControlMsg()const { return (control & uint32(ctrl_message)) != 0; }
		bool complete()     const { return (control & uint32(complete_flag)) != 0; }
		bool allowRestart() const { return (control & uint32(inhibit_restart_flag)) == 0; }
		bool allowSplit()   const { return (control & uint32(allow_gp_flag)) != 0; }
		bool setFlag(Flag flag);
		std::atomic<int>    workReq;   // > 0: someone needs work
		std::atomic<int>    restartReq;// == numThreads_: restart
		std::atomic<uint32> control;   // set of active control flags
		std::atomic<uint32> messages;  // global message counter
		std::atomic<uint32> updates;   // global number of "update"  messages
	}                    msg_;
	ScheduleStrategy     globalR_;      // global restart strategy
	const char*          exception_;
	uint32               maxRestarts_;  // disable global restarts once reached 
	int                  numThreads_;   // number of threads including master
	uint32               nextId_;       // for generating thread ids
	uint32               intGrace_;     // grace period for clauses to integrate
	uint32               intFlags_;     // bitset controlling clause integration
	bool                 intHeuristic_; // use heuristic in clause integration
	bool                 forceGP_;	    // force guiding path mode even if portfolio is used
};


//! A per-solver (i.e. thread) class that implements message handling and knowledge integration
/*!
 * The class adds itself as a post propagator to the given solver. Each time
 * propagateFixpoint() is called (i.e. on each new decision level), it checks
 * for new lemmas to integrate and synchronizes the search with any new models.
 * Furthermore, it adds a second (high-priority) post propagator for message handling.
 */
class ParallelHandler : public PostPropagator {
public:
	//! creates a new parallel handler and attaches it to the given solver
	/*!
	 * \param ctrl The object controlling the parallel solve operation
	 * \param s    The solver in which this object is used
	 * \param p    The solving parameters under which the solver operates
	 */
	explicit ParallelHandler(ParallelSolve* ctrl, Solver& s, const SolveParams& p);

	//! detaches the connection between the message handler and its solver
	void detach(bool onlyMessageHandler = true);
	//! (re-)establishes the connection between the message handler and its solver
	void attach();
	//! completly detaches this object from its solver and deletes any unprocessed lemmas
	void release();

	const Solver&      solver() const { return *solver_; }
	const SolveParams& params() const { return *params_; }
	Solver&            solver()       { return *solver_; }


	// overridden methods
	
	//! returns a priority suited for a post propagators that is non-deterministic
	uint32 priority() const { return priority_general + 100; }

	//! integrates new information
	bool propagateFixpoint(Solver& s);
	bool propagate(Solver& s) { return ParallelHandler::propagateFixpoint(s); }
	
	//! checks whether new information has invalidated current model
	bool isModel(Solver& s);

	// own interface
	// TODO: make functions virtual once necessary 
	
	//! called before solver starts to solve given guiding path
	void prepareForGP(const LitVec& gp, bool fromSplit);

	//! returns true if handler's guiding path is disjoint from all others
	bool disjointPath() const { return gp_.split; }
	void setDisjointPath(bool b) { gp_.split = b; }

	bool splittable() const { return updateModel_ == false; }

	/*!
	 * \name Message handlers
	 * \note 
	 *   Message handlers are intended as callbacks for ParallelSolve::handleMessages().
	 *   They shall not change the assignment of the given solver object.
	 *   If a meesage handler returns false, ParallelSolve::handleMessages() is exited and
	 *   false is returned.
	 */
	//@{
	
	//! request for termination
	/*!
	 * Sets a stop conflict and calls detach() to disable all further
	 * message handling.
	 * \note always returns false
	 */
	bool handleTerminateMessage(Solver& s);

	//! request for split
	/*!
	 * Splits off a new guiding path and adds it to the control object.
	 * \pre the guiding path of this object is "splittable"
	 * \note always returns true
	 */
	bool handleSplitMessage(Solver& s);

	//! request for model update
	/*!
	 * Enqueues a model message that is processed once
	 * propagateFixpoint() is called.
	 * \note always returns true
	 */
	bool handleModelMessage(Solver& s);

	//! request for (global) restart
	/*!
	 * \return true if restart is valid, else false
	 */
	bool handleRestartMessage(Solver& s);
	//@}  
private:
	bool simplify(Solver& s, bool re);
	bool integrateClauses(Solver& s, mt::SharedLiterals** arr, uint32 num);
	void add(ClauseHead* h);
	ParallelSolve* ctrl() const { return messageHandler_.ctrl; }
	typedef LitVec::size_type size_type;
	typedef PodVector<Constraint*>::type ClauseDB;
	ClauseDB           integrated_; // my integrated clauses
	Solver*            solver_;     // my solver
	const SolveParams* params_;     // my solving params
	size_type          intTail_;    // where to put next clause
	struct GP {
		LitVec    path;     // current guiding path
		size_type pos;      // pos in trail
		uint32    impl;     // number of additional implied literals
		bool      split;    // does gp result from a split?
		void reset() {
			path.clear();
			pos  = 0;
			impl = 0;
			split=false;
		}
	} gp_;
	struct MessageHandler : PostPropagator {
		explicit MessageHandler(ParallelSolve* c) : ctrl(c) {}
		uint32 priority() const { return PostPropagator::priority_highest; }
		bool   propagateFixpoint(Solver& s) { return ctrl->handleMessages(s); }
		bool   propagate(Solver& s)         { return MessageHandler::propagateFixpoint(s); }
		ParallelSolve* ctrl; // get messages from here
	}    messageHandler_;
	bool updateModel_;
};

class GlobalQueue : public Distributor {
public:
	GlobalQueue(uint32 maxShare, uint32 typesToShare, uint32 maxLbd);
	~GlobalQueue();
	uint32  receive(const Solver& in, mt::SharedLiterals** out, uint32 maxOut);
protected:
	mt::SharedLiterals* doPublish(const Solver& source, const Literal* lits, uint32 size, const ClauseExtra& extra);
private:
	void release();
	struct ClauseNode {
		ClauseNode()
			: targetMask(0), lits(0) {}
		uint64              targetMask;
		mt::SharedLiterals* lits;
	};
	class Queue : public MultiQueue<ClauseNode> {
	public:
		typedef MultiQueue<ClauseNode> base_type;
		using base_type::publish;
		Queue(uint32 m) : base_type(m) {}
	};
	struct ThreadInfo {
		Queue::ThreadId id;
		char pad[64 - sizeof(Queue::ThreadId)];
	};
	Queue::ThreadId& getThreadId(uint32 sId) const {
		return threadId_[sId].id;
	}
	Queue*               queue_;
	ThreadInfo*          threadId_;
};

}
#endif

#endif
