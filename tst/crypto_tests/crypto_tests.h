/*
 * crypto-tests.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef TST_CRYPTO_TESTS_CRYPTO_TESTS_H_
#define TST_CRYPTO_TESTS_CRYPTO_TESTS_H_


#include "crypt/crypto.h"

#include <string.h>
#include <stdio.h>

#include <gtest/gtest.h>

class CryptTest : public ::testing::Test {
public:

  void SetUp( ) override
  {
  }

  void TearDown( ) override
  {
  }

};


#endif /* TST_CRYPTO_TESTS_CRYPTO_TESTS_H_ */
