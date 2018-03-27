/*
 * frame_encrypt.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "frame_encrypt.h"

#include "crypto.h"
#include "frame_msg.h"
#include "devices.h"


static int checkCommand(const uint16_t cmd)
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

static FrameResult checkFrameMessage(const FrameMessage* const dst)
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

  res = checkCommand(dst->command);
  if(res != 0)
  {
    return INVALID_COMMAND;
  }

  return 0;
}

FrameResult readFrameMessage(FrameMessage* dst, const char* const src)
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

  res = checkFrameMessage(dst);
  return res;
}


int writeMessage(FrameMessage* msg){}

FrameResult runCommand(FrameMessage* dst)
{
  const int res = readFrameMessage(dst);
  if(res != 0)
  {
    return res;
  }

  if(checkDeviceValid(dst->device) != 0)
  {
    return INVALID_DEVICE;
  }

  FrameMessage response;
  response.start = StartCode;
  response.device = dst->device;

  if(dst->command == Set)
  {
    const int res = set_get_device_data[dst->device](dst->value, NULL);
    if(res == 0)
    {
      response.command = ReceiveOk;
      response.value = 0;
      set_crc(&response);
      return writeMessage(response);
    }
    else
    {
      response.command = ReceiveFailed;
      response.value = res;
      set_crc(&response);
      return writeMessage(response);
    }
  }

  else
  {
    int get_value = 0;
    const int res = set_get_device_data[dst->device](dst->value, &get_value);
    if(res == 0)
    {
      response.command = ReceiveOk;
      response.value = get_value;
      set_crc(&response);
      return writeMessage(response);
    }
    else
    {
      response.command = ReceiveFailed;
      response.value = res;
      set_crc(&response);
      return writeMessage(response);
    }
  }

}


//void (*setIO_functions[10]) (const int value);
//
//void setIO(const int device, const int value)
//{
//  setIO_functions[device](value);
//}
//
//void decode(FrameMessage* dst)
//{
//  if(dst->command == SetIO)
//  {
//    setIO(dst->device, dst->value);
//  }
//}





