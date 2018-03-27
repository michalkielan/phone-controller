/*
 * frame_encrypt.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_FRAME_ENCRYPT_H_
#define INC_FRAME_ENCRYPT_H_


typedef enum
{
  OK,
  FAILED_DECRYPT,
  INVALID_DATA,
  CRC_ERROR,
  START_INSTRUCTION_WRONG,
  INVALID_COMMAND,
  INVALID_DEVICE

} FrameResult;

enum Instruction
{
  StartCode = 0x1234
};

enum Commands
{
  CommandFirst,
  Set,
  Get,
  ReceiveOk,
  ReceiveFailed,
  CommandLast
};


#endif /* INC_FRAME_ENCRYPT_H_ */
