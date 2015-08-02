/*******************************************************************************
 * Author :          dingchangjiang
 * Email :           dcj227@163.com
 * Last modified : 2015-08-02 22:01
 * Filename : test_block_queue.cpp
 * Description : 
 * *****************************************************************************/

#include <iostream>

#include "block_queue.hpp"

block_queue<int> g_queue(100);

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
    if (!g_queue.pop(t, 1000)) {
      std::cout << "timeout" << std::endl;
      continue;
    } else {
      std::cout << t << std::endl;
    }
    g_queue.pop(t);
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

