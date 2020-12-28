#include "ll.h"

ListNode *ll_node_create(HatterSpeak *gs)
{
  // Allocate memory for the struct ListNode
  ListNode *lls = (ListNode *)malloc(sizeof(ListNode));
  // Checks if memory address is valid
  if (!lls)
  {
    exit(0);
  }
  // Sets gs property to gs
  lls->gs = gs;
  // Sets next property to NULL
  lls->next = NULL;

  // Return pointer to ListNode struct
  return lls;
}

void ll_node_delete(ListNode *n)
{
  // Deletes all of HatterSpeak Struct
  hs_delete(n->gs);
  free(n);
  return;
}

void ll_delete(ListNode *head)
{
  // temp var to store head
  ListNode *element = head;
  // Loops through entire linked list
  while (element != NULL)
  {
    element = element->next;
    // Delete props of each node
    ll_node_delete(head);
    // Shift from the head to tail of the linked list
    element = element->next;
  }
  return;
}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs)
{
  // temp var to store head
  ListNode *temp = *head;
  // Counter for Average Linked List Length
  ll_length_sum += 1;

  if (ll_lookup(head, gs->oldspeak) != NULL)
  {
    // Free gs properties
    free(gs->oldspeak);
    free(gs->hatterspeak);
    free(gs);

    return temp;
  }
  // Allocate memory for each new node
  ListNode *node = ll_node_create(gs);
  // Checks if memory address is valid
  if (!node)
  {
    exit(0);
  }
  // Set the next to current head
  node->next = *head;
  // Return the head of the current node
  return node;
}

ListNode *ll_lookup(ListNode **head, char *key)
{

  ListNode *current = *head;
  ListNode *previous = NULL;
  // Counter for Seeks
  seeks += 1;

  while (current != NULL)
  {
    // Counter for Average seek length
    nodes += 1;
    // If the current nodes oldspeak matches the key
    if (strcmp(current->gs->oldspeak, key) == 0)
    {
      // If move_to_front is true
      if (move_to_front)
      {

        // If previous != NULL
        if (previous != NULL)
        {
          // Set the previous next to current next
          previous->next = current->next;
          current->next = *head;
          *head = current;
        }
      }
      nodes += 1;

      return current;
    }
    previous = current;
    current = current->next;
  }
  return NULL;
}
