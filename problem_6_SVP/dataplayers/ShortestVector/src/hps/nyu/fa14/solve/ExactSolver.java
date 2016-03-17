package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.Vector;

/**
 * Implements the LocalSearch
 * 
 * @author ck1456@nyu.edu
 */
public class ExactSolver extends AbstractSolver {

    @Override
    public Vector solve(Basis b) {

        Vector v = new TrivialSolver().solve(b);
        v = localSearch(v);
        //v = exactSolution(v);
        v = exactSolution(v);
        updateIfBest(v);
        return v;
    }
    
    public Vector exactSolution(Vector v) {
      v = v.clone(); // don't modify the original
      double bestLength = Double.MAX_VALUE;
      Vector bestVector = v.clone();
      
      int maxRuns = 1000;
      int runs = 0;
      while (runs < maxRuns) {
        for(int j = 0; j < v.coef.length; j++) {
          for(int i = 0; i < v.coef.length; i++) {
            if(j != i) {
              //check if increasing or decreasing one of these coeffs will improve
              //increase j
              bestVector.coef[j] += 1;
              double len = bestVector.length();
              boolean entered = false;
              while(len != 0 && len < bestLength) {
                bestLength = len;
                bestVector.coef[j] += 1;
                len = bestVector.length();
                entered = true;
              }
              bestVector.coef[j] -= 1;
              if(!entered) {
                bestVector.coef[j] -= 1;
                len = bestVector.length();
                while(len != 0 && len < bestLength) {
                  bestLength = len;
                  bestVector.coef[j] -= 1;
                  len = bestVector.length();
                }
                bestVector.coef[j] += 1;
              }
              //increase i
              bestVector.coef[i] += 1;
              len = bestVector.length();
              entered = false;
              while(len != 0 && len < bestLength) {
                bestLength = len;
                bestVector.coef[i] += 1;
                len = bestVector.length();
                entered = true;
              }
              bestVector.coef[i] -= 1;
              if(!entered) {
                bestVector.coef[i] -= 1;
                len = bestVector.length();
                while(len != 0 && len < bestLength) {
                  bestLength = len;
                  bestVector.coef[i] -= 1;
                  len = bestVector.length();
                }
                bestVector.coef[i] += 1;
              }
            }
          }
        }
        runs++;
      }
      System.out.println("Best "+bestLength);
      return bestVector;
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
