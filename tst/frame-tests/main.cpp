/*
 * main.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */


#include "frame-tests.h"

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
