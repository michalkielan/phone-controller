/*
 * io_controller.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "io_controller.h"
#include "logger/logger.h"

#include <errno.h>
#include <string.h>
#include <malloc.h>


/**
 * @brief Structure for vector of callbacks, this structure is
 *        for singleton object, is should not be visible in header
 *        files and the object should not be created from the user
 */
typedef struct
{
  IoCallback* io_callbacks;
  size_t      capacity;
  size_t      index;
} IoCallbacksVector;


/**
 * @brief Singleton with vector of callbacks to set/get
 *        data from the io controllers.
 */
static IoCallbacksVector io_vector = {NULL, 0, 0};


int io_add_task(const IoCallback io_callback)
{
  if(io_callback == NULL)
  {
    LOGF(LOG_ERROR, "Function pointer should not be nullptr");
    return -EINVAL;
  }

  const size_t size = sizeof(IoCallback);
  const size_t start_capacity = 1;

  if(io_vector.index == 0)
  {
    io_vector.capacity = start_capacity;
    const size_t bytes = io_vector.capacity * size;
    io_vector.io_callbacks = (IoCallback*)malloc(bytes);

    if(io_vector.io_callbacks == NULL)
    {
      LOGF(LOG_ERROR, "Allocating vector first element failed, out of memory");
      return -ENOMEM;
    }
  }

  if(io_vector.index >= io_vector.capacity)
  {
    io_vector.capacity *= 2;
    const size_t bytes = io_vector.capacity * size;
    IoCallback* const tmp_callbacks = (IoCallback*)realloc(io_vector.io_callbacks, bytes);

    if(tmp_callbacks == NULL)
    {
      LOGF(LOG_ERROR, "Reallocing vector failed, out of memory");
      io_free();
      return -ENOMEM;
    }
    io_vector.io_callbacks = tmp_callbacks;
  }

  io_vector.io_callbacks[io_vector.index] = io_callback;

  const int id = io_vector.index;
  ++io_vector.index;

  return id;
}


size_t io_get_size()
{
  return io_vector.index;
}


/**
 * @brief Remove last element in callback vector
 *
 * \return 0 on sucess, error code otherwise
 */
static int remove_last()
{
  io_vector.io_callbacks[io_vector.index] = NULL;
  --io_vector.index;
  return 0;
}


/**
 * @brief Remove element in the middle of vector
 *
 * \param [in] index of element to be removed
 *
 * \return 0 on sucess, error code otherwise *
 */
static int remove_middle(const size_t index)
{
  const size_t size = sizeof(IoCallback);
  const size_t bytes = io_vector.capacity * size;
  IoCallback* tmp_callbacks = (IoCallback*)malloc(bytes);
  if(tmp_callbacks == NULL)
  {
    return -1;
  }

  size_t id = 0;
  for(size_t i=0; i< io_vector.index; i++)
  {
    if(id == index)
    {
      ++i;
    }
    tmp_callbacks[id++] = io_vector.io_callbacks[i];
  }

  free(io_vector.io_callbacks);
  io_vector.io_callbacks = tmp_callbacks;
  tmp_callbacks = NULL;

  return 0;
}

int io_remove_task(const size_t index)
{
  if(io_vector.index == index)
  {
    return remove_last();
  }

  else
  {
    return remove_middle(index);
  }
}


int io_call_task(const size_t index, const int input, int* output)
{
  if(index > io_vector.index)
  {
    LOGF(LOG_ERROR, "The index %d of function is out of range", index);
    return -ERANGE;
  }
  else
  {
    LOGF(LOG_INFO, "Callback: %d calling correctly", index);
    return io_vector.io_callbacks[index](input, output);
  }
}


void io_free()
{
  free(io_vector.io_callbacks);
  io_vector.io_callbacks = NULL;
  io_vector.index = 0;
  io_vector.capacity = 0;
}

