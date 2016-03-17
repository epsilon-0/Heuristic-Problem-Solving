package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.ISolutionMonitor;
import hps.nyu.fa14.ISolver;
import hps.nyu.fa14.Vector;

// Makes sure to write a new solution to disk each time a new (better one) is available
public class IncrementalProgressSolver extends AbstractSolver implements
        ISolutionMonitor {

    private final String outputPath;

    private final ISolver solver;

    public IncrementalProgressSolver(ISolver solver, String output) {
        this.solver = solver;
        this.outputPath = output;
        solver.addSolutionMonitor(this);
    }

    @Override
    public Vector solve(Basis b) {
        return solver.solve(b);
    }

    @Override
    public void updateSolution(Vector v) {
        synchronized (solver) {
            // Make sure that it is valid before writing to disk
            if(!v.isFeasible()) {
                // System.out.println("Solution is not feasible...ignoring");
                return;
            }

            try {
                v.writeFile(outputPath);
            } catch (Exception IOException) {
                System.err.println("Trouble writing incremental file");
            }
        }
    }
}
