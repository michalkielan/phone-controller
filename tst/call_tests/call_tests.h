/*
 * call-tests.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef TST_CALL_TESTS_CALL_TESTS_H_
#define TST_CALL_TESTS_CALL_TESTS_H_


#include "logger/logger.h"

#include <string.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include <io_controller.h>

class CallFunctionTest : public ::testing::Test {
public:

  void SetUp( ) override
  {
    set_log_level(LOG_NONE);
  }

  void TearDown( ) override
  {
  }

};


#endif /* TST_CALL_TESTS_CALL_TESTS_H_ */
