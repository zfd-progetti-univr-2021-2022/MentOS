///                MentOS, The Mentoring Operating system project
/// @file unistd.h
/// @brief Functions used to manage files.
/// @copyright (c) 2014-2021 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#pragma once

#include "sys/types.h"
#include "sys/dirent.h"
#include "stddef.h"

#define STDIN_FILENO  0 ///< Standard input.
#define STDOUT_FILENO 1 ///< Standard output.
#define STDERR_FILENO 2 ///< Standard error output.

/// @brief        Read data from a file descriptor.
/// @param fd     The file descriptor.
/// @param buf    The buffer.
/// @param nbytes The number of bytes to read.
/// @return       The number of read characters.
ssize_t read(int fd, void *buf, size_t nbytes);

/// @brief        Write data into a file descriptor.
/// @param fd     The file descriptor.
/// @param buf    The buffer collecting data to written.
/// @param nbytes The number of bytes to write.
/// @return       The number of written bytes.
ssize_t write(int fd, void *buf, size_t nbytes);

/// @brief          Opens the file specified by pathname.
/// @param pathname A pathname for a file.
/// @param flags    Used to set the file status flags and file access modes
///                 of the open file description.
/// @param mode     Specifies the file mode bits be applied when a new file
///                 is created.
/// @return         Returns a file descriptor, a small, nonnegative integer for
///                 use in subsequent system calls.
int open(const char *pathname, int flags, mode_t mode);

/// @brief Close a file descriptor.
/// @param fd The file descriptor.
/// @return The result of the operation.
int close(int fd);

/// @brief Repositions the file offset inside a file.
/// @param fd     The file descriptor of the file.
/// @param offset The offest to use for the operation.
/// @param whence The type of operation.
/// @return  Upon successful completion, returns the resulting offset
/// location as measured in bytes from the beginning of the file. On
/// error, the value (off_t) -1 is returned and errno is set to
/// indicate the error.
off_t lseek(int fd, off_t offset, int whence);

/// @brief Delete a name and possibly the file it refers to.
/// @param path The path to the file.
/// @return
int unlink(const char *path);

/// @brief Wrapper for exit system call.
/// @param status The exit status.
extern void exit(int status);

/// @brief Returns the process ID (PID) of the calling process.
/// @return pid_t process identifier.
extern pid_t getpid();

///@brief  Return session id of the given process.
///        If pid == 0 return the SID of the calling process
///        If pid != 0 return the SID corresponding to the process having identifier == pid
///@param pid process identifier from wich we want the SID
///@return On success return SID of the session
///        Otherwise return -1 with errno set on: EPERM or ESRCH  
extern pid_t getsid(pid_t pid);

///@brief creates a new session if the calling process is not a
///       process group leader.  The calling process is the leader of the
///       new session (i.e., its session ID is made the same as its process
///       ID).  The calling process also becomes the process group leader
///       of a new process group in the session (i.e., its process group ID
///       is made the same as its process ID).
///@return On success return SID of the session just created
///        Otherwise return -1 with errno : EPERM 
extern pid_t setsid();

///@brief returns the group ID of the calling process.
///@return GID of the current process
extern pid_t getgid();

///@brief sets the effective group ID of the calling process.
///@param pid process identifier to 
///@return On success, zero is returned.
///        Otherwise returns -1 with errno set to :EINVAL or EPERM  
extern int setgid(pid_t pid);

/// @brief Returns the parent process ID (PPID) of the calling process.
/// @return pid_t parent process identifier.
extern pid_t getppid();

/// @brief Clone the calling process, but without copying the whole address space.
///        The calling process is suspended until the new process exits or is
///        replaced by a call to `execve'.
/// @return Return -1 for errors, 0 to the new process, and the process ID of
///         the new process to the old process.
extern pid_t fork();

/// @brief Replaces the current process image with a new process image (argument list).
/// @param path The absolute path to the binary file to execute.
/// @param arg  A list of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @param ...  The argument list.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execl(const char *path, const char *arg, ...);

/// @brief Replaces the current process image with a new process image (argument list).
/// @param file The name of the binary file to execute, which is searched inside the
///             paths specified inside the PATH environmental variable.
/// @param arg  A list of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @param ...  The argument list.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execlp(const char *file, const char *arg, ...);

/// @brief Replaces the current process image with a new process image (argument list).
/// @param path The absolute path to the binary file to execute.
/// @param arg  A list of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @param ...  The argument list which contains as last argument the environment.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execle(const char *path, const char *arg, ...);

/// @brief Replaces the current process image with a new process image (argument list).
/// @param file The name of the binary file to execute, which is searched inside the
///             paths specified inside the PATH environmental variable.
/// @param arg  A list of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @param ...  The argument list which contains as last argument the environment.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execlpe(const char *file, const char *arg, ...);

/// @brief Replaces the current process image with a new process image (argument vector).
/// @param path The absolute path to the binary file to execute.
/// @param argv A vector of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execv(const char *path, char *const argv[]);

/// @brief Replaces the current process image with a new process image (argument vector).
/// @param file The name of the binary file to execute, which is searched inside the
///             paths specified inside the PATH environmental variable.
/// @param argv A vector of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execvp(const char *file, char *const argv[]);

/// @brief Replaces the current process image with a new process
///        image (argument vector), allows the caller to specify
///        the environment of the executed program via `envp`.
/// @param path The absolute path to the binary file to execute.
/// @param argv A vector of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @param envp A vector of one or more pointers to null-terminated strings that represent
///             the environment list available to the executed program.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execve(const char *path, char *const argv[], char *const envp[]);

/// @brief Replaces the current process image with a new process
///        image (argument vector), allows the caller to specify
///        the environment of the executed program via `envp`.
/// @param file The name of the binary file to execute, which is searched inside the
///             paths specified inside the PATH environmental variable.
/// @param argv A vector of one or more pointers to null-terminated strings that represent
///             the argument list available to the executed program.
/// @param envp A vector of one or more pointers to null-terminated strings that represent
///             the environment list available to the executed program.
/// @return Returns -1 only if an error has occurred, and sets errno.
int execvpe(const char *file, char *const argv[], char *const envp[]);

/// @brief Adds inc to the nice value for the calling thread.
/// @param inc The value to add to the nice.
/// @return On success, the new nice value is returned. On error, -1 is
///         returned, and errno is set appropriately.
int nice(int inc);

/// @brief Reboots the system, or enables/disables the reboot keystroke.
/// @param magic1 fails (with the error EINVAL) unless equals LINUX_REBOOT_MAGIC1.
/// @param magic2 fails (with the error EINVAL) unless equals LINUX_REBOOT_MAGIC2.
/// @param cmd The command to send to the reboot.
/// @param arg Argument passed with some specific commands.
/// @return For the values of cmd that stop or restart the system, a
///         successful call to reboot() does not return. For the other cmd
///         values, zero is returned on success. In all cases, -1 is
///         returned on failure, and errno is set appropriately.
int reboot(int magic1, int magic2, unsigned int cmd, void *arg);

/// @brief Get current working directory.
/// @param buf  The array where the CWD will be copied.
/// @param size The size of the array.
/// @return On success, returns the same pointer to buf.
///         On failure, returnr NULL, and errno is set to indicate the error.
char *getcwd(char *buf, size_t size);

/// @brief Changes the current working directory to the given path.
/// @param path The new current working directory.
int chdir(char const *path);

/// @brief Is identical to chdir(), the only difference is that the
///        directory is given as an open file descriptor.
/// @param fd The file descriptor of the open directory.
int fchdir(int fd);

/// Provide access to the directory entries.
/// @param fd The fd pointing to the opened directory.
/// @param dirp The buffer where de data should be placed.
/// @param count The size of the buffer.
/// @return On success, the number of bytes read is returned.  On end of
///         directory, 0 is returned.  On error, -1 is returned, and errno is set
///         appropriately.
int getdents(int fd, dirent_t *dirp, unsigned int count);

/// @brief Send signal to calling thread after desired seconds.
int alarm(int seconds);