/*
 * frame_msg.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Michal Kielan
 */

#ifndef FRAME_MSG_H_
#define FRAME_MSG_H_

#include <stdint.h>

/**
 * @brief Frame message buffer structure, should be
 *        packed to write/read bytes without any alignments
 */
typedef struct __attribute__((packed))
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
 * \return 0 on sucess, error code otherwise
 * - EINVAL when the pointers are not valid
 */
int frame2buf(char* dst, const FrameMessage* const src);


/**
 * @brief Convert buffer into frame
 *
 * \param [out] buffer
 * \param [in] buffer of bytes to be converted to frame structure
 *
 * \return 0 on sucess, error code otherwise
 * - EINVAL when the pointers are not valid
 */
int buf2frame(FrameMessage* dst, const char* const src);


/**
 * @brief Get checksum
 *
 * \param [in] frame message structure
 *
 * \return 0 on sucess, error code otherwise
 * - EINVAL when the pointers are not valid
 */
int get_crc(const FrameMessage* const msg);


/**
 * @brief Get checksum ni frame message
 *
 * \param [in] frame message structure
 *
 * \return 0 on sucess, error code otherwise
 * - EINVAL when the pointers are not valid
 */
int set_crc(FrameMessage* msg);


/**
 * @brief Check if checksum in frame is valid
 *
 * \param [in] frame message structure
 *
 * \return 0 on sucess, error code otherwise
 * - EINVAL when the pointers are not valid
 * - EDOM checkum is wrong
 */
int check_crc(const FrameMessage* const msg);


#endif /* FRAME_MSG_H_ */
