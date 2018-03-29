/*
 * frame_msg.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "frame/frame_msg.h"
#include "logger/logger.h"

#include <errno.h>
#include <string.h>

int frame2buf(char* dst, const FrameMessage* const src)
{
  if(dst == NULL || src == NULL)
  {
    LOGF(LOG_ERROR, "Buffers should not be nullptr");
    return -EINVAL;
  }
  else
  {
    const size_t bytes = sizeof(FrameMessage);
    memcpy(dst, src, bytes);
    LOGF(LOG_VERBOSE, "Buffers copy correctly");
    return 0;
  }
}

int buf2frame(FrameMessage* dst, const char* const src)
{
  if(dst == NULL || src == NULL)
  {
    LOGF(LOG_ERROR, "Buffers should not be nullptr");
    return -EINVAL;
  }
  else
  {
    const size_t bytes = sizeof(FrameMessage);
    memcpy(dst, src, bytes);
    LOGF(LOG_VERBOSE, "Buffers copy correctly");
    return 0;
  }
}


static uint8_t calc_crc(const FrameMessage* const msg)
{
  const int crc_bytes = sizeof(msg->crc);
  int bytes = sizeof(FrameMessage) - crc_bytes;
  const char* msg_begin = (char*)msg;

  uint8_t crc = 0;

  while(bytes--)
  {
    crc ^= *msg_begin++;
  }
  return crc;
}

int get_crc(const FrameMessage* const msg)
{
  if(msg == NULL)
  {
    LOGF(LOG_ERROR, "Frame message should not be nullptr");
    return -EINVAL;
  }
  else
  {
    LOGF(LOG_VERBOSE, "Get checksum correctly");
    return calc_crc(msg);
  }
}

int set_crc(FrameMessage* msg)
{
  if(msg == NULL)
  {
    LOGF(LOG_ERROR, "Frame message should not be nullptr");
    return -EINVAL;
  }
  else
  {
    const uint8_t crc = calc_crc(msg);
    msg->crc = crc;
    LOGF(LOG_VERBOSE, "Set checksum correctly");
    return 0;
  }
}

int check_crc(const FrameMessage* const msg)
{
  if(msg == NULL)
  {
    LOGF(LOG_ERROR, "Frame message should not be nullptr");
    return -EINVAL;
  }
  else
  {
    const uint8_t crc = calc_crc(msg);
    return (msg->crc == crc) ? 0 : -EDOM;
  }
}

