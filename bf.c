#include "bf.h"

extern double set_bits;
//
// Constructor for a BloomFilter .
//
// size : The number of entries in the BloomFilter .
//
BloomFilter *bf_create(uint32_t size)
{
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf)
  {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

//
// Destructor for a BloomFilter .
//
// bf: The BloomFilter .
//
void bf_delete(BloomFilter *bf)
{
  // Free's properties of struct bf
  bv_delete(bf->filter);
  free(bf);
}

//
// Inserts a new key into the BloomFilter .
// Indices to set bits are given by the hash functions .
//
// bf: The BloomFilter .
// key: The key to insert into the BloomFilter .
//
void bf_insert(BloomFilter *bf, char *key)
{
  // Create three indexes
  uint32_t index_one = ((hash(bf->primary, key)) % (bf->filter->length));
  uint32_t index_two = ((hash(bf->secondary, key)) % (bf->filter->length));
  uint32_t index_three = ((hash(bf->tertiary, key)) % (bf->filter->length));
  // Input three indexes to set three bits in bf
  bv_set_bit(bf->filter, index_one);
  bv_set_bit(bf->filter, index_two);
  bv_set_bit(bf->filter, index_three);
}

//
// Probes a BloomFilter to check if a key has been inserted .
//
// bf: The BloomFilter .
// key: The key in which to check membership . //
bool bf_probe(BloomFilter *bf, char *key)
{
  // Create three indexes
  uint32_t index_one = ((hash(bf->primary, key)) % (bf->filter->length));
  uint32_t index_two = ((hash(bf->secondary, key)) % (bf->filter->length));
  uint32_t index_three = ((hash(bf->tertiary, key)) % (bf->filter->length));

  // If any one of these indexes = 0, we know the key is not in the bf, thus return false
  if ((bv_get_bit(bf->filter, index_one)) == 0)
  {

    return false;
  }
  if ((bv_get_bit(bf->filter, index_two)) == 0)
  {

    return false;
  }
  if ((bv_get_bit(bf->filter, index_three)) == 0)
  {

    return false;
  }
  // Else return true
  return true;
}
