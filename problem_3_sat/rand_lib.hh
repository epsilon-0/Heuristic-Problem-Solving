#ifndef RAND_LIB_
#define RAND_LIB_

#include <time.h>

using namespace std;

unsigned int i_rand(unsigned int range) {

  if (range == 0) {
    return 0;
  }

  unsigned int x = (RAND_MAX + 1u) / range;
  unsigned int y = x * range;
  unsigned int r;

  do {
    r = rand();
  } while (r >= y);

  return (r / x);
}

// Function returning a pseudo-random float number in [0, 1).

float f_rand() { return ((float)rand()) / ((float)RAND_MAX + 1.0); }

#endif
