#ifndef COSMOPOLITAN_LIBC_DNS_PROTOTXT_H_
#define COSMOPOLITAN_LIBC_DNS_PROTOTXT_H_
#include "libc/sock/sock.h"
#include "libc/stdio/stdio.h"
COSMOPOLITAN_C_START_

const char *GetProtocolsTxtPath(char *, size_t);

int LookupProtoByNumber(const int, char *, size_t, const char *)
    paramsnonnull((2));
int LookupProtoByName(const char *, char *, size_t, const char *)
    paramsnonnull((1, 2));

/* TODO: implement like struct HostsTxt? */

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_DNS_PROTOTXT_H_ */
