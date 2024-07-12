#ifndef S21_AFFINE
#define S21_AFFINE

#include "s21_viewer.h"  // Импорт определения структуры Picture

// Функции аффинных преобразований
void rotate_X(Picture *shrek, double angle);
void rotate_Y(Picture *shrek, double angle);
void rotate_Z(Picture *shrek, double angle);
void scale(Picture *shrek, double scaleFactor);
void move_X(Picture *shrek, double dx);
void move_Y(Picture *shrek, double dy);
void move_Z(Picture *shrek, double dz);

#endif  // S21_AFFINE