///                MentOS, The Mentoring Operating system project
/// @file rmdir.c
/// @brief Make directory functions.
/// @copyright (c) 2014-2021 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include "sys/unistd.h"
#include "system/syscall_types.h"
#include "sys/errno.h"

_syscall1(int, rmdir, const char *, path)
