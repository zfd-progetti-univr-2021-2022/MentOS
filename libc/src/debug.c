///                MentOS, The Mentoring Operating system project
/// @file   debug.c
/// @brief  Debugging primitives.
/// @copyright (c) 2014-2021 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include <debug.h>

#include <stddef.h>
#include <io/port_io.h>
#include <stdio.h>
#include <string.h>
#include <sys/bitops.h>

/// Serial port for QEMU.
#define SERIAL_COM1 (0x03F8)

void dbg_putchar(char c)
{
#if (defined(DEBUG_STDIO) || defined(DEBUG_LOG))
    outportb(SERIAL_COM1, (uint8_t)c);
#endif
}

void dbg_puts(const char *s)
{
#if (defined(DEBUG_STDIO) || defined(DEBUG_LOG))
    while ((*s) != 0)
        dbg_putchar(*s++);
#endif
}

static inline void __debug_print_header(const char *file, const char *fun, int line)
{
    static char tmp_prefix[BUFSIZ], final_prefix[BUFSIZ];
    dbg_puts("[ LB |");
    sprintf(tmp_prefix, "%s:%d", file, line);
    sprintf(final_prefix, " %-20s ", tmp_prefix);
    dbg_puts(final_prefix);
    dbg_putchar('|');
    sprintf(final_prefix, " %-25s ] ", fun);
    dbg_puts(final_prefix);
}

void dbg_printf(const char *file, const char *fun, int line, const char *format, ...)
{
    // Define a buffer for the formatted string.
    static char formatted[BUFSIZ];
    static short new_line = 1;

    // Stage 1: FORMAT
    if (strlen(format) >= BUFSIZ)
        return;

    // Start variabile argument's list.
    va_list ap;
    va_start(ap, format);
    // Format the message.
    vsprintf(formatted, format, ap);
    // End the list of arguments.
    va_end(ap);

    // Stage 2: SEND
    if (new_line) {
        __debug_print_header(file, fun, line);
        new_line = 0;
    }
    for (size_t it = 0; (formatted[it] != 0) && (it < BUFSIZ); ++it) {
        dbg_putchar(formatted[it]);
        if (formatted[it] != '\n') {
            continue;
        }
        if ((it + 1) >= BUFSIZ) {
            continue;
        }
        if (formatted[it + 1] == 0) {
            new_line = 1;
        } else {
            __debug_print_header(file, fun, line);
        }
    }
}

const char *to_human_size(unsigned long bytes)
{
    static char output[200];
    const char *suffix[] = { "B", "KB", "MB", "GB", "TB" };
    char length          = sizeof(suffix) / sizeof(suffix[0]);
    int i                = 0;
    double dblBytes      = bytes;
    if (bytes > 1024) {
        for (i = 0; (bytes / 1024) > 0 && i < length - 1; i++, bytes /= 1024)
            dblBytes = bytes / 1024.0;
    }
    sprintf(output, "%.03lf %2s", dblBytes, suffix[i]);
    return output;
}

const char *dec_to_binary(unsigned long value)
{
    static char buffer[33];
    for (int i = 0; i < 32; ++i)
        buffer[i] = bit_check(value, 31 - i) ? '1' : '0';
    return buffer;
}