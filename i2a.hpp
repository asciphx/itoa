#ifndef I2A_HPP
#define I2A_HPP
/*
* This software is licensed under the AGPL-3.0 License.
*
* Copyright (C) 2023 Asciphx
*
* Permissions of this strongest copyleft license are conditioned on making available
* complete source code of licensed works and modifications, which include larger works
* using a licensed work, under the same license. Copyright and license notices must be
* preserved. Contributors provide an express grant of patent rights. When a modified
* version is used to provide a service over a network, the complete source code of
* the modified version must be made available.
*/
#if defined(_WIN32)
#define __ALIGN(_) __declspec(align(_))
#define _INLINE __forceinline
#else
#define __ALIGN(_) __attribute__((aligned(_)))
#define _INLINE inline __attribute__((always_inline))
#endif
using U32 = unsigned int;
static __ALIGN(1) volatile char _c3DigitsLut[0xbb9] =
"000001002003004005006007008009010011012013014015016017018019020021022023024025026027028029030031032033034035036037038039040041042043044045046047048049"
"050051052053054055056057058059060061062063064065066067068069070071072073074075076077078079080081082083084085086087088089090091092093094095096097098099"
"100101102103104105106107108109110111112113114115116117118119120121122123124125126127128129130131132133134135136137138139140141142143144145146147148149"
"150151152153154155156157158159160161162163164165166167168169170171172173174175176177178179180181182183184185186187188189190191192193194195196197198199"
"200201202203204205206207208209210211212213214215216217218219220221222223224225226227228229230231232233234235236237238239240241242243244245246247248249"
"250251252253254255256257258259260261262263264265266267268269270271272273274275276277278279280281282283284285286287288289290291292293294295296297298299"
"300301302303304305306307308309310311312313314315316317318319320321322323324325326327328329330331332333334335336337338339340341342343344345346347348349"
"350351352353354355356357358359360361362363364365366367368369370371372373374375376377378379380381382383384385386387388389390391392393394395396397398399"
"400401402403404405406407408409410411412413414415416417418419420421422423424425426427428429430431432433434435436437438439440441442443444445446447448449"
"450451452453454455456457458459460461462463464465466467468469470471472473474475476477478479480481482483484485486487488489490491492493494495496497498499"
"500501502503504505506507508509510511512513514515516517518519520521522523524525526527528529530531532533534535536537538539540541542543544545546547548549"
"550551552553554555556557558559560561562563564565566567568569570571572573574575576577578579580581582583584585586587588589590591592593594595596597598599"
"600601602603604605606607608609610611612613614615616617618619620621622623624625626627628629630631632633634635636637638639640641642643644645646647648649"
"650651652653654655656657658659660661662663664665666667668669670671672673674675676677678679680681682683684685686687688689690691692693694695696697698699"
"700701702703704705706707708709710711712713714715716717718719720721722723724725726727728729730731732733734735736737738739740741742743744745746747748749"
"750751752753754755756757758759760761762763764765766767768769770771772773774775776777778779780781782783784785786787788789790791792793794795796797798799"
"800801802803804805806807808809810811812813814815816817818819820821822823824825826827828829830831832833834835836837838839840841842843844845846847848849"
"850851852853854855856857858859860861862863864865866867868869870871872873874875876877878879880881882883884885886887888889890891892893894895896897898899"
"900901902903904905906907908909910911912913914915916917918919920921922923924925926927928929930931932933934935936937938939940941942943944945946947948949"
"950951952953954955956957958959960961962963964965966967968969970971972973974975976977978979980981982983984985986987988989990991992993994995996997998999";
static __ALIGN(1) volatile char _c2DigitsLut[0xc9] =
"0001020304050607080910111213141516171819202122232425262728293031323334353637383940414243444546474849"
"5051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
//The fastest htoa fuction
_INLINE static char* h2a(char* c, unsigned char i) {
  if (i < U32(1e2)) { i <<= 1; if (i > 19) *c++ = _c2DigitsLut[i]; *c++ = _c2DigitsLut[++i]; return c; }
  *c++ = _c3DigitsLut[i *= 3]; *c++ = _c3DigitsLut[++i]; *c++ = _c3DigitsLut[++i]; return c;
}
//The fastest atoa fuction
_INLINE static char* a2a(char* c, char i) { if (i < 0) { *c = 45; return h2a(++c, ~--i); } return h2a(c, i); }
//The fastest ttoa fuction
_INLINE static char* t2a(char* c, unsigned short i) {
  if (i < U32(1e3)) {
    if (i < U32(1e2)) {
      i <<= 1; if (i > 19) *c++ = _c2DigitsLut[i]; *c++ = _c2DigitsLut[++i]; return c;
    }
    *c++ = _c3DigitsLut[i *= 3]; *c++ = _c3DigitsLut[++i]; *c++ = _c3DigitsLut[++i]; return c;
  }
  const unsigned short a = (i / 100) * 3; if (i > 9999) *c++ = _c3DigitsLut[a]; *c++ = _c3DigitsLut[a + 1];
  *c++ = _c3DigitsLut[a + 2]; i = (i % 100) << 1; *c++ = _c2DigitsLut[i]; *c++ = _c2DigitsLut[++i]; return c;
}
//The fastest stoa fuction
_INLINE static char* s2a(char* c, short i) { if (i < 0) { *c = 45; return t2a(++c, ~--i); } return t2a(c, i); }
//The fastest utoa fuction
_INLINE static char* u2a(char* c, unsigned int i) {
  if (i < U32(1e5)) {
    if (i < U32(1e3)) {
      if (i < U32(1e2)) {
        i <<= 1; if (i > 19) *c++ = _c2DigitsLut[i]; *c++ = _c2DigitsLut[++i]; return c;
      }
      *c++ = _c3DigitsLut[i *= 3]; *c++ = _c3DigitsLut[++i]; *c++ = _c3DigitsLut[++i]; return c;
    }
    const unsigned short a = static_cast<unsigned short>(i / 100) * 3;
    if (i > 9999) *c++ = _c3DigitsLut[a]; *c++ = _c3DigitsLut[a + 1]; *c++ = _c3DigitsLut[a + 2];
    *c++ = _c2DigitsLut[i = (i % 100) << 1]; *c++ = _c2DigitsLut[++i]; return c;
  }
  const unsigned int S = i / 1000000;
  if (S < U32(1e2)) {
    unsigned int F = S << 1;
    if (S > 9) *c++ = _c2DigitsLut[F];
    *c++ = _c2DigitsLut[++F];
    i %= 1000000;
    F = (i / 1000) * 3;
    *c++ = _c3DigitsLut[F];
    *c++ = _c3DigitsLut[++F];
    *c++ = _c3DigitsLut[++F];
    F = (i % 1000) * 3;
    *c++ = _c3DigitsLut[F];
    *c++ = _c3DigitsLut[++F];
    *c++ = _c3DigitsLut[++F]; return c;
  }
  unsigned int F = (S / 100) << 1;
  if (S > 999) *c++ = _c2DigitsLut[F];
  *c++ = _c2DigitsLut[++F];
  F = (S % 100) << 1;
  *c++ = _c2DigitsLut[F];
  *c++ = _c2DigitsLut[++F];
  i %= 1000000;
  F = (i / 1000) * 3;
  *c++ = _c3DigitsLut[F];
  *c++ = _c3DigitsLut[++F];
  *c++ = _c3DigitsLut[++F];
  F = (i % 1000) * 3;
  *c++ = _c3DigitsLut[F];
  *c++ = _c3DigitsLut[++F];
  *c++ = _c3DigitsLut[++F]; return c;
}
//The fastest itoa fuction
_INLINE static char* i2a(char* c, int i) { if (i < 0) { *c = 45; return u2a(++c, ~--i); } return u2a(c, i); }
//The fastest u64toa fuction
_INLINE static char* u64toa(char* c, unsigned long long i) {
  if (i < 10000000000ULL) {
    if (i < U32(1e5)) {
      if (i < U32(1e3)) {
        if (i < U32(1e2)) {
          i <<= 1; if (i > 19) *c++ = _c2DigitsLut[i]; *c++ = _c2DigitsLut[++i]; return c;
        }
        *c++ = _c3DigitsLut[i *= 3]; *c++ = _c3DigitsLut[++i]; *c++ = _c3DigitsLut[++i]; return c;
      }
      const unsigned short a = static_cast<unsigned short>(i / 100) * 3;
      if (i > 9999) *c++ = _c3DigitsLut[a]; *c++ = _c3DigitsLut[a + 1]; *c++ = _c3DigitsLut[a + 2];
      *c++ = _c2DigitsLut[i = (i % 100) << 1]; *c++ = _c2DigitsLut[++i]; return c;
    }
    const unsigned int S = static_cast<unsigned int>(i / 1000000);
    if (S < U32(1e2)) {
      const unsigned int a = S << 1;
      if (S > 9) *c++ = _c2DigitsLut[a];
      *c++ = _c2DigitsLut[a + 1];
    } else {
      const unsigned int a = (S / 100) << 1;
      if (S > 999) *c++ = _c2DigitsLut[a];
      *c++ = _c2DigitsLut[a + 1];
      const unsigned int b = (S % 100) << 1;
      *c++ = _c2DigitsLut[b];
      *c++ = _c2DigitsLut[b + 1];
    }
    i %= 1000000;
    unsigned long long G = i / 1000 * 3;
    *c++ = _c3DigitsLut[G];
    *c++ = _c3DigitsLut[++G];
    *c++ = _c3DigitsLut[++G];
    G = (i % 1000) * 3;
    *c++ = _c3DigitsLut[G];
    *c++ = _c3DigitsLut[++G];
    *c++ = _c3DigitsLut[++G]; return c;
  }
  unsigned int h = static_cast<unsigned int>(i / 10000000000ULL);
  i %= 10000000000ULL;
  if (h < U32(1e6)) {
    if (h < U32(1e5)) {
      if (h < U32(1e3)) {
        if (h < U32(1e2)) {
          h <<= 1; if (h > 9) *c++ = _c2DigitsLut[h]; *c++ = _c2DigitsLut[++h]; goto $;
        }
        *c++ = _c3DigitsLut[h *= 3]; *c++ = _c3DigitsLut[++h]; *c++ = _c3DigitsLut[++h]; goto $;
      }
      const unsigned int a = h / 100;
      if (a < U32(1e2)) {
        const unsigned int b = a << 1; *c++ = _c2DigitsLut[b]; *c++ = _c2DigitsLut[b + 1];
        *c++ = _c2DigitsLut[h = (h % 100u) << 1]; *c++ = _c2DigitsLut[++h]; goto $;
      }
      const unsigned int b = a * 3; *c++ = _c3DigitsLut[b]; *c++ = _c3DigitsLut[b + 1]; *c++ = _c3DigitsLut[b + 2];
      *c++ = _c2DigitsLut[h = (h % 100) << 1]; *c++ = _c2DigitsLut[++h]; goto $;
    }
    const unsigned int b = h / 1000 * 3; *c++ = _c3DigitsLut[b]; *c++ = _c3DigitsLut[b + 1]; *c++ = _c3DigitsLut[b + 2];
    *c++ = _c3DigitsLut[h = (h % 1000) * 3]; *c++ = _c3DigitsLut[++h]; *c++ = _c3DigitsLut[++h];
  } else {
    unsigned int V = h / 1000, x = 7; char z = 3; unsigned int F = 3 * (h - (V * 1000));
    if (V < U32(1e6)) { if (V < U32(1e5)) { if (V < U32(1e4)) { z = 0; x -= 3; goto _; } x -= 2, z = 1; goto _; }  x -= 1, z = 2; }
  _:c[x] = _c3DigitsLut[F];
    c[++x] = _c3DigitsLut[++F];
    c[++x] = _c3DigitsLut[++F];
    h = V / 1000; x -= 5;
    F = 3 * (V - (h * 1000));
    c[x] = _c3DigitsLut[F];
    c[++x] = _c3DigitsLut[++F];
    c[++x] = _c3DigitsLut[++F];
    V = h / 1000; x -= 5;
    F = 3 * (h - (V * 1000));
    switch (z) {
    case 3: c[0] = V + 0x30;
    case 2: c[x] = _c3DigitsLut[F];
    case 1: c[x + 1] = _c3DigitsLut[F + 1];
    case 0: c[x + 2] = _c3DigitsLut[F + 2];
    }
    c += 7 + z;
  }
$:h = static_cast<unsigned int>(i / 10000000) * 3; i %= 10000000;
  *c++ = _c3DigitsLut[h];
  *c++ = _c3DigitsLut[++h];
  *c++ = _c3DigitsLut[++h];
  h = static_cast<unsigned int>(i / 10000) * 3; i %= 10000;
  *c++ = _c3DigitsLut[h];
  *c++ = _c3DigitsLut[++h];
  *c++ = _c3DigitsLut[++h];
  h = static_cast<unsigned int>(i / 10) * 3;
  *c++ = _c3DigitsLut[h];
  *c++ = _c3DigitsLut[++h];
  *c++ = _c3DigitsLut[++h];
  *c++ = i % 10 + 0x30;
  return c;
}
//The fastest i64toa fuction
_INLINE static char* i64toa(char* c, long long i) { if (i < 0) { *c = 45; return u64toa(++c, ~--i); } return u64toa(c, i); }
#undef __ALIGN
#undef _INLINE
#endif // I2A_HPP
