#include "hash.h"

//
// Constructor for a HashTable .

//
// length : Length of the HashTable .
// salt : Salt for the HashTable .
//
HashTable *ht_create(uint32_t length) {
  // Allocate memory for the hash table
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    // Set salts
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    // Set length
    ht->length = length;
    // Create heads
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    // Return pointer to hashtable
    return ht;
  }

  return (HashTable *)NIL;
}

void ht_delete(HashTable *ht) {
  // Free properties of struct ht
  free(ht->heads);
  free(ht);
}

//
// Returns number of entries in hash table
//
// h: The HashTable .
//
uint32_t ht_count(HashTable *ht) {
  // Set count to 0
  uint32_t count = 0;
  // Loop through all heads checking whether they are not nulll
  for (uint32_t index = 0; index <= ht->length; index++) {
    if (ht->heads[index] != NULL) {
      // Increment valid heads found
      count++;
    }
  }
  // Return number of heads
  return count;
}

//
// Searches a HashTable for a key .
// Returns the ListNode if found and returns NULL otherwise .
// This should call the ll_lookup () function .
//
// ht: The HashTable .
// key: The key to search for .
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  // Create index from hash()
  uint32_t index = (hash(ht->salt, key) % ht->length);
  // Look through linked list with specific key
  return ll_lookup(&ht->heads[index], key);
}

//
// First creates a new ListNode from HatterSpeak .
// The created ListNode is then inserted into a HashTable .
// This should call the ll_insert () function .
//
// ht: The HashTable .
// gs: The HatterSpeak to add to the HashTable .
//
void ht_insert(HashTable *ht, HatterSpeak *gs) {
  // Create index from hash()
  uint32_t index = (hash(ht->salt, gs->oldspeak) % ht->length);
  // Pass in list of heads to ll_insert
  ht->heads[index] = ll_insert(&ht->heads[index], gs);
}
// The rest of the functions you must implement yourselves .
