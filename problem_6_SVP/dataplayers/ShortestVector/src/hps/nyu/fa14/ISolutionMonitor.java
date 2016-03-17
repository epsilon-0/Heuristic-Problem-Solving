package hps.nyu.fa14;

public interface ISolutionMonitor {

    /**
     * Notify a monitor that an new (better) vector has been produced
     * 
     * @param v
     */
    void updateSolution(Vector v);
}
