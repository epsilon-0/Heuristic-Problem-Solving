package hps.nyu.fa14;

import hps.nyu.fa14.solve.AbstractSolver;

public class TimedSolver extends AbstractSolver implements ISolutionMonitor,
        Runnable {

    private final int maxSeconds;
    private final ISolver solver;
    private Basis currentBasis;
    // Make sure to give yourself this much overhead for setting up the thread
    private final int SETUP_MILLIS = 150;

    public TimedSolver(ISolver solver, int seconds) {
        this.solver = solver;
        maxSeconds = seconds;
    }

    @SuppressWarnings("deprecation")
    // Yes, I know stop is deprecated, but that is silly
    @Override
    public Vector solve(Basis b) {

        // Set up the solver to report the best solution reported so far
        currentBasis = b;

        // run a thread.
        Thread solveThread = new Thread(this);
        solveThread.start();
        try {
            // Wait until the thread finishes or we time out
            solveThread.join((maxSeconds * 1000) - SETUP_MILLIS);
        } catch (Exception ex) {/* suppress */
            System.out.println();
        }

        if(solveThread.isAlive()) {
            // Interrupt does not do what we need (or expect) it to do, so fail
            // solveThread.interrupt();
            solveThread.stop();
        }

        // Wait a certain amount of time, then kill and output
        return bestSolution;
    }

    @Override
    public void run() {
        solver.addSolutionMonitor(this);
        Vector v = solver.solve(currentBasis);
        // If we get this far, assume the solver returned the best assignment
        synchronized (currentBasis) {
            updateIfBest(v);
        }
    }

    @Override
    public void updateSolution(Vector v) {
        synchronized (currentBasis) {
            updateIfBest(v);
        }
    }
}
