/*
 * crypt_xor.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "crypt_xor.h"

#include <errno.h>

static const char*  key = "5rt5@^Y265^y6Y^$2U&d5u&U%36yhteU&5@6gfs4$c3Y%$54yw212r@$R@(*^%$>";
static const size_t key_size = strlen(key);

int crypt_xor(void* dst, const void* const src, const size_t size)
{
  if(dst == NULL || src == NULL || size > key_size)
  {
    return EINVAL;
  }

  size_t len = size;
  char* dst_begin = (char*)dst;
  char const* src_begin = (char const*)src;
  char const* key_begin = (char const*)key;

  while(len--)
  {
    *dst_begin++ = *key_begin++ ^ *src_begin++;
  }

  return 0;
}
