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


/**
 * @brief Get FrameMessage buffer size in bytes
 *
 * \param [in] frame message structure
 *
 * return size of frame message (without crc)
 */
static int get_frame_size(const FrameMessage* const msg)
{
  const int crc_bytes = sizeof(msg->crc);
  return sizeof(FrameMessage) - crc_bytes;
}


/**
 * @brief Calculate checksum using xor, the checksum in calculating
 *        by xor each bytes of frame
 *
 * \param [in] frame message structure
 *
 * return checksum (one byte)
 */
static uint8_t calc_crc(const FrameMessage* const msg)
{
  int bytes = get_frame_size(msg);
  const char* msg_begin = (const char*)msg;

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

