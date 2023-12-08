#ifndef COSMOPOLITAN_LIBC_DNS_SERVICESTXT_H_
#define COSMOPOLITAN_LIBC_DNS_SERVICESTXT_H_
#include "libc/sock/sock.h"
#include "libc/stdio/stdio.h"
COSMOPOLITAN_C_START_

char *GetSystemDirectoryPath(char *, size_t, const char *);
int LookupServicesByPort(const int, char *, size_t, char *, size_t,
                         const char *) paramsnonnull((2, 4));
int LookupServicesByName(const char *, char *, size_t, char *, size_t,
                         const char *) paramsnonnull((1, 2));
const char *GetServicesTxtPath(char *, size_t);

/* TODO: implement like struct HostsTxt? */

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_DNS_SERVICESTXT_H_ */
