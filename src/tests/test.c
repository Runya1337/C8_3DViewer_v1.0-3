#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../backend/s21_affine.h"
#include "../backend/s21_parser.h"

START_TEST(parser_correct_1) {
  Picture *shrek = initPicture();
  parserMain("figures/correct/бity.obj", shrek);
  print_Shrek(shrek);
  ck_assert_int_eq(SUCCESS, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_correct_2) {
  Picture *shrek = initPicture();
  parserMain("figures/correct/ball.obj", shrek);
  ck_assert_int_eq(SUCCESS, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_correct_3) {
  Picture *shrek = initPicture();
  parserMain("figures/correct/Bugatti.obj", shrek);
  ck_assert_int_eq(SUCCESS, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_correct_4) {
  Picture *shrek = initPicture();
  parserMain("figures/correct/car.obj", shrek);
  ck_assert_int_eq(SUCCESS, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_correct_5) {
  Picture *shrek = initPicture();
  parserMain("figures/correct/cat.obj", shrek);
  ck_assert_int_eq(SUCCESS, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_incorrect_1) {
  Picture *shrek = initPicture();
  parserMain("figures/incorrect/dot_error.obj", shrek);
  ck_assert_int_eq(FAIL, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_incorrect_2) {
  Picture *shrek = initPicture();
  parserMain("figures/incorrect/facet_that_less_than_1.obj", shrek);
  ck_assert_int_eq(FAIL, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(parser_incorrect_3) {
  Picture *shrek = initPicture();
  parserMain("figures/incorrect/facet_that_not_exist.obj", shrek);
  ck_assert_int_eq(FAIL, shrek->status);
  clearPicture(shrek);
}
END_TEST

START_TEST(affine_test_rotate_X) {
  double arg;
  arg = 3.1415926535 / 2;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 1;
    vertex.vertexes[i + 2] = 1;
  }
  rotate_X(&vertex, arg);
  arg = arg * M_PI / 180;
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i], 1);
    ck_assert_double_eq(vertex.vertexes[i + 1], cos(arg) + sin(arg));
    ck_assert_double_eq(vertex.vertexes[i + 2], -sin(arg) + cos(arg));
  }
  free(vertex.vertexes);
}

START_TEST(affine_test_rotate_Y) {
  double arg;
  arg = 3.1415926535 / 2;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 1;
    vertex.vertexes[i + 2] = 1;
  }
  rotate_Y(&vertex, arg);
  arg = arg * M_PI / 180;
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i], cos(arg) - sin(arg));
    ck_assert_double_eq(vertex.vertexes[i + 1], 1);
    ck_assert_double_eq(vertex.vertexes[i + 2], sin(arg) + cos(arg));
  }
  free(vertex.vertexes);
}

START_TEST(affine_test_rotate_Z) {
  double arg;
  arg = 3.1415926535 / 2;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 1;
    vertex.vertexes[i + 2] = 1;
  }
  rotate_Z(&vertex, arg);
  arg = arg * M_PI / 180;
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i], cos(arg) - sin(arg));
    ck_assert_double_eq(vertex.vertexes[i + 1], sin(arg) + cos(arg));
    ck_assert_double_eq(vertex.vertexes[i + 2], 1);
  }
  free(vertex.vertexes);
}

START_TEST(affine_test_move_X) {
  double arg = 1.0;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 2;
    vertex.vertexes[i + 2] = 3;
  }
  move_X(&vertex, arg);
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i], 2);
  }
  free(vertex.vertexes);
}

START_TEST(affine_test_move_Y) {
  double arg = 1.0;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 2;
    vertex.vertexes[i + 2] = 3;
  }
  move_Y(&vertex, arg);
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i + 1], 3);
  }
  free(vertex.vertexes);
}

START_TEST(affine_test_move_Z) {
  double arg = 1.0;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 2;
    vertex.vertexes[i + 2] = 3;
  }
  move_Z(&vertex, arg);
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i + 2], 4);
  }
  free(vertex.vertexes);
}

START_TEST(affine_test_scale) {
  double arg = 0.9;
  Picture vertex = {0};
  vertex.vertex_index = 12;
  vertex.vertexes = (double *)calloc(vertex.vertex_index, sizeof(double));

  for (int i = 0; i < vertex.vertex_index; i += 3) {
    vertex.vertexes[i] = 1;
    vertex.vertexes[i + 1] = 2;
    vertex.vertexes[i + 2] = 3;
  }
  scale(&vertex, arg);
  for (int i = 0; i < vertex.vertex_index; i += 3) {
    ck_assert_double_eq(vertex.vertexes[i], 1 * arg);
    ck_assert_double_eq(vertex.vertexes[i + 1], 2 * arg);
    ck_assert_double_eq(vertex.vertexes[i + 2], 3 * arg);
  }
  free(vertex.vertexes);
}

// getGeometryInfo(argv[1], &object);
Suite *s21_3Dviever_suite() {
  Suite *suite;

  suite = suite_create("s21_3Dviever");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, parser_correct_1);
  tcase_add_test(tcase_core, parser_correct_2);
  tcase_add_test(tcase_core, parser_correct_3);
  tcase_add_test(tcase_core, parser_correct_4);
  tcase_add_test(tcase_core, parser_correct_5);

  tcase_add_test(tcase_core, parser_incorrect_1);
  tcase_add_test(tcase_core, parser_incorrect_2);
  tcase_add_test(tcase_core, parser_incorrect_3);

  tcase_add_test(tcase_core, affine_test_rotate_X);
  tcase_add_test(tcase_core, affine_test_rotate_Y);
  tcase_add_test(tcase_core, affine_test_rotate_Z);
  tcase_add_test(tcase_core, affine_test_move_X);
  tcase_add_test(tcase_core, affine_test_move_Y);
  tcase_add_test(tcase_core, affine_test_move_Z);
  tcase_add_test(tcase_core, affine_test_scale);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  Suite *suite = s21_3Dviever_suite();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_VERBOSE);

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
