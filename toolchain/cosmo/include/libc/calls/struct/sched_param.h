#ifndef COSMOPOLITAN_LIBC_CALLS_STRUCT_SCHED_PARAM_H_
#define COSMOPOLITAN_LIBC_CALLS_STRUCT_SCHED_PARAM_H_
#include "libc/calls/struct/timespec.h"
COSMOPOLITAN_C_START_

struct sched_param {
  int32_t sched_priority;
};

int sched_get_priority_max(int);
int sched_get_priority_min(int);
int sched_getparam(int, struct sched_param *);
int sched_getscheduler(int);
int sched_rr_get_interval(int, struct timespec *);
int sched_setparam(int, const struct sched_param *);
int sched_setscheduler(int, int, const struct sched_param *);

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_CALLS_STRUCT_SCHED_PARAM_H_ */
