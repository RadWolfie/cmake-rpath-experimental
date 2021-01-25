#include "include/library.h"

static char message[] = "Hello World from library!";

void greet(char** handshake) {
  *handshake = message;
}
