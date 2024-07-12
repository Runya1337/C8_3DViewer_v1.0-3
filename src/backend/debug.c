#include "s21_parser.h"

int main() {
  Picture shrek = {0};
  parserMain("figures/correct/Shrek.obj", &shrek);
  clearPicture(&shrek);
  return 0;
}