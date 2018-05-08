#include <stdio.h>
#include <stdlib.h>
#include "lshtein.h"
#include "greatest.h"

unsigned int
levenshtein(const char *a, const char *b) {
  unsigned int length = strlen(a);
  unsigned int bLength = strlen(b);
  unsigned int *cache = calloc(length, sizeof(unsigned int));
  unsigned int index = 0;
  unsigned int bIndex = 0;
  unsigned int distance;
  unsigned int bDistance;
  unsigned int result;
  char code;

  /* Shortcut optimizations / degenerate cases. */
  if (a == b) {
    return 0;
  }

  if (length == 0) {
    return bLength;
  }

  if (bLength == 0) {
    return length;
  }

  /* initialize the vector. */
  while (index < length) {
    cache[index] = index + 1;
    index++;
  }

  /* Loop. */
  while (bIndex < bLength) {
    code = b[bIndex];
    result = distance = bIndex++;
    index = -1;

    while (++index < length) {
      bDistance = code == a[index] ? distance : distance + 1;
      distance = cache[index];

      cache[index] = result = distance > result
        ? bDistance > result
          ? result + 1
          : bDistance
        : bDistance > distance
          ? distance + 1
          : bDistance;
    }
  }

  free(cache);

  return result;
}

TEST file_test1(void) {
    FILE *fp = fopen("./data/words-100K.txt", "rb");
    ASSERT(fp != NULL);

    fclose(fp);

    PASS();
}

TEST test1(void) {
    FILE *fp = fopen("./data/words-100K.txt", "rb");

    char prev[256];
    char curr[256];

    int i=0;

    fscanf(fp, "%s", prev);

    while(fscanf(fp, "%s", curr)!= EOF) {
        int dist1 = levenshtein(prev, curr);
        int dist2 = ldist(prev, curr);
        if(dist1 != dist2) {
            printf("%s:%s\t%d:%d\n", prev, curr, dist1, dist2);
        }
        memcpy(prev, curr, 256);
    }

    fclose(fp);
    PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(lshtein_suite) {
    RUN_TEST(file_test1);
    RUN_TEST(test1);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    /* Individual tests can be run directly in main, outside of suites. */
    /* RUN_TEST(x_should_equal_1); */

    /* Tests can also be gathered into test suites. */
    RUN_SUITE(lshtein_suite);

    GREATEST_MAIN_END();        /* display results */
}