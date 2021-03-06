/***********************************************************************
 * Author :          dingchangjiang
 * Email :           dcj227@163.com
 * Last modified :   2015-08-07 20:52
 * Filename :        block_queue_boost.hpp
 * Description :     
 * *********************************************************************/

#ifndef BLOCK_QUEUE_BOOST_HPP
#define BLOCK_QUEUE_BOOST_HPP

#include <sys/time.h>

#include <assert.h>
#include <queue>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

template<class T>
class BlockQueue {
 public: 
  BlockQueue() {
  }

  ~BlockQueue() {
  }

  int push(const T& item) {
    {
      boost::mutex::scoped_lock lock(queue_mutex_);
      queue_.push(item);
    }
    queue_cond_.notify_one();
    return 0;
  }

  int pop(T* item) {
    assert(item);
    boost::mutex::scoped_lock lock(queue_mutex_);
    if (!queue_.empty()) {
      (*item) = queue_.front();
      queue_.pop();
    } else {
      queue_cond_.wait(lock);

      (*item) = queue_.front();
      queue_.pop();
    }
    return 0;
  }

  int pop(T* item, int timeout_ms) {
    assert(item);
    boost::mutex::scoped_lock lock(queue_mutex_);
    if (!queue_.empty() || 
        queue_cond_.timed_wait(
            lock,
            boost::get_system_time()
            + boost::posix_time::seconds(timeout_ms))) {
      (*item) = queue_.front();
      queue_.pop();
      return 0;
    } else {
      return -1;
    }
  }

 private:
  boost::condition_variable queue_cond_;
  boost::mutex      queue_mutex_;
  std::queue<T>     queue_;
};

#endif  // BLOCK_QUEUE_BOOST_HPP
