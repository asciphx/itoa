#pragma once
// SSE2 implementation according to http://0x80.pl/articles/sse-itoa.html
// Modifications: (1) fix incorrect digits (2) accept all ranges (3) write to user provided buffer.

#if defined(i386) || defined(__amd64) || defined(_M_IX86) || defined(_M_X64)

#include <cassert>
#include <emmintrin.h>
#include <stdint.h>
#ifdef _MSC_VER
#include "intrin.h"
#endif
#ifdef _MSC_VER
#define __ALIGN(_) __declspec(align(_))
#else
#define __ALIGN(_) __attribute__ ((aligned(_)))
#endif
static __ALIGN(2) const char gDigitsLut[0xc9] =
"0001020304050607080910111213141516171819202122232425262728293031323334353637383940414243444546474849"
"5051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
static const unsigned int kDiv10000 = 0xd1b71759;
static __ALIGN(16) const unsigned int kDiv10000Vector[4] = { kDiv10000, kDiv10000, kDiv10000, kDiv10000 };
static __ALIGN(16) const unsigned int k10000Vector[4] = { 10000, 10000, 10000, 10000 };
static __ALIGN(16) const uint16_t kDivPowersVector[8] = { 8389, 5243, 13108, 32768, 8389, 5243, 13108, 32768 }; // 10^3, 10^2, 10^1, 10^0
static __ALIGN(16) const uint16_t kShiftPowersVector[8] = {
	1 << (16 - (23 + 2 - 16)),
	1 << (16 - (19 + 2 - 16)),
	1 << (16 - 1 - 2),
	1 << (15),
	1 << (16 - (23 + 2 - 16)),
	1 << (16 - (19 + 2 - 16)),
	1 << (16 - 1 - 2),
	1 << (15)
};
static __ALIGN(16) const uint16_t k10Vector[8] = { 10, 10, 10, 10, 10, 10, 10, 10 };
static __ALIGN(16) const char kAsciiZero[16] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };

inline __m128i Convert8DigitsSSE2(unsigned int value) {
  assert(value <= 99999999);

  // abcd, efgh = abcdefgh divmod 10000 
  const __m128i abcdefgh = _mm_cvtsi32_si128(value);
  const __m128i abcd = _mm_srli_epi64(_mm_mul_epu32(abcdefgh, reinterpret_cast<const __m128i*>(kDiv10000Vector)[0]), 45);
  const __m128i efgh = _mm_sub_epi32(abcdefgh, _mm_mul_epu32(abcd, reinterpret_cast<const __m128i*>(k10000Vector)[0]));

  // v1 = [ abcd, efgh, 0, 0, 0, 0, 0, 0 ]
  const __m128i v1 = _mm_unpacklo_epi16(abcd, efgh);

  // v1a = v1 * 4 = [ abcd * 4, efgh * 4, 0, 0, 0, 0, 0, 0 ]
  const __m128i v1a = _mm_slli_epi64(v1, 2);

  // v2 = [ abcd * 4, abcd * 4, abcd * 4, abcd * 4, efgh * 4, efgh * 4, efgh * 4, efgh * 4 ]
  const __m128i v2a = _mm_unpacklo_epi16(v1a, v1a);
  const __m128i v2 = _mm_unpacklo_epi32(v2a, v2a);

  // v4 = v2 div 10^3, 10^2, 10^1, 10^0 = [ a, ab, abc, abcd, e, ef, efg, efgh ]
  const __m128i v3 = _mm_mulhi_epu16(v2, reinterpret_cast<const __m128i*>(kDivPowersVector)[0]);
  const __m128i v4 = _mm_mulhi_epu16(v3, reinterpret_cast<const __m128i*>(kShiftPowersVector)[0]);

  // v5 = v4 * 10 = [ a0, ab0, abc0, abcd0, e0, ef0, efg0, efgh0 ]
  const __m128i v5 = _mm_mullo_epi16(v4, reinterpret_cast<const __m128i*>(k10Vector)[0]);

  // v6 = v5 << 16 = [ 0, a0, ab0, abc0, 0, e0, ef0, efg0 ]
  const __m128i v6 = _mm_slli_epi64(v5, 16);

  // v7 = v4 - v6 = { a, b, c, d, e, f, g, h }
  const __m128i v7 = _mm_sub_epi16(v4, v6);

  return v7;
}

inline __m128i ShiftDigits_SSE2(__m128i a, unsigned digit) {
  assert(digit <= 8);
  switch (digit) {
  case 0: return a;
  case 1: return _mm_srli_si128(a, 1);
  case 2: return _mm_srli_si128(a, 2);
  case 3: return _mm_srli_si128(a, 3);
  case 4: return _mm_srli_si128(a, 4);
  case 5: return _mm_srli_si128(a, 5);
  case 6: return _mm_srli_si128(a, 6);
  case 7: return _mm_srli_si128(a, 7);
  case 8: return _mm_srli_si128(a, 8);
  }
  return a; // should not execute here.
}

inline void u32toa_sse2(unsigned int value, char* buffer) {
  if (value < 10000) {
	const unsigned int d1 = (value / 100) << 1;
	const unsigned int d2 = (value % 100) << 1;

	if (value >= 1000)
	  *buffer++ = gDigitsLut[d1];
	if (value >= 100)
	  *buffer++ = gDigitsLut[d1 + 1];
	if (value >= 10)
	  *buffer++ = gDigitsLut[d2];
	*buffer++ = gDigitsLut[d2 + 1];
	*buffer++ = '\0';
  } else if (value < 100000000) {
	const unsigned int b = value / 10000;
	const unsigned int c = value % 10000;

	const unsigned int d1 = (b / 100) << 1;
	const unsigned int d2 = (b % 100) << 1;

	const unsigned int d3 = (c / 100) << 1;
	const unsigned int d4 = (c % 100) << 1;

	if (value >= 10000000)
	  *buffer++ = gDigitsLut[d1];
	if (value >= 1000000)
	  *buffer++ = gDigitsLut[d1 + 1];
	if (value >= 100000)
	  *buffer++ = gDigitsLut[d2];
	*buffer++ = gDigitsLut[d2 + 1];

	*buffer++ = gDigitsLut[d3];
	*buffer++ = gDigitsLut[d3 + 1];
	*buffer++ = gDigitsLut[d4];
	*buffer++ = gDigitsLut[d4 + 1];
	*buffer++ = '\0';
  } else {
	// value = aabbbbbbbb in decimal

	const unsigned int a = value / 100000000; // 1 to 42
	value %= 100000000;

	if (a >= 10) {
	  const unsigned i = a << 1;
	  *buffer++ = gDigitsLut[i];
	  *buffer++ = gDigitsLut[i + 1];
	} else
	  *buffer++ = '0' + static_cast<char>(a);

	const __m128i b = Convert8DigitsSSE2(value);
	const __m128i ba = _mm_add_epi8(_mm_packus_epi16(_mm_setzero_si128(), b), reinterpret_cast<const __m128i*>(kAsciiZero)[0]);
	const __m128i result = _mm_srli_si128(ba, 8);
	_mm_storel_epi64(reinterpret_cast<__m128i*>(buffer), result);
	buffer[8] = '\0';
  }
}

void i32toa_sse2(int32_t value, char* buffer) {
  unsigned int u = static_cast<unsigned int>(value);
  if (value < 0) {
	*buffer++ = '-';
	u = ~u + 1;
  }
  u32toa_sse2(u, buffer);
}

inline void u64toa_sse2(uint64_t value, char* buffer) {
  if (value < 100000000) {
	unsigned int v = static_cast<unsigned int>(value);
	if (v < 10000) {
	  const unsigned int d1 = (v / 100) << 1;
	  const unsigned int d2 = (v % 100) << 1;

	  if (v >= 1000)
		*buffer++ = gDigitsLut[d1];
	  if (v >= 100)
		*buffer++ = gDigitsLut[d1 + 1];
	  if (v >= 10)
		*buffer++ = gDigitsLut[d2];
	  *buffer++ = gDigitsLut[d2 + 1];
	  *buffer++ = '\0';
	} else {
	  // value = bbbbcccc
	  const unsigned int b = v / 10000;
	  const unsigned int c = v % 10000;

	  const unsigned int d1 = (b / 100) << 1;
	  const unsigned int d2 = (b % 100) << 1;

	  const unsigned int d3 = (c / 100) << 1;
	  const unsigned int d4 = (c % 100) << 1;

	  if (value >= 10000000)
		*buffer++ = gDigitsLut[d1];
	  if (value >= 1000000)
		*buffer++ = gDigitsLut[d1 + 1];
	  if (value >= 100000)
		*buffer++ = gDigitsLut[d2];
	  *buffer++ = gDigitsLut[d2 + 1];

	  *buffer++ = gDigitsLut[d3];
	  *buffer++ = gDigitsLut[d3 + 1];
	  *buffer++ = gDigitsLut[d4];
	  *buffer++ = gDigitsLut[d4 + 1];
	  *buffer++ = '\0';
	}
  } else if (value < 10000000000000000) {
	const unsigned int v0 = static_cast<unsigned int>(value / 100000000);
	const unsigned int v1 = static_cast<unsigned int>(value % 100000000);

	const __m128i a0 = Convert8DigitsSSE2(v0);
	const __m128i a1 = Convert8DigitsSSE2(v1);

	// Convert to bytes, add '0'
	const __m128i va = _mm_add_epi8(_mm_packus_epi16(a0, a1), reinterpret_cast<const __m128i*>(kAsciiZero)[0]);

	// Count number of digit
	const unsigned mask = _mm_movemask_epi8(_mm_cmpeq_epi8(va, reinterpret_cast<const __m128i*>(kAsciiZero)[0]));
#ifdef _MSC_VER
	unsigned long digit;
	_BitScanForward(&digit, ~mask | 0x8000);
#else
	unsigned digit = __builtin_ctz(~mask | 0x8000);
#endif

	// Shift digits to the beginning
	__m128i result = ShiftDigits_SSE2(va, digit);
	_mm_storeu_si128(reinterpret_cast<__m128i*>(buffer), result);
	buffer[16 - digit] = '\0';
  } else {
	const unsigned int a = static_cast<unsigned int>(value / 10000000000000000); // 1 to 1844
	value %= 10000000000000000;

	if (a < 10)
	  *buffer++ = '0' + static_cast<char>(a);
	else if (a < 100) {
	  const unsigned int i = a << 1;
	  *buffer++ = gDigitsLut[i];
	  *buffer++ = gDigitsLut[i + 1];
	} else if (a < 1000) {
	  *buffer++ = '0' + static_cast<char>(a / 100);

	  const unsigned int i = (a % 100) << 1;
	  *buffer++ = gDigitsLut[i];
	  *buffer++ = gDigitsLut[i + 1];
	} else {
	  const unsigned int i = (a / 100) << 1;
	  const unsigned int j = (a % 100) << 1;
	  *buffer++ = gDigitsLut[i];
	  *buffer++ = gDigitsLut[i + 1];
	  *buffer++ = gDigitsLut[j];
	  *buffer++ = gDigitsLut[j + 1];
	}

	const unsigned int v0 = static_cast<unsigned int>(value / 100000000);
	const unsigned int v1 = static_cast<unsigned int>(value % 100000000);

	const __m128i a0 = Convert8DigitsSSE2(v0);
	const __m128i a1 = Convert8DigitsSSE2(v1);

	// Convert to bytes, add '0'
	const __m128i va = _mm_add_epi8(_mm_packus_epi16(a0, a1), reinterpret_cast<const __m128i*>(kAsciiZero)[0]);
	_mm_storeu_si128(reinterpret_cast<__m128i*>(buffer), va);
	buffer[16] = '\0';
  }
}

void i64toa_sse2(int64_t value, char* buffer) {
  uint64_t u = static_cast<uint64_t>(value);
  if (value < 0) {
	*buffer++ = '-';
	u = ~u + 1;
  }
  u64toa_sse2(u, buffer);
}
#endif