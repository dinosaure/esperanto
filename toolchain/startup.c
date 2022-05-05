#include "cosmopolitan/cosmopolitan.h"

#pragma GCC push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

/* XXX(dinosaure): we tweak the caml runtime which should provide these
 * functions. The goal is to reset [sys_open_flags]/[posix_signals] by right
 * values given by Cosmopolitan **after** the APE boot. */
extern void _esperanto_init_sys_open_flags(const int[]);
extern void _esperanto_init_posix_signals(const int[]);

int main(int argc, char *argv[]) {
  int open_flags[] = {
      O_RDONLY, O_WRONLY, O_APPEND | O_WRONLY, O_CREAT, O_TRUNC, O_EXCL,
      0,        0,        O_NONBLOCK}; // Cosmopolitan does not provide O_BINARY
                                       // and O_TRUNC
  int posix_signals[] = {SIGABRT, SIGALRM,   SIGFPE,  SIGHUP,  SIGILL,  SIGINT,
                         SIGKILL, SIGPIPE,   SIGQUIT, SIGSEGV, SIGTERM, SIGUSR1,
                         SIGUSR2, SIGCHLD,   SIGCONT, SIGSTOP, SIGTSTP, SIGTTIN,
                         SIGTTOU, SIGVTALRM, SIGPROF, SIGBUS,  SIGPOLL, SIGSYS,
                         SIGTRAP, SIGURG,    SIGXCPU, SIGXFSZ};

  _esperanto_init_sys_open_flags(open_flags);
  _esperanto_init_posix_signals(posix_signals);

  caml_startup(
      argv); // TODO(dinosaure): check if [argv] terminates with [NULL].

  return (0);
}

#pragma GCC pop
