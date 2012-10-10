/* vi: set sw=4 ts=4: */
/*
 * link() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

#if defined(__NR_linkat) && !defined(__NR_link)
int link(const char *oldpath, const char *newpath)
{
	return linkat(AT_FDCWD, oldpath, AT_FDCWD, newpath, 0);
}
#else
_syscall2(int, link, const char *, oldpath, const char *, newpath)
#endif
