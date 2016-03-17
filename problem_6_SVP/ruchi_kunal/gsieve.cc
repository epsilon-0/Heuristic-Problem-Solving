#include "gsieve.h"

// Cleans up used memory
void GSieve::CleanUp() {
  list<ListPoint*>::iterator lp_it;
  for (lp_it = list_.begin(); lp_it != list_.end(); ++lp_it)
    DeleteListPoint(*lp_it);
  list_.clear();
  while (!queue_.empty()) {
    DeleteListPoint(queue_.front());
    queue_.pop();
  }
}

// Initializes the reducer.
void GSieve::Init(const mat_ZZ &B, KleinSampler* sampler) {
  n_ = B.NumRows();
  m_ = B.NumCols();
  sampler_ = sampler;
  collisions_ = 0;
  iterations_ = 0;
  // Clean up list and queue
  CleanUp();
  // Here we should do LLL,BKZ reduction if not already done
  
  sampler_->Init(B);
  best_sqr_norm_ = to_long(B[0]*B[0]);
  ListPoint* p;
  long current_norm;
  for (int i = 0; i < n_; ++i) {
    p = NewListPoint(m_);
    VecZZToListPoint(B[i], p);
    current_norm = UpdateList(p);
    if (current_norm < best_sqr_norm_)
      best_sqr_norm_ = current_norm;
  }
  max_list_size_ = list_.size();
  goal_sqr_norm_ = 0;
  verbose_ = 0;
}

void GSieve::SetGoalSqrNorm(long norm) {
  goal_sqr_norm_ = norm;
}

void GSieve::SetVerbose(bool verbose) {
  verbose_ = verbose;
}

// Reduces recuirsively the point with all the points with smaller norm
// Adds the point to the list if we don't have colission
// and puts to the queue all the points with bigger norm
// that can be reduced with it.
int GSieve::UpdateList(ListPoint* p) {
  list<ListPoint*>::iterator lp_it, tmp_lp_it;
  ListPoint* lp;
  bool needs_reduction = true;
  // Reduce the new lattice point
  // with the vectors with smaller norm
  while(needs_reduction) {
    needs_reduction = false;
    for (lp_it = list_.begin(); lp_it != list_.end(); ++lp_it) {
      lp = *lp_it;
      if (lp->norm > p->norm)
        break;
      //If there is one reduction the vector should re-pass the list
      if (Reduce(p, lp)) {
        needs_reduction = true;
      }
    }
  }
  // We got a collision
  if (p->norm == 0) {
    DeleteListPoint(p);
    return 0;
  }
  // lp_it shows to the first point with bigger norm
  // this is where we will insert the new point
  list_.insert(lp_it, p);
  // Let's reduce now the vectors with bigger norm
  while (lp_it != list_.end()) {
    tmp_lp_it = lp_it;
    lp = *lp_it;
    ++lp_it;
    if (Reduce(lp, p)) {
      list_.erase(tmp_lp_it);
      queue_.push(lp);
    }
  }
  return p->norm;
}

bool GSieve::Start(const mat_ZZ &B) {
  ListPoint* current_point;
  int64 current_norm;
  
  // Loop till you find a short enough vector,
  // or enough collisions.
  // The 0.1 * max_list_size_ + 200 is much more
  // than needed in general so we are almost sure
  // we have found the shortest vector.
   while ((best_sqr_norm_ > goal_sqr_norm_) && 
          (collisions_ < 0.1 * max_list_size_ + 200)) {
    iterations_++;
    max_list_size_ = max(max_list_size_, long(list_.size()));
    // Get next point for reduction
    if (queue_.empty()) {
      current_point = sampler_->Sample();
    } else {
      current_point = queue_.front();
      queue_.pop();
    }
    // Reduce it and put the vectors of the list that
    // need reduction to the queue.
    current_norm = UpdateList(current_point);
    if (current_norm == 0) {
      collisions_++;
    }
    if (current_norm > 0 && current_norm < best_sqr_norm_) {
      best_sqr_norm_ = current_norm;
    }
  }
  if (verbose_) {
    vec_int64 a;
    cout << "Maximum list size = " << max_list_size_ << "\n";
    cout << "Number of iterations = " << iterations_ << "\n";
    cout << "Number of collisions = " << collisions_ << "\n";
  }
  //cout << "Best vector = " << list_.front()->v << "\n";
  cout << list_.front()->v << "\n";
  //cout << "Square norm = " << best_sqr_norm_ << "\n";
  /*ListPoint* myx = NewListPoint(m_);
  VecZZToListPoint(B[0],myx);
  cout<<list_.front()->v[0];
  vec_int64 myy;
  vec_int64 myx;
  //for(int i=0;i<m_;i++)
    //list_.front()->v >> myy;
  myy = list_.front()->v;
  mat_int64 B1;
  B1 = B;
  long int l = LatticeSolve(myx, B1, myy);
  if(l)
  {
    cout << "Answer = " << myx->v << "\n";
  }
  else
  {
    cout << "Solver returned 0" << "\n";
  }*/



  if (best_sqr_norm_ > goal_sqr_norm_)
    return false;
  return true;
}
