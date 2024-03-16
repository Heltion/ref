using i128 = __int128_t;
i64 power(i64 a, i64 r, i64 mod) {
  i64 res = 1;
  for (; r; r >>= 1, a = (i128)a * a % mod)
    if (r & 1) res = (i128)res * a % mod;

  return res;
}
bool miller_rabin(i64 n) {
  static constexpr array<int, 9> p = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  if (n == 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  int r = countr_zero(u64(n - 1));
  i64 d = (n - 1) >> r;
  for (int pi : p) {
    if (pi < n) {
      i64 x = power(pi, d, n);
      if (x == 1 or x == n - 1) continue;
      for (int j = 1; j < r; j += 1) {
        x = (i128)x * x % n;
        if (x == n - 1) break;
      }
      if (x != n - 1) return false;
    }
  }
  return true;
};
vector<i64> pollard_rho(i64 n) {
  if (n == 1) return {};
  vector<i64> res, stack = {n};
  while (not stack.empty()) {
    i64 n = stack.back();
    stack.pop_back();
    if (miller_rabin(n)) {
      res.push_back(n);
      continue;
    }
    i64 d = n;
    for (i64 c = random_device()() % n; d == n; c += 1) {
      d = 1;
      for (i64 k = 1, y = 0, x = 0, s = 1; d == 1; k <<= 1, y = x, s = 1)
        for (int i = 1; i <= k; i += 1) {
          x = ((i128)x * x + c) % n;
          s = (i128)s * abs(x - y) % n;
          if (not(i % 63) or i == k) {
            d = gcd(s, n);
            if (d != 1) break;
          }
        }
    }
    stack.push_back(d);
    stack.push_back(n / d);
  };
  return res;
}