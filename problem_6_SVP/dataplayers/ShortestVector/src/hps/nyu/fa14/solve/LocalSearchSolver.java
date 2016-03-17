package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.Vector;

/**
 * Implements the LocalSearch
 * 
 * @author ck1456@nyu.edu
 */
public class LocalSearchSolver extends AbstractSolver {

    @Override
    public Vector solve(Basis b) {
        Vector v = localSearch(b.zeroVector());
        updateIfBest(v);
        return v;
    }

    public static Vector localSearch(Vector v) {

        // Incrementally optimize this vector
        v = v.clone(); // don't modify the original
        double bestLength = Double.MAX_VALUE;
        Vector bestVector = v.clone();

        int[] increments = new int[] { -4, 1, 1, 1, 1, 1, 1, 1, 1, -4 };

        boolean improved = true;
        while (improved) {
            improved = false;
            // n^2 search over coefficient length
            v = bestVector;
            cLoop: for(int j = 0; j < v.coef.length; j++) {
                for(int inc1 : increments) {
                    v.coef[j] = v.coef[j] + inc1;
                    Vector v1= v.clone();
                    for(int i = 0; i < v1.coef.length; i++) {
                        for(int inc2 : increments) {
                            v1.coef[i] = v1.coef[i] + inc2;
                            if(v1.length() > 0 && v1.length() < bestLength) {
                                bestLength = v1.length();
                                bestVector = v1.clone();
                                improved = true;
                                break cLoop;
                            }
                        }
                    }
                }
            }
        }
        return bestVector;
    }
}