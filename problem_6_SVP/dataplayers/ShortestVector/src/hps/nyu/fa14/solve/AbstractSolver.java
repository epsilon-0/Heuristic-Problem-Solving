package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.ISolutionMonitor;
import hps.nyu.fa14.ISolver;
import hps.nyu.fa14.Vector;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractSolver implements ISolver {

    @Override
    public abstract Vector solve(Basis b);
    
    protected List<ISolutionMonitor> monitors = new ArrayList<ISolutionMonitor>();

    @Override
    public void addSolutionMonitor(ISolutionMonitor monitor) {
        monitors.add(monitor);
    }

    protected void notifyNewSolution(Vector v) {
        for(ISolutionMonitor m : monitors) {
            m.updateSolution(v);
        }
    }

    public Vector bestSolution;
    private double bestValue = Double.MAX_VALUE;

    protected boolean updateIfBest(Vector v) {
        double len = v.length();
        if(len > 0 && len < bestValue) {
            bestSolution = v;
            bestValue = len;
            notifyNewSolution(v);
            return true;
        }
        return false;
    }
}
