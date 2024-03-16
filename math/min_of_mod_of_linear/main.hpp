i64 min_of_mod(i64 n, i64 m, i64 a, i64 b, bool rev = false, i64 p = 1, i64 q = 1) {
  if (not a) return b;
  if (rev) {
    if (b < m - a) {
      i64 t = (m - b - 1) / a, d = t * p;
      if (n <= d) return (n - 1) / p * a + b;
      n -= d;
      b += a * t;
    }
    b = m - 1 - b;
  } else {
    if (b >= a) {
      i64 t = (m - b + a - 1) / a, d = (t - 1) * p + q;
      if (n <= d) return b;
      n -= d;
      b += a * t - m;
    }
    b = a - 1 - b;
  }
  return (rev ? m : a) - 1 - min_of_mod(n, a, m % a, b, not rev, (m / a - 1) * p + q, m / a * p + q);
}