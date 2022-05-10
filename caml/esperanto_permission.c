
void _esperanto_init_permission(const int cosmopolitan_permission[]) {
  memcpy(access_permission_table, cosmopolitan_permission,
         sizeof(access_permission_table));
}
