SRC_DIR=../src/
INC_DIR=../inc/

SRC=
SRC+=${SRC_DIR}frame_msg.c
SRC+=${SRC_DIR}crypt_xor.c
SRC+=${SRC_DIR}crypto.c

INC=${INC_DIR}

CFLAGS=-Wall -g -ggdb3 -O2
CXXFLAGS=-std=c++11

LINK=-lgtest


all: frame_tests crypto_tests


TEST_FRAME_DIR=frame-tests/
TEST_FRAME_SRC=
TEST_FRAME_SRC+=${TEST_FRAME_DIR}frame-tests.cpp
TEST_FRAME_SRC+=${TEST_FRAME_DIR}main.cpp

frame_tests:
	${CXX} ${TEST_FRAME_SRC} ${SRC} ${CXXFLAGS} ${CFLAGS} -I${INC} -o run-frame_tests ${LINK}
	
	
TEST_CRYPT_DIR=crypto-tests/
TEST_CRYPT_SRC=
TEST_CRYPT_SRC+=${TEST_CRYPT_DIR}crypto-tests.cpp
TEST_CRYPT_SRC+=${TEST_CRYPT_DIR}main.cpp

crypto_tests:
	${CXX} ${TEST_CRYPT_SRC} ${SRC} ${CXXFLAGS} ${CFLAGS} -I${INC} -o run-crypto_tests ${LINK}

