#include <stdint.h>

typedef struct {
  void* buffer;
  uint32_t elemento_slab;
  uint8_t size_slab;
} slab;

