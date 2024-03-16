optional<i64> sqrt_mod(i64 y, i64 p) {
  if (y <= 1) return y;
  auto power = [&]<class T>(auto mul, T a, i64 r, auto res) {
    for (; r; r >>= 1, a = mul(a, a))
      if (r & 1) res = mul(res, a);
    return res;
  };
  auto mul_mod = [&](i64 x, i64 y) { return x * y % p; };
  if (power(mul_mod, y, (p - 1) / 2, 1) != 1) return {};
  i64 x, w;
  do {
    x = random_device()() % p;
    w = (x * x + p - y) % p;
  } while (power(mul_mod, w, (p - 1) / 2, 1) == 1);
  using P = pair<i64, i64>;
  auto mul_pair = [&](P p0, P p1) {
    auto [x0, y0] = p0;
    auto [x1, y1] = p1;
    return pair((x0 * x1 + y0 * y1 % p * w) % p, (x0 * y1 + y0 * x1) % p);
  };
  return power(mul_pair, P(x, 1), (p + 1) / 2, P(1, 0)).first;
}