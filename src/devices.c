/*
 * devices.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include <string.h>

/**
 * @brief Maximum number of devices
 *
 */
static const int io_max = 10;

/**
 * @brief Arrays of callbacks to set/get data from the i/o
 *
 * \param [in] data to set
 * \param [in] data to get
 */
int (*io_call[io_max]) (const int input, int* output);


/**
 * @brief Check if function pointer is valid
 *
 * \param [in] device id
 *
 * return 0 on sucess, otherwie 1
 */
int io_check_valid(const int io_id)
{
  if(io_call[io_id] == NULL || io_id >= io_max)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void i()
{
  for(unsigned int i=0; i<io_max; i++)
  {
    io_call[i] = NULL;
  }
}
