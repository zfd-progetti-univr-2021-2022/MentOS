///                MentOS, The Mentoring Operating system project
/// @file write.c
/// @brief
/// @copyright (c) 2014-2021 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include "sys/unistd.h"
#include "system/syscall_types.h"
#include "sys/errno.h"

_syscall3(ssize_t, write, int, fd, void *, buf, size_t, nbytes)
