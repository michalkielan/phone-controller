/*
 * crypt_xor.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_CRYPT_XOR_H_
#define INC_CRYPT_XOR_H_

#include "crypt_xor.h"

#include <string.h>

/**
 * @brief Crypt array of data using xor method, the key is global
 *        buffer of random characters. This function is used for
 *        crypt and encrypt.
 *
 * \param [out] pointer to decrypted/encrypted output buffer of data
 * \param [in]  pointer to decrypted/encrypted output buffer of data
 * \param [in]  size of buffer, must be lower than size of key buffer,
 *              size of key buffer is usually 64 bytes.
 *
 * \return 0 on sucess, error code otherwise
 * - EINVAL when the pointers are not valid, or size is too much
 */
int crypt_xor(void* dst, const void* const src, const size_t size);



#endif /* INC_CRYPT_XOR_H_ */
