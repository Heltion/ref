i64 sum_of_floor(i64 n, i64 m, i64 a, i64 b) {
  i64 res = 0;
  while (n) {
    res += a / m * n * (n - 1) / 2;
    a %= m;
    res += b / m * n;
    b %= m;
    i64 y = a * n + b;
    if (y < m) break;
    tie(n, m, a, b) = tuple(y / m, a, m, y % m);
  }
  return res;
}