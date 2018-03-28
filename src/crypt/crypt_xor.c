/*
 * crypt_xor.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "crypt/crypt_xor.h"
#include "crypt/key_64.h"

#include <errno.h>

static const size_t key_size = strlen(key_64);

int crypt_xor(void* dst, const void* const src, const size_t size)
{
  if(dst == NULL || src == NULL || size > key_size)
  {
    return EINVAL;
  }

  size_t len = size;
  char* dst_begin = (char*)dst;
  char const* src_begin = (char const*)src;
  char const* key_begin = (char const*)key_64;

  while(len--)
  {
    *dst_begin++ = *key_begin++ ^ *src_begin++;
  }

  return 0;
}