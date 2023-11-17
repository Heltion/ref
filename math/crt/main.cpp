tuple<i64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x = 1, y = 0, x1 = 0, y1 = 1;
  while (b) {
    i64 q = a / b;
    tie(x, x1) = pair(x1, x - q * x1);
    tie(y, y1) = pair(y1, y - q * y1);
    tie(a, b) = pair(b, a - q * b);
  }
  return {a, x, y};
}
optional<pair<i64, i64>> linear_equations(i64 a0, i64 b0, i64 a1, i64 b1) {
  auto [d, x, y] = exgcd(a0, a1);
  if ((b1 - b0) % d) { return {}; }
  i64 a = a0 / d * a1, b = (i128)(b1 - b0) / d * x % (a1 / d);
  if (b < 0) { b += a1 / d; }
  b = (i128)(a0 * b + b0) % a;
  if (b < 0) { b += a; }
  return {{a, b}};
}