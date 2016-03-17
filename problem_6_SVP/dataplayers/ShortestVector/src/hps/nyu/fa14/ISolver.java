package hps.nyu.fa14;

public interface ISolver {
    Vector solve(Basis b);
    void addSolutionMonitor(ISolutionMonitor monitor);
}
