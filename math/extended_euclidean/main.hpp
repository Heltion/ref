template <typename T>
tuple<T, T, T> exgcd(T a, T b) {
  T x = 1, y = 0, x1 = 0, y1 = 1;
  while (b) {
    T q = a / b;
    tie(x, x1) = pair(x1, x - q * x1);
    tie(y, y1) = pair(y1, x - q * y1);
    tie(a, b) = pair(b, a - q * b);
  }
  return {a, x, y};
}
template <typename T>
optional<pair<T, T>> crt(T a0, T b0, T a1, T b1) {
  auto [d, x, y] = exgcd(a0, a1);
  if ((b1 - b0) % d) return {};
  T a = a0 / d * a1, b = (b1 - b0) / d * x % (a1 / d);
  if (b < 0) b += a1 / d;
  b = (a0 * b + b0) % a;
  if (b < 0) b += a;
  return {{a, b}};
}