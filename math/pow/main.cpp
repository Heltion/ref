i64 power(i64 a, i64 r, i64 mod) {
  i64 res = 1;
  for (; r; r >>= 1, a = (i128)a * a % mod) {
    if (r & 1) { res = (i128)res * a % mod; }
  }
  return res;
}