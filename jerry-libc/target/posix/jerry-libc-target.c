/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Jerry libc platform-specific functions posix implementation
 */

#include <assert.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#if defined (__linux__)
#define SYSCALL_NO(NAME) __NR_ ## NAME
#elif defined (__APPLE__) && defined (__MACH__)
#define SYS_exit_group SYS_exit
#define SYSCALL_NO(NAME) SYS_ ## NAME
#else /* !__linux && !(__APPLE__ && __MACH__) */
#error "Unsupported OS"
#endif /* __linux__ */

#include "jerry-libc-defs.h"

long int syscall_0 (long int syscall_no);
long int syscall_1 (long int syscall_no, long int arg1);
long int syscall_2 (long int syscall_no, long int arg1, long int arg2);
long int syscall_3 (long int syscall_no, long int arg1, long int arg2, long int arg3);

/**
 * Exit - cause normal process termination with specified status code
 */
void __attr_weak___ __attr_noreturn___ __attr_used___
exit (int status) /**< status code */
{
#ifdef ENABLE_INIT_FINI
  libc_fini_array ();
#endif /* ENABLE_INIT_FINI */

  syscall_1 (SYSCALL_NO (close), (long int) stdin);
  syscall_1 (SYSCALL_NO (close), (long int) stdout);
  syscall_1 (SYSCALL_NO (close), (long int) stderr);

  syscall_1 (SYSCALL_NO (exit_group), status);

  while (true)
  {
    /* unreachable */
  }
} /* exit */

/**
 * Abort current process, producing an abnormal program termination.
 * The function raises the SIGABRT signal.
 */
void __attr_weak___ __attr_noreturn___ __attr_used___
abort (void)
{
  syscall_1 (SYSCALL_NO (close), (long int) stdin);
  syscall_1 (SYSCALL_NO (close), (long int) stdout);
  syscall_1 (SYSCALL_NO (close), (long int) stderr);

  raise (SIGABRT);

  while (true)
  {
    /* unreachable */
  }
} /* abort */

/**
 * Send a signal to the current process.
 *
 * @return 0 - upon successful completion,
 *         non-zero value - otherwise.
 */
int __attr_weak___ __attr_used___
raise (int sig) /**< signal number */
{
  return (int) syscall_2 (SYSCALL_NO (kill), syscall_0 (SYSCALL_NO (getpid)), sig);
} /* raise */

/**
 * fopen
 *
 * @return FILE pointer - upon successful completion,
 *         NULL - otherwise.
 */
FILE * __attr_weak___
fopen (const char *path, /**< file path */
       const char *mode) /**< file open mode */
{
  bool may_read = false;
  bool may_write = false;
  bool truncate = false;
  bool create_if_not_exist = false;
  bool position_at_end = false;
  int modifier_position = 1;

  assert (path != NULL && mode != NULL);
  assert (mode[1] == '\0'
          || (mode[1] == '+' && mode[2] == '\0')
          || (mode[1] == 'b' && mode[2] == '\0')
          || (mode[1] == 'b' && mode[2] == '+' && mode[3] == '\0'));

  if (mode[1] == 'b')
  {
    modifier_position = 2;
  }

  switch (mode[0])
  {
    case 'r':
    {
      may_read = true;
      may_write = (mode[modifier_position] == '+');
      break;
    }
    case 'w':
    {
      may_write = true;
      truncate = true;
      create_if_not_exist = true;
      may_read = (mode[modifier_position] == '+');
      break;
    }
    case 'a':
    {
      may_write = true;
      position_at_end = true;
      create_if_not_exist = true;
      if (mode[modifier_position] == '+')
      {
        assert (false && "unsupported mode a+");
      }
      break;
    }
    default:
    {
      assert (false && "unsupported mode");
    }
  }

  int flags = 0;
  int access = S_IRUSR | S_IWUSR;
  if (may_read && !may_write)
  {
    flags = O_RDONLY;
  }
  else if (!may_read && may_write)
  {
    flags = O_WRONLY;
  }
  else
  {
    assert (may_read && may_write);

    flags = O_RDWR;
  }

  if (truncate)
  {
    flags |= O_TRUNC;
  }

  if (create_if_not_exist)
  {
    flags |= O_CREAT;
  }

  if (position_at_end)
  {
    flags |= O_APPEND;
  }

  long int ret = syscall_3 (SYSCALL_NO (open), (long int) path, flags, access);

  return ((ret < 0) ? NULL : (void *) (uintptr_t) (ret));
} /* fopen */

/**
 * fclose
 *
 * @return 0 - upon successful completion,
 *         non-zero value - otherwise.
 */
int __attr_weak___
fclose (FILE *fp) /**< stream pointer */
{
  syscall_2 (SYSCALL_NO (close), (long int) fp, 0);

  return 0;
} /* fclose */

/**
 * fread
 *
 * @return number of elements read
 */
size_t __attr_weak___
fread (void *ptr, /**< address of buffer to read to */
       size_t size, /**< size of elements to read */
       size_t nmemb, /**< number of elements to read */
       FILE *stream) /**< stream pointer */
{
  long int ret;
  size_t bytes_read = 0;

  if (size == 0)
  {
    return 0;
  }

  do
  {
    ret = syscall_3 (SYSCALL_NO (read),
                     (long int) stream,
                     (long int) ((uint8_t *) ptr + bytes_read),
                     (long int) (size * nmemb - bytes_read));

    bytes_read += (size_t) ret;
  }
  while (bytes_read != size * nmemb && ret != 0);

  return bytes_read / size;
} /* fread */

/**
 * fwrite
 *
 * @return number of elements written
 */
size_t __attr_weak___
fwrite (const void *ptr, /**< data to write */
        size_t size, /**< size of elements to write */
        size_t nmemb, /**< number of elements */
        FILE *stream) /**< stream pointer */
{
  size_t bytes_written = 0;

  if (size == 0)
  {
    return 0;
  }

  do
  {
    long int ret = syscall_3 (SYSCALL_NO (write),
                              (long int) stream,
                              (long int) ((uint8_t *) ptr + bytes_written),
                              (long int) (size * nmemb - bytes_written));

    bytes_written += (size_t) ret;
  }
  while (bytes_written != size * nmemb);

  return bytes_written / size;
} /* fwrite */

/**
 * This function can get the time as well as a timezone.
 *
 * @return 0 if success, -1 otherwise
 */
int __attr_weak___
gettimeofday (void *tp,  /**< struct timeval */
              void *tzp) /**< struct timezone */
{
  return (int) syscall_2 (SYSCALL_NO (gettimeofday), (long int) tp, (long int) tzp);
} /* gettimeofday */
