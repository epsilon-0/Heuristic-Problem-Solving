package svp;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigInteger;

public class SystemCall {

	public static BigInteger[] getMatrices(String[] args, int numVectors,
			int numDimensions, long startTime) {
		Runtime r = Runtime.getRuntime();
		BufferedReader bStarReader = null;
		BufferedReader muReader = null;
		BufferedReader bkzReader = null;
		BigInteger[] vector = null;
		try {
			long[][] bkz = new long[numVectors][numDimensions];
			double[][] mu = new double[numVectors][numDimensions];
			double[] bstar = new double[numVectors];
			String line = null;
			String[] dimensions = null;
			int i = 0;

			// BKZ
			Process p = r
					.exec("./get_bkz_reduction " + args[0] + " " + args[1]);
			p.waitFor();
			bkzReader = new BufferedReader(new FileReader(new File(args[1])));
			line = bkzReader.readLine();

			i = 0;
			while (line != null) {
				dimensions = line.split(" ");
				for (int j = 0; j < numDimensions; j++) {
					bkz[i][j] = Long.valueOf(dimensions[j]);
				}
				i++;
				line = bkzReader.readLine();
			}

			// mu
			p = r.exec("./get_gram_schmidt mu " + args[0] + " " + args[1]);
			muReader = new BufferedReader(new FileReader(new File(args[1])));
			p.waitFor();
			line = muReader.readLine();

			i = 0;
			while (line != null) {
				dimensions = line.split(" ");
				for (int j = 0; j < numDimensions; j++) {
					mu[i][j] = Double.valueOf(dimensions[j]);
				}
				i++;
				line = muReader.readLine();
			}

			// bstar
			p = r.exec("./get_gram_schmidt bstar " + args[0] + " " + args[1]);
			p.waitFor();
			bStarReader = new BufferedReader(new FileReader(new File(args[1])));
			p.waitFor();
			line = bStarReader.readLine();

			i = 0;
			dimensions = line.split(" ");
			for (int j = 0; j < numDimensions; j++) {
				bstar[j] = Double.valueOf(dimensions[j]);
			}

			bkzReader.close();
			muReader.close();
			bStarReader.close();

			// call exact algorithm
			Sieve sieve = new Sieve(bkz, mu, bstar, startTime);
			vector = sieve.runExact();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {

		}
		return vector;
	}

}
