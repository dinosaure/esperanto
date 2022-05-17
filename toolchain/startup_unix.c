#include "cosmopolitan/cosmopolitan.h"

#pragma GCC push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

struct socket_option {
  int level;
  int option;
};

extern void _esperanto_init_permission(const int[]);
extern void _esperanto_init_open_flag(const int[]);
extern void _esperanto_init_socket_type(const int[]);
extern void _esperanto_init_sockopt_bool(const struct socket_option[]);
extern void _esperanto_init_sockopt_int(const struct socket_option[]);
extern void _esperanto_init_sockopt_linger(const struct socket_option[]);
extern void _esperanto_init_sockopt_timeval(const struct socket_option[]);
extern void _esperanto_init_sockopt_unix_error(const struct socket_option[]);
extern void _esperanto_init_error(const int[]);
extern void _esperanto_init_wait_flag(const int[]);
extern void _esperanto_init_unix_signals(const int[]);

struct termios terminal_status;

enum { Bool, Enum, Speed, Char, End };

enum { Input, Output };

#define iflags ((long)(&terminal_status.c_iflag))
#define oflags ((long)(&terminal_status.c_oflag))
#define cflags ((long)(&terminal_status.c_cflag))
#define lflags ((long)(&terminal_status.c_lflag))

struct speed_e {
  speed_t speed;
  int baud;
};

extern void _esperanto_init_terminal_io_descr(const long[]);
extern void _esperanto_init_speedtable(const struct speed_e[]);
extern void _esperanto_init_when_flag_table(const int[]);
extern void _esperanto_init_queue_flag_table(const int[]);

void _esperanto_init_unix() {
  int access_permission_table[] = {
      R_OK, W_OK,
#ifdef _WIN32
      /* Since there is no concept of execute permission on Windows,
         we fall b+ack to the read permission */
      R_OK,
#else
      X_OK,
#endif
      F_OK};
  int open_flag_table[15] = {
      O_RDONLY, O_WRONLY, O_RDWR,  O_NONBLOCK, O_APPEND, O_CREAT, O_TRUNC,
      O_EXCL,   O_NOCTTY, O_DSYNC, O_SYNC,     O_RSYNC,  0, /* O_SHARE_DELETE,
                                                               Windows-only */
      0, /* O_CLOEXEC, treated specially */
      0  /* O_KEEPEXEC, treated specially */
  };
  int socket_domain_table[] = {PF_UNIX, PF_INET, PF_INET6, PF_UNSPEC};
  struct socket_option sockopt_bool[] = {
      {SOL_SOCKET, SO_DEBUG},      {SOL_SOCKET, SO_BROADCAST},
      {SOL_SOCKET, SO_REUSEADDR},  {SOL_SOCKET, SO_KEEPALIVE},
      {SOL_SOCKET, SO_DONTROUTE},  {SOL_SOCKET, SO_OOBINLINE},
      {SOL_SOCKET, SO_ACCEPTCONN}, {IPPROTO_TCP, TCP_NODELAY},
      {IPPROTO_IPV6, IPV6_V6ONLY}, {SOL_SOCKET, SO_REUSEPORT}};

  struct socket_option sockopt_int[] = {
      {SOL_SOCKET, SO_SNDBUF},   {SOL_SOCKET, SO_RCVBUF},
      {SOL_SOCKET, SO_ERROR},    {SOL_SOCKET, SO_TYPE},
      {SOL_SOCKET, SO_RCVLOWAT}, {SOL_SOCKET, SO_SNDLOWAT}};

  struct socket_option sockopt_linger[] = {{SOL_SOCKET, SO_LINGER}};

  struct socket_option sockopt_timeval[] = {{SOL_SOCKET, SO_RCVTIMEO},
                                            {SOL_SOCKET, SO_SNDTIMEO}};

  struct socket_option sockopt_unix_error[] = {{SOL_SOCKET, SO_ERROR}};

  int error_table[] = {
      E2BIG,           EACCES,
      EAGAIN,          EBADF,
      EBUSY,           ECHILD,
      EDEADLK,         EDOM,
      EEXIST,          EFAULT,
      EFBIG,           EINTR,
      EINVAL,          EIO,
      EISDIR,          EMFILE,
      EMLINK,          ENAMETOOLONG,
      ENFILE,          ENODEV,
      ENOENT,          ENOEXEC,
      ENOLCK,          ENOMEM,
      ENOSPC,          ENOSYS,
      ENOTDIR,         ENOTEMPTY,
      ENOTTY,          ENXIO,
      EPERM,           EPIPE,
      ERANGE,          EROFS,
      ESPIPE,          ESRCH,
      EXDEV,           EWOULDBLOCK,
      EINPROGRESS,     EALREADY,
      ENOTSOCK,        EDESTADDRREQ,
      EMSGSIZE,        EPROTOTYPE,
      ENOPROTOOPT,     EPROTONOSUPPORT,
      ESOCKTNOSUPPORT, EOPNOTSUPP,
      EPFNOSUPPORT,    EAFNOSUPPORT,
      EADDRINUSE,      EADDRNOTAVAIL,
      ENETDOWN,        ENETUNREACH,
      ENETRESET,       ECONNABORTED,
      ECONNRESET,      ENOBUFS,
      EISCONN,         ENOTCONN,
      ESHUTDOWN,       ETOOMANYREFS,
      ETIMEDOUT,       ECONNREFUSED,
      EHOSTDOWN,       EHOSTUNREACH,
      ELOOP,           EOVERFLOW /*, EUNKNOWNERR */
  };
  int wait_flag_table[] = {WNOHANG, WUNTRACED};
  int sigprocmask_cmd[3] = {SIG_SETMASK, SIG_BLOCK, SIG_UNBLOCK};

  long terminal_io_descr[] = {
      /* Input modes */
      Bool, iflags, IGNBRK, Bool, iflags, BRKINT, Bool, iflags, IGNPAR, Bool,
      iflags, PARMRK, Bool, iflags, INPCK, Bool, iflags, ISTRIP, Bool, iflags,
      INLCR, Bool, iflags, IGNCR, Bool, iflags, ICRNL, Bool, iflags, IXON, Bool,
      iflags, IXOFF,
      /* Output modes */
      Bool, oflags, OPOST,
      /* Control modes */
      Speed, Output, Speed, Input, Enum, cflags, 5, 4, CSIZE, CS5, CS6, CS7,
      CS8, Enum, cflags, 1, 2, CSTOPB, 0, CSTOPB, Bool, cflags, CREAD, Bool,
      cflags, PARENB, Bool, cflags, PARODD, Bool, cflags, HUPCL, Bool, cflags,
      CLOCAL,
      /* Local modes */
      Bool, lflags, ISIG, Bool, lflags, ICANON, Bool, lflags, NOFLSH, Bool,
      lflags, ECHO, Bool, lflags, ECHOE, Bool, lflags, ECHOK, Bool, lflags,
      ECHONL,
      /* Control characters */
      Char, VINTR, Char, VQUIT, Char, VERASE, Char, VKILL, Char, VEOF, Char,
      VEOL, Char, VMIN, Char, VTIME, Char, VSTART, Char, VSTOP, End};

#undef iflags
#undef oflags
#undef cflags
#undef lflags

  struct speed_e speedtable[] = {

      /* standard speeds */
      {B0, 0},
      {B50, 50},
      {B75, 75},
      {B110, 110},
      {B134, 134},
      {B150, 150},
#ifdef B200
      /* Shouldn't need to be ifdef'd but I'm not sure it's available
         everywhere. */
      {B200, 200},
#endif
      {B300, 300},
      {B600, 600},
      {B1200, 1200},
      {B1800, 1800},
      {B2400, 2400},
      {B4800, 4800},
      {B9600, 9600},
      {B19200, 19200},
      {B38400, 38400},

  /* usual extensions */
#ifdef B57600
      {B57600, 57600},
#endif
#ifdef B115200
      {B115200, 115200},
#endif
#ifdef B230400
      {B230400, 230400},
#endif

  /* Linux extensions */
#ifdef B460800
      {B460800, 460800},
#endif
#ifdef B500000
      {B500000, 500000},
#endif
#ifdef B576000
      {B576000, 576000},
#endif
#ifdef B921600
      {B921600, 921600},
#endif
#ifdef B1000000
      {B1000000, 1000000},
#endif
#ifdef B1152000
      {B1152000, 1152000},
#endif
#ifdef B1500000
      {B1500000, 1500000},
#endif
#ifdef B2000000
      {B2000000, 2000000},
#endif
#ifdef B2500000
      {B2500000, 2500000},
#endif
#ifdef B3000000
      {B3000000, 3000000},
#endif
#ifdef B3500000
      {B3500000, 3500000},
#endif
#ifdef B4000000
      {B4000000, 4000000},
#endif

  /* MacOS extensions */
#ifdef B7200
      {B7200, 7200},
#endif
#ifdef B14400
      {B14400, 14400},
#endif
#ifdef B28800
      {B28800, 28800},
#endif
#ifdef B76800
      {B76800, 76800},
#endif

  /* Cygwin extensions (in addition to the Linux ones) */
#ifdef B128000
      {B128000, 128000},
#endif
#ifdef B256000
      {B256000, 256000},
#endif
  };

  int when_flag_table[] = {TCSANOW, TCSADRAIN, TCSAFLUSH};

  int queue_flag_table[] = {TCIFLUSH, TCOFLUSH, TCIOFLUSH};

  _esperanto_init_permission(access_permission_table);
  _esperanto_init_open_flag(open_flag_table);
  _esperanto_init_socket_type(socket_domain_table);
  _esperanto_init_sockopt_bool(sockopt_bool);
  _esperanto_init_sockopt_int(sockopt_int);
  _esperanto_init_sockopt_linger(sockopt_linger);
  _esperanto_init_sockopt_timeval(sockopt_timeval);
  _esperanto_init_sockopt_unix_error(sockopt_unix_error);
  _esperanto_init_error(error_table);
  _esperanto_init_wait_flag(wait_flag_table);
  // #ifdef POSIX_SIGNALS
  _esperanto_init_unix_signals(sigprocmask_cmd);
  // #endif
  _esperanto_init_terminal_io_descr(terminal_io_descr);
  _esperanto_init_speedtable(speedtable);
  _esperanto_init_when_flag_table(when_flag_table);
  _esperanto_init_queue_flag_table(queue_flag_table);
}

#pragma GCC pop
