/*
 * devices.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include <string.h>

/**
 * @brief Maximum number of each device
 *
 */
static const int devices_max = 10;

/**
 * @brief Arrays of function pointers to set/get data from the
 *        devices.
 *
 * \param [in] data to set
 * \param [in] data to get
 */
int (*set_get_device_data[devices_max]) (const int in, const int* const out);


/**
 * @brief Check if function pointer is valid
 *
 * \param [in] device id
 *
 * return 0 on sucess, otherwie 1
 */
int checkDeviceValid(const int device_id)
{
  if(set_get_device_data[device_id] == NULL || device_id >= devices_max)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void init_devices()
{
  for(unsigned int i=0; i<devices_max; i++)
  {
    set_get_device_data[i] = NULL;
  }

}
