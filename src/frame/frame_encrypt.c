/**
 * @file frame_encrypt.c
 *
 * @brief
 *
 * @date 27 Mar 2018
 * @author Michal Kielan
 */

#include "frame/frame_encrypt.h"
#include "io_controller.h"
#include "crypt/crypto.h"
#include "frame/frame_msg.h"
#include "logger/logger.h"
#include "error_codes.h"

static int check_command(const uint16_t cmd)
{
  if(cmd <= CommandFirst || cmd >= CommandLast)
  {
    LOGF(LOG_ERROR, "Command %d, not found", cmd);
    return Failed;
  }
  else
  {
    LOGF(LOG_VERBOSE, "Command %d correct", cmd);
    return Ok;
  }
}

static int check_frame_message(const FrameMessage* const dst)
{
  int res = check_crc(dst);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Checksum %d is wrong", get_crc(dst));
    return InvalidChecksum;
  }

  if(dst->start == StartCode)
  {
    LOGF(LOG_ERROR, "Start instruction wrong");
    return InvalidInstruction;
  }

  res = check_command(dst->command);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Invalid command");
    return InvalidCommand;
  }

  return Ok;
}

int read_frame_message(FrameMessage* dst, const char* const src)
{
  const size_t N = sizeof(FrameMessage);
  char buf[N];

  int res = decrypt(dst, src, N);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Decryption failed");
    return DecryptFailed;
  }

  res = buf2frame(dst, buf);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Invalid input buffer");
    return InvalidData;
  }

  return check_frame_message(dst);
}


int write_message(FrameMessage* msg)
{
  set_crc(msg);
  //return hw_write_message(msg);
  return 0;
}


void call()
{

}

void call_set(FrameMessage* msg, FrameMessage* response)
{
  const int res = io_call_task(msg->device, msg->data, NULL);
  if(res == 0)
  {
    LOGF(LOG_INFO, "Calling io_call_task successed");
    response->command = ResponseOk;
    response->data = 0;
  }
  else
  {
    LOGF(LOG_ERROR, "Calling io_call_task failed");
    response->command = ResponseFailed;
    response->data = res;
  }
}

void call_get(FrameMessage* msg, FrameMessage* response)
{
  int data = 0;
  const int res = io_call_task(msg->device, msg->data, &data);
  if(res == 0)
  {
    LOGF(LOG_INFO, "Calling io_call_task successed");
    response->command = ResponseOk;
    response->data = data;
  }
  else
  {
    LOGF(LOG_ERROR, "Calling io_call_task failed");
    response->command = ResponseFailed;
    response->data = res;
  }
}

int run_command(FrameMessage* msg)
{
  if(msg == NULL)
  {
    return InvalidData;
  }
  FrameMessage response;
  response.start = StartCode;
  response.device = msg->device;

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
    return Ok;
  }
  else
  {
    LOGF(LOG_ERROR, "Response sent failed");
    return ErrorSendingMessage;
  }
}

