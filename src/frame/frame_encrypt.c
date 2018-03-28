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

static int check_command(const uint16_t cmd)
{
  if(cmd <= CommandFirst || cmd >= CommandLast)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

static FrameResult check_frame_message(const FrameMessage* const dst)
{
  int res = check_crc(dst);
  if(res != 0)
  {
    return CRC_ERROR;
  }

  if(dst->start == StartCode)
  {
    return START_INSTRUCTION_WRONG;
  }

  res = check_command(dst->command);
  if(res != 0)
  {
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
    return FAILED_DECRYPT;
  }

  res = buf2frame(dst, buf);
  if(res != 0)
  {
    return INVALID_DATA;
  }

  return check_frame_message(dst);
}


int write_message(FrameMessage* msg)
{
  //return hw_write_message(msg);
  return 0;
}

FrameResult run_command(FrameMessage* dst)
{
  FrameMessage response;
  response.start = StartCode;
  response.device = dst->device;

  if(dst->command == Set)
  {
    const int res = io_call_task(dst->device, dst->value, NULL);
    if(res == 0)
    {
      response.command = ReceiveOk;
      response.value = 0;
      set_crc(&response);
      if(write_message(&response) ==  0)
      {
        return OK;
      }
      else
      {
        return ERROR_SENDING_MESSAGE;
      }
    }
    else
    {
      response.command = ReceiveFailed;
      response.value = res;
      set_crc(&response);
      if(write_message(&response) ==  0)
      {
        return OK;
      }
      else
      {
        return ERROR_SENDING_MESSAGE;
      }
    }
  }

  else
  {
    int get_value = 0;
    const int res = io_call_task(dst->device, dst->value, &get_value);
    if(res == 0)
    {
      response.command = ReceiveOk;
      response.value = get_value;
      set_crc(&response);
      if(write_message(&response) ==  0)
      {
        return OK;
      }
      else
      {
        return ERROR_SENDING_MESSAGE;
      }
    }
    else
    {
      response.command = ReceiveFailed;
      response.value = res;
      set_crc(&response);
      if(write_message(&response) ==  0)
      {
        return OK;
      }
      else
      {
        return ERROR_SENDING_MESSAGE;
      }
    }
  }
}

