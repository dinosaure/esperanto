
#if defined(HAS_WAITPID) || defined(HAS_WAIT4)
void _esperanto_init_wait_flag(const int cosmopolitan_wait[]) {
  memcpy(wait_flag_table, cosmopolitan_wait, sizeof(wait_flag_table));
}
#endif /* defined(HAS_WAITPID) || defined(HAS_WAIT4) */
