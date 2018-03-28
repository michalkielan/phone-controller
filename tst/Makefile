SRC_DIR=../src/
INC_DIR=../inc/

SRC=
SRC+=$(wildcard $(SRC_DIR)/*.c)
SRC+=$(wildcard $(SRC_DIR)/crypt/*.c)
SRC+=$(wildcard $(SRC_DIR)/frame/*.c)

INC=${INC_DIR}

SANITIZERS=
#SANITIZERS+=-fsanitize=address

CFLAGS=-Wall -g -ggdb3 -O2 

CXXFLAGS=-std=c++11 ${SANITIZERS}

FLAGS=${CFLAGS} ${CXXFLAGS}

LINK=-lgtest
LINK+=${SANITIZERS}

TESTS=
TESTS+=frame_tests_tst
TESTS+=crypto_tests_tst
TESTS+=call_tests_tst


test: ${TESTS}


TEST_FRAME=frame_tests
TEST_FRAME_DIR=${TEST_FRAME}/
TEST_FRAME_SRC=$(wildcard $(TEST_FRAME_DIR)/*.cpp)

frame_tests_tst:
	${CXX} ${TEST_FRAME_SRC} ${SRC} ${FLAGS} -I${INC} -o run_${TEST_FRAME}_tst ${LINK}
		
TEST_CRYPT=crypto_tests
TEST_CRYPT_DIR=${TEST_CRYPT}/
TEST_CRYPT_SRC=$(wildcard $(TEST_CRYPT_DIR)/*.cpp)

crypto_tests_tst:
	${CXX} ${TEST_CRYPT_SRC} ${SRC} ${FLAGS} -I${INC} -o run_${TEST_CRYPT}_tst ${LINK}

TEST_CALL=call_tests
TEST_CALL_DIR=${TEST_CALL}/
TEST_CALL_SRC=$(wildcard $(TEST_CALL_DIR)/*.cpp)

call_tests_tst:
	${CXX} ${TEST_CALL_SRC} ${SRC} ${FLAGS} -I${INC} -o run_${TEST_CALL}_tst ${LINK}
		
run-tests:
	$(foreach var,$(TESTS),./run_${var};)
	
clean:
	rm -rf run_*

