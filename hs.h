#include <stdio.h>
#include <stdlib.h>

typedef struct HatterSpeak {
  char *oldspeak;
  char *hatterspeak;
} HatterSpeak;

HatterSpeak *hs_create(char *key, char *value);

void hs_delete(HatterSpeak *hs);
