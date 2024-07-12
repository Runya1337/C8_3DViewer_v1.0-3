#include "s21_affine.h"

void rotate_X(Picture *shrek, double angle) {
  angle = angle * M_PI / 180;  // Конвертация угла в радианы
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    double Y = shrek->vertexes[i + 1];
    double Z = shrek->vertexes[i + 2];
    shrek->vertexes[i + 1] = Y * cos(angle) + Z * sin(angle);
    shrek->vertexes[i + 2] = -Y * sin(angle) + Z * cos(angle);
  }
}

void rotate_Y(Picture *shrek, double angle) {
  angle = angle * M_PI / 180;  // Конвертация угла в радианы
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    double X = shrek->vertexes[i];
    double Z = shrek->vertexes[i + 2];
    shrek->vertexes[i] = X * cos(angle) - Z * sin(angle);
    shrek->vertexes[i + 2] = X * sin(angle) + Z * cos(angle);
  }
}

void rotate_Z(Picture *shrek, double angle) {
  angle = angle * M_PI / 180;  // Конвертация угла в радианы
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    double X = shrek->vertexes[i];
    double Y = shrek->vertexes[i + 1];
    shrek->vertexes[i] = X * cos(angle) - Y * sin(angle);
    shrek->vertexes[i + 1] = X * sin(angle) + Y * cos(angle);
  }
}

void scale(Picture *shrek, double scaleFactor) {
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    shrek->vertexes[i] *= scaleFactor;      // X
    shrek->vertexes[i + 1] *= scaleFactor;  // Y
    shrek->vertexes[i + 2] *= scaleFactor;  // Z
  }
}

void move_X(Picture *shrek, double dx) {
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    shrek->vertexes[i] += dx;
  }
}

void move_Y(Picture *shrek, double dy) {
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    shrek->vertexes[i + 1] += dy;
  }
}

void move_Z(Picture *shrek, double dz) {
  for (int i = 0; i < shrek->vertex_index; i += 3) {
    shrek->vertexes[i + 2] += dz;
  }
}