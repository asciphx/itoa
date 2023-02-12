#ifndef I2A_H
#define I2A_H
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
#pragma warning(disable:4244)
#ifdef __cplusplus
extern "C" {
#endif
  //The fastest u2a fuction
  void u2a(char* c, unsigned int i);
  //The fastest itoa fuction
  static
#if defined(_WIN32)
	__forceinline
#else
	inline __attribute__((always_inline))
#endif
	void i2a(char* c, int i) {
	if (i < 0) { *c = 45; u2a(c + 1, ~i + 1); } u2a(c, i);
  }
  //The fastest u64toa fuction
  unsigned char u64toa(char* c, unsigned long long i);
  //The fastest i64toa fuction
  static
#if defined(_WIN32)
	__forceinline
#else
	inline __attribute__((always_inline))
#endif
	unsigned char i64toa(char* c, long long i) {
	if (i < 0) { *c = 45; return u64toa(c + 1, ~i + 1); } return u64toa(c, i);
  }
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif // I2A_H
