#include "s21_parser.h"  // Подключение заголовочного файла с определением структуры Picture и прототипами функций

int parserMain(char *url_file, Picture *shrek) {
  int status = SUCCESS;
  FILE *file = NULL;
  int size_v = 0;
  int max_f = 0;
  file = fopen(url_file, "r");
  if (file == NULL) {
    status = FAIL;
    printf("\n\nNOOPEN\n\n");
  } else {
    parcer_helper(file, shrek);
    if (max_f > (size_v + 1)) {
      shrek->status = FAIL;
      printf("\nточки соединения не сущесвтует\n\n");
    }
  }
  // print_Shrek(shrek);
  return status;
}

void parcer_helper(FILE *file, Picture *shrek) {
  char line[LINE_SIZE];
  // считываю количество вертексов и строк полигонов
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      shrek->vertex_count += 1;
    } else if (line[0] == 'f' && line[1] == ' ') {
      shrek->facets_count += 1;
    }
  }
  fseek(file, 0, SEEK_SET);
  // выделяем память под вертексы
  shrek->vertexes = (double *)calloc((shrek->vertex_count * 3), sizeof(double));
  while (fgets(line, sizeof(line), file) && shrek->status == SUCCESS) {
    if ((line[0] == 'v' && line[1] == ' ') ||
        (line[0] == 'f' && line[1] == ' ')) {
      parcer_distributor(line, shrek);
    }
  }
  fclose(file);
}

void parcer_distributor(char *string, Picture *shrek) {
  char splitsym[] = " ";
  string[strcspn(string, "\n")] = '\0';
  string[strcspn(string, "\r")] = '\0';
  strtokstring_add_memory(string, splitsym, shrek);
}

void strtokstring_add_memory(char *string, char splitsym[], Picture *shrek) {
  char *token = strtok(string, splitsym);
  int counter_lex_v = 0;
  int counter_lex_f = 0;
  int start_index_row_f = 0;
  bool status_v = false;
  bool status_f = false;
  if (strcmp(token, "v") == 0) {
    status_v = true;
  } else if (strcmp(token, "f") == 0) {
    status_f = true;
  }
  token = strtok(NULL, splitsym);
  while (token != NULL && shrek->status == SUCCESS) {
    if (status_v == true) {
      if (IsDigit(token) == SUCCESS) {
        counter_lex_v += 1;
        add_vertexex_list(shrek, token);
        token = strtok(NULL, splitsym);
      } else {
        shrek->status = FAIL;
        printf("\nподается не число\n\n");
      }

    } else if (status_f == true) {
      counter_lex_f += 1;
      add_facets_list(shrek, token, &counter_lex_f, &start_index_row_f);
      token = strtok(NULL, splitsym);
    }
  }
  if (status_v == true) {
    validation_string_v(shrek, counter_lex_v);
  } else if (status_f == true) {
    shrek->facets[shrek->facets_index] = start_index_row_f - 1;
    shrek->facets_index += 1;
  }
}

void add_facets_list(Picture *shrek, char *token_value, int *parser_index,
                     int *start_index_row_f) {
  parser_string_f(token_value, shrek, parser_index, start_index_row_f);
}

void parser_string_f(char *token_value, Picture *shrek, int *index_f,
                     int *start_index_row_f) {
  char pretoken[strlen(token_value)];
  strcpy(pretoken, token_value);
  int value = 0;
  if (get_index_f(pretoken, &value) == SUCCESS) {
    check_negative_index(&value, shrek);
    if (*index_f == 1) {
      shrek->facets = (int *)realloc(shrek->facets,
                                     (shrek->facets_index + 2) * sizeof(int));
      shrek->facets[shrek->facets_index] = value - 1;
      *start_index_row_f = value;
    } else {
      shrek->facets = (int *)realloc(shrek->facets,
                                     (shrek->facets_index + 2) * sizeof(int));
      shrek->facets[shrek->facets_index] = value - 1;
      shrek->facets_index += 1;
      shrek->facets[shrek->facets_index] = value - 1;
    }
    shrek->facets_index += 1;
  } else {
    shrek->status = FAIL;
    printf("\nподается не число на полигон\n\n");
  }
}

void check_negative_index(int *value, Picture *shrek) {
  if (*value == 0 || (abs(*value) > (shrek->vertex_index / 3))) {
    shrek->status = FAIL;
    printf("\nнегативный индекс не трансформируется в нормальный\n\n");
  } else if (*value < 0) {
    *value = (shrek->vertex_index / 3) + 1 + *value;
  }
}

int get_index_f(char *token_value, int *value) {
  int counter = 1;
  char *endptr = NULL;
  int status = SUCCESS;
  if (token_value[0] == '/') {
    status = FAIL;
    printf("\n полигоне нет соединяемой точки\n");
  } else {
    for (int i = 0; token_value[i] != '\0' && token_value[i] != '/' &&
                    token_value[i] != '\r';
         i++) {
      if ((token_value[i] >= '0' && token_value[i] <= '9') ||
          token_value[i] == '-') {
        counter += 1;
      } else {
        printf("\nподается не число get index f \n\n");
        status = FAIL;
      }
    }
    *value = strtod(token_value, &endptr);
  }
  return status;
}

void validation_string_v(Picture *shrek, int counter_lex_v) {
  if (counter_lex_v < 3 || counter_lex_v > 4) {
    printf("\nколичество значений под xyz больше чем нужно или меньше \n\n");
    shrek->status = FAIL;
  } else if (counter_lex_v == 3) {
    // shrek->vertexes[shrek->vertex_index] = -1.0;
    // shrek->vertex_index += 1;
  }
}

void add_vertexex_list(Picture *shrek, char *token_value) {
  long double value_v = 0.0;
  char *endptr = NULL;
  value_v = strtold(token_value, &endptr);
  shrek->vertexes[shrek->vertex_index] = value_v;
  // МЕСТО ДЛЯ ПОИСКА МАКСИМАЛЬНОЙ ТОЧКИ
  search_min_points(shrek, value_v, shrek->vertex_index % 3);
  search_max_points(shrek, value_v, shrek->vertex_index % 3);
  shrek->vertex_index += 1;
}

int IsDigit(char *string) {
  int status = SUCCESS;
  int counter_index = 0;
  int counter_dot = 0;
  int minus = 0;
  if (string[0] == '-') {
    minus = 1;
    counter_index++;
  }
  while (string[counter_index + 1] != '\0' && status == 0) {
    if (isdigit(string[counter_index])) {
      status = SUCCESS;
    } else {
      if (string[counter_index] == '.' || string[counter_index] == '-') {
        if (string[counter_index] == '.') {
          counter_dot = counter_dot + 1;
        }
        status = SUCCESS;
      } else {
        printf("\nне число подается\n\n");
        status = FAIL;
      }
    }
    counter_index += 1;
  }
  if (!isdigit(string[counter_index]) && string[counter_index] > 32) {
    printf("last symb\n");
    status = FAIL;
  }
  if (counter_dot > 1) {
    printf("\nподается некорректное число с большим количеством точек\n\n");
    status = FAIL;
  }
  return status;
}

Picture *initPicture() {
  Picture *shrek = (Picture *)malloc(sizeof(Picture));
  if (shrek == NULL) {
    return NULL;
  }
  shrek->vertexes = (double *)calloc(MIN_SIZE, sizeof(double));
  shrek->facets = (int *)calloc(MIN_SIZE, sizeof(int));
  if (shrek->vertexes == NULL || shrek->facets == NULL) {
    // Обработка ошибки при выделении памяти
    clearPicture(shrek);
    return NULL;
  }
  // Установка начальных значений остальных полей структуры
  shrek->vertex_count = 0;
  shrek->facets_count = 0;
  shrek->facets_max = 0;
  shrek->max_x = 0;
  shrek->max_y = 0;
  shrek->max_z = 0;
  shrek->min_x = 0;
  shrek->min_y = 0;
  shrek->min_z = 0;
  shrek->facets_index = 0;
  shrek->vertex_index = 0;
  shrek->scale_k = 0.5;
  return shrek;
}

void clearPicture(Picture *shrek) {
  if (shrek->vertexes != NULL) {
    free(shrek->vertexes);
    shrek->vertexes = NULL;
  }
  if (shrek->facets != NULL) {
    free(shrek->facets);
    shrek->facets = NULL;
  }

  shrek->max_x = -INFINITY;
  shrek->max_y = -INFINITY;
  shrek->max_z = -INFINITY;

  shrek->min_x = INFINITY;
  shrek->min_y = INFINITY;
  shrek->min_z = INFINITY;

  shrek->vertex_count = 0;
  shrek->facets_count = 0;
  shrek->vertex_index = 0;
  shrek->facets_index = 0;
  shrek->facets_max = 0;
  shrek->status = SUCCESS;
  shrek->scale_k = 0.5;
}

void print_Shrek(Picture *shrek) {
  int count = 0;
  if (shrek->status == SUCCESS) {
    for (int i = 0; i <= shrek->vertex_index - 1; i++) {
      if (count == 3) {
        printf("\n");
        count = 0;
      }
      printf("%lf ", shrek->vertexes[i]);
      count++;
    }
    printf("\n");
    for (int j = 0; j <= shrek->facets_index - 1; j++) {
      printf("%d ", shrek->facets[j]);
    }
    printf("\n");
    printf("MAX POINT X %Lf\n", shrek->max_x);
    printf("MAX POINT Y %Lf\n", shrek->max_y);
    printf("MAX POINT Z %Lf\n", shrek->max_z);
    printf("MIN POINT X %Lf\n", shrek->min_x);
    printf("MIN POINT Y %Lf\n", shrek->min_y);
    printf("MIN POINT Z %Lf\n", shrek->min_z);
    printf("Facets count %d\n", shrek->facets_index);
    printf("Vertex count %d\n", shrek->vertex_count);
    printf("Vertex count %d\n", shrek->vertex_index);
  } else {
    printf("\nERROR\n");
  }
}

void search_max_points(Picture *shrek, double xyz, int place_index) {
  if (shrek->vertex_index < 3) {
    if (place_index == 0) {
      shrek->max_x = xyz;
    } else if (place_index == 1) {
      shrek->max_y = xyz;
    } else if (place_index == 2) {
      shrek->max_z = xyz;
    }
  } else {
    if (place_index == 0) {
      if (xyz > shrek->max_x) {
        shrek->max_x = xyz;
      }
    } else if (place_index == 1) {
      if (xyz > shrek->max_y) {
        shrek->max_y = xyz;
      }
    } else if (place_index == 2) {
      if (xyz > shrek->max_z) {
        shrek->max_z = xyz;
      }
    }
  }
}

void search_min_points(Picture *shrek, double xyz, int place_index) {
  if (shrek->vertex_index < 3) {
    if (place_index == 0) {
      shrek->min_x = xyz;
    } else if (place_index == 1) {
      shrek->min_y = xyz;
    } else if (place_index == 2) {
      shrek->min_z = xyz;
    }
  } else {
    if (place_index == 0) {
      if (xyz < shrek->min_x) {
        shrek->min_x = xyz;
      }
    } else if (place_index == 1) {
      if (xyz < shrek->min_y) {
        shrek->min_y = xyz;
      }
    } else if (place_index == 2) {
      if (xyz < shrek->min_z) {
        shrek->min_z = xyz;
      }
    }
  }
}
