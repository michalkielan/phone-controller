/*
 * main.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */


#include "tests.h"

int main(int argc, char **argv) {

  FrameMessage msg;
  msg.start = 34153;
  msg.device = 4311;
  msg.command = 55704;
  msg.value = 23981;

  set_crc(&msg);
  set_crc(&msg);
  set_crc(&msg);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
