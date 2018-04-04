/**
 * @file crypt.c
 *
 * @brief Interface for crypt algorithms
 *
 * @date 27 Mar 2018
 * @author Michal Kielan
 */

#include "crypt/crypt_xor.h"

int encrypt(void* dst, const void* const src, const size_t size)
{
  return crypt_xor(dst, src, size);
}

int decrypt(void* dst, const void* const src, const size_t size)
{
  return crypt_xor(dst, src, size);
}
