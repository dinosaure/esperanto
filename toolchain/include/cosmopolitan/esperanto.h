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

#undef R_OK
#undef W_OK
#undef X_OK
#undef F_OK

#define R_OK 0
#define W_OK 0
#define X_OK 0
#define F_OK 0

#define NGROUPS_MAX _POSIX_NGROUPS_MAX

#undef O_NOCTTY
#undef O_DSYNC
#undef O_SYNC
#undef O_RSYNC

#define O_NOCTTY 0
#define O_DSYNC  0
#define O_SYNC   0
#define O_RSYNC  0

#undef PF_UNIX
#undef PF_INET
#undef PF_INET6
#undef PF_UNSPEC

#define PF_UNIX   0
#define PF_INET   0
#define PF_INET6  0
#define PF_UNSPEC 0

#undef SOL_SOCKET
#undef SO_DEBUG
#undef SO_BROADCAST
#undef SO_REUSEADDR
#undef SO_REUSEPORT
#undef SO_KEEPALIVE
#undef SO_DONTROUTE
#undef SO_OOBINLINE
#undef SO_ACCEPTCONN
#undef SO_SNDBUF
#undef SO_RCVBUF
#undef SO_ERROR
#undef SO_TYPE
#undef SO_RCVLOWAT
#undef SO_SNDLOWAT
#undef SO_LINGER
#undef SO_SNDTIMEO
#undef SO_RCVTIMEO
#undef TCP_NODELAY
#undef IPPROTO_IPV6
#undef IPV6_V6ONLY

#define SOL_SOCKET 0
#define SO_DEBUG 0
#define SO_BROADCAST 0
#define SO_REUSEADDR 0
#define SO_REUSEPORT 0
#define SO_KEEPALIVE 0
#define SO_DONTROUTE 0
#define SO_OOBINLINE 0
#define SO_ACCEPTCONN 0
#define SO_SNDBUF 0
#define SO_RCVBUF 0
#define SO_ERROR 0
#define SO_TYPE 0
#define SO_RCVLOWAT 0
#define SO_SNDLOWAT 0
#define SO_LINGER 0
#define SO_SNDTIMEO 0
#define SO_RCVTIMEO 0
#define TCP_NODELAY 0
#define IPPROTO_IPV6 0
#define IPV6_V6ONLY 0

#undef E2BIG
#undef EACCES
#undef EAGAIN
#undef EBADF
#undef EBUSY
#undef ECHILD
#undef EDEADLK
#undef EDOM
#undef EEXIST
#undef EFAULT
#undef EFBIG
#undef EINTR
#undef EINVAL
#undef EIO
#undef EISDIR
#undef EMFILE
#undef EMLINK
#undef ENAMETOOLONG
#undef ENFILE
#undef ENODEV
#undef ENOENT
#undef ENOEXEC
#undef ENOLCK
#undef ENOMEM
#undef ENOSPC
#undef ENOSYS
#undef ENOTDIR
#undef ENOTEMPTY
#undef ENOTTY
#undef ENXIO
#undef EPERM
#undef EPIPE
#undef ERANGE
#undef EROFS
#undef ESPIPE
#undef ESRCH
#undef EXDEV
#undef EWOULDBLOCK
#undef EINPROGRESS
#undef EALREADY
#undef ENOTSOCK
#undef EDESTADDRREQ
#undef EMSGSIZE
#undef EPROTOTYPE
#undef ENOPROTOOPT
#undef EPROTONOSUPPORT
#undef ESOCKTNOSUPPORT
#undef EOPNOTSUPP
#undef EPFNOSUPPORT
#undef EAFNOSUPPORT
#undef EADDRINUSE
#undef EADDRNOTAVAIL
#undef ENETDOWN
#undef ENETUNREACH
#undef ENETRESET
#undef ECONNABORTED
#undef ECONNRESET
#undef ENOBUFS
#undef EISCONN
#undef ENOTCONN
#undef ESHUTDOWN
#undef ETOOMANYREFS
#undef ETIMEDOUT
#undef ECONNREFUSED
#undef EHOSTDOWN
#undef EHOSTUNREACH
#undef ELOOP
#undef EOVERFLOW
#undef EUNKNOWNERR

#define E2BIG 0
#define EACCES 0
#define EAGAIN 0
#define EBADF 0
#define EBUSY 0
#define ECHILD 0
#define EDEADLK 0
#define EDOM 0
#define EEXIST 0
#define EFAULT 0
#define EFBIG 0
#define EINTR 0
#define EINVAL 0
#define EIO 0
#define EISDIR 0
#define EMFILE 0
#define EMLINK 0
#define ENAMETOOLONG 0
#define ENFILE 0
#define ENODEV 0
#define ENOENT 0
#define ENOEXEC 0
#define ENOLCK 0
#define ENOMEM 0
#define ENOSPC 0
#define ENOSYS 0
#define ENOTDIR 0
#define ENOTEMPTY 0
#define ENOTTY 0
#define ENXIO 0
#define EPERM 0
#define EPIPE 0
#define ERANGE 0
#define EROFS 0
#define ESPIPE 0
#define ESRCH 0
#define EXDEV 0
#define EWOULDBLOCK 0
#define EINPROGRESS 0
#define EALREADY 0
#define ENOTSOCK 0
#define EDESTADDRREQ 0
#define EMSGSIZE 0
#define EPROTOTYPE 0
#define ENOPROTOOPT 0
#define EPROTONOSUPPORT 0
#define ESOCKTNOSUPPORT 0
#define EOPNOTSUPP 0
#define EPFNOSUPPORT 0
#define EAFNOSUPPORT 0
#define EADDRINUSE 0
#define EADDRNOTAVAIL 0
#define ENETDOWN 0
#define ENETUNREACH 0
#define ENETRESET 0
#define ECONNABORTED 0
#define ECONNRESET 0
#define ENOBUFS 0
#define EISCONN 0
#define ENOTCONN 0
#define ESHUTDOWN 0
#define ETOOMANYREFS 0
#define ETIMEDOUT 0
#define ECONNREFUSED 0
#define EHOSTDOWN 0
#define EHOSTUNREACH 0
#define ELOOP 0
#define EOVERFLOW 0
#define EUNKNOWNERR 0

#if defined(HAS_WAITPID) || defined(HAS_WAIT4)
#undef WNOHANG
#undef WUNTRACED

#define WNOHANG 0
#define WUNTRACED 0
#endif /* defined(HAS_WAITPID) || defined(HAS_WAIT4) */

#undef SIG_SETMASK
#undef SIG_BLOCK
#undef SIG_UNBLOCK

#define SIG_SETMASK 0
#define SIG_BLOCK 0
#define SIG_UNBLOCK 0

#endif /* __OCAML_ESPERANTO__ */
#endif /* CAML_NAME_SPACE */

#ifndef __ESPERANTO_OFF_T__
#define __ESPERANTO_OFF_T__

/* XXX(dinosaure): [pth] requires [off_t] but recognizes it via `cc -E`.
 * However [cosmopolitan] defines it with `#define`. The result of `cc -E` is
 * **without** `off_t`. This trick _undef_ `off_t` and redefine it with
 * `typedef`. By this way, [pth] is able to recognize the existence of this
 * type and it does not try to redefine it by itself. */

#undef off_t
typedef int64_t off_t;

#endif /* __ESPERANTO_OFF_T__ */

#ifndef __ESPERANTO_SIGJMP_BUF__
#define __ESPERANTO_SIGJMP_BUF__

#ifndef __unused
#define __unused(x) x __attribute__((unused))
#endif

typedef jmp_buf sigjmp_buf;

#ifdef CAML_NAME_SPACE
#define sigsetjmp(env, savesigs) setjmp(env)
/* XXX(dinosaure): ANY calls of `sigsetjmp` are done with [savesigs = 0] into
 * OCaml. `sigsetjmp` can have an other behavior ONLY IF [savesigs <> 0]. */
#endif /* CAML_NAME_SPACE */

#endif /* __ESPERANTO_SIGJMP_BUF__ */
