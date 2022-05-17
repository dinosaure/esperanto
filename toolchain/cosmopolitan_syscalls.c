#include "cosmopolitan/cosmopolitan.h"

pid_t __esperanto_fork(void) { return (fork()); }
unsigned int __esperanto_sleep(unsigned int seconds) {
  return (sleep(seconds));
}
int __esperanto_nanosleep(const struct timespec *reg, struct timespec *rem) {
  return (nanosleep(reg, rem));
}
int __esperanto_usleep(unsigned int usec) { return (usleep(usec)); }
int __esperanto_system(const char *command) { return (system(command)); }
int __esperanto_sigwait(const sigset_t *set, int *sig) {
  assert(false);
  // XXX(dinosaure): Cosmopolitan does not implements [sigwait] but only [threads.cmxa]
  // requires it so it's ~~fine~~.
}
pid_t __esperanto_waitpid(pid_t pid, int *wstatus, int options) {
  return (waitpid(pid, wstatus, options));
}
int __esperanto_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
  return (connect(sockfd, addr, addrlen));
}
int __esperanto_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  return (accept(sockfd, addr, addrlen));
}
int __esperanto_select(int nfds, fd_set *readfds, fd_set *writefds,
                       fd_set *exceptfds, struct timeval *timeout) {
  return (select(nfds, readfds, writefds, exceptfds, timeout));
}
int __esperanto_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
  return (poll(fds, nfds, timeout));
}
ssize_t __esperanto_read(int fd, void *buf, size_t count) {
  return (read(fd, buf, count));
}
ssize_t __esperanto_write(int fd, void *buf, size_t count) {
  return (write(fd, buf, count));
}
ssize_t __esperanto_readv(int fd, const struct iovec *iov, int iovcnt) {
  return (readv(fd, iov, iovcnt));
}
ssize_t __esperanto_writev(int fd, const struct iovec *iov, int iovcnt) {
  return (writev(fd, iov, iovcnt));
}
ssize_t __esperanto_recv(int sockfd, void *buf, size_t len, int flags) {
  return (recv(sockfd, buf, len, flags));
}
ssize_t __esperanto_send(int sockfd, const void *buf, size_t len, int flags) {
  return (send(sockfd, buf, len, flags));
}
ssize_t __esperanto_recvfrom(int sockfd, void *buf, size_t len, int flags,
                             struct sockaddr *src_addr, socklen_t *addrlen) {
  return (recvfrom(sockfd, buf, len, flags, src_addr, addrlen));
}
ssize_t __esperanto_sendto(int sockfd, const void *buf, size_t len, int flags,
                           const struct sockaddr *dest_addr,
                           socklen_t addrlen) {
  return (sendto(sockfd, buf, len, flags, dest_addr, addrlen));
}
ssize_t __esperanto_pread(int fd, void *buf, size_t count, off_t offset) {
  return (pread(fd, buf, count, offset));
}
ssize_t __esperanto_pwrite(int fd, const void *buf, size_t count,
                           off_t offset) {
  return (pwrite(fd, buf, count, offset));
}
