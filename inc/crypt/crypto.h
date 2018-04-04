/**
 * @file crypt.h
 *
 * @brief Interface for crypt algorithms
 *
 * @date 27 Mar 2018
 * @author Michal Kielan
 */

#ifndef INC_CRYPTO_H_
#define INC_CRYPTO_H_

#include <string.h>

/**
 * @brief Encrypt buffer of data
 *
 * @param [out] encrypted buffer
 * @param [in]  buffer of data to be encrypt
 * @param [in]  size of buffer
 *
 * @return 0 on sucess, error code otherwise
 */
int encrypt(void* dst, const void* const src, const size_t size);


/**
 * @brief Decrypt buffer of data
 *
 * @param [out] decrypted data
 * @param [in]  buffer of encrypted data
 * @param [in]  size of buffer
 *
 * @return 0 on sucess, error code otherwise
 */
int decrypt(void* dst, const void* const src, const size_t size);


#endif /* INC_CRYPTO_H_ */
