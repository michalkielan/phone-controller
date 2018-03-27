/*
 * frame_msg.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "frame_msg.h"

#include <errno.h>
#include <string.h>

int frame2buf(char* dst, const FrameMessage* const src)
{
  if(dst == NULL || src == NULL)
  {
    return EINVAL;
  }
  else
  {
    const size_t bytes = sizeof(FrameMessage);
    memcpy(dst, src, bytes);
    return 0;
  }
}

int buf2frame(FrameMessage* dst, const char* const src)
{
  if(dst == NULL || src == NULL)
  {
    return EINVAL;
  }
  else
  {
    const size_t bytes = sizeof(FrameMessage);
    memcpy(dst, src, bytes);
    return 0;
  }
}


static uint8_t calc_crc(const FrameMessage* const msg)
{
  uint8_t crc = 0;

  const int crc_bytes = sizeof(msg->crc);
  const int bytes = sizeof(FrameMessage) - crc_bytes;
  const char* msg_ptr = (char*)msg;

  for(int i=0; i<bytes; i++)
  {
    crc ^= *(msg_ptr + i);
  }
  return crc;
}

int get_crc(const FrameMessage* const msg)
{
  if(msg == NULL)
  {
    return EINVAL;
  }
  else
  {
    return calc_crc(msg);
  }
}

int set_crc(FrameMessage* msg)
{
  if(msg == NULL)
  {
    return EINVAL;
  }
  else
  {
    const uint8_t crc = calc_crc(msg);
    msg->crc = crc;
    return 0;
  }
}

int check_crc(const FrameMessage* const msg)
{
  if(msg == NULL)
  {
    return -EINVAL;
  }
  else
  {
    const uint8_t crc = calc_crc(msg);
    return (msg->crc == crc) ? 0 : -EDOM;
  }
}



