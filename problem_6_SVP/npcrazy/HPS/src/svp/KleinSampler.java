package svp;

public class KleinSampler {

	private long[][] basis;
	private double[][] mu;
	private double[] bstar;

	private int n;
	private int m;
	private double t;
	private double[] coef;
	private double[] sPrimeSquare;

	public KleinSampler(long[][] basis, double[][] mu, double[] bstar) {
		this.basis = basis;
		this.mu = mu;
		this.bstar = bstar;
		this.n = basis.length;
		this.m = basis[0].length;
		coef = new double[n];
		sPrimeSquare = new double[n];
		long maxStarSqrNorm = 0;
		for (int i = 0; i < n; ++i) {
			maxStarSqrNorm = Math.max(maxStarSqrNorm, (long) this.bstar[i]);
		}
		this.t = Math.log(n);
		double sSquare = maxStarSqrNorm * Math.log(n);
		for (int i = 0; i < n; ++i) {
			sPrimeSquare[i] = sSquare / this.bstar[i];
		}
	}

	private long sampleZ(double c, double sSquare) {
		double s = Math.sqrt(sSquare);
		long minC = (long) Math.floor(c - s * this.t);
		long maxC = (long) Math.ceil(c + s * this.t);
		long x;
		double rho;
		while (true) {
			x = minC + Math.round((maxC - minC) * Math.random());
			rho = Math.exp(-1 * Math.PI * (x - c) * (x - c) / sSquare);
			if (Math.random() <= rho) {
				return x;
			}
		}
	}

	public ListPoint sample() {
		ListPoint lp = new ListPoint(this.m);
		for (int i = 0; i < n; ++i) {
			coef[i] = 0;
		}
		for (int i = n - 1; i >= 0; --i) {
			coef[i] = sampleZ(coef[i], sPrimeSquare[i]);
			for (int j = 0; j < i; j++) {
				coef[j] -= (coef[i] * mu[i][j]);
			}
		}
		lp.norm = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				lp.v[i] += coef[j] * basis[j][i];
			}
			lp.norm += lp.v[i] * lp.v[i];
		}
		return lp;
	}

}