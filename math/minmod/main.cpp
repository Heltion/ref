u64 min_of_mod(u64 n, u64 m, u64 a, u64 b, u64 c = 1, u64 p = 1, u64 q = 1) {
  if (a == 0) { return b; }
  if (c % 2) {
    if (b >= a) {
      u64 t = (m - b + a - 1) / a;
      u64 d = (t - 1) * p + q;
      if (n <= d) { return b; }
      n -= d;
      b += a * t - m;
    }
    b = a - 1 - b;
  } else {
    if (b < m - a) {
      u64 t = (m - b - 1) / a;
      u64 d = t * p;
      if (n <= d) { return (n - 1) / p * a + b; }
      n -= d;
      b += a * t;
    }
    b = m - 1 - b;
  }
  u64 d = m / a;
  u64 res = min_of_mod(n, a, m % a, b, c += 1, (d - 1) * p + q, d * p + q);
  return c % 2 ? m - 1 - res : a - 1 - res;
}