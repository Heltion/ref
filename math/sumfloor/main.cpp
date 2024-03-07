u64 sum_of_floor(u64 n, u64 m, u64 a, u64 b) {
  u64 ans = 0;
  while (n) {
    ans += a / m * n * (n - 1) / 2;
    a %= m;
    ans += b / m * n;
    b %= m;
    u64 y = a * n + b;
    if (y < m) {
      break;
    }
    tie(n, m, a, b) = tuple(y / m, a, m, y % m);
  }
  return ans;
}