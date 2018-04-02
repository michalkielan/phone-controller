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
#include "sim/sim.h"


static const size_t max_buffer_size = 60;
static uint8_t message_buffer[max_buffer_size];

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

static int check_frame_message(const FrameMessage* const dst)
{
  int res = check_crc(dst);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Checksum %d is wrong", get_crc(dst));
    return InvalidChecksum;
  }

  if(dst->start != StartCode)
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

  const size_t size = get_buffer_size(msg);
  char* buf = (char*)malloc(size);
  if(buf == NULL)
  {
    LOGF(LOG_ERROR, "Allocating message buffer failed");
    return BadAlloc;
  }

  const int res = frame2buf(buf, msg);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Creating buffer frame failed");
    return Failed;
  }

  res = sim_send_data(buf, size);
  if(res != 0)
  {
    LOGF(LOG_ERROR, "Send sms failed");
    return Failed;
  }

  free(buf);

  LOGF(LOG_INFO, "Send sms correct");
  return Ok;
}


int get_message()
{

  //const int res = sim_receive_data(message_buffer, );
}



void call()
{

}

void call_set(FrameMessage* msg, FrameMessage* response)
{
  const int res = io_call_task(msg->device, msg->data, &msg->num_bytes);
  if(res == 0)
  {
    LOGF(LOG_INFO, "Calling io_call_task successed");
    response->command = ResponseOk;
    response->num_bytes = 0;
    response->data = NULL;
  }
  else
  {
    LOGF(LOG_ERROR, "Calling io_call_task failed");
    response->command = ResponseFailed;
    response->num_bytes = 1;
    response->data =  message_buffer;
    response->data[0] = res;
  }
}

int get_data(char* ptr, const size_t N)
{
  char data[] = {1,2,3,4,5};
  ptr = data;
}

void call_get(FrameMessage* msg, FrameMessage* response)
{
  assert(msg != NULL);
  assert(response != NULL);
  msg->data = message_buffer;
  const int res = io_call_task(msg->device, msg->data, &msg->num_bytes);
  if(res == 0)
  {
    LOGF(LOG_INFO, "Calling io_call_task successed");
    response->command = ResponseOk;
  }
  else
  {
    LOGF(LOG_ERROR, "Calling io_call_task failed");
    response->command = ResponseFailed;
    response->data[0] = res;
  }
}

int run_command(FrameMessage* msg)
{
  assert(msg != NULL);
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

