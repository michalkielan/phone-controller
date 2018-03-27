/*
 * call-tests.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */


#include "call-tests.h"

#include "devices.h"


int setIO_device_1(const int in, const int* const out)
{
  std::cout << "IO device 1: " << in << std::endl;
  return 0;
}



TEST_F(CallFunctionTest, test)
{
  init_devices();
  const int dev_led_1 = 0;

  set_get_device_data[dev_led_1] = setIO_device_1;

  set_get_device_data[dev_led_1](3, NULL);

}
