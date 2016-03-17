package svp;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Calendar;

public class SVP {

	public static double getEuclidianLength(BigInteger[] vector) {
		double sum = 0.0;
		for (int i = 0; i < vector.length; ++i) {
			sum += Math.pow(vector[i].doubleValue(), 2);
		}
		return Math.sqrt(sum);
	}

	public static double[][] getCoefficients(BigInteger[][] matrix,
			BigInteger[] vector) {
		double[][] sums = new double[vector.length][1];
		for (int i = 0; i < sums.length; ++i) {
			sums[i][0] = vector[i].doubleValue();
		}
		double[][] factors = new double[vector.length][matrix.length];
		for (int i = 0; i < matrix.length; ++i) {
			for (int j = 0; j < vector.length; ++j) {
				factors[j][i] = matrix[i][j].doubleValue();
			}
		}
		Jama.Matrix factorsMatrix = new Jama.Matrix(factors);
		Jama.Matrix sumsMatrix = new Jama.Matrix(sums);
		Jama.Matrix solution = factorsMatrix.solve(sumsMatrix);
		return solution.getArray();
	}

	public static void main(String[] args) {
		PrintWriter writer = null;
		try {

			double[][] coefficients1 = heuristic1(args);
			double[][] coefficients2 = heuristic2(args);
			writer = new PrintWriter(new FileWriter(args[1]));
			if (coefficients2 != null) {
				for (int j = 0; j < coefficients2.length; ++j) {
					writer.println(Math.round(coefficients2[j][0]));
				}
			} else {
				for (int j = 0; j < coefficients1.length; ++j) {
					writer.println(Math.round(coefficients1[j][0]));
				}
			}
		} catch (Exception e) {
			System.out.println("Exception caught: " + e);
			e.printStackTrace();
		} finally {
			writer.close();
		}
	}

	public static double[][] heuristic1(String[] args) {
		BufferedReader reader;

		double[][] coefficients = null;
		try {
			reader = new BufferedReader(new FileReader(args[0]));

			String[] params = reader.readLine().split(" ");
			int numVectors = Integer.parseInt(params[0]);
			int numDimensions = Integer.parseInt(params[1]);
			BigInteger[][] matrix = new BigInteger[numVectors][numDimensions];
			BigInteger[][] l3Reduction = new BigInteger[numVectors][numDimensions];
			for (int i = 0; i < numVectors; ++i) {
				String[] dimensions = reader.readLine().split(" ");
				for (int j = 0; j < dimensions.length; ++j) {
					l3Reduction[i][j] = new BigInteger(dimensions[j]);
					matrix[i][j] = new BigInteger(dimensions[j]);
				}
			}
			LLL.integral_LLL(l3Reduction, numVectors, numDimensions);
			coefficients = getCoefficients(matrix, l3Reduction[0]);
			reader.close();
		} catch (NumberFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return coefficients;
	}

	public static double[][] heuristic2(String[] args) {
		BufferedReader reader = null;
		double[][] coefficients = null;

		try {
			final String[] arguments = args;
			reader = new BufferedReader(new FileReader(args[0]));
			String[] params = reader.readLine().split(" ");
			final int numVectors = Integer.parseInt(params[0]);
			final int numDimensions = Integer.parseInt(params[1]);
			BigInteger[] vector = SystemCall.getMatrices(arguments, numVectors,
					numDimensions, Calendar.getInstance().getTimeInMillis());
			BigInteger[][] matrix = new BigInteger[numVectors][numDimensions];
			for (int i = 0; i < numVectors; ++i) {
				String[] dimensions = reader.readLine().split(" ");
				for (int j = 0; j < dimensions.length; ++j) {
					matrix[i][j] = new BigInteger(dimensions[j]);
				}
			}
			coefficients = getCoefficients(matrix, vector);
			return coefficients;

		} catch (NumberFormatException e) {
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				reader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return coefficients;
	}
}