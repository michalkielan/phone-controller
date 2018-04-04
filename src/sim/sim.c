/**
 * @file sim.c
 *
 * @brief
 *
 * @date 1 Apr 2018
 * @author Michal Kielan
 */


#include "sim/sim.h"


int sim_send_sms(const void* const buffer, const size_t size)
{
  //
  return 0;
}

int sim_receive_sms(void* buffer, const size_t size)
{
  //
  return 0;
}

int sim_send_data(const void* const buffer, const size_t size)
{
  return sim_send_sms(buffer, size);
}

int sim_receive_data(void* buffer, const size_t size)
{
  return sim_receive_sms(buffer, size);
}
