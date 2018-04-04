/**
 * @file crypt_xor.c
 *
 * @brief Implementation of xor crypt algorithm
 *
 * @date 27 Mar 2018
 * @author Michal Kielan
 */

#include "crypt/crypt_xor.h"
#include "crypt/key_64.h"
#include "logger/logger.h"

#include <errno.h>
#include <assert.h>

int crypt_xor(void* dst, const void* const src, const size_t size)
{
	assert(dst != NULL);
	assert(src != NULL);

	const size_t key_size = strlen(key_64);

  if(size > key_size)
  {
    LOGF(LOG_ERROR, "Buffer size should not be bigger than, keysize: %d", key_size);
    return -EINVAL;
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
