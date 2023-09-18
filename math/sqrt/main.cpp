i64 sqrt(i64 y, i64 p) {
  static mt19937_64 mt;
  if (y <= 1) { return y; };
  if (power(y, (p - 1) / 2, p) != 1) { return -1; }
  uniform_int_distribution uid(i64(0), p - 1);
  i64 x, w;
  do {
    x = uid(mt);
    w = (x * x + p - y) % p;
  } while (power(w, (p - 1) / 2, p) == 1);
  auto mul = [&](pair<i64, i64> a, pair<i64, i64> b) {
    return pair((a.first * b.first + a.second * b.second % p * w) % p,
                (a.first * b.second + a.second * b.first) % p);
  };
  pair<i64, i64> a = {x, 1}, res = {1, 0};
  for (i64 r = (p + 1) >> 1; r; r >>= 1, a = mul(a, a)) {
    if (r & 1) { res = mul(res, a); }
  }
  return res.first;
}