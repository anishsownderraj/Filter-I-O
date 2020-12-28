#include "hs.h"
#include <stdio.h>
#include <string.h>

HatterSpeak *hs_create(char *oldspeak, char *hatterspeak) {
  // Allocate memory for the struct BitVector
  HatterSpeak *hs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  // Checks if memory address is valid
  if (!hs) {
    exit(0);
  }

  hs->oldspeak = (char *)malloc((strlen(oldspeak)) * sizeof(char) + 1);
  // Checks if memory address is valid
  if (!hs->oldspeak) {
    exit(0);
  }
  // Doesn't malloc if we don't have a hatterspeak word
  if (hatterspeak != NULL) {
    hs->hatterspeak = (char *)malloc(strlen(hatterspeak) * sizeof(char) + 1);
    // Checks if memory address is valid
    if (!hs->hatterspeak) {
      exit(0);
    }
    // Set the value of hatterspeak
    hs->hatterspeak = strcpy(hs->hatterspeak, hatterspeak);
  }

  // Set the value for oldspeak
  hs->oldspeak = strcpy(hs->oldspeak, oldspeak);

  // Return pointer for hatterspeak struct
  return hs;
}

void hs_delete(HatterSpeak *hs) {
  // Frees properties of hs struct
  free(hs->oldspeak);
  free(hs->hatterspeak);
  free(hs);
  return;
}
