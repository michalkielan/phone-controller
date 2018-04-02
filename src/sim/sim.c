/*
 * sim.c
 *
 *  Created on: Apr 1, 2018
 *      Author: Michal Kielan
 */


#include "sim/sim.h"


static PhoneNumber supervisor;

typedef struct
{
  unsigned int id;
  PhoneNumber number;
} AvailablePhonesVector;



int sim_add_number(const PhoneNumber number)
{

}


int sim_remove_number(const PhoneNumber number)
{

}


void sim_set_supervisor(const PhoneNumber number)
{
  supervisor = number;
}

int sim_send_sms(void* buffer, const size_t size)
{

}

int sim_receive_sms(void* buffer, const size_t size)
{

}
