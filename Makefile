all: test_block_queue test_block_queue_std test_block_queue_boost
		
test_block_queue:
	g++ -g -o test_block_queue test_block_queue.cpp -lpthread

test_block_queue_std:
	g++ -g -o test_block_queue_std test_block_queue_std.cpp -lpthread

test_block_queue_boost:
	g++ -g -I /home/dcj/projects/third-64/boost/include/ \
			test_block_queue_boost.cpp -o test_block_queue_boost \
			-L /home/dcj/projects/third-64/boost/lib/ \
			-lboost_system -lboost_thread -lpthread -lrt

clean:
	rm -rf test_block_queue.o test_block_queue
	rm -rf test_block_queue_std.o test_block_queue_std
	rm -rf test_block_queue_boost.o test_block_queue_boost

