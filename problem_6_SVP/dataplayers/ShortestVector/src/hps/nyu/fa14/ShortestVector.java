package hps.nyu.fa14;

import hps.nyu.fa14.solve.IncrementalProgressSolver;
import hps.nyu.fa14.solve.LinearRelaxationSolver;

import java.io.File;
import java.io.IOException;

/**
 * Given a basis for a lattice, determine the shortest vector in the lattice
 */
public class ShortestVector {

    private static Vector solve(Basis b, String outputPath) {

        ISolver solver = new LinearRelaxationSolver();
        ISolver timedSolver = new TimedSolver(solver, 119);
        ISolver progressSolver = new IncrementalProgressSolver(timedSolver,
                outputPath);
        Vector vec = progressSolver.solve(b);
        System.out.println("Vector Length: " + vec.length());
        return vec;
    }

    public static void main(String[] args) throws IOException {
        if(args.length != 2) {
            usage();
        }
        // first parameter is input
        String inputFile = args[0];
        String outputFile = args[1];

        // Make directory for the output file if it does not exist
        File outFile = new File(outputFile);
        outFile.getAbsoluteFile().getParentFile().mkdirs();

        Basis b = Basis.parseFile(inputFile);
        Vector vec = solve(b, outputFile);

        vec.writeFile(outputFile);
    }

    private static void usage() {
        // How to use it
        System.out.println("java -jar ShortestVector.jar <input> <output>");
        System.exit(1);
    }

}
