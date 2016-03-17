package svp;

import java.math.BigInteger;

// This code was ported from the LLL.cc in Singular's IntegerProgramming implementation.

public class LLL {

	static final BigInteger ZERO = BigInteger.ZERO;
	static final BigInteger ONE = BigInteger.ONE;
	static final BigInteger TWO = new BigInteger("2");
	static final BigInteger THREE = new BigInteger("3");
	static final BigInteger FOUR = new BigInteger("4");

	/*
	 * Returns p divided by q and floors the remainder
	 */
	static BigInteger floorDivide(BigInteger p, BigInteger q) {

		BigInteger[] n = p.divideAndRemainder(q);
		// Java almost does the right thing. If the number being divided
		// is negative and the remainder is non-zero, the floor should be one
		// less
		if (p.signum() == (-1) && n[1].signum() != 0) {
			n[0] = n[0].subtract(BigInteger.ONE);
		}
		return n[0];
	}

	// subroutines for the LLL-algorithms

	// the REDI procedure for relations(...) (to compute the Kernel Basis,
	// algorithm 2.7.2 in Cohen's book)
	static void REDI_KB(int k, int l, BigInteger[][] b, int number_of_vectors,
			int vector_dimension, BigInteger[][] H, BigInteger[] d,
			BigInteger[][] lambda) {
		BigInteger lambda_k_l_2 = lambda[k][l].multiply(TWO);
		if (lambda_k_l_2.abs().compareTo(d[l + 1]) <= 0) {
			return;
		}
		BigInteger num = lambda_k_l_2.add(d[l + 1]);
		BigInteger q = floorDivide(num, d[l + 1].multiply(TWO));

		// q is the integer quotient of the division
		// (2*lambda[k][l]+d[l+1])/(2*d[l+1]).
		for (int n = 0; n < number_of_vectors; n++) {
			H[k][n] = H[k][n].subtract(q.multiply(H[l][n]));
		}
		for (int m = 0; m < vector_dimension; m++) {
			b[k][m] = b[k][m].subtract(q.multiply(b[l][m]));
		}
		lambda[k][l] = lambda[k][l].subtract(q.multiply(d[l + 1]));

		for (int i = 0; i <= l - 1; i++) {
			lambda[k][i] = lambda[k][i].subtract(q.multiply(lambda[l][i]));
		}
	}

	// the REDI procedure for the integer LLL algorithm (algorithm 2.6.7 in
	// Cohen's book)
	static void REDI_IL(int k, int l, BigInteger[][] b, int vector_dimension,
			BigInteger[] d, BigInteger[][] lambda) {
		BigInteger lambda_k_l_2 = lambda[k][l].multiply(TWO);
		if (lambda_k_l_2.abs().compareTo(d[l + 1]) <= 0) {
			return;
		}
		BigInteger num = lambda_k_l_2.add(d[l + 1]);
		BigInteger q = floorDivide(num, d[l + 1].multiply(TWO));
		// q is the integer quotient of the division
		// (2*lambda[k][l]+d[l+1])/(2*d[l+1]).
		for (int m = 0; m < vector_dimension; m++) {
			b[k][m] = b[k][m].subtract(q.multiply(b[l][m]));
		}
		lambda[k][l] = lambda[k][l].subtract(q.multiply(d[l + 1]));
		for (int i = 0; i <= l - 1; i++) {
			lambda[k][i] = lambda[k][i].subtract(q.multiply(lambda[l][i]));
		}
	}

	// the SWAPI procedure of algorithm 2.6.7
	static void SWAPI(int k, int k_max, BigInteger[][] b, BigInteger[] d,
			BigInteger[][] lambda) {
		// exchange b[k] and b[k-1]
		BigInteger[] aswap = b[k];
		b[k] = b[k - 1];
		b[k - 1] = aswap;
		if (k > 1) {
			for (int j = 0; j <= k - 2; j++) {
				// exchange lambda[k][j] and lambda[k-1][j]
				BigInteger swap = lambda[k][j];
				lambda[k][j] = lambda[k - 1][j];
				lambda[k - 1][j] = swap;
			}
		}
		BigInteger _lambda = lambda[k][k - 1];
		BigInteger num = d[k - 1].multiply(d[k + 1]).add(
				_lambda.multiply(_lambda));
		BigInteger B = floorDivide(num, d[k]);
		// It might be better to choose another evaluation order for this
		// formula, see below.
		for (int i = k + 1; i <= k_max; i++) {
			BigInteger t = lambda[i][k];
			num = d[k + 1].multiply(lambda[i][k - 1]).subtract(
					_lambda.multiply(t));
			lambda[i][k] = floorDivide(num, d[k]);
			num = B.multiply(t).add(_lambda.multiply(lambda[i][k]));
			lambda[i][k - 1] = floorDivide(num, d[k + 1]);
		}
		d[k] = B;
	}

	// the SWAPK procedure of algorithm 2.7.2
	static void SWAPK(int k, int k_max, BigInteger[][] b, BigInteger[][] H,
			boolean[] f, BigInteger[] d, BigInteger[][] lambda) {
		// exchange H[k] and H[k-1]
		BigInteger[] aswap = H[k];
		H[k] = H[k - 1];
		H[k - 1] = aswap;
		// exchange b[k] and b[k-1] by the same method
		aswap = b[k];
		b[k] = b[k - 1];
		b[k - 1] = aswap;
		if (k > 1) {
			for (int j = 0; j <= k - 2; j++) {
				// exchange lambda[k][j] and lambda[k-1][j]
				BigInteger swap = lambda[k][j];
				lambda[k][j] = lambda[k - 1][j];
				lambda[k - 1][j] = swap;
			}
		}
		BigInteger _lambda = lambda[k][k - 1];
		if (_lambda.compareTo(ZERO) == 0) {
			d[k] = d[k - 1];
			f[k - 1] = false;
			f[k] = true;
			lambda[k][k - 1] = ZERO;
			for (int i = k + 1; i <= k_max; i++) {
				lambda[i][k] = lambda[i][k - 1];
				lambda[i][k - 1] = ZERO;
			}
		} else {
			for (int i = k + 1; i <= k_max; i++) {
				BigInteger lnum = _lambda.multiply(lambda[i][k - 1]);
				lambda[i][k - 1] = floorDivide(lnum, d[k]);
			}
			// Multiplie lambda[i][k-1] by _lambda/d[k].
			// One could also write
			// lambda[i][k-1]*=(lambda/d[k]); (*)
			// Without a BigInt class, this can prevent overflows when computing
			// _lambda*lambda[i][k-1].
			// But examples show that lambda/d[k] is in general not an integer.
			// So (*) could lead to problems due to the inexact floating point
			// arithmetic...
			// Therefore, we chose the secure evaluation order in all such
			// cases.
			BigInteger t = d[k + 1];
			BigInteger num = _lambda.multiply(_lambda);
			d[k] = floorDivide(num, d[k]);
			d[k + 1] = d[k];
			for (int j = k + 1; j <= k_max - 1; j++) {
				for (int i = j + 1; i <= k_max; i++) {
					num = lambda[i][j].multiply(d[k]);
					lambda[i][j] = floorDivide(num, t);
				}
			}
			for (int j = k + 1; j <= k_max; j++) {
				// d[j+1]=(d[j+1]*d[k])/t;
				num = d[j + 1].multiply(d[k]);
				d[j + 1] = floorDivide(num, t);
			}
		}

	}

	public static BigInteger[][] relations(BigInteger[][] b) {
		// consider special case
		int number_of_vectors = b.length;
		int vector_dimension = b[0].length;
		if (number_of_vectors == 1)
			// Only one vector which has no relations if it is not zero,
			// else relation 1.
		{
			boolean r = true; // Suppose the only column of the matrix is zero.
			for (int m = 0; m < vector_dimension; m++) {
				if (b[0][m].compareTo(ZERO) != 0) {
					// nonzero entry detected
					r = false;
				}
			}
			if (r) {
				BigInteger[][] H = new BigInteger[1][];
				H[0] = new BigInteger[1];
				H[0][0] = ONE;
				// This is the lattice basis of the relations...
				return H;
			}
			return null;
		}
		// The names are chosen (as far as possible) according to Cohen's book.
		// However, for technical reasons, the indices do not run from 1 to
		// (e.g.) number_of_vectors, but from 0 to number_of_vectors-1.
		// Therefore all indices are shifted by -1 in comparison with this book,
		// except from the indices of the array d which has size
		// number_of_vectors+1.
		BigInteger[][] H = new BigInteger[number_of_vectors][];
		for (int n = 0; n < b.length; n++) {
			H[n] = new BigInteger[number_of_vectors];
		}
		boolean[] f = new boolean[number_of_vectors];
		for (int i = 0; i < f.length; i++) {
			f[i] = false;
		}
		BigInteger[] d = new BigInteger[number_of_vectors + 1];
		BigInteger[][] lambda = new BigInteger[number_of_vectors][];
		for (int n = 1; n < number_of_vectors; n++) {
			lambda[n] = new BigInteger[n];
		}
		// We only need lambda[n][k] for n>k.
		// Step 1: Initialization
		int k = 1;
		int k_max = 0;
		// for iteration
		d[0] = ONE;
		BigInteger t = ZERO;
		for (int m = 0; m < vector_dimension; m++) {
			t = t.add(b[0][m].multiply(b[0][m]));
		}
		// Now, t is the scalar product of b[0] with itself.
		for (int n = 0; n < number_of_vectors; n++) {
			for (int l = 0; l < number_of_vectors; l++) {
				if (n == l) {
					H[n][l] = ONE;
				} else {
					H[n][l] = ZERO;
				}
			}
		}
		// Now, H equals the matrix I_(number_of_vectors).
		if (t.compareTo(ZERO) != 0) {
			d[1] = t;
			f[0] = true;
		} else {
			d[1] = ONE;
			f[0] = false;
		}
		// The other steps are not programmed with "goto" as in Cohen's book.
		// Instead, we enter a do-while-loop which terminates iff
		// k>=number_of_vectors.
		do {
			// Step 2: Incremental Gram-Schmidt
			if (k > k_max)
				// else we can immediately go to step 3.
			{
				k_max = k;
				for (int j = 0; j <= k; j++) {
					if (!f[j] && (j < k)) {
						lambda[k][j] = ZERO;
					} else {
						BigInteger u = ZERO;
						// compute scalar product of b[k] and b[j]
						for (int m = 0; m < vector_dimension; m++) {
							u = u.add(b[k][m].multiply(b[j][m]));
						}
						for (int i = 0; i <= j - 1; i++) {
							if (f[i]) {
								BigInteger n = d[i + 1].multiply(u).subtract(
										lambda[k][i].multiply(lambda[j][i]));
								u = floorDivide(n, d[i]);
							}
						}
						if (j < k) {
							lambda[k][j] = u;
						} else {
							if (u.compareTo(ZERO) != 0) {
								d[k + 1] = u;
								f[k] = true;
							} else {
								d[k + 1] = d[k];
								f[k] = false;
							}
						}
					}
				}
			}
			// Step 3: Test f[k]==0 and f[k-1]!=0
			do {
				if (f[k - 1]) {
					REDI_KB(k, k - 1, b, number_of_vectors, vector_dimension,
							H, d, lambda);
				}

				if (f[k - 1] && !f[k]) {
					SWAPK(k, k_max, b, H, f, d, lambda);
					if (k > 1) {
						k--;
					} else {
						k = 1;
					}
				} else {
					break;
				}
			} while (true);
			// Now the conditions above are no BigIntegerer satisfied.
			for (int l = k - 2; l >= 0; l--) {
				if (f[l]) {
					REDI_KB(k, l, b, number_of_vectors, vector_dimension, H, d,
							lambda);
				}
			}
			k++;
			// Step 4: Finished?
		} while (k < number_of_vectors);
		// Now we have computed a lattice basis of the relations of the b[i].
		// Prepare the LLL-reduction.
		// Compute the dimension r of the relations.
		int r = 0;
		for (int n = 0; n < number_of_vectors; n++) {
			if (!f[n]) {
				r++;
			} else {
				break;
			}
		}
		// Delete the part of H that is no BigIntegerer needed (especially the
		// vectors
		// H[r],...,H[number_of_vectors-1]).
		BigInteger[][] aux = H;
		if (r > 0) {
			H = new BigInteger[r][];
		} else {
			H = null;
		}
		for (int i = 0; i < r; i++) {
			H[i] = aux[i];
		}
		integral_LLL(H, r, number_of_vectors);
		return H;
	}

	static void integral_LLL(BigInteger[][] b, int number_of_vectors,
			int vector_dimension) {
		// consider special case
		if (number_of_vectors <= 1) {
			// 0 or 1 input vector, nothing to be done
			return;
		}
		// The names are chosen (as far as possible) according to Cohen's book.
		// However, for technical reasons, the indices do not run from 1 to
		// (e.g.) number_of_vectors, but from 0 to number_of_vectors-1.
		// Therefore all indices are shifted by -1 in comparison with this book,
		// except from the indices of the array d which has size
		// number_of_vectors+1.

		BigInteger[] d = new BigInteger[number_of_vectors + 1];
		BigInteger[][] lambda = new BigInteger[number_of_vectors][];
		for (int s = 1; s < number_of_vectors; s++) {
			lambda[s] = new BigInteger[s];
		}
		// We only need lambda[n][k] for n>k.
		// Step 1: Initialization
		int k = 1;
		int k_max = 0;
		// for iteration
		d[0] = ONE;
		d[1] = ZERO;
		for (int n = 0; n < vector_dimension; n++) {
			d[1] = d[1].add(b[0][n].multiply(b[0][n]));
		}
		// The other steps are not programmed with "goto" as in Cohen's book.
		// Instead, we enter a do-while-loop which terminates iff k>r.
		do {
			// Step 2: Incremental Gram-Schmidt
			if (k > k_max)
				// else we can immediately go to step 3.
			{
				k_max = k;

				for (int j = 0; j <= k; j++) {
					BigInteger u = ZERO;
					// compute scalar product of b[k] and b[j]
					for (int n = 0; n < vector_dimension; n++) {
						u = u.add(b[k][n].multiply(b[j][n]));
					}
					for (int i = 0; i <= j - 1; i++) {
						u = u.multiply(d[i + 1]);
						u = u.subtract(lambda[k][i].multiply(lambda[j][i]));
						u = floorDivide(u, d[i]);
					}
					if (j < k) {
						lambda[k][j] = u;
					} else {
						// j==k
						d[k + 1] = u;
					}
				}
				if (d[k + 1].compareTo(ZERO) == 0) {
					throw new RuntimeException(
							"Algorithm failure: input vectors must be linearly independent.");
				}
			}
			// Step 3: Test LLL-condition
			do {
				REDI_IL(k, k - 1, b, vector_dimension, d, lambda);
				if (FOUR.multiply(d[k + 1].multiply(d[k - 1])).compareTo(
						THREE.multiply(d[k].multiply(d[k])).subtract(
								lambda[k][k - 1].multiply(lambda[k][k - 1]))) < 0) {
					SWAPI(k, k_max, b, d, lambda);
					if (k > 1) {
						k--;
					}
				} else {
					break;
				}

			} while (true);
			// Now the condition above is no BigIntegerer satisfied.
			for (int l = k - 2; l >= 0; l--) {
				REDI_IL(k, l, b, vector_dimension, d, lambda);
			}
			k++;
			// Step 4: Finished?
		} while (k < number_of_vectors);
		// Now, b contains the LLL-reduced lattice basis.
	}
}
