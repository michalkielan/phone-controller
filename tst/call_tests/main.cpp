/*
 * main.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */


#include "call_tests.h"

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
