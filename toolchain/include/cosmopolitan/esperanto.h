#ifdef CAML_NAME_SPACE
#ifndef __OCAML_ESPERANTO__
#define __OCAML_ESPERANTO__

#pragma GCC diagnostic ignored "-Wredundant-decls"
/* XXX(dinosaure): only for OCaml and [./configure]. */

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

// #if defined(HAS_WAITPID) || defined(HAS_WAIT4)
#undef WNOHANG
#undef WUNTRACED

#define WNOHANG 0
#define WUNTRACED 0
// #endif /* defined(HAS_WAITPID) || defined(HAS_WAIT4) */

#undef SIG_SETMASK
#undef SIG_BLOCK
#undef SIG_UNBLOCK

#define SIG_SETMASK 0
#define SIG_BLOCK 0
#define SIG_UNBLOCK 0

#undef IGNBRK
#undef BRKINT
#undef IGNPAR
#undef PARMRK
#undef INPCK
#undef ISTRIP
#undef INLCR
#undef IGNCR
#undef ICRNL
#undef IXON
#undef IXOFF
#undef OPOST
#undef CSIZE
#undef CS5
#undef CS6
#undef CS7
#undef CS8
#undef CSTOPB
#undef CREAD
#undef PARENB
#undef PARODD
#undef HUPCL
#undef CLOCAL
#undef ISIG
#undef ICANON
#undef NOFLSH
#undef ECHO
#undef ECHOE
#undef ECHOK
#undef ECHONL
#undef VINTR
#undef VQUIT
#undef VERASE
#undef VKILL
#undef VEOF
#undef VEOL
#undef VMIN
#undef VTIME
#undef VSTART
#undef VSTOP

#define IGNBRK 0
#define BRKINT 0
#define IGNPAR 0
#define PARMRK 0
#define INPCK 0
#define ISTRIP 0
#define INLCR 0
#define IGNCR 0
#define ICRNL 0
#define IXON 0
#define IXOFF 0
#define OPOST 0
#define CSIZE 0
#define CS5 0
#define CS6 0
#define CS7 0
#define CS8 0
#define CSTOPB 0
#define CREAD 0
#define PARENB 0
#define PARODD 0
#define HUPCL 0
#define CLOCAL 0
#define ISIG 0
#define ICANON 0
#define NOFLSH 0
#define ECHO 0
#define ECHOE 0
#define ECHOK 0
#define ECHONL 0
#define VINTR 0
#define VQUIT 0
#define VERASE 0
#define VKILL 0
#define VEOF 0
#define VEOL 0
#define VMIN 0
#define VTIME 0
#define VSTART 0
#define VSTOP 0

#undef B0
#undef B50
#undef B75
#undef B110
#undef B134
#undef B150
#undef B200
#undef B300
#undef B600
#undef B1200
#undef B1800
#undef B2400
#undef B4800
#undef B9600
#undef B19200
#undef B38400
#undef B57600
#undef B115200
#undef B230400
#undef B460800
#undef B500000
#undef B576000
#undef B921600
#undef B1000000
#undef B1152000
#undef B1500000
#undef B2000000
#undef B2500000
#undef B3000000
#undef B3500000
#undef B4000000
#undef B7200
#undef B14400
#undef B28800
#undef B76800
#undef B128000
#undef B256000

#define B0 0
#define B50 0
#define B75 0
#define B110 0
#define B134 0
#define B150 0
#define B200 0
#define B300 0
#define B600 0
#define B1200 0
#define B1800 0
#define B2400 0
#define B4800 0
#define B9600 0
#define B19200 0
#define B38400 0
#define B57600 0
#define B115200 0
#define B230400 0
#define B460800 0
#define B500000 0
#define B576000 0
#define B921600 0
#define B1000000 0
#define B1152000 0
#define B1500000 0
#define B2000000 0
#define B2500000 0
#define B3000000 0
#define B3500000 0
#define B4000000 0
#define B7200 0
#define B14400 0
#define B28800 0
#define B76800 0
#define B128000 0
#define B256000 0

#undef TCOOFF
#undef TCOON
#undef TCIOFF
#undef TCION

#define TCOOFF 0
#define TCOON 0
#define TCIOFF 0
#define TCION 0

#undef TCIFLUSH
#undef TCOFLUSH
#undef TCIOFLUSH

#define TCIFLUSH 0
#define TCOFLUSH 0
#define TCIOFLUSH 0

/* XXX(dinosaure): This set of functions is a relicat (from [pth]) which can be
 * interesting to plug a specific implementation of these syscalls at the link
 * time. On [cc.in]/[ld.in], you can see the [${DRIVER}] variable which can be
 * set by the user with something else than Cosmopolitan. */
extern pid_t   __esperanto_fork(void);
extern int     __esperanto_nanosleep(const struct timespec *, struct timespec *);
extern int     __esperanto_usleep(unsigned int);
extern int     __esperanto_system(const char *);
extern int     __esperanto_sigwait(const sigset_t *, int *);
extern int     __esperanto_waitpid(pid_t, int *, int);
extern int     __esperanto_connect(int, struct sockaddr *, socklen_t);
extern int     __esperanto_accept(int, struct sockaddr *, socklen_t);
extern int     __esperanto_select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
extern int     __esperanto_poll(struct pollfd *, nfds_t, int);
extern ssize_t __esperanto_read(int, void *, size_t);
extern ssize_t __esperanto_write(int, void *, size_t);
extern ssize_t __esperanto_readv(int, const struct iovec *, int);
extern ssize_t __esperanto_writev(int, const struct iovec *, int);
extern ssize_t __esperanto_recv(int, void *, size_t, int);
extern ssize_t __esperanto_send(int, const void *, size_t, int);
extern ssize_t __esperanto_recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
extern ssize_t __esperanto_sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
extern ssize_t __esperanto_pread(int, void *, size_t, off_t);
extern ssize_t __esperanto_pwrite(int, const void *, size_t, off_t);

#define fork       __esperanto_fork
#define sleep      __esperanto_sleep
#define nanosleep  __esperanto_nanosleep
#define usleep     __esperanto_usleep
#define system     __esperanto_system
#define sigwait    __esperanto_sigwait
#define waitpid    __esperanto_waitpid
#define connect    __esperanto_connect
#define accept     __esperanto_accept
#define select     __esperanto_select
#define poll       __esperanto_poll
#define read       __esperanto_read
#define write      __esperanto_write
#define readv      __esperanto_readv
#define writev     __esperanto_writev
#define recv       __esperanto_recv
#define send       __esperanto_send
#define recvfrom   __esperanto_recvfrom
#define sendto     __esperanto_sendto
#define pread      __esperanto_pread
#define pwrite     __esperanto_pwrite

#endif /* __OCAML_ESPERANTO__ */
#endif /* CAML_NAME_SPACE */

// XXX(dinosaure): for [mirage-crypto]
#define __MIRAGE_CRYPTO_NO_ACCELERATE__
#define MIN(a, b) ((a < b) ? (a) : (b))
// XXX(dinosaure): on FreeBSD, MIN is undefined & required by [mirage-crypto]
#pragma GCC diagnostic ignored "-Wunused-variable"
// XXX(dinosaure): for [ocaml-gmp]
// Some warnings are promoted as errors due to Cosmopolitan's pragma
// The existence of [FILE*] is checked by the definition of [__DEFINED_FILE]
// as musl does.
#pragma GCC diagnostic ignored "-Wuninitialized"
#if !defined(__clang__) // XXX(dinosaure): emit a warning with clang
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#pragma GCC diagnostic ignored "-Wredundant-decls"
#define __DEFINED_FILE
#undef __GNUC__
