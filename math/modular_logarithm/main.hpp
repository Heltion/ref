optional<i64> log_mod(i64 x, i64 y, i64 m) {
  if (y == 1 or m == 1) return 0;
  if (not x) return y ? nullopt : optional(1);
  i64 k = 0, z = 1;
  for (i64 d; z != y and (d = gcd(x, m)) != 1; k += 1) {
    if (y % d) return {};
    m /= d;
    y /= d;
    z = z * (x / d) % m;
  }
  if (z == y) return k;
  unordered_map<i64, i64> mp;
  i64 p = 1, n = sqrt(m);
  for (int i = 0; i < n; i += 1, p = p * x % m) mp[y * p % m] = i;
  z = z * p % m;
  for (int i = 1; i <= n; i += 1, z = z * p % m)
    if (mp.contains(z)) return k + i * n - mp[z];
  return {};
}