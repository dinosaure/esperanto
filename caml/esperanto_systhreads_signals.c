
void _esperanto_init_systhreads_signals(
    const int cosmopolitan_systhreads_signals[]) {
  memcpy(sigmask_cmd, cosmopolitan_systhreads_signals, sizeof(sigmask_cmd));
}
