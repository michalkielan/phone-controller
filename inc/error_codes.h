/**
 * @file error_codes.h
 *
 * @brief Error codes
 *
 * @date 31 Mar 2018
 * @author Michal Kielan
 */

#ifndef INC_ERROR_CODES_H_
#define INC_ERROR_CODES_H_


/**
 * @brief Error codes
 */
enum Result
{
  BadAlloc = -9,
  DecryptFailed,
  InvalidData,
  InvalidChecksum,
  InvalidInstruction,
  InvalidCommand,
  InvalidDevide,
  ErrorSendingMessage,
  Failed,
  Ok = 0,
};


#endif /* INC_ERROR_CODES_H_ */
