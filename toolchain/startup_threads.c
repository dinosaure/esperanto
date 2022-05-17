#include "cosmopolitan/cosmopolitan.h"

#pragma GCC push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

extern void _esperanto_init_systhreads_signals(const int[]);

void _esperanto_init_systhreads() {
  int sigmask_cmd[3] = {SIG_SETMASK, SIG_BLOCK, SIG_UNBLOCK};

  _esperanto_init_systhreads_signals(sigmask_cmd);
}

#pragma GCC pop
