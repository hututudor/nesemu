#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/utils/term_colors.h"

typedef struct {
  bool (*func)();
  const char *name;
} test_t;

#define MAX_TESTS 1024

#define TEST_BEGIN(name) bool test_##name() {
#define TEST_END \
  return true;   \
  }

#define ASSERT(expression)                                         \
  if (!(expression)) {                                             \
    printf("%s(assertion \"%s\") %s", TERM_COLOR_RED, #expression, \
           TERM_COLOR_RESET);                                      \
    return false;                                                  \
  }

#define SUITE_BEGIN(name)                                        \
  int suite_##name() {                                           \
    test_t *tests = (test_t *)calloc(MAX_TESTS, sizeof(test_t)); \
    const char *suite = #name;                                   \
    int tests_count = 0;                                         \
    int passed_tests_count = 0;

#define SUITE_END                                                    \
  for (int test_index = 0; test_index < tests_count; test_index++) { \
    printf("%s[%s]%s %s ", TERM_COLOR_BLUE, suite, TERM_COLOR_RESET, \
           tests[test_index].name);                                  \
    if (tests[test_index].func()) {                                  \
      printf("%s[PASSED]%s\n", TERM_COLOR_GREEN, TERM_COLOR_RESET);  \
      passed_tests_count++;                                          \
    } else {                                                         \
      printf("%s[FAILED]%s\n", TERM_COLOR_RED, TERM_COLOR_RESET);    \
    }                                                                \
  }                                                                  \
  bool have_all_passed = (passed_tests_count == tests_count);        \
  printf("%sSuite \"%s\" passed %d/%d%s\n",                          \
         have_all_passed ? TERM_COLOR_GREEN : TERM_COLOR_RED, suite, \
         passed_tests_count, tests_count, TERM_COLOR_RESET);         \
  free(tests);                                                       \
  return passed_tests_count;                                         \
  }

#define SUITE_ADD(test_name)                  \
  tests[tests_count].func = test_##test_name; \
  tests[tests_count].name = #test_name;       \
  tests_count++;
