/**
 * @file io_controller.h
 *
 * @brief Interface to control io devices
 *
 * @date 31 Mar Sep 2018
 * @author Michal Kielan
 */

#ifndef INC_IO_CONTROLLER_H_
#define INC_IO_CONTROLLER_H_

#include <string.h>

/**
 * @brief Typedef for callbacks to set/get data from the i/o
 *
 * @param [in] data to set
 * @param [in] data to get
 */
typedef int (*IoCallback)(const int input, int* output);


/**
 * @brief Create task to controll io device, it dynamically allocate
 *        vector of function pointers, the reallocations happens
 *        automatically when there is no place for new elements
 *
 * @param [in] function pointer
 *
 * @return 0 on sucess, error code otherwise
 *   -ENOMEM when out of memory
 */
int io_add_task(const IoCallback io_callback);


/**
 * @brief Get size of callback vector in number of elements
 *
 * @return size of vector (the same as v.size() in c++)
 */
size_t io_get_size();


/**
 * @brief Call io controller function
 *
 * @param [in] index
 * @param [in] input value
 * @param [out] output value
 *
 * @return
 */
int io_call_task(const size_t index, const int input, int* output);


/**
 * @brief Remove element of vector,
 *        be careful this function is expensive because it copy
 *        the whole vector and the all of the old indexes are invalid
 *
 * @param [in] index
 *
 * @return 0 on sucess, error code otherwise
 */
int io_remove_task(const size_t index);


/**
 * @brief Free io vector and reset the index value
 */
void io_free();



#endif /* INC_IO_CONTROLLER_H_ */
