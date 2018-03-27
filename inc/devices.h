/*
 * devices.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_DEVICES_H_
#define INC_DEVICES_H_


/**
 * @brief Arrays of callbacks to set/get data from the i/o
 *
 * \param [in] data to set
 * \param [in] data to get
 */
extern int (*io_call[]) (const int input, int* output);


/**
 * @brief Check if function pointer is valid
 *
 * \param [in] device id
 *
 * return 0 on sucess, otherwie 1
 */
int io_check_valid(const int io_id);


/**
 * @brief Init callbacks to NULL
 *
 */
void io_init();


#endif /* INC_DEVICES_H_ */
