SRC=*.c
SRC=*.cpp
SRC+=../src/frame_msg.c

INC=../inc/

all:
	${CXX} -std=c++11 main.cpp tests.cpp ../src/frame_msg.c -I${INC} -o run-tests -lgtest
