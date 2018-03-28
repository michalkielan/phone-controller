/*
 * devices.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Michal Kielan
 */

#include "devices.h"

#include <string.h>
#include <malloc.h>
#include <errno.h>


/**
 * @brief Structure of vector of callbacks to set/get
 *        data from the io controllers
 */
static IoCallbacksVector io_vector = {NULL, 0, 0};

int io_add_task(const IoCallback io_callback)
{
  const size_t size = sizeof(IoCallback);
  const size_t start_capacity = 1;

  if(io_vector.index == 0)
  {
    io_vector.capacity = start_capacity;
    const size_t bytes = io_vector.capacity * size;
    io_vector.io_callbacks = (IoCallback*)malloc(bytes);

    if(io_vector.io_callbacks == NULL)
    {
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

int io_call_task(const size_t index, const int input, int* output)
{
  if(index > io_vector.index)
  {
    return -ERANGE;
  }
  else
  {
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

