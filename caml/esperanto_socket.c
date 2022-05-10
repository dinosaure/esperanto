
void _esperanto_init_socket_type(const int cosmopolitan_socket_type[]) {
  memcpy(socket_type_table, cosmopolitan_socket_type,
         sizeof(socket_type_table));
}
