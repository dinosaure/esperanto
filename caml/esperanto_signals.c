
void _esperanto_init_posix_signals(const int cosmopolitan_posix_signals[]) {
  memcpy(posix_signals, cosmopolitan_posix_signals,
         sizeof(posix_signals));
}
