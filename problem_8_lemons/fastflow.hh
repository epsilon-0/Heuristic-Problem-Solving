#ifndef DINITZ_
#define DINITZ_

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

typedef double TYPE;

class Dinitz {
private:
  TYPE INF;
  double EPS;
  vector<int> Q, fin, pro, dist, next, to;
  vector<TYPE> cap, flow;
  int src, snk, nNode, nEdge;

public:
  Dinitz(int _src, int _snk, int _n) {
    int maxn = 2 * _n;
    INF = 922337203680775807;
    EPS = 1e-9;
    Q.resize(maxn);
    fin.resize(maxn, -1);
    pro.resize(maxn);
    dist.resize(maxn);
    src = _src, snk = _snk, nNode = _n, nEdge = 0;
  }

  void add(int u, int v, TYPE c) {
    to.push_back(v);
    cap.push_back(c);
    flow.push_back(0);
    next.push_back(fin[u]);
    fin[u] = nEdge++;
    cout << u << " " << v << " " << c << endl;
    // to.push_back(u); cap.push_back(c); flow.push_back(0);
    // next.push_back(fin[v]); fin[v] = nEdge++; // uncommment for undirected
    // graph
  }

  bool bfs() {
    int st, en, i, u, v;
    for (int pos = 0; pos < dist.size(); pos++)
      dist[pos] = -1;
    dist[src] = st = en = 0;
    Q[en++] = src;
    while (st < en) {
      u = Q[st++];
      for (i = fin[u]; i >= 0; i = next[i]) {
        v = to[i];
        if ((cap[i] - flow[i] > EPS) && dist[v] == -1) {
          dist[v] = dist[u] + 1;
          Q[en++] = v;
        }
      }
    }
    return dist[snk] != -1;
  }

  TYPE dfs(int u, TYPE fl) {
    if (u == snk)
      return fl;
    TYPE df;
    for (int &e = pro[u], v; e >= 0; e = next[e]) {
      v = to[e];
      if ((cap[e] - flow[e] > EPS) && dist[v] == dist[u] + 1) {
        df = dfs(v, min(cap[e] - flow[e], fl));
        if (df > EPS) {
          flow[e] += df;
          flow[e ^ 1] -= df;
          return df;
        }
      }
    }
    return 0;
  }

  TYPE dinitz() {
    TYPE ret = 0;
    TYPE df;
    while (bfs()) {
      for (int i = 1; i <= nNode; i++)
        pro[i] = fin[i];
      while (true) {
        df = dfs(src, INF);
        if (df > EPS)
          ret += df;
        else
          break;
      }
    }
    return ret;
  }

  vector<bool> getMinCut() {
    vector<bool> mincut(nNode + 1, false);
    bfs();
    assert(dist[src] == 0);
    assert(dist[snk] == -1);
    for (int i = 1; i <= nNode; i++) {
      mincut[i] = (dist[i] != -1);
    }
    return mincut;
  }
};

#endif
