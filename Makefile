
THIRD_64 = /home/dcj/projects/thrid-64/


all: test_block_queue test_block_queue_std test_block_queue_boost

test_block_queue: test_block_queue.o
	g++ -g -o test_block_queue test_block_queue.cpp -lpthread

test_block_queue_std: test_block_queue_std.o
	g++ -g -o test_block_queue_std test_block_queue_std.cpp -lpthread

test_block_queue_boost: test_block_queue_boost.o
	g++ -g -o test_block_queue_boost test_block_queue_boost.cpp \
			-I"/home/dcj/projects/third-64/boost/include" \
			-L"/home/dcj/projects/third-64/boost/lib" \
			-lboost_system.a -lboost_thread.a

clean:
	rm -rf test_block_queue.o test_block_queue
	rm -rf test_block_queue_std.o test_block_queue_std
	rm -rf test_block_queue_boost.o test_block_queue_boost

