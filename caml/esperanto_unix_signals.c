
#ifdef POSIX_SIGNALS

void _esperanto_init_unix_signals(const int cosmopolitan_unix_signals[]) {
  memcpy(sigprocmask_cmd, cosmopolitan_unix_signals, sizeof(sigprocmask_cmd));
}

#endif /* POSIX_SIGNALS */
