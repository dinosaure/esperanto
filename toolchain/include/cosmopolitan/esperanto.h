#ifdef CAML_NAME_SPACE
#ifndef __OCAML_ESPERANTO__
#define __OCAML_ESPERANTO__

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

#undef O_CREAT
#undef O_TRUNC
#undef O_APPEND
#undef O_EXCL
#undef O_NONBLOCK

#define O_CREAT    0
#define O_TRUNC    0
#define O_APPEND   0
#define O_EXCL     0
#define O_NONBLOCK 0

#endif /* __OCAML_ESPERANTO__ */
#endif /* CAML_NAME_SPACE */
