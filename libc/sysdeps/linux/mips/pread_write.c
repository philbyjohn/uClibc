/* vi: set sw=4 ts=4: */
/*
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <endian.h>
#include <sgidefs.h>

#ifdef __NR_pread64
# ifdef __NR_pread
#  error "__NR_pread and __NR_pread64 both defined???"
# endif
# define __NR_pread __NR_pread64
#endif

#ifdef __NR_pread
# if _MIPS_SIM == _MIPS_SIM_ABI64 /* glibc uses it for N32 as well */
#  define __NR___syscall_pread __NR_pread
static _syscall4(ssize_t, __syscall_pread, int, fd, void *, buf, size_t, count, off_t, offset)
#  define MY_PREAD(fd, buf, count, offset) \
	__syscall_pread(fd, buf, count, offset)
#  define MY_PREAD64(fd, buf, count, offset) \
	__syscall_pread(fd, buf, count, offset)
# else /* O32 || N32 */
#  define __NR___syscall_pread __NR_pread
static _syscall6(ssize_t, __syscall_pread, int, fd, void *, buf,
		 size_t, count, int, dummy, off_t, offset_hi, off_t, offset_lo)
#  define MY_PREAD(fd, buf, count, offset) \
	__syscall_pread(fd, buf, count, 0, OFF_HI_LO(offset))
#  define MY_PREAD64(fd, buf, count, offset) \
	__syscall_pread(fd, buf, count, 0, OFF64_HI_LO(offset))
# endif
#endif

#ifdef __NR_pwrite64
# ifdef __NR_pwrite
#  error "__NR_pwrite and __NR_pwrite64 both defined???"
# endif
# define __NR_pwrite __NR_pwrite64
#endif

#ifdef __NR_pwrite
# if _MIPS_SIM == _MIPS_SIM_ABI64 /* glibc uses it for N32 as well */
#  define __NR___syscall_pwrite __NR_pwrite
static _syscall4(ssize_t, __syscall_pwrite, int, fd, const void *, buf, size_t, count, off_t, offset)
#  define MY_PWRITE(fd, buf, count, offset) \
	__syscall_pwrite(fd, buf, count, offset)
#  define MY_PWRITE64(fd, buf, count, offset) \
	__syscall_pwrite(fd, buf, count, offset)
# else /* O32 || N32 */
#  define __NR___syscall_pwrite __NR_pwrite
static _syscall6(ssize_t, __syscall_pwrite, int, fd, const void *, buf,
		 size_t, count, int, dummy, off_t, offset_hi, off_t, offset_lo)
#  define MY_PWRITE(fd, buf, count, offset) \
	__syscall_pwrite(fd, buf, count, 0, OFF_HI_LO(offset))
#  define MY_PWRITE64(fd, buf, count, offset) \
	__syscall_pwrite(fd, buf, count, 0, OFF64_HI_LO(offset))
# endif
#endif

#include "../common/pread_write.c"
