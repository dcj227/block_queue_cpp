/***********************************************************************
 * Author :          dingchangjiang
 * Email :           dcj227@163.com
 * Last modified : 2015-08-05 22:32
 * Filename : test_block_queue_std.cpp
 * Description : 
 * *********************************************************************/

#include <iostream>

#include "block_queue_std.hpp"

BlockQueueStd<int> g_queue;

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
  g_queue.init();

  pthread_t id;
  pthread_create(&id, NULL, p, NULL);
  // pthread_create(&id, NULL, p, NULL);
  // pthread_create(&id, NULL, c, NULL);
  pthread_create(&id, NULL, c, NULL);
  for ( ; ; ) {
    sleep(1);
  }

  g_queue.clean();
  return 0;
}
