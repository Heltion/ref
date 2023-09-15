bool miller_rabin(i64 n) {
  static constexpr array<int, 9> p = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  if (n == 1) { return false; }
  if (n == 2) { return true; }
  if (not(n % 2)) { return false; }
  int r = countr_zero(u64(n - 1));
  i64 d = (n - 1) >> r;
  for (int pi : p) {
    if (pi >= n) { break; }
    i64 x = power(pi, d, n);
    if (x == 1 or x == n - 1) { continue; };
    for (int j = 1; j < r; j += 1) {
      x = (i128)x * x % n;
      if (x == n - 1) { break; }
    }
    if (x != n - 1) { return false; }
  }
  return true;
};