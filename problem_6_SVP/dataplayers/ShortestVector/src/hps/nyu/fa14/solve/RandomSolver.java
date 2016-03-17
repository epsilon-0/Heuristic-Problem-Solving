package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.Vector;

import java.util.Random;

public class RandomSolver extends AbstractSolver {

    private static final Random RAND = new Random();
    
    @Override
    public Vector solve(Basis b) {
        Vector vec = b.zeroVector();

        // Pick a random vector
        vec.coef[RAND.nextInt(vec.coef.length)] = 1;
        return vec;
    }

}
