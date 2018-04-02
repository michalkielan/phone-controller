/*
 * devices.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_DEVICES_H_
#define INC_DEVICES_H_

#include <string.h>

/**
 * @brief Typedef for callbacks to set/get data from the i/o
 *
 * \param [in] data pointer
 * \param [in] data size
 */
typedef int (*IoCallback)(void* data, const size_t size);


/**
 * @brief Create task to controll io device, it dynamically allocate
 *        vector of function pointers, the reallocations happens
 *        automatically when there is no place for new elements
 *
 * \param [in] function pointer
 *
 * \return 0 on sucess, error code otherwise
 * - ENOMEM when out of memory
 */
int io_add_task(const IoCallback io_callback);


/**
 * @brief Call io controller function
 *
 * \param [in] index
 * \param [in] input value
 * \param [out] output value
 *
 * \return
 */
int io_call_task(const size_t index, void* data, const size_t size);


/**
 * @brief Free io vector and reset the index value
 */
void io_free();



#endif /* INC_DEVICES_H_ */
