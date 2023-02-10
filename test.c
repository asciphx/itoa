#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
/*
 * This software is licensed under the AGPL-3.0 License.
 *
 * Copyright (C) 2023 Asciphx <maxspore@foxmail.com>
 *
 * Permissions of this strongest copyleft license are conditioned on making available
 * complete source code of licensed works and modifications, which include larger works
 * using a licensed work, under the same license. Copyright and license notices must be
 * preserved. Contributors provide an express grant of patent rights. When a modified
 * version is used to provide a service over a network, the complete source code of
 * the modified version must be made available.
 */
#include "i2a.h"
//This is the fastest version of itoa in the universe, only the fastest, not faster.
int main(){
  char* c = (char*)malloc(21 * sizeof(char));
  clock_t start = clock();
  //itoa test
  for (int i = INT32_MIN; i < 2147483600; i += 79) i2a(c, i);
  printf("use %.6f seconds\n", (float)(clock() - start) / CLOCKS_PER_SEC);
  start = clock();
  //u64toa test
  for (int i = 0; i < 1000000; ++i) u64toa(c, UINT64_MAX);
  printf("use %.6f seconds\n", (float)(clock() - start) / CLOCKS_PER_SEC);
  //other test
  i2a(c, INT32_MIN); printf("%s\n", c);
  i2a(c, INT32_MAX); printf("%s\n", c);
  u2a(c, UINT32_MAX); printf("%s\n", c);
  u64toa(c, UINT64_MAX); printf("%s\n", c);
  i64toa(c, INT64_MAX); printf("%s\n", c);
  i64toa(c, INT64_MIN); printf("%s\n", c);
  free(c);
  return 0;
}