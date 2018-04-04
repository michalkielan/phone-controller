/**
 * @file sim.h
 *
 * @brief Interface for sim module receive/transmit data
 *
 * @date 1 Apr 2018
 * @author Michal Kielan
 */

#ifndef INC_SIM_SIM_H_
#define INC_SIM_SIM_H_

#include <stdio.h>
#include <stdint.h>


int sim_send_sms(void* buffer, const size_t size);
int sim_receive_sms(void* buffer, const size_t size);

int sim_send_data(void* buffer, const size_t size);
int sim_receive_data(void* buffer, const size_t size);


#endif /* INC_SIM_SIM_H_ */
