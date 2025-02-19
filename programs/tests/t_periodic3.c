///                MentOS, The Mentoring Operating system project
/// @file t_periodic3.c
/// @brief
/// @copyright (c) 2014-2021 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include <stdio.h>
#include <sched.h>
#include <sys/unistd.h>
#include <strerror.h>

int main(int argc, char *argv[])
{
    pid_t cpid = getpid();
    sched_param_t param;
    // Get current parameters.
    sched_getparam(cpid, &param);
    // Change parameters.
    param.period      = 3000;
    param.deadline    = 3000;
    param.is_periodic = true;
    // Set modified parameters.
    sched_setparam(cpid, &param);
    int counter = 0;
    while (1) {
        if (++counter == 10)
            break;
        printf("[periodic3] counter: %d\n", counter);
        if (waitperiod() == -1) {
            printf("[%s] Error in waitperiod: %s\n", argv[0], strerror(errno));
            break;
        }
    }
    return 0;
}
