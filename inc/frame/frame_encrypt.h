/**
 * @file frame_encrypt.h
 *
 * @brief
 *
 * @date 27 Mar 2018
 * @author Michal Kielan
 */

#ifndef INC_FRAME_ENCRYPT_H_
#define INC_FRAME_ENCRYPT_H_


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
