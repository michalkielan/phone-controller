/*
 * tests.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "frame_tests.h"
#include "frame/frame_msg.h"

#include <string.h>
#include <stdio.h>
#include <random>

static const unsigned int iterations = 2000000;

TEST_F(FrameMessageTest, BufFrameConversion)
{
  const int size = sizeof(FrameMessage);
  char buf[size];

  EXPECT_EQ(0, frame2buf(buf, &mMsg));

  FrameMessage out;
  EXPECT_EQ(0, buf2frame(&out, buf));
  EXPECT_EQ(0, memcmp(&out, &mMsg, size));
}

TEST_F(FrameMessageTest, BufFrameConversionRandom)
{
  const int size = sizeof(FrameMessage);
  char buf[size];

  unsigned int i=0;
  while(++i < iterations)
  {
    for(int i=0; i<size; i++)
    {
      buf[i] = rand()%0xFF;
    }

    FrameMessage lhs, rhs;
    ASSERT_EQ(0, frame2buf(buf, &lhs));
    ASSERT_EQ(0, buf2frame(&rhs, buf));
    ASSERT_EQ(0, memcmp(&lhs, &rhs, size));
  }
}


TEST_F(FrameMessageTest, BufFrameNullCheck)
{
  const int size = sizeof(FrameMessage);
  char buf[size];

  EXPECT_NE(0, frame2buf(NULL, &mMsg));
  EXPECT_NE(0, frame2buf(buf, NULL));
  EXPECT_NE(0, frame2buf(NULL, NULL));

  EXPECT_NE(0, buf2frame(NULL, buf));
  EXPECT_NE(0, buf2frame(&mMsg, NULL));
  EXPECT_NE(0, buf2frame(NULL, NULL));
}

TEST_F(FrameMessageTest, ChecksumNullTest)
{
  EXPECT_NE(0, set_crc(NULL));
  EXPECT_NE(0, get_crc(NULL));
  EXPECT_NE(0, check_crc(NULL));

  EXPECT_EQ(0, set_crc(&mMsg));
  EXPECT_EQ(0, check_crc(&mMsg));
  EXPECT_GE(get_crc(&mMsg), 0);
  EXPECT_EQ(get_crc(&mMsg), get_crc(&mMsg));
}

TEST_F(FrameMessageTest, ChecksumSameNumTest)
{
  FrameMessage msg;
  for(uint8_t i=0; i<0xFF; i++)
  {
    memset(&msg, i, sizeof(FrameMessage));
    EXPECT_EQ(get_crc(&msg), 0);
  }
}

TEST_F(FrameMessageTest, ChecksumRandom)
{
  const int size = sizeof(FrameMessage);
  char buf[size];

  unsigned int i=0;
  while(++i < iterations)
  {
    for(int i=0; i<size; i++)
    {
      buf[i] = rand()%0xFF;
    }

    FrameMessage msg;
    ASSERT_EQ(0, buf2frame(&msg, buf));
    ASSERT_EQ(0, set_crc(&msg));
    ASSERT_EQ(0, set_crc(&msg));
    ASSERT_EQ(0, set_crc(&msg));
    ASSERT_EQ(0, set_crc(&msg));
    ASSERT_EQ(0, set_crc(&msg));
    ASSERT_EQ(0, check_crc(&msg));
    ASSERT_GE(get_crc(&msg), 0);
    ASSERT_EQ(get_crc(&msg), get_crc(&msg));
  }
}




