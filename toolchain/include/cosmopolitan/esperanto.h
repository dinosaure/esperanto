#ifdef __OCAML__
#ifndef __ESPERANTO__
#define __ESPERANTO__

#pragma GCC diagnostic ignored "-Wredundant-decls"

#undef SIGUSR1
#undef SIGUSR2
#undef SIGCHLD
#undef SIGCONT
#undef SIGSTOP
#undef SIGTSTP
#undef SIGBUS
#undef SIGPOLL
#undef SIGSYS
#undef SIGURG

#define O_CREAT    0
#define O_TRUNC    0
#define O_APPEND   0
#define O_EXCL     0
#define O_NONBLOCK 0

#endif /* __ESPERANTO__ */
#endif /* __OCAML__ */
