#ifndef __GSIEVE__
#define __GSIEVE__

#include <iostream>
#include <list>
#include <queue>

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/LLL.h>
#include "common.h"
#include "sampler.h"

NTL_CLIENT

class GSieve {
  public:
    ~GSieve() {
      CleanUp();
    }
    void Init(const mat_ZZ& B, KleinSampler* sampler);
    void SetGoalSqrNorm(long norm);
    void SetVerbose(bool verbose);
    void CleanUp();
    bool Start(const mat_ZZ &B);
  private:
    int UpdateList(ListPoint* p);
    KleinSampler* sampler_;
    long n_;
    long m_;
    int64 best_sqr_norm_;
    int64 goal_sqr_norm_;
    list<ListPoint*> list_;
    queue<ListPoint*> queue_;
    // Statistics
    long max_list_size_;
    long iterations_;
    long collisions_;
    bool verbose_;
};

#endif
