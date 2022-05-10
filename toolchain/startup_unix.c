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
}

#pragma GCC pop
