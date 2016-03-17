package svp;

import java.math.BigInteger;

public class ListPoint {

	public long[] v;
	public long norm = 0;

	public ListPoint(int dimensions) {
		// entries initialized to 0
		v = new long[dimensions];
	}

	public BigInteger[] getBI() {
		BigInteger[] bi = new BigInteger[v.length];
		for (int i = 0; i < v.length; i++) {
			bi[i] = new BigInteger(String.valueOf(v[i]));
		}
		return bi;
	}
}