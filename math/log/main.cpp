i64 log(i64 x, i64 y, i64 n) {
  if (y == 1 or n == 1) {
    return 0;
  }
  if (not x) {
    return y ? -1 : 1;
  }
  i64 res = 0, k = 1 % n;
  for (i64 d; k != y and (d = gcd(x, n)) != 1; res += 1) {
    if (y % d) {
      return -1;
    }
    n /= d;
    y /= d;
    k = k * (x / d) % n;
  }
  if (k == y) {
    return res;
  }
  unordered_map<i64, i64> mp;
  i64 px = 1, m = sqrt(n) + 1;
  for (int i = 0; i < m; i += 1, px = px * x % n) {
    mp[y * px % n] = i;
  }
  i64 ppx = k * px % n;
  for (int i = 1; i <= m; i += 1, ppx = ppx * px % n) {
    if (mp.count(ppx)) {
      return res + i * m - mp[ppx];
    }
  }
  return -1;
}