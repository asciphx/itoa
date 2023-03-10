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
 * 
 * See C++ version for details https://github.com/asciphx/FabCc/blob/lithium/fc/include/h/itoa.h
 */
// #include "i2a.h"
#include "i2a.hpp"
#include "third-party/sse2.h"
#include "third-party/jeaiii.hpp"
 //This is the fastest version of itoa in the universe, only the fastest, not faster.
int main() {
  char c[21] = { 0 };
  clock_t start_c;
  start_c = clock();
  for (unsigned long long i = 0; i < 99000000099; i += 999) jeaiii::to_text_from_integer(c, UINT64_MAX - i);
  printf("u64toa_jeaiii use %.6f seconds\n", (float)(clock() - start_c) / CLOCKS_PER_SEC);
  start_c = clock();
  for (unsigned long long i = 0; i < 99000000099; i += 999) u64toa_sse2(UINT64_MAX - i, c);
  printf("u64toa_sse2 use %.6f seconds\n", (float)(clock() - start_c) / CLOCKS_PER_SEC);
  start_c = clock();
  for (unsigned long long i = 0; i < 99000000099; i += 999) u64toa(c, UINT64_MAX - i);
  printf("u64toa use %.6f seconds\n", (float)(clock() - start_c) / CLOCKS_PER_SEC);
  start_c = clock();
  for (int i = -90000000; i < 90000000; i += 9) jeaiii::to_text_from_integer(c, UINT32_MAX - i);
  printf("u32toa_jeaiii use %.6f seconds\n", (float)(clock() - start_c) / CLOCKS_PER_SEC);
  start_c = clock();
  for (int i = -90000000; i < 90000000; i += 9) u32toa_sse2(UINT32_MAX - i, c);
  printf("u32toa_sse2 use %.6f seconds\n", (float)(clock() - start_c) / CLOCKS_PER_SEC);
  start_c = clock();
  for (int i = -90000000; i < 90000000; i += 9) u2a(c, UINT32_MAX - i);
  printf("u2a use %.6f seconds\n", (float)(clock() - start_c) / CLOCKS_PER_SEC);
  return 0;
  i2a(c, -9); printf("%s\n", c);
  i2a(c, -98); printf("%s\n", c);
  i2a(c, -987); printf("%s\n", c);
  i2a(c, -9876); printf("%s\n", c);
  i2a(c, -98765); printf("%s\n", c);
  i2a(c, -987654); printf("%s\n", c);
  i2a(c, -9876543); printf("%s\n", c);
  i2a(c, -98765432); printf("%s\n", c);
  i2a(c, -987654321); printf("%s\n", c);
  i2a(c, INT32_MIN); printf("%s\n", c);
  i2a(c, INT32_MAX); printf("%s\n", c);
  i64toa(c, INT64_MAX); printf("%s\n", c);
  i64toa(c, INT64_MIN); printf("%s\n", c);
  u2a(c, 9); printf("%s\n", c);
  u2a(c, 98); printf("%s\n", c);
  u2a(c, 987); printf("%s\n", c);
  u2a(c, 9876); printf("%s\n", c);
  u2a(c, 98765); printf("%s\n", c);
  u2a(c, 987654); printf("%s\n", c);
  u2a(c, 9876543); printf("%s\n", c);
  u2a(c, 98765432); printf("%s\n", c);
  u2a(c, 987654321); printf("%s\n", c);
  u2a(c, UINT32_MAX); printf("%s\n", c);
  u64toa(c, UINT64_MAX); printf("%s\n", c);
  return 0;
}