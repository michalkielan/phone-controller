/*
 * frame_encrypt.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_FRAME_ENCRYPT_H_
#define INC_FRAME_ENCRYPT_H_

#include "error_codes.h"

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
  ResponseOk,
  ResponseFailed,
  CommandLast
};


#endif /* INC_FRAME_ENCRYPT_H_ */
