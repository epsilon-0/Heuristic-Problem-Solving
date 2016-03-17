package hps.nyu.fa14;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Random;

public class Basis {

    public final int dim;
    public final int vecCount;
    public final int[][] vectors;

    public Basis(int dim, int vecCount) {
        this.dim = dim;
        this.vecCount = vecCount;
        vectors = new int[vecCount][dim];
    }

    public Vector zeroVector() {
        Vector vec = new Vector(this);
        return vec;
    }

    private static final Random RAND = new Random();
    public static Basis random(int dim, int vecCount){
        Basis b = new Basis(dim, vecCount);
        for(int v = 0; v < vecCount; v++){
            for(int d = 0; d < dim; d++){
                // Range is -300 < v_ij < 300 per spec
                b.vectors[v][d] = RAND.nextInt(599) - 299;
            }
        }
        return b;
    }
    
    public static Basis parse(InputStream input) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(input));

        // Read vector count, dimensions
        String[] dims = br.readLine().trim().split("\\s");
        int V = Integer.parseInt(dims[0]);
        int D = Integer.parseInt(dims[1]);
        Basis B = new Basis(D, V);

        // Read vectors
        for(int v = 0; v < B.vecCount; v++) {
            String[] coords = br.readLine().trim().split("\\s");
            for(int d = 0; d < B.dim; d++) {
                B.vectors[v][d] = Integer.parseInt(coords[d]);
            }
        }
        return B;
    }

    public static Basis parseFile(String filePath) throws IOException {
        return parse(new FileInputStream(new File(filePath)));
    }
    
}
