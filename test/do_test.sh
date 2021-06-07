#!/bin/zsh

clang++ -Wall -Wextra -Werror \
		-std=c++98 -pedantic \
		main.cpp \
		test_list.cpp \
		test_vector.cpp \
		test_map.cpp \
		test_stack.cpp \
		test_queue.cpp \
		test_set.cpp \
		test_multimap.cpp \
		test_multiset.cpp \
		-o my_containers
		
clang++ -Wall -Wextra -Werror \
		-std=c++98 -pedantic \
		main.cpp \
		test_list.cpp \
		test_vector.cpp \
		test_map.cpp \
		test_stack.cpp \
		test_queue.cpp \
		test_set.cpp \
		test_multimap.cpp \
		test_multiset.cpp \
		-D STD \
		-o std_containers

./my_containers > my_result
./std_containers > std_result

rm my_containers
rm std_containers

diff my_result std_result

rm my_result
rm std_result