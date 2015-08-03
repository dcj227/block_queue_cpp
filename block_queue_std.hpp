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

  /*
   *
   */
  int init() {
    int ret = -1;
    ret = pthread_mutex_init(&mutex_, NULL);
    if (ret != 0) {
      return -1;
    }
    ret = pthread_cond_init(&cond_, NULL);
    if (ret != 0) {
      pthread_mutex_destory(&mutex);   
      return -1;
    }
    return 0;
  }

  int push(const T& item) {
    if (pthread_mutex_lock(&mutex) != 0) {
      return -1;
    }
    queue_.push(item); 
    //if (queue_.size() == 1) {
    //  pthread_cond_broadcast(cond_);
    //}
    if (pthread_cond_broadcast(cond_) != 0) {
      return -1;
    }
    if (pthread_mutex_unlock(&mutex) != 0) {
      return 
    }
    return 0;
  }
  int pop(const T* item) {
    return 0;
  }
 private:
  pthread_mutex_t   mutex_;
  pthread_cond_t    cond_;
  std::queue<T>     queue_;
};

#endif  // BLOCK_QUEUE_STD_HPP 
