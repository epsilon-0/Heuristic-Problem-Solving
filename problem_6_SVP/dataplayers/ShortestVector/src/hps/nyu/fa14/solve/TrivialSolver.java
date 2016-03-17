package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.Vector;

public class TrivialSolver extends AbstractSolver {

    @Override
    public Vector solve(Basis b) {
        Vector vec = b.zeroVector();
        
        double minLength = Double.MAX_VALUE;
        int shortestVector = -1;
        // return the shortest vector
        for(int i = 0; i < b.vecCount; i++){
            double len = Vector.vectorLength(b.vectors[i]);
            if(len < minLength){
                minLength = len;
                shortestVector = i; 
            }
        }
        vec.coef[shortestVector] = 1;
        updateIfBest(vec);
        return vec;
    }

}
