/*
 * frame_msg.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#include "frame/frame_msg.h"
#include "logger/logger.h"

#include "error_codes.h"
#include <string.h>

int frame2buf(void* dst, const FrameMessage* const src)
{
  int frame_bytes = get_frame_size(src);
  const char* msg_begin = (const char*)src;
  char* buffer = (char*)dst;

  while(frame_bytes--)
  {
      *buffer++ = *msg_begin++;
  }

  int buffer_bytes = src->num_bytes;
  const char* buffer_begin = (const char*)src->data;

  while(buffer_bytes--)
  {
      *buffer++ = *buffer_begin++;
  }

  *buffer++ = src->crc;

  LOGF(LOG_VERBOSE, "Buffers copy correctly");
  return Ok;
}

int buf2frame(FrameMessage* dst, const void* const src)
{
  int frame_bytes = get_frame_size(src);
  const char* msg_begin = (const char*)src;
  char* buffer = (char*)dst;

  while(frame_bytes--)
  {
      *buffer++ = *msg_begin++;
  }

  int buffer_bytes = dst->num_bytes;
  dst->data = (char*)malloc(dst->num_bytes);

  const char* buffer_begin = (const char*)dst->data;

  while(buffer_bytes--)
  {
      *buffer++ = *buffer_begin++;
  }

  LOGF(LOG_VERBOSE, "Buffers copy correctly");
  return Ok;
}

void buf_release(FrameMessage* msg)
{
  free(msg->data);
}


/**
 * @brief Get frame messgae size
 *
 * \param [in] frame message structure
 *
 * return size of frame message (without crc and data pointer)
 */
size_t get_frame_size(const FrameMessage* const msg)
{
  int bytes = sizeof(FrameMessage);
  bytes -= sizeof(msg->data);
  bytes -= sizeof(msg->crc);
  return bytes;
}


size_t get_buffer_size(const FrameMessage* const msg)
{
  int bytes = sizeof(FrameMessage);
  bytes -= sizeof(msg->data);
  bytes += msg->num_bytes;
  return bytes;
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
  assert(msg != NULL);
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
  return calc_crc(msg);
}

int set_crc(FrameMessage* msg)
{
  const uint8_t crc = calc_crc(msg);
  msg->crc = crc;
  LOGF(LOG_VERBOSE, "Set checksum correctly");
  return Ok;
}

int check_crc(const FrameMessage* const msg)
{
  const uint8_t crc = calc_crc(msg);
  return (msg->crc == crc) ? Ok : Failed;
}

