#ifndef COSMOPOLITAN_LIBC_NT_STRUCT_IMAGEBASERELOCATION_H_
#define COSMOPOLITAN_LIBC_NT_STRUCT_IMAGEBASERELOCATION_H_

struct NtImageBaseRelocation {
  uint32_t VirtualAddress;
  uint32_t SizeOfBlock;
};

#endif /* COSMOPOLITAN_LIBC_NT_STRUCT_IMAGEBASERELOCATION_H_ */