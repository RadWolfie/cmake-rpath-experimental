#include <stdio.h>

#include "include/library.h"

int main(void) {
  char* message = NULL;
  greet(&message);
  
  if (message!=NULL) {
    printf("%s", message);
  }
  else {
    printf("%s", "greet didn't return with a message...");
  }
  
  return 0;
}
