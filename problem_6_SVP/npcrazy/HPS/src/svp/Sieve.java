package svp;

import java.math.BigInteger;
import java.util.Calendar;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Queue;

public class Sieve {

	private int n;
	private int m;
	private KleinSampler sampler;
	private long collisions = 0;
//	private long iterations = 0;
	private long bestSqrNorm = 0;
	private long goalSqrNorm = 0;
	private int maxListSize = 0;
	private LinkedList<ListPoint> list;
	private Queue<ListPoint> queue;

	long startTime;

	public Sieve(long[][] basis, double[][] mu, double[] bstar, long startTime) {
		this.startTime = startTime;
		this.n = basis.length;
		this.m = basis[0].length;
		this.list = new LinkedList<ListPoint>();
		this.queue = new LinkedList<ListPoint>();
		this.sampler = new KleinSampler(basis, mu, bstar);
		this.bestSqrNorm = dotProduct(basis[0], basis[0]);
		long currentNorm = 0;
		for (int i = 0; i < n; ++i) {
			ListPoint p = getListPoint(m, basis[i]);
			currentNorm = updateList(p);
			if (currentNorm < this.bestSqrNorm) {
				this.bestSqrNorm = currentNorm;
			}
		}
		this.maxListSize = list.size();
	}

	private long dotProduct(long[] a, long[] b) {
		long dotProduct = 0;
		for (int i = 0; i < a.length; ++i) {
			dotProduct += (a[i] * b[i]);
		}
		return dotProduct;
	}

	private ListPoint getListPoint(int dim, long[] vec) {
		ListPoint lp = new ListPoint(dim);
		lp.norm = 0;
		for (int i = 0; i < dim; ++i) {
			lp.v[i] = vec[i];
			lp.norm += lp.v[i] * lp.v[i];
		}
		return lp;
	}

	private boolean reduce(ListPoint p1, ListPoint p2) {
		int dims = p1.v.length;
		long dotProduct = dotProduct(p1.v, p2.v);
		if ((long) Math.abs(2 * dotProduct) <= p2.norm) {
			return false;
		}
		long q = Math.round((double) dotProduct / p2.norm);
		for (int i = 0; i < dims; ++i) {
			p1.v[i] -= q * p2.v[i];
		}
		p1.norm = p1.norm + q * q * p2.norm - 2 * q * dotProduct;
		return true;
	}

	long updateList(ListPoint p) {
		// list<ListPoint*>::iterator lp_it, tmp_lp_it;
		boolean needsReduction = true;
		ListIterator<ListPoint> lpIt = list.listIterator();
		while (needsReduction) {
			needsReduction = false;
			lpIt = list.listIterator();
			while (lpIt.hasNext()) {
				ListPoint lp = lpIt.next();
				if (lp.norm > p.norm) {
					break;
				}
				if (reduce(p, lp)) {
					needsReduction = true;
				}
			}
		}
		// We got a collision
		if (p.norm == 0) {
			return 0;
		}
		// lpIt shows to the first point with bigger norm
		// this is where we will insert the new point
		lpIt.add(p);
		// Let's reduce now the vectors with bigger norm
		while (lpIt.hasNext()) {
			// tmp_lp_it = lp_it;
			ListPoint lp = lpIt.next();
			// ++lp_it;
			if (reduce(lp, p)) {
				lpIt.remove();
				queue.add(lp);
			}
		}
		return p.norm;
	}

	public BigInteger[] runExact() {
		ListPoint currentPoint;
		long currentNorm;

		// Loop till you find a short enough vector,
		// or enough collisions.
		// The 0.1 * max_list_size_ + 200 is much more
		// than needed in general so we are almost sure
		// we have found the shortest vector.
		long currTime = Calendar.getInstance().getTimeInMillis();
		while ((this.bestSqrNorm > this.goalSqrNorm)
				&& (this.collisions < (maxListSize / 10) + 200)
				&& (currTime - startTime < 110000)) {
//			this.iterations++;
			this.maxListSize = (int) Math.max(maxListSize, list.size());
			// Get next point for reduction
			if (queue.isEmpty()) {
				currentPoint = sampler.sample();
			} else {
				currentPoint = queue.remove();

			}
			// Reduce it and put the vectors of the list that
			// need reduction to the queue.
			currentNorm = updateList(currentPoint);
			if (currentNorm == 0) {
				this.collisions++;
			}
			if (currentNorm > 0 && currentNorm < this.bestSqrNorm) {
				this.bestSqrNorm = currentNorm;
			}
			currTime = Calendar.getInstance().getTimeInMillis();
		}
		return list.getFirst().getBI();
	}

}