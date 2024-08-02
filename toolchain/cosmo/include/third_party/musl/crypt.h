#ifndef COSMOPOLITAN_THIRD_PARTY_MUSL_CRYPT_H_
#define COSMOPOLITAN_THIRD_PARTY_MUSL_CRYPT_H_
COSMOPOLITAN_C_START_

struct crypt_data {
  int initialized;
  char __buf[256];
};

char *crypt(const char *, const char *) libcesque;
char *crypt_r(const char *, const char *, struct crypt_data *) libcesque;

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_THIRD_PARTY_MUSL_CRYPT_H_ */
