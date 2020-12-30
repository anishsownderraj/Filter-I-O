// header files
#include "bf.h"
#include "hash.h"
#include "parser.h"
#include "speck.h"
//matching input
#include <regex.h>
//getopt
#include <getopt.h>
//uint32_t
#include <inttypes.h>
////math macros
#include <math.h>
//printf,scanf
#include <stdio.h>
//calloc
#include <stdlib.h>
//true,false
#include <stdbool.h>
// Options for getop
#define OPTIONS "h:f:mbs"

//regex
regex_t word_regex;
// move to front
bool move_to_front;
// Stat vars
uint32_t seeks;
double nodes;
double ll_length_sum;
double non_null_head;
double set_bits;

//MAIN
int main(int argc, char **argv)
{

  // Default values
  uint32_t ht_size = 10000;
  uint32_t bf_length = pow(2, 20);

  // Bool vars
  bool forbidden = false;
  bool kindabad = false;

  // S_flag
  bool s_flag = false;

  int c = 0;
  // While Loop will terminate once it reaches NULL giving a value of 0
  while ((c = getopt(argc, argv, OPTIONS)) != -1)
  {

    switch (c)
    {
    // CASE H
    case 'h':
      ht_size = atoi(optarg);
      break;
    // CASE F
    case 'f':
      bf_length = atoi(optarg);
      break;
    // CASE M
    case 'm':
      move_to_front = true;
      break;
    // CASE B
    case 'b':
      move_to_front = false;
      break;
    //CASE S
    case 's':
      s_flag = true;
      break;
    }
  }

  // Create bloom filter
  BloomFilter *bf = bf_create(bf_length);
  // Create hash table
  HashTable *ht = ht_create(ht_size);

  // Oldspeak.txt
  // First file to read from
  FILE *fp_1 = fopen("oldspeak.txt", "read");

  char each_word[10000];

  // Parsing through the file
  while (fscanf(fp_1, "%s \n", each_word) != EOF)
  {
    bf_insert(bf, each_word);
    HatterSpeak *fw = hs_create(each_word, NULL);
    ht_insert(ht, fw);
  }
  fclose(fp_1);

  //Hatterspeak.txt
  // Second file to read from
  FILE *fp_2 = fopen("hatterspeak.txt", "read");

  char old[10000];
  char hat[10000];

  // Parsing through the file
  while (fscanf(fp_2, "%s %s \n", old, hat) != EOF)
  {
    bf_insert(bf, old);
    HatterSpeak *ew = hs_create(old, hat);
    ht_insert(ht, ew);
  }

  // Initialize REGEX expression
  if (regcomp(
          &word_regex, "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*", REG_EXTENDED))
  {
    printf("WRONG");
    return 0;
  }

  char *myword;

  // Create two heads for my two ll's to store the output
  ListNode **headop_1 = (ListNode **)calloc(1000000, sizeof(char));
  ListNode **headop_2 = (ListNode **)calloc(1000000, sizeof(char));
  // Temp vars
  ListNode *head_1 = NULL;
  ListNode *head_2 = NULL;

  // Parse through input and set it to myword
  while ((myword = next_word(stdin, &word_regex)))
  {
    // Probe the word to see if exists in the hashtable
    if (bf_probe(bf, myword))
    {
      // Traverse the linked list to find the word
      ListNode *node = ht_lookup(ht, myword);

      // If node is not NULL
      if (node)
      {
        // If node has a hatterspeak = NULL, we know its forbidden
        if (node->gs->hatterspeak != NULL)
        {
          HatterSpeak *gw = hs_create(node->gs->oldspeak, node->gs->hatterspeak);
          head_1 = ll_insert(headop_1, gw);
          headop_1 = &head_1;
          kindabad = true;
        }
        // Else we have a revisable word
        else
        {
          HatterSpeak *hw = hs_create(myword, node->gs->hatterspeak);
          head_2 = ll_insert(headop_2, hw);
          headop_2 = &head_2;
          forbidden = true;
        }
      }
    }
  }
  // Clear the words from the parser
  clear_words();

  // If -s is not present
  if (s_flag != true)
  {
    // Case 1: We have forbidden and revisable words
    if (kindabad == true && forbidden == true)
    {
      printf("Dear Comrade,\n\n");
      printf("You have chosen to use words that the queen has decreed "
             "oldspeak.\n");
      printf("Due to your infraction you will be sent to the dungeon where you "
             "will\n");
      printf("be taught hatterspeak\n");
    }
    // Case 2: We have only revisable words
    if (kindabad == true && forbidden == false)
    {
      printf("Dear Wonderlander,\n\n");
      printf("The decree for hatterspeak finds your message lacking. Some of "
             "the \n");
      printf("words that you used are not hatterspeak.\n");
      printf(
          "The list shows how to turn the oldspeak words into hatterspeak\n");
    }
    // Case 3: We have only forbidden words
    if (kindabad == false && forbidden == true)
    {

      printf("Dear Wonderlander,\n\n");
      printf("You have chosen to use words that the queen has decreed "
             "oldspeak.\n");
      printf("Due to your infraction you will be sent to the dungeon where you "
             "will\n");
      printf("be taught hatterspeak\n");
    }

    // If forbidden words present, loop & print them
    if (forbidden)
    {
      ListNode *element = head_2;
      printf("Forbidden Words:\n\n");

      // Loops through and prints
      while (element != NULL)
      {
        printf("%s\n", element->gs->oldspeak);

        // Changes current node to next node
        element = element->next;
      }
    }

    // If revisable words present, loop & print them
    if (kindabad)
    {
      // Header
      if (kindabad == true && forbidden == true)
      {
        printf("\nAppropiate hatterspeak translations.\n\n");
      }
      else
      {
        printf("\n");
      }
      ListNode *element = head_1;

      // Loops through and prints
      while (element != NULL)
      {

        printf("%s -> %s\n", element->gs->oldspeak, element->gs->hatterspeak);

        // Changes current node to next node
        element = element->next;
      }
    }
  }

  // Print stats if -s present
  if (s_flag)
  {
    printf("\n");
    printf("Seeks: %d\n", seeks);
    printf("Average seek length: %f\n", (nodes / seeks));
    printf("Average Linked List Length: %f\n", (ll_length_sum / ht->length));
    non_null_head = ht_count(ht);
    printf("Hash table load: %f%%\n", ((non_null_head / ht->length) * 100));
    for (uint32_t index = 0; index < bf_length; index++)
    {
      if (bv_get_bit(bf->filter, index) == 1)
      {
        // Add 3 to counter for bf load
        set_bits += 1;
      }
    }
    printf("Bloom filter load: %f%%\n", (set_bits / bf_length) * 100);
  }
}

