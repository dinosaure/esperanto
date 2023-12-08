#ifndef COSMOPOLITAN_LIBC_BITS_SEGMENTATION_H_
#define COSMOPOLITAN_LIBC_BITS_SEGMENTATION_H_
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#ifdef _COSMO_SOURCE

/**
 * Reads scalar from memory, offset by segment.
 *
 * @return *(MEM) relative to segment
 * @see pushpop()
 */
#define fs(MEM) __peek("fs", MEM)
#define gs(MEM) __peek("gs", MEM)

#define __peek(SEGMENT, ADDRESS)                                  \
  ({                                                              \
    typeof(*(ADDRESS)) Pk;                                        \
    asm("mov\t%%" SEGMENT ":%1,%0" : "=r"(Pk) : "m"(*(ADDRESS))); \
    Pk;                                                           \
  })

#endif /* _COSMO_SOURCE */
#endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* COSMOPOLITAN_LIBC_BITS_SEGMENTATION_H_ */
