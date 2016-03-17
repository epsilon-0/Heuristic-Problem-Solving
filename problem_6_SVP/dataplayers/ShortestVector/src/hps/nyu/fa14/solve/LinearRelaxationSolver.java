package hps.nyu.fa14.solve;

import hps.nyu.fa14.Basis;
import hps.nyu.fa14.Vector;
import benchmarks.detinfer.pj.edu.rit.numeric.LinearSolve;

/**
 * A wholly new and brilliant idea incorporating a sense of linear relaxation
 */
public class LinearRelaxationSolver extends AbstractSolver {

    @Override
    public Vector solve(Basis b) {

        Vector startVector = new LLLSolver().solve(b);
        updateIfBest(startVector);
        //System.out.println("StartVector " + startVector.length());
        double startVectorLength = startVector.length();

        int sysSize = Math.max(b.dim, b.vecCount);
        double[][] A = new double[sysSize][sysSize];
        for(int i = 0; i < sysSize; i++) {
            for(int j = 0; j < sysSize; j++) {
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
        for(int k = 0; k < 10; k++) {
            for(int j = 0; j < b.dim; j++) {
                int targetDim = j; // RAND.nextInt(b.dim);
                double reduction = Math.max((.9 - (k * .09)), .001);
                for(int i = 0; i < b.dim; i++) {
                    if(i == targetDim) {
                        sVecVals[i] = startVectorLength * reduction;
                    } else {
                        sVecVals[i] = 0;
                    }
                }

                LinearSolve linearSolver = new LinearSolve(A);
                linearSolver.solve(coefs, sVecVals);

                // Construct the vector with these coefficients
                Vector v = b.zeroVector();
                for(int i = 0; i < b.vecCount; i++) {
                    v.coef[i] = (int) Math.round(coefs[i]);
                }
                if(updateIfBest(v)){
                    // Improved over LLL
                    //System.out.println(String.format("Improved! (red=%f) %f / %f", reduction, v.length(), startVectorLength));
                }
            }
        }
        
        Vector bestTest = bestSolution.clone();

        Vector localSearch2 = LocalSearchSolver.localSearch(bestTest);
        if(updateIfBest(localSearch2)){
            //System.out.println("LocalSearch is good (best test)");
        }

        Vector localSearch = LocalSearchSolver.localSearch(b.zeroVector());
        if(updateIfBest(localSearch)){
            //System.out.println("LocalSearch is good (zero vector)");
        }

//        int[] mostSimilarVectors = similarVectors(vectorDots(b));
//        int[] diff = subtract(b.vectors[mostSimilarVectors[0]], b.vectors[mostSimilarVectors[1]]);
//        if(Vector.vectorLength(diff) <= bestSolution.length()){
//            System.out.println("Diff is small");
//        }
            
        return bestSolution;
    }


    /*
    private static double dotProduct(int[] v1, int[] v2){
        double sum = 0;
        for(int i = 0; i < v1.length; i++){
            sum += v1[i] * v2[i];
        }
        return sum / (Vector.vectorLength(v1) * Vector.vectorLength(v2));
    }
    
    private static double[][] vectorDots(Basis b){
        double[][] dots = new double[b.vecCount][b.vecCount];
        for(int i = 0; i < b.vecCount; i++){
            for(int j = i; j < b.vecCount; j++){
                dots[i][j] = dots[j][i] = dotProduct(b.vectors[i], b.vectors[j]);
            }
        }
            return dots;
    }

    private static int[] similarVectors(double[][] dotProducts){
        
        double maxCorr = 0;
        int[] vecs = new int[2];
        for(int i = 0; i < dotProducts.length; i++){
            for(int j = i + 1; j < dotProducts.length; j++){
                if(dotProducts[i][j] > maxCorr){
                    maxCorr = dotProducts[i][j];
                    vecs[0] = i;
                    vecs[1] = j;
                }
            }
        }
        return vecs;
    }
    
    private static int[] subtract(int[] vec1, int[] vec2){
        int[] diff = new int[vec1.length];
        for(int i = 0; i < vec1.length; i++){
            diff[i] = vec1[i] - vec2[i];
        }
        return diff;
    }
    */
}
