/*
 * crypto.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include <crypt_xor.h>

int encrypt(void* dst, const void* const src, const size_t size)
{
  return crypt_xor(dst, src, size);
}

int decrypt(void* dst, const void* const src, const size_t size)
{
  return crypt_xor(dst, src, size);
}
