/*
 * tests.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "frame/frame_msg.h"

#include <string.h>
#include <stdio.h>

#include <gtest/gtest.h>

class FrameMessageTest : public ::testing::Test {
public:

	FrameMessage mMsg;
	char         mBuf[sizeof(FrameMessage)];

	void SetUp( ) override
	{
	  mMsg.start = 123;
	  mMsg.command = 13;
	  mMsg.crc = 12;
	  mMsg.device = 98;
	  mMsg.data = 1;
	  mMsg.crc = 0;
	}

	void TearDown( ) override
	{
	}

};
