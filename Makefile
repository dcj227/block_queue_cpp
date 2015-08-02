all: test_block_queue

test_block_queue: test_block_queue.o
	g++ -g -o test_block_queue test_block_queue.cpp -lpthread

clean:
	rm -rf block_queue.o block_queue
