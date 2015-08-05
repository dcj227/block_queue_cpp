all: test_block_queue test_block_queue_std

test_block_queue: test_block_queue.o
	g++ -g -o test_block_queue test_block_queue.cpp -lpthread

test_block_queue_std: test_block_queue_std.o
	g++ -g -o test_block_queue_std test_block_queue_std.cpp -lpthread

clean:
	rm -rf test_block_queue.o test_block_queue
	rm -rf test_block_queue_std.o test_block_queue_std

