/*
 * tests.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "tests.h"

#include "frame_msg.h"

#include <string.h>
#include <stdio.h>
#include <random>


const unsigned int iterations = 2000000;

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
  FrameMessage msg;
  const uint16_t max = 0xFFFF;

  unsigned int i=0;

  const int size = sizeof(FrameMessage);
  char buf[size];

  while(++i < iterations)
  {
    for(int i=0; i<size; i++)
    {
      buf[i] = rand()%0xFF;
    }

    FrameMessage l, r;
    EXPECT_EQ(0, frame2buf(buf, &l));
    EXPECT_EQ(0, buf2frame(&r, buf));
    EXPECT_EQ(0, memcmp(&l, &r, size));
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

TEST_F(FrameMessageTest, ChecksumTest)
{
  EXPECT_NE(0, set_crc(NULL));
  EXPECT_NE(0, get_crc(NULL));
  EXPECT_NE(0, check_crc(NULL));

  EXPECT_EQ(0, set_crc(&mMsg));
  EXPECT_EQ(0, check_crc(&mMsg));
  EXPECT_GE(get_crc(&mMsg), 0);
  EXPECT_EQ(get_crc(&mMsg), get_crc(&mMsg));

  FrameMessage msg;
  memset(&msg, 0, sizeof(FrameMessage));
  EXPECT_EQ(get_crc(&msg), 0);
}

TEST_F(FrameMessageTest, ChecksumRandom)
{
  FrameMessage msg;
  const uint16_t max = 0xFFFF;

  unsigned int i=0;

  const int size = sizeof(FrameMessage);
  char buf[size];

  while(++i < iterations)
  {
    for(int i=0; i<size; i++)
    {
      buf[i] = rand()%0xFF;
    }

    FrameMessage msg;
    ASSERT_NE(0, buf2frame(&msg, buf));
    ASSERT_EQ(0, set_crc(&msg));
    ASSERT_EQ(0, check_crc(&msg));
    ASSERT_GE(get_crc(&msg), 0);
    ASSERT_EQ(get_crc(&msg), get_crc(&msg));
  }
}




