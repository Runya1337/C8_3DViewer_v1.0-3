#ifndef S21_VIEWER_H
#define S21_VIEWER_H

#define SUCCESS 0
#define FAIL 1
#define LINE_SIZE 4096
#define MIN_SIZE 1

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct picture {
  double *vertexes;
  int *facets;
  long double max_x, max_y, max_z;
  long double min_x, min_y, min_z;
  int vertex_count;
  int facets_count;
  int vertex_index;
  int facets_index;
  int facets_max;
  int status;
  double scale_k;
} Picture;

#endif  // S21_VIEWER