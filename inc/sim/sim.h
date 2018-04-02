/*
 * sim.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_SIM_SIM_H_
#define INC_SIM_SIM_H_

#include <stdio.h>
#include <stdint.h>

typedef enum
{
  Polad = 48,
} CallCode;

typedef struct
{
  CallCode code;
  uint8_t  phone_number[9];

} PhoneNumber;


int sim_set_supervisor(const PhoneNumber phoneNumber);

int sim_send_sms(void* buffer, const size_t size);
int sim_receive_sms(void* buffer, const size_t size);

int sim_send_data(void* buffer, const size_t size);
int sim_receive_data(void* buffer, const size_t size);


#endif /* INC_SIM_SIM_H_ */
