#ifndef S21_PARSER_H  // Защита от повторного включения заголовочного файла
#define S21_PARSER_H

#include "s21_viewer.h"  // Импорт определения структуры Picture

int parserMain(char *url_file, Picture *shrek);
void parcer_helper(FILE *file, Picture *shrek);
void parcer_distributor(char *string, Picture *shrek);
// void parcer_helper_f(char *string, int *status, int *facets, int *size_f, int
// *max_f);
void strtokstring_add_memory(char *string, char splitsym[], Picture *shrek);
int IsDigit(char *string);
void parser_tokens_in_list(Picture *shrek, char **tokens, int count_token);
Picture *initPicture();
void parser_string_f(char *token_value, Picture *shrek, int *index_f,
                     int *start_index_row_f);
void clearPicture(Picture *shrek);
void add_vertexex_list(Picture *shrek, char *token_value);
void validation_string_v(Picture *shrek, int counter_lex_v);
void add_facets_list(Picture *shrek, char *token_value, int *parser_index,
                     int *start_index_row_f);
int get_index_f(char *token_value, int *value);
void print_Shrek(Picture *shrek);
void search_max_points(Picture *shrek, double xyz, int place_index);
void search_min_points(Picture *shrek, double xyz, int place_index);
void check_negative_index(int *value, Picture *shrek);

#endif  // S21_PARSER_H
