#include "cosmopolitan/cosmopolitan.h"

extern pid_t __pthread_fork(void);
extern unsigned int __pthread_sleep(unsigned int);
extern int __pthread_nanosleep(const struct timespec *, struct timespec *);
extern int __pthread_usleep(unsigned int);
extern int __pthread_system(const char *);
extern int __pthread_sigwait(const sigset_t *, int *);
extern pid_t __pthread_waitpid(pid_t, int *, int);
extern int __pthread_connect(int, struct sockaddr *, socklen_t);
extern int __pthread_accept(int, struct sockaddr *, socklen_t *);
extern int __pthread_select(int, fd_set *, fd_set *, fd_set *,
                            struct timeval *);
extern int __pthread_poll(struct pollfd *, nfds_t, int);
extern ssize_t __pthread_read(int, void *, size_t);
extern ssize_t __pthread_write(int, const void *, size_t);
extern ssize_t __pthread_readv(int, const struct iovec *, int);
extern ssize_t __pthread_writev(int, const struct iovec *, int);
extern ssize_t __pthread_recv(int, void *, size_t, int);
extern ssize_t __pthread_send(int, const void *, size_t, int);
extern ssize_t __pthread_recvfrom(int, void *, size_t, int, struct sockaddr *,
                                  socklen_t *);
extern ssize_t __pthread_sendto(int, const void *, size_t, int,
                                const struct sockaddr *, socklen_t);
extern ssize_t __pthread_pread(int, void *, size_t, off_t);
extern ssize_t __pthread_pwrite(int, const void *, size_t, off_t);

pid_t __esperanto_fork(void) { return (__pthread_fork()); }
unsigned int __esperanto_sleep(unsigned int seconds) {
  return (__pthread_sleep(seconds));
}
int __esperanto_nanosleep(const struct timespec *reg, struct timespec *rem) {
  return (__pthread_nanosleep(reg, rem));
}
int __esperanto_usleep(unsigned int usec) { return (__pthread_usleep(usec)); }
int __esperanto_system(const char *command) {
  return (__pthread_system(command));
}
int __esperanto_sigwait(const sigset_t *set, int *sig) {
  return (__pthread_sigwait(set, sig));
}
pid_t __esperanto_waitpid(pid_t pid, int *wstatus, int options) {
  return (__pthread_waitpid(pid, wstatus, options));
}
int __esperanto_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
  return (__pthread_connect(sockfd, addr, addrlen));
}
int __esperanto_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  return (__pthread_accept(sockfd, addr, addrlen));
}
int __esperanto_select(int nfds, fd_set *readfds, fd_set *writefds,
                       fd_set *exceptfds, struct timeval *timeout) {
  return (__pthread_select(nfds, readfds, writefds, exceptfds, timeout));
}
int __esperanto_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
  return (__pthread_poll(fds, nfds, timeout));
}
ssize_t __esperanto_read(int fd, void *buf, size_t count) {
  return (__pthread_read(fd, buf, count));
}
ssize_t __esperanto_write(int fd, void *buf, size_t count) {
  return (__pthread_write(fd, buf, count));
}
ssize_t __esperanto_readv(int fd, const struct iovec *iov, int iovcnt) {
  return (__pthread_readv(fd, iov, iovcnt));
}
ssize_t __esperanto_writev(int fd, const struct iovec *iov, int iovcnt) {
  return (__pthread_writev(fd, iov, iovcnt));
}
ssize_t __esperanto_recv(int sockfd, void *buf, size_t len, int flags) {
  return (__pthread_recv(sockfd, buf, len, flags));
}
ssize_t __esperanto_send(int sockfd, const void *buf, size_t len, int flags) {
  return (__pthread_send(sockfd, buf, len, flags));
}
ssize_t __esperanto_recvfrom(int sockfd, void *buf, size_t len, int flags,
                             struct sockaddr *src_addr, socklen_t *addrlen) {
  return (__pthread_recvfrom(sockfd, buf, len, flags, src_addr, addrlen));
}
ssize_t __esperanto_sendto(int sockfd, const void *buf, size_t len, int flags,
                           const struct sockaddr *dest_addr,
                           socklen_t addrlen) {
  return (__pthread_sendto(sockfd, buf, len, flags, dest_addr, addrlen));
}
ssize_t __esperanto_pread(int fd, void *buf, size_t count, off_t offset) {
  return (__pthread_pread(fd, buf, count, offset));
}
ssize_t __esperanto_pwrite(int fd, const void *buf, size_t count,
                           off_t offset) {
  return (__pthread_pwrite(fd, buf, count, offset));
}
