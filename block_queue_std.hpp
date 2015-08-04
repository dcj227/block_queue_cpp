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

#include <queue>

template<class T>
class BlockQueueStd {
 public:
  BlockQueueStd() {
  }

  ~BlockQueueStd() {
    pthread_mutex_destory(&mutex_);
    pthread_cond_destory(&cond_);
  }

  int init() {
    int ret = -1;
    ret = pthread_mutex_init(&mutex_, NULL);
    if (ret != 0) {
      return -1;
    }
    ret = pthread_cond_init(&cond_, NULL);
    if (ret != 0) {
      pthread_mutex_destory(&mutex_);   
      return -1;
    }
    return 0;
  }

  int push(const T& item) {
    if (pthread_mutex_lock(&mutex_) != 0) {
      return -1;
    }

    queue_.push(item); 

    // we havn't to deal with failed return, since either success
    // or fail the followed code should been executed at all.
    // pthread_cond_broadcast(cond_);

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
    (*item) = queue_.front();
    queue_.pop();

    if (pthread_mutex_unlock(&mutex) != 0) {
      return -1;
    }

    return 0;
  }
  
  int pop(T* item, int timeout_ms) {
    return 0;
  }

 private:
  pthread_mutex_t   mutex_;
  pthread_cond_t    cond_;
  std::queue<T>     queue_;
};

#endif  // BLOCK_QUEUE_STD_HPP 
