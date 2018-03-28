/*
 * call-tests.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */


#include "call-tests.h"

#include "devices.h"


static const int value_set = 1554;
static const int value_get = 5225;

int set_io_0(const int input, int* output)
{
  if(input == value_set)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int get_io_1(const int input, int* output)
{
  (void)input;

  if(output != NULL)
  {
    output = value_get;
    return 0;
  }
  else
  {
    return 1;
  }
}


TEST_F(CallFunctionTest, test)
{
  const int dev_io_0 = 0;
  const int dev_io_1 = 1;

  io_call[dev_io_0] = set_io_0;
  io_call[dev_io_1] = get_io_1;


  EXPECT_EQ(0, io_call[dev_io_0](value_set, NULL));

  int get_val = 0;
  EXPECT_EQ(0, io_call[dev_io_0](0, &get_val));
  EXPECT_EQ(value_get, get_val);

}
