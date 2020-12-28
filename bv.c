// header file
#include "bv.h"
// math macros
#include <math.h>
//printf,scanf
#include <stdlib.h>

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
// BitVector struct with properties
BitVector *bv_create(uint32_t bit_len) {
  // Allocate memory for the struct BitVector
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  // Checks if memory address is valid
  if (!v) {
    exit(0);
  }
  // Declare variables from struct BitVector + 1
  v->length = bit_len;
  // Allocates memory for the vector in BitVector
  v->vector = (uint8_t *)calloc(sizeof(uint8_t), ((bit_len / 8) + 1));
  // Checks if memory address is valid
  if (!v->vector) {
    exit(0);
  }
  // Return pointer
  return v;
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector *v) {
  // Free's allocated memory from the struct and vector
  free(v->vector);
  free(v);
}

//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) {
  // Return the lenght of our BitVector
  return (v->length);
}

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  // Get specific Byte
  uint32_t byte = floor(i / 8);
  // Get index of the bit we want to access
  uint8_t index_of = i % 8;
  // Mask
  uint8_t value = 0x01;
  // Shift Left
  uint8_t shift = value << (index_of);
  // OR
  uint8_t or_result = (v->vector[byte] | shift);
  //Store result
  v->vector[byte] = or_result;
}

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  // Get specific Byte
  uint32_t byte = floor(i / 8);
  // Get index of the bit we want to access
  uint8_t index_of = i % 8;
  // Mask
  uint8_t value = 0x01;

  // Shift Left
  uint8_t shift = ~(value << index_of);
  // AND
  uint8_t and_result = (v->vector[byte] & shift);
  //Store result
  v->vector[byte] = and_result;
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  // Get specific Byte
  uint32_t byte = floor(i / 8);
  // Get index of the bit we want to access
  uint8_t index_of = i % 8;
  // mask
  uint8_t mask = 0x01;
  // Shift Right
  uint8_t shift = v->vector[byte] >> (index_of);
  // AND
  uint8_t and_result = (shift & mask);

  return and_result;
}

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  // Store in each byte in memory ('11111111')
  for (uint32_t index = 0; index <= (v->length / 8); index++) {
    v->vector[index] = 0xFF;
  }
}
