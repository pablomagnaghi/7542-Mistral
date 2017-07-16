#include "common_Mutex.h"

#include <pthread.h>

pthread_mutex_t* Mutex::getMutex() {
  return &mutex;
}

Mutex::Mutex() {
  pthread_mutex_init( &mutex, NULL );
}

void Mutex::lock() {
  pthread_mutex_lock(&mutex);
}

void Mutex::unlock() {
  pthread_mutex_unlock(&mutex);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&mutex);
}
