/*
 * frame_msg.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#ifndef FRAME_MSG_H_
#define FRAME_MSG_H_

#include <stdint.h>

typedef struct
{
  uint16_t start;
  uint16_t device;
  uint16_t command;
  uint16_t value;
  uint8_t  crc;
} FrameMessage;


/**
 * @brief Convert frame structure to buffer
 *
 * \param [out] buffer of bytes
 * \param [in] frame structure to be converted to buffer
 *
 * \return EINVAL when the pointers are not valid, SUCESS otherwise
 */
int frame2buf(char* dst, const FrameMessage* const src);


/**
 * @brief Convert buffer into frame
 *
 * \param [out] buffer
 * \param [in] buffer of bytes to be converted to frame structure
 *
 * \return EINVAL when the pointers are not valid, SUCESS otherwise
 */
int buf2frame(FrameMessage* dst, const char* const src);



#endif /* FRAME_MSG_H_ */
