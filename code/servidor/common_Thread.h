#ifndef _THREAD_H_INCLUDED_
#define _THREAD_H_INCLUDED_

#include <pthread.h>

class Thread {
private:
  pthread_t thread;

protected:
  virtual void run() = 0;

public:
  // Intenta terminar el Thread correctamente.Depende del thread
  // lo mejor es que luego de llamar a tryToStop(), haciendo un join()
  // el thread finalice su ejecución.

  virtual void tryToStop() = 0;

  void start() {
    pthread_create( &thread, NULL, (void* (*)(void*))&go, this );
  }

  void join() {
    pthread_join( this->thread, NULL );
  }

  void cancel() {
	pthread_cancel( this->thread );
  }

  static void go( Thread* working_class ) {
    working_class->run();
  }

};
#endif
