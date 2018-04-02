/*
 * call-tests.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */


#include "call_tests.h"

#include "devices.h"
#include "frame/frame_encrypt.h"
#include "frame/frame_msg.h"

#include <vector>

static const unsigned int iterations = 100000;

class Led
{
  static bool state;

public:

  static int set(const int input, int* output)
  {
    state = input;
    return 0;
  }

  static int get(const int input, int* output)
  {
    *output = state;
    return 0;
  }
};

bool Led::state = 0;


TEST_F(CallFunctionTest, ledBlinking)
{
  const int led_set = io_add_task(&Led::set);
  const int led_get = io_add_task(&Led::get);

  for(int i=0; i<100; i++)
  {
    static int led_status = 0;
    EXPECT_EQ(0, io_call_task(led_get, 0, &led_status));
    EXPECT_EQ(0, io_call_task(led_set, !led_status, NULL));
  }

  io_free();
}

int fun(const int input, int* output)
{
  *output = input;
  return input;
}

TEST_F(CallFunctionTest, initManyFunctions)
{
  std::vector<int> ids;
  for(unsigned int i=0; i<iterations; i++)
  {
    const int id = io_add_task(&fun);
    ASSERT_GE(id, 0);

    ids.push_back(id);
  }

  for(unsigned int i=0; i< ids.size(); i++)
  {
    int get_val = 0;
    EXPECT_EQ(i, io_call_task(i, i, &get_val));
    EXPECT_EQ(get_val, i);
  }

  io_free();
}


void led_set(const bool state) {}

int led_set_io(const int in, int* out)
{
  (void)out;
  led_set(in);
  return 0;
}

TEST_F(CallFunctionTest, test)
{
  const int id = io_add_task(&led_set_io);

  /// buffer from reader
  FrameMessage msg;
  msg.start = StartCode;
  msg.device = id;
  msg.command = Set;
  msg.value = 1;
  set_crc(&msg);

  char buffer[sizeof(msg)];

  frame2buf(buffer, &msg);


}


















