package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.Vector;

import java.math.BigInteger;

import benchmarks.detinfer.pj.edu.rit.numeric.LinearSolve;

import com.milowski.monos.binomial.LLL;

/**
 * Implements the LLL approximation to shortest vector
 * Resources:
 *  https://code.google.com/p/monos-algebra/source/browse/trunk/platform/src/com/milowski/monos/binomial/LLL.java?r=2
 *  http://soot.googlecode.com/svn/CalFuzzer2.0/src/benchmarks/detinfer/pj/edu/rit/numeric/LinearSolve.java
 *  
 *  http://cseweb.ucsd.edu/~daniele/papers/AlgoEncyclopedia.pdf
 *  https://www.math.auckland.ac.nz/~sgal018/crypto-book/ch18.pdf
 *  
 * @author ck1456@nyu.edu
 */
public class LLLSolver extends AbstractSolver {

    @Override
    public Vector solve(Basis b) {

        BigInteger[][] big = convertToBigInteger(b);

        LLL.integral_LLL(big, big.length, big[0].length);

        // TODO: Not actually necessary to do this conversion,
        // because we have to convert to double for solving linear equations
        int[][] reduced = convertToInteger(big);
        
        double shortest = Double.MAX_VALUE;
        int vectorIndex = -1;
        for(int i = 0; i < b.vecCount; i++) {
            double vLen = Vector.vectorLength(reduced[i]);
            //System.out.println(String.format("%s", vLen));
            // Find the shortest vector and solve a system of linear equations
            // to reconstruct it
            if(vLen < shortest){
                shortest = vLen;
                vectorIndex = i;
            }
        }
        
        // Need to swap dimensions here:
        // The LinearSolve library expects vectors in columns (not rows)
        // and the matrix must be square
        // (the rest are sufficiently large, but linearly independent so they
        // won't prevent solving the system of linear equations)
        int sysSize = Math.max(b.dim, b.vecCount);
        double[][] A = new double[sysSize][sysSize];
        for(int i = 0; i < sysSize; i++){
            for(int j = 0; j < sysSize; j++){
                A[i][j] = 10000000 + i + j;
            }
        }
        
        for(int v = 0; v < b.vecCount; v++) {
            for(int d = 0; d < b.dim; d++) {
                A[d][v] = b.vectors[v][d]; // NOTE: dimension swap
            }
        }
        
        // coefficients to solve for (1 per basis vector)
        double[] coefs = new double[sysSize];
        
        // Copy coordinate values from the shortest vector (target) 
        double[] sVecVals = new double[b.dim];
        for(int i = 0; i < b.dim; i++){
            sVecVals[i] = reduced[vectorIndex][i];
        }
        
        LinearSolve linearSolver = new LinearSolve(A);
        linearSolver.solve(coefs, sVecVals);
        
        // Construct the vector with these coefficients
        Vector v = b.zeroVector();
        for(int i = 0; i < b.vecCount; i++){
            v.coef[i] = (int)Math.round(coefs[i]);
        }

        updateIfBest(v);
        return v;
    }

    @SuppressWarnings("unused")
    private static void dump(BigInteger[][] b) {
        for(int i = 0; i < b.length; i++) {
            if(b[i] == null) {
                continue;
            }
            for(int j = 0; j < b[i].length; j++) {
                System.out.print(String.format("%3d ", b[i][j].intValue()));
            }
            System.out.println();
        }
    }

    private static BigInteger[][] convertToBigInteger(Basis b) {
        BigInteger[][] big = new BigInteger[b.vecCount][b.dim];
        for(int v = 0; v < b.vecCount; v++) {
            for(int d = 0; d < b.dim; d++) {
                big[v][d] = BigInteger.valueOf(b.vectors[v][d]);
            }
        }
        return big;
    }

    private static int[][] convertToInteger(BigInteger[][] big) {
        int[][] b = new int[big.length][big[0].length];
        for(int v = 0; v < big.length; v++) {
            for(int d = 0; d < big[0].length; d++) {
                b[v][d] = big[v][d].intValue();
            }
        }
        return b;
    }
    
    @SuppressWarnings("unused")
    private static double[][] convertToDouble(int[][] b) {
        double[][] dB = new double[b.length][b[0].length];
        for(int v = 0; v < b.length; v++) {
            for(int d = 0; d < b[0].length; d++) {
                dB[v][d] = b[v][d];
            }
        }
        return dB;
    }
}
