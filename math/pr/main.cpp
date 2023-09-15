vector<i64> pollard_rho(i64 n) {
  static mt19937_64 mt;
  uniform_int_distribution uid(i64(0), n);
  if (n == 1) { return {}; }
  vector<i64> res;
  function<void(i64)> rho = [&](i64 n) {
    if (miller_rabin(n)) { return res.push_back(n); }
    i64 d = n;
    while (d == n) {
      d = 1;
      for (i64 k = 1, y = 0, x = 0, s = 1, c = uid(mt); d == 1;
           k <<= 1, y = x, s = 1) {
        for (int i = 1; i <= k; i += 1) {
          x = ((i128)x * x + c) % n;
          s = (i128)s * abs(x - y) % n;
          if (not(i % 127) or i == k) {
            d = gcd(s, n);
            if (d != 1) { break; }
          }
        }
      }
    }
    rho(d);
    rho(n / d);
  };
  rho(n);
  return res;
}