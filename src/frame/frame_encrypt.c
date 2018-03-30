/*
 * frame_encrypt.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "crypt/crypto.h"
#include "frame/frame_encrypt.h"
#include "frame/frame_msg.h"
#include "devices.h"
#include "logger/logger.h"

static int check_command(const uint16_t cmd)
{
  if(cmd <= CommandFirst || cmd >= CommandLast)
  {
    LOGF(LOG_ERROR, "Command %d, not found", cmd);
    return 1;
  }
  else
  {
    LOGF(LOG_VERBOSE, "Command %d correct", cmd);
    return 0;
  }
}

static FrameResult check_frame_message(const FrameMessage* const dst)
{
  int res = check_crc(dst);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Checksum %d is wrong", get_crc(dst));
    return CRC_ERROR;
  }

  if(dst->start == StartCode)
  {
    LOGF(LOG_ERROR, "Start instruction wrong");
    return START_INSTRUCTION_WRONG;
  }

  res = check_command(dst->command);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Invalid command");
    return INVALID_COMMAND;
  }

  return OK;
}

FrameResult read_frame_message(FrameMessage* dst, const char* const src)
{
  const size_t N = sizeof(FrameMessage);
  char buf[N];

  int res = decrypt(dst, src, N);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Decryption failed");
    return FAILED_DECRYPT;
  }

  res = buf2frame(dst, buf);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Invalid input buffer");
    return INVALID_DATA;
  }

  return check_frame_message(dst);
}


int write_message(FrameMessage* msg)
{
  set_crc(&msg);
  //return hw_write_message(msg);
  return 0;
}


void call()
{

}

void call_set(FrameMessage* msg, FrameMessage* response)
{
  const int res = io_call_task(msg->device, msg->value, NULL);
  if(res == 0)
  {
    LOGF(LOG_INFO, "Calling io_call_task successed");
    response->command = ResponseOk;
    response->value = 0;
  }
  else
  {
    LOGF(LOG_ERROR, "Calling io_call_task failed");
    response->command = ResponseFailed;
    response->value = res;
  }
}

void call_get(FrameMessage* msg, FrameMessage* response)
{
  int data = 0;
  const int res = io_call_task(msg->device, msg->value, data);
  if(res == 0)
  {
    LOGF(LOG_INFO, "Calling io_call_task successed");
    response->command = ResponseOk;
    response->value = data;
  }
  else
  {
    LOGF(LOG_ERROR, "Calling io_call_task failed");
    response->command = ResponseFailed;
    response->value = res;
  }
}

FrameResult run_command(FrameMessage* msg)
{
  if(msg == NULL)
  {
    return INVALID_DATA;
  }
  FrameMessage response;
  response.start = StartCode;
  response.device = msg->device;

  int res = 0;
  if(msg->command == Set)
  {
    call_set(msg, &response);
  }

  else
  {
    call_get(msg, &response);
  }

  if(write_message(&response) ==  0)
  {
    LOGF(LOG_INFO, "Response sent correctly");
    return OK;
  }
  else
  {
    LOGF(LOG_ERROR, "Response sent failed");
    return ERROR_SENDING_MESSAGE;
  }
}

