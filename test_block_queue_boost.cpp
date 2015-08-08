/***********************************************************************
 * Author :          dingchangjiang
 * Email :           dcj227@163.com
 * Last modified : 2015-08-06 23:55
 * Filename : test_block_queue_boost.cpp
 * Description : 
 * *********************************************************************/

#include <pthread.h>

#include <iostream>

#include "block_queue_boost.hpp"

BlockQueue<int> g_queue;

void *p(void *args) {
  sleep(1);
  int data = 0;
  for (int i = 0; i < 100; ++i) {
    g_queue.push(data++);
  }
  return NULL;
}

void *c(void *args) {
  while(true) {
    int t = 0;
    if (g_queue.pop(&t, 1000) != 0) {
      std::cout << "timeout" << std::endl;
      continue;
    } else {
      std::cout << t << std::endl;
    }
    g_queue.pop(&t);
    std::cout << "block=" << t << std::endl;
  }
  return NULL;
}

int main() {
  pthread_t id;
  pthread_create(&id, NULL, p, NULL);
  // pthread_create(&id, NULL, p, NULL);
  // pthread_create(&id, NULL, c, NULL);
  pthread_create(&id, NULL, c, NULL);
  for ( ; ; ) {
    sleep(1);
  }
  return 0;
}
