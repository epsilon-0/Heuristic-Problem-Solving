package hps.nyu.fa14;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class Vector {

    public final Basis B;
    public final int[] coef;

    public Vector(Basis b) {
        B = b;
        coef = new int[B.vecCount];
    }

    public double length() {
        // determine the coordinates of the new vector
        double[] vec = new double[B.dim];
        for(int v = 0; v < coef.length; v++) {
            for(int d = 0; d < B.dim; d++) {
                vec[d] += (coef[v] * B.vectors[v][d]);
            }
        }
        // and then its length
        return vectorLength(vec);
    }
    
    public double length(int i,int j) {
      // determine the coordinates of the new vector
      double[] vec = new double[B.dim];
      for(int v = i; v < j; v++) {
          for(int d = 0; d < B.dim; d++) {
              vec[d] += (coef[v] * B.vectors[v][d]);
          }
      }
      // and then its length
      return vectorLength(vec);
  }

    // Must be a non-zero vector to be feasible
    public boolean isFeasible(){
        return length() != 0.0;
    }
    
    public Vector clone() {
        Vector newVec = new Vector(B);
        for(int i = 0; i < coef.length; i++) {
            newVec.coef[i] = coef[i];
        }
        return newVec;
    }

    public static double vectorLength(int[] vec) {
        double[] dVec = new double[vec.length];
        for(int i = 0; i < vec.length; i++) {
            dVec[i] = vec[i];
        }
        return vectorLength(dVec);
    }

    public static double vectorLength(double[] vec) {
        double sum = 0;
        for(int d = 0; d < vec.length; d++) {
            sum += (vec[d] * vec[d]);
        }
        return Math.sqrt(sum);
    }

    public void write(OutputStream output) throws IOException {
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(output));
        for(int i = 0; i < coef.length; i++) {
            bw.write(String.format("%d", coef[i]));
            bw.newLine();
        }
        bw.close();
    }

    public void writeFile(String filename) throws IOException {
        write(new FileOutputStream(new File(filename)));
    }
}
