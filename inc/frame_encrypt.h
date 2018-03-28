/*
 * frame_encrypt.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_FRAME_ENCRYPT_H_
#define INC_FRAME_ENCRYPT_H_

/**
 * @brief Error codes of frame write/read
 */
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


/**
 * @brief Hard coded instructions
 */
enum Instruction
{
  StartCode = 0x1234
};


/**
 * @brief Commands to control io controllers
 */
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
