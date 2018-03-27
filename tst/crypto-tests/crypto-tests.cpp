/*
 * crypto-tests.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "crypto-tests.h"

#include "crypto.h"

static const unsigned int bufferLimit = 64;
static const unsigned int iterations = 2000000;

TEST_F(CryptTest, CryptDataTest)
{
  const char* buf_in = "abcdefghijklmn";
  const unsigned int N = strlen(buf_in);

  char buf_crypt[N];
  char buf_out[N];

  EXPECT_EQ(0, encrypt(buf_crypt, buf_in, N));
  EXPECT_EQ(0, decrypt(buf_out, buf_crypt, N));
  EXPECT_EQ(0, memcmp(buf_in, buf_out, N));
}


TEST_F(CryptTest, CryptNullTest)
{
  const char* buf_in = "abcdefghijklmn";
  const unsigned int N = strlen(buf_in);

  char buf_crypt[N];
  char buf_out[N];

  EXPECT_NE(0, encrypt(NULL, buf_in, N));
  EXPECT_NE(0, encrypt(buf_crypt, NULL, N));
  EXPECT_NE(0, encrypt(NULL, NULL, N));

  EXPECT_NE(0, decrypt(NULL, buf_crypt, N));
  EXPECT_NE(0, decrypt(buf_out, NULL, N));
  EXPECT_NE(0, decrypt(NULL, NULL, N));
}

TEST_F(CryptTest, CryptDataBufferTooBig)
{
  const unsigned int N = 80;

  std::vector<unsigned char> buf_in;
  std::vector<unsigned char> buf_crypt;
  std::vector<unsigned char> buf_out;

  buf_in.resize(N);
  buf_crypt.resize(N);
  buf_out.resize(N);

  for(auto& el : buf_in)
  {
    el = rand() % 0xFF;
  }

  EXPECT_EQ(0, encrypt(buf_crypt.data(),buf_in.data(), bufferLimit-1));
  EXPECT_EQ(0, decrypt(buf_out.data(), buf_crypt.data(), bufferLimit-1));
  EXPECT_EQ(0, memcmp(buf_in.data(), buf_out.data(), bufferLimit-1));

  EXPECT_EQ(0, encrypt(buf_crypt.data(),buf_in.data(), bufferLimit));
  EXPECT_EQ(0, decrypt(buf_out.data(), buf_crypt.data(), bufferLimit));
  EXPECT_EQ(0, memcmp(buf_in.data(), buf_out.data(), bufferLimit));

  EXPECT_NE(0, encrypt(buf_crypt.data(),buf_in.data(), bufferLimit+1));
  EXPECT_NE(0, decrypt(buf_out.data(), buf_crypt.data(), bufferLimit+1));
}

TEST_F(CryptTest, CryptDataRandom)
{
  const unsigned int N = bufferLimit - 1;

  std::vector<unsigned char> buf_in;
  std::vector<unsigned char> buf_crypt;
  std::vector<unsigned char> buf_out;

  buf_in.resize(N);
  buf_crypt.resize(N);
  buf_out.resize(N);

  for(auto& el : buf_in)
  {
    el = rand() % 0xFF;
  }

  unsigned int i=0;
  while(++i < iterations)
  {
    for(auto& el : buf_in)
    {
      el = rand() % 0xFF;
    }

    EXPECT_EQ(0, encrypt(buf_crypt.data(),buf_in.data(), N));
    EXPECT_EQ(0, decrypt(buf_out.data(), buf_crypt.data(), N));
    EXPECT_EQ(0, memcmp(buf_in.data(), buf_out.data(), N));

    std::fill(buf_in.begin(),    buf_in.end(),    0);
    std::fill(buf_crypt.begin(), buf_crypt.end(), 0);
    std::fill(buf_out.begin(),   buf_out.end(),   0);
  }
}




