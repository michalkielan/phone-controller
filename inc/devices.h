/*
 * devices.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_DEVICES_H_
#define INC_DEVICES_H_


extern int (*set_get_device_data[]) (const int in, const int* const out);


void init_devices();

#endif /* INC_DEVICES_H_ */
