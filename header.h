#ifndef __HEADER
#define __HEADER

#include<pthread.h>


class CHECKER {
    
public:
    
private:

  pthread_mutex_t _mutex;
  pthread_cond_t full = PTHREAD_COND_INITIALIZER;
  pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
};

#endif

