// 
// Copyright (c) 2006-2011, Benjamin Kaufmann
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
#ifndef CLASP_SOLVER_TYPES_H_INCLUDED
#define CLASP_SOLVER_TYPES_H_INCLUDED
#ifdef _MSC_VER
#pragma once
#endif

#include <clasp/literal.h>
#include <clasp/constraint.h>
#include <clasp/util/left_right_sequence.h>
#include <clasp/util/misc_types.h>
#include <clasp/util/type_manip.h>

/*!
 * \file 
 * Contains some types used by a Solver
 */
namespace Clasp {
namespace mt { class   SharedLiterals; }


/*!
 * \addtogroup solver
 */
//@{

///////////////////////////////////////////////////////////////////////////////
// Count a thing or two...
///////////////////////////////////////////////////////////////////////////////
//! A struct for aggregating basic problem statistics
/*!
 * Maintained in SharedContext
 */
struct ProblemStats {
	ProblemStats() { reset(); }
	uint32  vars;
	uint32  vars_eliminated;
	uint32  vars_frozen;
	uint32  constraints;
	uint32  constraints_binary;
	uint32  constraints_ternary;
	void    reset() { std::memset(this, 0, sizeof(*this)); }
	void diff(const ProblemStats& o) {
		vars               = std::max(vars, o.vars)-std::min(vars, o.vars);
		vars_eliminated    = std::max(vars_eliminated, o.vars_eliminated)-std::min(vars_eliminated, o.vars_eliminated);
		vars_frozen        = std::max(vars_frozen, o.vars_frozen)-std::min(vars_frozen, o.vars_frozen);
		constraints        = std::max(constraints, o.constraints) - std::min(constraints, o.constraints);
		constraints_binary = std::max(constraints_binary, o.constraints_binary) - std::min(constraints_binary, o.constraints_binary);
		constraints_ternary= std::max(constraints_ternary, o.constraints_ternary) - std::min(constraints_ternary, o.constraints_ternary);
	} 
};

//! A struct for aggregating statistics relevant for parallel solving
/*!
 * Always associated with one solver (thread)
 */
struct ParallelStats {
	ParallelStats() { reset(); }
	double  cpuTime; /**< (Estimated) cpu time of the current solver */
	uint64  splits;  /**< Number of split requests handled */
	uint64  gps;     /**< Number of guiding paths received */
	uint64  gpLits;  /**< Sum of literals in received guiding paths */
	uint64  shared;  /**< Number of nogoods shared */
	bool    terminated;
	void    reset() { 
		std::memset(this, 0, sizeof(*this)); 
		cpuTime    = 0.0;
		terminated = false;
	}
	void    accu(const ParallelStats& o) {
		cpuTime += o.cpuTime;
		splits  += o.splits;
		gps     += o.gps;
		gpLits  += o.gpLits;
		shared  += o.shared;
		terminated |= o.terminated;
	}

	void newGP(LitVec::size_type length) {
		++gps;
		gpLits += length;
	}
};

//! A struct for jump statistics
struct JumpStats {
	JumpStats() { reset(); }
	void reset(){ std::memset(this, 0, sizeof(*this)); }
	void accu(const JumpStats& o) {
		jumps   += o.jumps;
		bJumps  += o.bJumps;
		jumpSum += o.jumpSum;
		boundSum+= o.boundSum;
		if (o.maxJump   > maxJump)   maxJump   = o.maxJump;
		if (o.maxJumpEx > maxJumpEx) maxJumpEx = o.maxJumpEx;
		if (o.maxBound  > maxBound)  maxBound  = o.maxBound;
	}
	void    update(uint32 dl, uint32 uipLevel, uint32 bLevel) {
		++jumps;
		jumpSum += dl - uipLevel; 
		maxJump = std::max(maxJump, dl - uipLevel);
		if (uipLevel < bLevel) {
			++bJumps;
			boundSum += bLevel - uipLevel;
			maxJumpEx = std::max(maxJumpEx, dl - bLevel);
			maxBound  = std::max(maxBound, bLevel - uipLevel);
		}
		else { maxJumpEx = maxJump; }
	}
	double avgJumpLen()   const { return jumpSum/std::max(1.0,(double)jumps); }
	double avgJumpLenEx() const { return (jumpSum-boundSum)/std::max(1.0,(double)jumps); }
	uint64  jumps;    /**< Number of backjumps (i.e. number of analyzed conflicts) */
	uint64  bJumps;   /**< Number of backjumps that were bounded */
	uint64  jumpSum;  /**< Number of levels that could be skipped w.r.t first-uip */
	uint64  boundSum; /**< Number of levels that could not be skipped because of backtrack-level*/
	uint32  maxJump;  /**< Longest possible backjump */
	uint32  maxJumpEx;/**< Longest executed backjump (< maxJump if longest jump was bounded) */
	uint32  maxBound; /**< Max difference between uip- and backtrack-level */
};

//! A struct for holding core solving statistics used by a solver
struct CoreStats {
	CoreStats() { reset(); }
	void reset(){ std::memset(this, 0, sizeof(*this)); }
	void accu(const CoreStats& o) {
		choices  += o.choices;
		conflicts+= o.conflicts;
		restarts += o.restarts;
		models   += o.models;
		
		binary   += o.binary;
		ternary  += o.ternary;
		deleted  += o.deleted;
		modLits  += o.modLits;
		for (int i = 0; i != Constraint_t::max_value; ++i) {
			learnts[i] += o.learnts[i];
			lits[i]    += o.lits[i];
		}
	}
	void addLearnt(uint32 size, ConstraintType t) {
		assert(t != Constraint_t::static_constraint && t <= Constraint_t::max_value);
		++learnts[t-1];
		lits[t-1] += size;
		binary += (size == 2);
		ternary+= (size == 3);
	}
	void removeLearnt(uint32 size, ConstraintType t) {
		assert(t != Constraint_t::static_constraint && t <= Constraint_t::max_value);
		--learnts[t-1];
		lits[t-1] -= size;
		binary -= (size == 2);
		ternary-= (size == 3);
	}
	void addModel(uint32 size) {
		++models;
		modLits += size;
	}
	void removeModel(uint32 size) {
		--models;
		modLits -= size;
	}
	uint64 choices;   /**< Number of choices performed */
	uint64 conflicts; /**< Number of conflicts found */
	uint64 restarts;  /**< Number of restarts */ 
	uint64 models;    /**< Number of models found */

	uint64 learnts[Constraint_t::max_value]; /**< Number of learnt nogoods of type t-1 */
	uint64 lits[Constraint_t::max_value];    /**< Sum of literals in nogoods of type t-1 */
	uint64 binary;    /**< Number of learnt binary nogoods */
	uint64 ternary;   /**< Number of learnt ternary nogoods*/
	uint64 deleted;   /**< Sum of learnt nogoods removed */
	uint64 modLits;   /**< Sum of decision literals in models */
};

//! A struct for aggregating statistics of one solve operation
struct SolveStats : public CoreStats {
	SolveStats() : jumps(0), parallel(0) { }
	SolveStats(const SolveStats& o) : CoreStats(o), jumps(0), parallel(0) { 
		if (o.jumps)    jumps    = new JumpStats(*o.jumps); 
		if (o.parallel) parallel = new ParallelStats(*o.parallel);
	}
	~SolveStats() { delete jumps; delete parallel; }
	void enableJumpStats()    { if (!jumps)   jumps    = new JumpStats();   }
	void enableParallelStats(){ if (!parallel)parallel = new ParallelStats(); }
	void reset() {  
		CoreStats::reset();
		if (jumps)   jumps->reset();
		if (parallel)parallel->reset();
	}
	void accu(const SolveStats& o) {
		CoreStats::accu(o);
		if (jumps && o.jumps) jumps->accu(*o.jumps);
		if (parallel && o.parallel) parallel->accu(*o.parallel);
	}
	void updateJumps(uint32 dl, uint32 uipLevel, uint32 bLevel) {
		if (!jumps) return;
		jumps->update(dl, uipLevel, bLevel);
	}
	JumpStats*     jumps;    /**< optional jump statistics */
	ParallelStats* parallel; /**< optional parallel statistics */
private:
	SolveStats& operator=(const SolveStats&);
};
///////////////////////////////////////////////////////////////////////////////

//! Type for passing additional clause information 
class ClauseExtra {
public:
	enum { MAX_LBD = (1<<7)-1, MAX_ACTIVITY = (1<<15)-1 }; 
	ClauseExtra() 
		: act_(0), lbd_(MAX_LBD), rootLbd_(MAX_LBD), type_(0), tag_(0) {}
	ConstraintType type()     const { return static_cast<ConstraintType>(type_); }
	uint32         activity() const { return static_cast<uint32>(act_); }
	uint32         lbd()      const { return static_cast<uint32>(lbd_); }
	uint32         rootLbd()  const { return static_cast<uint32>(rootLbd_); }
	bool           tagged()   const { return tag_ != 0; }
	ClauseExtra& setType(ConstraintType t) { type_ = static_cast<uint32>(t); return *this; }
	ClauseExtra& setActivity(uint32 act)   {
		if (act > MAX_ACTIVITY) act = MAX_ACTIVITY;
		act_ = act;
		return *this;
	}
	ClauseExtra& setLbd(uint32 a_lbd, uint32 a_rootLbd) {
		assert(a_lbd >= a_rootLbd);
		if (a_lbd > static_cast<uint32>(MAX_LBD)) {
			a_lbd    = static_cast<uint32>(MAX_LBD);
			a_rootLbd= std::min(a_lbd, a_rootLbd);
		}
		lbd_     = a_lbd;
		rootLbd_ = a_rootLbd;
		return *this;
	}
	
	ClauseExtra& tag() { tag_ = 1; return *this; }
private:
	uint32 act_     : 15; // Initial clause activity
	uint32 lbd_     :  7; // Literal block distance in the range [0, MAX_LBD]
	uint32 rootLbd_ :  7; // LBD w.r.t to current root level ([0, MAX_LBD])
	uint32 type_    :  2; // Type of clause
	uint32 tag_     :  1; // conditional clause?
};

//! (Abstract) base class for clause types
/*!
 * ClauseHead is used to enforce a common memory-layout for all clauses.
 * It contains the two watched literals and a cache literal to improve
 * propagation performance. A virtual call to Constraint::propagate()
 * is only needed if the other watch is not true and the cache literal
 * is false.
 */
class ClauseHead : public LearntConstraint {
public:
	enum { HEAD_LITS = 3, MAX_LBD = (1<<5)-1, TAGGED_CLAUSE = 1023};
	explicit ClauseHead(const ClauseExtra& init);
	// base interface
	//! propagates the head and calls propagateTail() if necessary
	PropResult propagate(Solver& s, Literal, uint32& data);
	//! type of clause
	ConstraintType type() const    { return ConstraintType(extra_.data.type); }
	//! true if this clause currently is the antecedent of an assignment
	bool     locked(const Solver& s) const;
	//! returns the activity of this clause
	Activity activity() const       { return makeActivity(extra_.data.act, extra_.data.lbd); }
	//! halves the activity of this clause
	void     decreaseActivity()     { extra_.data.act >>= 1; }
	//! downcast from LearntConstraint
	ClauseHead* clause()           { return this; }
	
	// clause interface
	typedef std::pair<bool, bool> BoolPair;
	//! increase activity
	void bumpActivity()     { extra_.data.act += (extra_.data.act != ClauseExtra::MAX_ACTIVITY); }
	//! adds watches for first two literals in head to solver
	void attach(Solver& s);
	//! returns true if head is satisfied w.r.t current assignment in s
	bool satisfied(const Solver& s);
	//! conditional clause?
	bool tagged() const     { return extra_.data.key == uint32(TAGGED_CLAUSE); }
	uint32 lbd()  const     { return extra_.data.lbd; }
	void setLbd(uint32 lbd) { extra_.data.lbd = std::min(lbd, (uint32)MAX_LBD); }
	
	//! removes watches from s
	virtual void     detach(Solver& s);
	//! returns the size of this clause
	virtual uint32   size()              const = 0;
	//! returns the literals of this clause in out
	virtual void     toLits(LitVec& out) const = 0;
	//! returns true if this clause is a valid "reverse antecedent" for p
	virtual bool     isReverseReason(const Solver& s, Literal p, uint32 maxL, uint32 maxN) = 0;
	//! removes p from clause if possible
	/*!
	 * \return
	 *   The first component of the returned pair specifies whether or not
	 *   p was removed from the clause.
	 *   The second component of the returned pair specifies whether
	 *   the clause should be kept (false) or removed (true). 
	 */
	virtual BoolPair strengthen(Solver& s, Literal p, bool allowToShort = true) = 0;
protected:
	friend struct ClauseWatch;
	bool               toImplication(Solver& s);
	void               clearTagged(){ extra_.data.key = 0; }
	//! propagates the tail part of the clause
	/*!
	 * \pre head_[pos] == ~p && head_[pos^1] is the other watched literal
	 */
	virtual PropResult propagateTail(Solver& s, Literal p, uint32 pos) = 0;
	union Data {
		uint32              extra[2];
		mt::SharedLiterals* shared;
	}       data_;
	union Extra { 
		Extra() : rep(0) {}
		struct {
			uint32 act : 15; // activity of clause
			uint32 key : 10; // lru key of clause
			uint32 lbd :  5; // lbd of clause
			uint32 type:  2; // type of clause
		}      data;
		uint32 rep;
	}       extra_;
	Literal head_[HEAD_LITS]; // two watched literals and one cache literal
};
///////////////////////////////////////////////////////////////////////////////
// Watches
///////////////////////////////////////////////////////////////////////////////
//! Represents a clause watch in a Solver.
struct ClauseWatch {
	//! clause watch: clause head
	explicit ClauseWatch(ClauseHead* a_head) : head(a_head) { }
	ClauseHead* head;
	struct EqHead {
		explicit EqHead(ClauseHead* h) : head(h) {}
		bool operator()(const ClauseWatch& w) const { return head == w.head; }
		ClauseHead* head;
	};
};

//! Represents a generic watch in a Solver.
struct GenericWatch {
	//! a constraint and some associated data
	explicit GenericWatch(Constraint* a_con, uint32 a_data = 0) : con(a_con), data(a_data) {}
	//! calls propagate on the stored constraint and passes the stored data to that constraint.
	Constraint::PropResult propagate(Solver& s, Literal p) { return con->propagate(s, p, data); }
	
	Constraint* con;    /**< The constraint watching a certain literal */
	uint32      data;   /**< Additional data associated with this watch - passed to constraint on update */

	struct EqConstraint {
		explicit EqConstraint(Constraint* c) : con(c) {}
		bool operator()(const GenericWatch& w) const { return con == w.con; }
		Constraint* con;
	};	
};

#ifndef DISABLE_MULTI_THREADING
typedef bk_lib::left_right_sequence<Literal, std::pair<Literal,Literal>, 64-sizeof(std::atomic<void*>)> ImplListBase;
#else
typedef bk_lib::left_right_sequence<Literal, std::pair<Literal,Literal>, 64> ImplListBase;
#endif

//! A list of implications resulting from binary and ternary clauses
class ImplicationList : public ImplListBase {
public:
	typedef ImplListBase          base_type;
	typedef base_type::left_type  left_type;
	typedef base_type::right_type right_type;
	typedef base_type::size_type  size_type;
	typedef base_type::align_type align_type;
	typedef base_type::max_type   max_type;
	typedef base_type::buf_type   buf_type;

	typedef base_type::left_iterator       left_iterator;
	typedef base_type::const_left_iterator const_left_iterator;
	typedef base_type::right_iterator       right_iterator;
	typedef base_type::const_right_iterator const_right_iterator;

	ImplicationList() : base_type() {
		setLearnt(0);
	}
	ImplicationList(const ImplicationList& other);
	~ImplicationList();
	ImplicationList& operator=(const ImplicationList&);

	bool empty() const { return base_type::empty() && learnt() == 0; }
	//! clear list and optionally release memory
	void clear(bool releaseMem);
	
	//! does the list contain learnt implications?
	bool hasLearnt() const { return learnt() != 0; }
	
	//! does the list contain the implication p resp. (p, q)?
	bool hasLearntImplication(Literal p, Literal q = negLit(0)) const;

	//! add the learnt implication p resp. (p, q)
	void addLearnt(Literal p, Literal q = negLit(0));
	
	//! propagate this list of implications
	/*!
	 * \pre p is true and this list stores the implications for p
	 */
	bool propagate(Solver& s, Literal p) const;

	Antecedent getReverseReason(Solver& s, uint32 maxLev) const;
private:
	struct Block {
		typedef std::atomic<Block*> atomic_block_ptr;
		typedef std::atomic<uint32> atomic_size;
		enum { block_cap = (64 - (sizeof(atomic_size)+sizeof(atomic_block_ptr)))/sizeof(Literal) };
		explicit Block() {
			for (int i = 0; i != block_cap; ++i) { data[i] = posLit(0); }
			size = 0;
			next = 0;
		}
		void add(const Literal* x, uint32 size);
		atomic_block_ptr next;
		atomic_size      size;
		Literal          data[block_cap];
	};
	void copy(Block* b);
	void publish(Block* b) {
		b->next = learnt();
		setLearnt(b);
	}
#ifndef DISABLE_MULTI_THREADING
	void setLearnt(Block* b) { learnt_ = b; }
	Block* learnt() const    { return learnt_; }
	Block::atomic_block_ptr learnt_;
#else
	void   setLearnt(Block*) { }
	Block* learnt() const    { return 0; }
#endif
};

//! Min-size-clause watch list type
typedef ImplicationList SWL;

//! Watch list type
typedef bk_lib::left_right_sequence<ClauseWatch, GenericWatch, 0> WatchList;

inline void remove_bin(SWL& w, Literal p) {
	w.erase_left_unordered(std::find(w.left_begin(), w.left_end(), p));
	w.try_shrink();
}
inline void remove_tern(SWL& w, Literal p) {
	w.erase_right_unordered(std::find_if(w.right_begin(), w.right_end(), PairContains<Literal>(p)));
	w.try_shrink();
}

inline void releaseVec(SWL& w)       { w.clear(true); }
inline void releaseVec(WatchList& w) { w.clear(true); }


//! Base class for distributing learnt knowledge between solvers
class Distributor {
public:
	Distributor(uint32 maxShare, uint32 typesToShare, uint32 maxLbd);
	virtual ~Distributor();
	void                publishShort(const Solver& source, ConstraintType t, Literal p, Literal q = negLit(0), Literal r = negLit(0));
	mt::SharedLiterals* publish(const Solver& source, const Literal* lits, uint32 size, const ClauseExtra& extra);
	virtual uint32      receive(const Solver& in, mt::SharedLiterals** out, uint32 maxOut) = 0;
protected:
	virtual mt::SharedLiterals* doPublish(const Solver& source, const Literal* lits, uint32 size, const ClauseExtra& extra) = 0;
private:
	Distributor(const Distributor&);
	Distributor& operator=(const Distributor&);
	uint32 maxShare_;
	uint32 lbdMax_    : 16;
	uint32 typeMask_  : 16;
};

//! Allocator for small (at most 32-byte) clauses
class SmallClauseAlloc {
public:
	SmallClauseAlloc();
	~SmallClauseAlloc();
	void* allocate() {
		if(freeList_ == 0) {
			allocBlock();
		}
		Chunk* r   = freeList_;
		freeList_  = r->next;
		return r;
	}
	void   free(void* mem) {
		Chunk* b = reinterpret_cast<Chunk*>(mem);
		b->next  = freeList_;
		freeList_= b;
	}
private:
	SmallClauseAlloc(const SmallClauseAlloc&);
	SmallClauseAlloc& operator=(const SmallClauseAlloc&);
	struct Chunk {
		Chunk*        next; // enforce ptr alignment
		unsigned char mem[32 - sizeof(Chunk*)];
	};
	struct Block {
		enum { num_chunks = 1023 };
		Block* next;
		unsigned char pad[32-sizeof(Block*)];
		Chunk  chunk[num_chunks];
	};
	void allocBlock();
	Block*  blocks_;
	Chunk*  freeList_;
};

///////////////////////////////////////////////////////////////////////////////

//! Stores static information about variables
class VarInfo {
public:
	enum FLAGS {
		RESERVED_1 = 0x1u, // reserved for future
		RESERVED_2 = 0x2u, // use
		NANT   = 0x4u, // if this var is an atom, is it in NAnt(P)
		PROJECT= 0x8u, // do we project on this var?
		BODY   = 0x10u,// is this var representing a body?
		EQ     = 0x20u,// is the var representing both a body and an atom?
		ELIM   = 0x40u,// is the variable eliminated?
		FROZEN = 0x80u // is the variable frozen?
	};
	VarInfo() {}
	void  reserve(uint32 maxSize) { info_.reserve(maxSize); }
	void  add(bool body) {
		uint8 m = (!body?0:flag(BODY));
		info_.push_back( m );
	}
	bool      empty()                const { return info_.empty(); }
	uint32    numVars()              const { return (uint32)info_.size(); }
	bool      isSet(Var v, FLAGS f)  const { return (info_[v] & flag(f)) != 0; }
	void      toggle(Var v, FLAGS f)       { info_[v] ^= flag(f); }
	void      clear() { info_.clear(); }
private:
	// Bit:   7     6   5   4    3    2   1     0
	//      frozen elim eq body proj nant reserved
	typedef PodVector<uint8>::type InfoVec;
	static uint8 flag(FLAGS x) { return uint8(x); }
	
	VarInfo(const VarInfo&);
	VarInfo& operator=(const VarInfo&);
	InfoVec info_;
};

//! Type for storing reasons for variable assignments together with additional data
/*!
 * \note On 32-bit systems additional data is stored in the high-word of antecedents 
 */
struct ReasonStore32 : PodVector<Antecedent>::type {
	uint32  dataSize() const     { return (uint32)size(); }
	void    dataResize(uint32)   {}
	uint32  data(uint32 v) const { return static_cast<uint32>((*this)[v].asUint()>>32);}
	void    setData(uint32 v, uint32 data) { encode((*this)[v], data); }
	static  void encode(Antecedent& a, uint32 data) {
		a.asUint() = (uint64(data)<<32) | static_cast<uint32>(a.asUint());
	}
	struct value_type {
		value_type(const Antecedent& a, uint32 d) : ante_(a) {
			if (d != UINT32_MAX) { encode(ante_, d); }
		}
		const Antecedent& ante() const { return ante_;      }
		      uint32      data() const { return UINT32_MAX; }
		Antecedent ante_;
	};
};

//! Type for storing reasons for variable assignments together with additional data
/*
 * \note On 64-bit systems additional data is stored in a separate container
 *       whose size must be manually set.
 */
struct ReasonStore64 : PodVector<Antecedent>::type {
	uint32  dataSize() const      { return (uint32)data_.size(); }
	void    dataResize(uint32 nv) { if (nv > dataSize()) data_.resize(nv, UINT32_MAX); }
	uint32  data(uint32 v) const  { return data_[v]; }
	void    setData(uint32 v, uint32 data) { data_[v] = data; }
	VarVec data_;
	struct value_type : std::pair<Antecedent, uint32> {
		value_type(const Antecedent& a, uint32 d) : std::pair<Antecedent, uint32>(a, d) {}
		const Antecedent& ante() const { return first;  }
		      uint32      data() const { return second; }
	};
};

//! Stores assignment related information.
/*!
 * For each variable v, the class stores 
 *  - v's current value (value_free if unassigned)
 *  - the decision level on which v was assign (only valid if value(v) != value_free)
 *  - the reason why v is in the assignment (only valid if value(v) != value_free)
 *  - (optionally) some additional data associated with the reason
 *  .
 * Furthermore, the class stores the sequences of assignments as a set of
 * true literals in its trail-member.
 */
class Assignment  {
public:
	typedef PodVector<uint32>::type     AssignVec;
	typedef PodVector<uint8>::type      SavedVec;
	typedef bk_lib::detail::if_then_else<
		sizeof(Constraint*)==sizeof(uint64)
		, ReasonStore64
		, ReasonStore32>::type            ReasonVec;
	typedef ReasonVec::value_type       ReasonWithData;
	Assignment() : front(0), eliminated_(0) { }
	LitVec            trail;   // assignment sequence
	LitVec::size_type front;   // "propagation queue"
	bool              qEmpty() const { return front == trail.size(); }
	uint32            qSize()  const { return (uint32)trail.size() - front; }
	Literal           qPop()         { return trail[front++]; }
	void              qReset()       { front  = trail.size(); }

	//! number of variables in the three-valued assignment
	uint32            numVars()    const { return (uint32)assign_.size(); }
	//! number of assigned variables
	uint32            assigned()   const { return (uint32)trail.size();   }
	//! number of free variables
	uint32            free()       const { return numVars() - (assigned()+eliminated_);   }
	//! returns the largest possible decision level
	uint32            maxLevel()   const { return (1u<<28)-1; }
	//! returns v's value in the three-valued assignment
	ValueRep          value(Var v) const { return ValueRep(assign_[v] & 3u); }
	//! returns v's previously saved value in the three-valued assignment
	ValueRep          saved(Var v) const { return v < saved_.size() ? saved_[v] : value_free; }
	//! returns the decision level on which v was assigned if value(v) != value_free
	uint32            level(Var v) const { return assign_[v] >> 4u; }
	//! returns the reason for v being assigned if value(v) != value_free
	const Antecedent& reason(Var v)const { return reason_[v]; }
	//! returns the number of allocated data slots
	uint32            numData()    const { return reason_.dataSize(); }
	//! returns the reason data associated with v
	uint32            data(Var v)  const { assert(v < reason_.dataSize()); return reason_.data(v); }

	//! resize to nv variables
	void resize(uint32 nv) {
		assign_.resize(nv);
		reason_.resize(nv);
	}
	//! adds var to assignment - initially the new var is unassigned
	Var addVar() {
		assign_.push_back(0);
		reason_.push_back(0);
		return numVars()-1;
	}
	//! allocates data slots for nv variables to be used for storing additional reason data
	void requestData(uint32 nv) {
		reason_.dataResize(nv);
	}
	//! eliminate var from assignment
	void eliminate(Var v) {
		assert(value(v) == value_free && "Can not eliminate assigned var!\n");
		setValue(v, value_true);
		++eliminated_;
	}

	//! assigns p.var() on level lev to the value that makes p true and store x as reason for the assignment
	/*!
	 * \return true if the assignment is consistent. False, otherwise.
	 * \post if true is returned, p is in trail. Otherwise, ~p is.
	 */
	bool assign(Literal p, uint32 lev, const Antecedent& x) {
		const Var      v   = p.var();
		const ValueRep val = value(v);
		if (val == value_free) {
			assign_[v] = (lev<<4) + trueValue(p);
			reason_[v] = x;
			trail.push_back(p);
			return true;
		}
		return val == trueValue(p);
	}
	bool assign(Literal p, uint32 lev, Constraint* c, uint32 data) {
		const Var      v   = p.var();
		const ValueRep val = value(v);
		if (val == value_free) {
			assign_[v] = (lev<<4) + trueValue(p);
			reason_[v] = c;
			reason_.setData(v, data);
			trail.push_back(p);
			return true;
		}
		return val == trueValue(p);
	}
	//! undos all assignments in the range trail[first, last).
	/*!
	 * \param first first assignment to be undone
	 * \param save  if true, previous assignment of a var is saved before it is undone
	 */
	void undoTrail(LitVec::size_type first, bool save) {
		if (!save) { popUntil<&Assignment::clearValue>(trail[first]); }
		else       { saved_.resize(numVars(), 0); popUntil<&Assignment::saveAndClear>(trail[first]); }
		front  = trail.size();
	}
	//! undos the last assignment
	void undoLast() { clearValue(trail.back().var()); trail.pop_back(); }
	//! returns the last assignment as a true literal
	Literal last() const { return trail.back(); }
	Literal&last()       { return trail.back(); }
	//! sets val as "previous value" of v
	void setSavedValue(Var v, ValueRep val) {
		if (saved_.size() <= v) saved_.resize(v+1, 0);
		saved_[v] = val;
	}
	/*!
	 * \name implementation functions
	 * Low-level implementation functions. Use with care and only if you
	 * know what you are doing!
	 */
	//@{
	bool seen(Var v, uint8 m) const { return (assign_[v] & (m<<2)) != 0; }
	void setSeen(Var v, uint8 m)    { assign_[v] |= (m<<2); }
	void clearSeen(Var v)           { assign_[v] &= ~uint32(12); }
	void clearValue(Var v)          { assign_[v] = 0; }
	void setValue(Var v, ValueRep val) {
		assert(value(v) == val || value(v) == value_free);
		assign_[v] = val;
	}
	void setReason(Var v, const Antecedent& a) { reason_[v] = a;  }
	void setData(Var v, uint32 data) { reason_.setData(v, data); }
	void copyAssignment(Assignment& o) const { o.assign_ = assign_; }
	//@}
private:
	Assignment(const Assignment&);
	Assignment& operator=(const Assignment&);
	void    saveAndClear(Var v) { saved_[v] = value(v); clearValue(v); }
	template <void (Assignment::*op)(Var v)>
	void popUntil(Literal stop) {
		Literal p;
		do {
			p = trail.back(); trail.pop_back();
			(this->*op)(p.var());
		} while (p != stop);
	}
	AssignVec assign_; // for each var: three-valued assignment
	ReasonVec reason_; // for each var: reason for being assigned (+ optional data)
	SavedVec  saved_;  // for each var: previous assignment
	uint32    eliminated_;
};

//! Stores information about a literal that is implied on an earlier level than the current decision level.
struct ImpliedLiteral {
	typedef Assignment::ReasonWithData AnteInfo;
	ImpliedLiteral(Literal a_lit, uint32 a_level, const Antecedent& a_ante, uint32 a_data = UINT32_MAX) 
		: lit(a_lit)
		, level(a_level)
		, ante(a_ante, a_data) {
	}
	Literal     lit;    /**< The implied literal */
	uint32      level;  /**< The earliest decision level on which lit is implied */
	AnteInfo    ante;   /**< The reason why lit is implied on decision-level level */
};

struct CCMinRecursive {
	enum State { state_open = 0, state_poison = 1, state_removable = 2 };
	void  init(uint32 numV) { extra.resize(numV,0); }
	State state(Literal p) const { return State(extra[p.var()]); }
	bool  checkRecursive(Literal p) {
		if (state(p) == state_open) { p.clearWatch(); dfsStack.push_back(p); }
		return state(p) != state_poison;
	}
	void  markVisited(Literal p, State st) {
		if (state(p) == state_open) {
			visited.push_back(p.var());
		}
		extra[p.var()] = static_cast<uint8>(st);
	}
	void clear() {
		for (; !visited.empty(); visited.pop_back()) {
			extra[visited.back()] = 0;
		}
	}
	typedef PodVector<uint8>::type DfsState;
	LitVec   dfsStack;
	VarVec   visited;
	DfsState extra;
};
	
class SharedContext;
class Enumerator;

//! Base class for preprocessors working on clauses only
class SatPreprocessor {
public:
	SatPreprocessor() : ctx_(0) {}
	virtual ~SatPreprocessor();
	void setContext(SharedContext& ctx) { ctx_ = &ctx; }
	virtual bool addClause(const LitVec& cl) = 0;
	virtual bool preprocess(bool enumerateModels) = 0;
	virtual void extendModel(Assignment& m, LitVec& open) = 0;
	virtual bool limit(uint32 numCons) const = 0;
	struct Stats {
		Stats() : clRemoved(0), clAdded(0), litsRemoved(0) {}
		uint32 clRemoved;
		uint32 clAdded;
		uint32 litsRemoved;
	} stats;
protected:
	void reportProgress(char t, uint32 min, uint32 max);
	SharedContext*  ctx_;
private:
	SatPreprocessor(const SatPreprocessor&);
	SatPreprocessor& operator=(const SatPreprocessor&);
};

//! Aggregates information to be shared between solver objects
/*!
 * Among other things, SharedContext objects store 
 * static information on variables, the (possibly unused) 
 * symbol table, as well as the binary and ternary 
 * implication graph of the input problem.
 * 
 * Although objects of this class can be shared between solvers,
 * initialization shall be done non-concurrently by a single
 * distinguished solver (aka the master). 
 *
 * Once initialization is completed, other solvers s can 
 * attach to this object by calling ctx->attach(s).
 */
class SharedContext {
public:
	typedef std::auto_ptr<SatPreprocessor> SatPrepro;
	typedef PodVector<SWL>::type           ShortClauseImplications;
	typedef ProblemStats                   Stats;
	typedef LitVec::size_type              size_type;
	
	enum InitMode { init_share_symbols };
	
	//! creates a new object for sharing variables and the binary and ternary implication graph.
	SharedContext();
	//! creates a new object that shares its symbol table with rhs
	SharedContext(const SharedContext& rhs,  InitMode m);
	
	~SharedContext();
	
	//! enables sharing of initial problem constraints
	/*!
	 * If this function is not called, problem constraints are
	 * cloned whenever a solver attaches to this object. Otherwise,
	 * they are shared.
	 */
	void enableConstraintSharing() {  shareConstr_ = true; }

	//! enables sharing of learnt constraints
	/*!
	 * If this function is not called, learnt constraints are
	 * not shared between different solvers. Otherwise,
	 * sharing is possible and controlled by a distribution 
	 * strategy.
	 */
	void enableLearntSharing(Distributor* d) { 
		distributor_.reset(d); 
	}

	//! resets this object to the state after default construction
	void reset();
	
	//! returns true if var represents a valid variable in this object
	/*!
	 * \note The range of valid variables is [1..numVars()]. The variable 0
	 * is a special sentinel variable. 
	 */
	bool validVar(Var var) const { return var <= numVars(); }

	//! returns the number of problem variables.
	/*!
	 * \note The special sentinel-var 0 is not counted, i.e. numVars() returns
	 * the number of problem-variables.
	 * To iterate over all problem variables use a loop like:
	 * \code
	 * for (Var i = 1; i <= numVars(); ++i) {...}
	 * \endcode
	 */
	uint32 numVars() const { return varInfo_.numVars() - 1; }

	//! returns the number of eliminated vars
	uint32 numEliminatedVars()const { return problem_.vars_eliminated; }

	//! reserve space for at least varGuess variables 
	/*!
	 * \param varGuess number of vars to reserve space for
	 * \note if the number of variables is known upfront, passing the correct value
	 * for varGuess avoids repeated regrowing of the state data structures
	 */
	void reserveVars(uint32 varGuess);

	//! adds a new variable of type t.
	/*!
	 * \param t  type of the new variable (either Var_t::atom_var or Var_t::body_var)
	 * \param eq true if var represents both an atom and a body. In that case
	 *           t is the variable's primary type and determines the preferred literal.
	 * \return The index of the new variable
	 * \note The problem variables are numbered from 1 onwards!
	 */
	Var addVar(VarType t, bool eq = false);

	//! requests a special tag literal for tagging conditional knowledge
	/*!
	 * Once a tag literal p is set, newly learnt clauses containing ~p are
	 * tagged as "conditional". Conditional clauses can be removed from a solver
	 * by calling Solver::removeConditional(). Furthermore, calling 
	 * Solver::strengthenConditional() removes ~p from conditional clauses and
	 * transforms them to unconditional knowledge.
	 *
	 * \note Typically, the tag literal is an initial assumption and hence true during 
	 *       the whole search. 
	 */
	void    requestTagLiteral();
	Literal tagLiteral() const   { return tag_; }
	void    removeTagLiteral();

	//! request additional reason data slot for variable v
	void    requestData(Var v);

	//! returns the type of variable v.
	/*!
	 * If v was added with parameter eq=true, the return value
	 * is Var_t::atom_body_var.
	 */
	VarType type(Var v) const {
		assert(validVar(v));
		return varInfo_.isSet(v, VarInfo::EQ)
			? Var_t::atom_body_var
			: VarType(Var_t::atom_var + varInfo_.isSet(v, VarInfo::BODY));
	}

	//! returns the preferred decision literal of variable v w.r.t its type
	/*!
	 * \return 
	 *  - posLit(v) if type(v) == body_var
	 *  - negLit(v) if type(v) == atom_var
	 * \note if type(v) is atom_body_var, the preferred literal is determined
	 *       by v's primary type, i.e. the one that was initially passed to addVar().
	 */
	Literal preferredLiteralByType(Var v) const {
		assert(validVar(v));
		return Literal(v, !varInfo_.isSet(v, VarInfo::BODY));
	}

	//! returns true if v is currently eliminated, i.e. no longer part of the problem
	bool eliminated(Var v)  const     { assert(validVar(v)); return varInfo_.isSet(v, VarInfo::ELIM); }
	//! returns true if v is excluded from variable elimination
	bool frozen(Var v)      const     { assert(validVar(v)); return varInfo_.isSet(v, VarInfo::FROZEN); }
	//! returns true if v is a projection variable
	bool project(Var v)     const     { assert(validVar(v)); return varInfo_.isSet(v, VarInfo::PROJECT);}
	//! returns true if v is contained in a negative loop or head of a choice rule
	bool nant(Var v)        const     { assert(validVar(v)); return varInfo_.isSet(v, VarInfo::NANT);}
	
	//! freezes/defreezes a variable (a frozen var is exempt from SatELite preprocessing)
	void setFrozen(Var v, bool b);
	void setProject(Var v, bool b)    { assert(validVar(v)); if (b != varInfo_.isSet(v, VarInfo::PROJECT)) varInfo_.toggle(v, VarInfo::PROJECT); }
	void setNant(Var v, bool b)       { assert(validVar(v)); if (b != varInfo_.isSet(v, VarInfo::NANT))    varInfo_.toggle(v, VarInfo::NANT);    }
	/*!
	 * \name problem specification
	 * Functions for adding a problem to the master solver.
	 * Problem specification is a four-stage process:
	 * - first, add variables to the SharedContext object 
	 * - second, call startAddConstraints() passing the master solver
	 * - third, add problem constraints
	 * - finally, endInit() shall be called to finished the initialization process
	 * .
	 * \note After endInit() was called, only learnt constraints may be added to the solver.
	 * \note In incremental setting, the process must be repeated for each incremental step.
	 * 
	 * \note Problem specification is *not* thread-safe, i.e. during initialization no other thread shall
	 * access the context.
	 *
	 * \note unique() is a precondition for all functions in this group!
	 */
	//@{

	bool unique() const   { return shareCount_ <= 1; } 

	//! starts initialization phase
	/*!
	 * Must be called once before constraints can be added.
	 */
	void startAddConstraints(Solver& master, uint32 constraintGuess = 100);

	//! returns the number of problem constraints
	uint32 numConstraints()   const;

	//! eliminates the variable v
	/*!
	 * \pre v must not occur in any constraint 
	 *  and frozen(v) == false and value(v) == value_free
	 */
	void eliminate(Var v);

	//! adds the constraint c to the master solver
	/*!
	 * \pre endInit() was not called.
	 */
	void add(Constraint* c);

	//! adds the unary constraint p to the master solver.
	/*!
	 * \note unary constraints are immediately asserted.
	 * \return false if asserting p leads to a conflict.
	 */
	bool addUnary(Literal p);

	//! adds the binary constraint (p, q) to the shared implication graph
	void addBinary(Literal p, Literal q) {
		assert(unique() && "Modifying shared object is not allowed!");
		++numBin_;
		btig_[(~p).index()].push_left(q);
		btig_[(~q).index()].push_left(p);
	}
	
	//! adds the ternary constraint (p, q, r) to the shared implication graph
	void addTernary(Literal p, Literal q, Literal r) {
		assert(unique() && "Modifying shared object is not allowed!");
		++numTern_;
		btig_[(~p).index()].push_right(std::make_pair(q, r));
		btig_[(~q).index()].push_right(std::make_pair(p, r));
		btig_[(~r).index()].push_right(std::make_pair(p, q));
	}

	//! adds p as post propagator to the master solver
	/*!
	 * \pre p was not added previously and is not part of any other solver
	 * \note post propagators are stored in priority order
	 * \see PostPropagator::priority()
	 */
	void addPost(PostPropagator* p);

	//! attaches the given enumerator to this object
	/*!
	 * \note ownership is transferred
	 * \note In incremental setting, the enumerator must be reattached in
	 *       each incremental step by calling addEnumerator(enumerator());
	 */
	void        addEnumerator(Enumerator* en);
	Enumerator* enumerator() const { return enumerator_.get(); }

	//! finishes initialization of the master solver
	/*!
	 * endInit must be called once before search is started. After endInit()
	 * was called, a number (shareCount-1) of other solvers can be attached to the 
	 * shared context and learnt constraints may be added to solver.
	 * \return 
	 *  - false if the constraints are initially conflicting. True otherwise.
	 * \note
	 * The master solver can't recover from top-level conflicts, i.e. if endInit()
	 * returned false, the solver is in an unusable state.
	 */
	bool endInit(uint32 shareCount = 1);

	//! attaches s to this object
	/*!
	 * \pre other != master()
	 * \note It is safe to attach multiple solvers concurrently
	 * but the master solver shall not change during the whole
	 * operation.
	 */
	bool attach(Solver& other);

	//! detaches s from this object
	/*!
	 * The function removes any enumeration related constraints from s.
	 * Shall be called once after search has stopped.
	 * \note The function is concurrency-safe w.r.t to different solver objects, 
	 *       i.e. in a parallel search different solvers may call detach()
	 *       concurrently.
	 */
	void detach(Solver& s);

	//! estimates the problem complexity
	/*!
	 * \return sum of c->estimateComplexity(*master()) for each problem 
	 *         constraint c.
	 */
	uint32 problemComplexity() const;

	//! size of top-level after last call to endInit()
	size_type topLevelSize() const { return lastTopLevel_; }
	//@}

	/*!
	 * \name learning
	 * Functions for distributing knowledge
	 * 
	 * \note The functions in this group can be safely called 
	 * from multiple threads.
	 */
	//@{

	//! learns the binary clause (p, q)
	/*!
	 * \note 
	 *   The binary clause (p, q) is stored in a shared data-structure but
	 *   threads are not informed about the new clause.
	 *   It is the caller's responsibility to distribute the new information.
	 */
	bool learnBinary(Literal p, Literal q);
	
	//! learns the ternary clause (p, q, r)
	/*!
	 * \note 
	 *   The ternary clause (p, q, r) is stored in a shared data-structure but
	 *   threads are not informed about the new clause.
	 *   It is the caller's responsibility to distribute the new information.
	 */
	bool learnTernary(Literal p, Literal q, Literal r);
	
	//! distributes the clause in lits to other threads
	/*!
	 * The function first calls the distribution strategy 
	 * to decides whether the clause is a good candidate for distribution.
	 * If so, it distributes the clause and returns a handle to the
	 * now shared literals of the clause. Otherwise, it returns 0.
	 *
	 * \param owner The solver that created the clause.
	 * \param lits  The literals of the clause.
	 * \param size  The number of literals in the clause
	 * \param extra Additional information about the clause
	 * \note 
	 *   If the return value is not null, it is the caller's 
	 *   responsibility to release the returned handle (i.e. by calling release()).
	 */
	mt::SharedLiterals* distribute(const Solver& owner, const Literal* lits, uint32 size, const ClauseExtra& extra) const;
	void                distributeShared(const Solver& owner, Literal p, Literal q, Literal r, ConstraintType type) const;

	//! tries to receive at most maxOut clauses
	/*!
	 * The function queries the distribution object for new clauses to be delivered to
	 * the solver target. Clauses are stored in out.
	 * \return the number of clauses received
	 */
	uint32 receive(const Solver& target, mt::SharedLiterals** out, uint32 maxOut) const;

	//! returns the number of learnt binary and ternary clauses
	uint32 numLearntShort() const { return learntBin_ + learntTern_; }

	//@}

	bool         shareConstraints() const { return shareConstr_; }
	const Stats& stats()     const   { return problem_; }
	uint32       numBinary() const   { return numBin_; }
	uint32       numTernary()const   { return numTern_; }
	SymbolTable& symTab()    const   { return symTabPtr_->symTab; }
	Solver*      master()    const   { return master_; }	
	void         simplifyBtig(Literal p);
	SatPrepro    satPrepro;  // preprocessor
	const ShortClauseImplications& shortClauseImplications()  const { return btig_; }
	uint32       numShortImplications(Literal p) const { 
		return btig_[p.index()].size();
	}
private:
	SharedContext(const SharedContext&);
	SharedContext& operator=(const SharedContext&);
	struct SharedSymTab {
		SharedSymTab() : refs(1) {}
		SymbolTable symTab;
		uint32      refs;
	}* symTabPtr_;
	typedef ShortClauseImplications BTIG;
	typedef std::auto_ptr<Distributor> DistPtr;
	typedef std::auto_ptr<Enumerator>  EnumPtr;
	ProblemStats problem_;     // problem statistics
	VarInfo      varInfo_;     // varInfo[v] stores info about variable v
	BTIG         btig_;        // binary-/ternary implication graph
	mt::Mutex*   mutex_;       // mutex protecting BTIG
	Solver*      master_;      // master solver, responsible for init
	EnumPtr      enumerator_;  // enumerator object
	DistPtr      distributor_; // object for distributing learnt knowledge
	Literal      tag_;         // literal for tagging learnt constraints
	size_type    lastInit_;    // size of master's db after last init
	size_type    lastTopLevel_;// size of master's top-level after last init
	uint32       numBin_;      // number of binary clauses
	uint32       numTern_;     // number of ternary clauses
	uint32       learntBin_;   // number of learnt binary clauses
	uint32       learntTern_;  // number of learnt ternary clauses
	uint32       shareCount_;  // number of objects sharing this object
	bool         shareConstr_; // sharing of problem constraints enabled?
};

//@}
}
#endif
