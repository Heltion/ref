i64 phi(i64 n) {
  auto pd = pollard_rho(n);
  ranges::sort(pd);
  pd.erase(ranges::unique(pd).begin(), pd.end());
  for (i64 pi : pd) { n = n / pi * (pi - 1); }
  return n;
}
i64 minimum_primitive_root(i64 n) {
  i64 pn = phi(n);
  auto pd = pollard_rho(pn);
  ranges::sort(pd);
  pd.erase(ranges::unique(pd).begin(), pd.end());
  auto check = [&](i64 r) {
    if (gcd(r, n) != 1) { return false; }
    for (i64 pi : pd) {
      if (power(r, pn / pi, n) == 1) { return false; }
    }
    return true;
  };
  i64 r = 1;
  while (not check(r)) { r += 1; }
  return r;
}