#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

class Mutex {
private:
  pthread_mutex_t mutex;
  pthread_mutex_t* getMutex();

  Mutex( const Mutex& );
  Mutex& operator= ( const Mutex& );

public:
  Mutex();
  void lock();
  void unlock();
  ~Mutex();
};

#endif
