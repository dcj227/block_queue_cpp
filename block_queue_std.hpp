/*******************************************************************************
 * Author :          dingchangjiang
 * Email :           dcj227@163.com
 * Last modified : 2015-08-03 21:37
 * Filename : block_queue_std.hpp
 * Description : implement block queue using std::queue. 
 * *****************************************************************************/

#ifndef BLOCK_QUEUE_STD_HPP
#define BLOCK_QUEUE_STD_HPP

#include <pthread.h>
#include <sys/time.h>

#include <assert.h>
#include <queue>

template<class T>
class BlockQueue {
 public:
  BlockQueue() {
  }

  ~BlockQueue() {
  }

  int init() {
    int ret = -1;
    ret = pthread_mutex_init(&mutex_, NULL);
    if (ret != 0) {
      return -1;
    }
    ret = pthread_cond_init(&cond_, NULL);
    if (ret != 0) {
      pthread_mutex_destroy(&mutex_);
      return -1;
    }
    return 0;
  }

  int clean() {
    int ret_mutex = pthread_mutex_destroy(&mutex_);
    int ret_cond = pthread_cond_destroy(&cond_);
    return (ret_mutex | ret_cond) != 0 ? -1 : 0;
  }

  int push(const T& item) {
    if (pthread_mutex_lock(&mutex_) != 0) {
      return -1;
    }

    queue_.push(item); 

    // we havn't to deal with failed return, since either success
    // or fail the followed code should been executed at all.
    pthread_cond_broadcast(&cond_);

    if (pthread_mutex_unlock(&mutex_) != 0) {
      return -1;
    }

    return 0;
  }

  int pop(T* item) {
    assert(item);
    if (pthread_mutex_lock(&mutex_) != 0) {
      return -1;
    }

    /*
    if (!queue_.empty()) {
      (*item) = queue_.front();
      queue_.pop();
    } else {
      if (pthread_cond_wait(&cond_, &mutex_) == 0) {
        (*item) = queue_.front();
        queue_.pop();
      }
    }
    */

    if (!queue_.empty() || pthread_cond_wait(&cond_, &mutex_) == 0) {
      pthread_mutex_unlock(&mutex_);
      (*item) = queue_.front();
      queue_.pop();
    }

    if (pthread_mutex_unlock(&mutex_) != 0) {
      return -1;
    }

    return 0;
  }

  int pop(T* item, int timeout_ms) {
    assert(item);
    struct timespec t = {0, 0};
    struct timeval now = {0, 0};
    gettimeofday(&now, NULL); 
    t.tv_sec = now.tv_sec + timeout_ms / 1000;
    t.tv_nsec = (timeout_ms % 1000) * 1000;

    if (pthread_mutex_lock(&mutex_) != 0) {
      return -1;
    }

    if (!queue_.empty()
        || pthread_cond_timedwait(&cond_, &mutex_, &t) == 0) {
      pthread_mutex_unlock(&mutex_);
      (*item) = queue_.front();
      queue_.pop();
    }

    if (pthread_mutex_unlock(&mutex_) != 0) {
      return -1;
    }

    return 0;
  }

 private:
  BlockQueue(const BlockQueue& queue);
  BlockQueue& operator=(const BlockQueue& queue);

  pthread_mutex_t   mutex_;
  pthread_cond_t    cond_;
  std::queue<T>     queue_;
};

#endif  // BLOCK_QUEUE_STD_HPP 
