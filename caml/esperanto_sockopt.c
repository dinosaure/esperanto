
void _esperanto_init_sockopt_bool(
    const struct socket_option cosmopolitan_sockopt_bool[]) {
  memcpy(sockopt_bool, cosmopolitan_sockopt_bool, sizeof(sockopt_bool));
}

void _esperanto_init_sockopt_int(
    const struct socket_option cosmopolitan_sockopt_int[]) {
  memcpy(sockopt_int, cosmopolitan_sockopt_int, sizeof(sockopt_int));
}

void _esperanto_init_sockopt_linger(
    const struct socket_option cosmopolitan_sockopt_linger[]) {
  memcpy(sockopt_linger, cosmopolitan_sockopt_linger, sizeof(sockopt_linger));
}

void _esperanto_init_sockopt_timeval(
    const struct socket_option cosmopolitan_sockopt_timeval[]) {
  memcpy(sockopt_timeval, cosmopolitan_sockopt_timeval,
         sizeof(sockopt_timeval));
}

void _esperanto_init_sockopt_unix_error(
    const struct socket_option cosmopolitan_sockopt_unix_error[]) {
  memcpy(sockopt_unix_error, cosmopolitan_sockopt_unix_error,
         sizeof(sockopt_unix_error));
}
