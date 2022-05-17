
void _esperanto_init_terminal_io_descr(
    const long cosmopolitan_terminal_io_descr[]) {
  memcpy(terminal_io_descr, cosmopolitan_terminal_io_descr,
         sizeof(terminal_io_descr));
}

struct speed_e {
  speed_t speed;
  int baud;
};

void _esperanto_init_speedtable(
    const struct speed_e cosmopolitan_speedtable[]) {
  memcpy(speedtable, cosmopolitan_speedtable, sizeof(speedtable));
}

void _esperanto_init_when_flag_table(const int cosmopolitan_when_flag_table[]) {
  memcpy(when_flag_table, cosmopolitan_when_flag_table,
         sizeof(when_flag_table));
}

void _esperanto_init_queue_flag_table(
    const int cosmopolitan_queue_flag_table[]) {
  memcpy(queue_flag_table, cosmopolitan_queue_flag_table,
         sizeof(queue_flag_table));
}
