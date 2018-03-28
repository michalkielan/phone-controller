SRC_DIR=../src/
INC_DIR=../inc/

SRC=
SRC+=${SRC_DIR}frame_msg.c
SRC+=${SRC_DIR}crypt_xor.c
SRC+=${SRC_DIR}crypto.c
SRC+=${SRC_DIR}devices.c

INC=${INC_DIR}

CFLAGS=-Wall -g -ggdb3 -O2 
#-fsanitize=address
CXXFLAGS=-std=c++11

LINK=-lgtest


all: frame_tests crypto_tests call_tests


TEST_FRAME=frame-tests
TEST_FRAME_DIR=${TEST_FRAME}/
TEST_FRAME_SRC=
TEST_FRAME_SRC+=${TEST_FRAME_DIR}frame-tests.cpp
TEST_FRAME_SRC+=${TEST_FRAME_DIR}main.cpp

frame_tests:
	${CXX} ${TEST_FRAME_SRC} ${SRC} ${CXXFLAGS} ${CFLAGS} -I${INC} -o run-${TEST_FRAME} ${LINK}
	
	
TEST_CRYPT=crypto-tests
TEST_CRYPT_DIR=${TEST_CRYPT}/
TEST_CRYPT_SRC=
TEST_CRYPT_SRC+=${TEST_CRYPT_DIR}crypto-tests.cpp
TEST_CRYPT_SRC+=${TEST_CRYPT_DIR}main.cpp

crypto_tests:
	${CXX} ${TEST_CRYPT_SRC} ${SRC} ${CXXFLAGS} ${CFLAGS} -I${INC} -o run-${TEST_CRYPT} ${LINK}

TEST_CALL=call-tests
TEST_CALL_DIR=${TEST_CALL}/
TEST_CALL_SRC=
TEST_CALL_SRC+=${TEST_CALL_DIR}call-tests.cpp
TEST_CALL_SRC+=${TEST_CALL_DIR}main.cpp

call_tests:
	${CXX} ${TEST_CALL_SRC} ${SRC} ${CXXFLAGS} ${CFLAGS} -I${INC} -o run-${TEST_CALL} ${LINK}

