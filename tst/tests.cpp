/*
 * tests.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "tests.h"

#include "frame_msg.h"

#include <string.h>
#include <stdio.h>


TEST_F(FrameMessageTest, BufFrameConversion)
{
  const int size = sizeof(FrameMessage);
  char buf[size];

  EXPECT_EQ(0, frame2buf(buf, &mMsg));

  FrameMessage out;
  EXPECT_EQ(0, buf2frame(&out, buf));

  EXPECT_EQ(0, memcmp(&out, &mMsg, size));
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


//void test_frame()
//{
//  FrameMessage msg;
//  msg.start = 123;
//  msg.command = 13;
//  msg.crc = 12;
//  msg.device = 98;
//  msg.value = 1;
//  msg.crc = 0;
//
//  const int size = sizeof(FrameMessage);
//  char buf[size];
//
//  frame2buf(buf, &msg);
//
//  FrameMessage ret;
//  buf2frame(&ret, buf);
//
//  const int res = memcmp(&msg, &ret, size);
//
//  if(res == 0)
//  {
//    printf("correct");
//  }
//  else
//  {
//    printf("failed");
//  }
//}
//
//void test_frame_crc()
//{
//
//  FrameMessage msg;
//  msg.start = 123;
//  msg.command = 13;
//  msg.crc = 12;
//  msg.device = 98;
//  msg.value = 1;
//  msg.crc = 0;
//
//  const int size = sizeof(FrameMessage);
//  char buf[size];
//
//  frame2buf(buf, &msg);
//
//  FrameMessage ret;
//  buf2frame(&ret, buf);
//
////  const int crc = get_crc(&buf);
//
////  printf("crc: %d", crc);
//
//}
