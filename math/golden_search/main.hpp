template <int step>
f64 local_minimum(auto& f, f64 l, f64 r) {
  auto get = [&](f64 l, f64 r) { return (numbers::phi - 1) * l + (2 - numbers::phi) * r; };
  f64 ml = get(l, r), mr = get(r, l), fml = f(ml), fmr = f(mr);
  for (int _ = 0; _ < step; _ += 1)
    if (fml > fmr) {
      l = exchange(ml, mr);
      fml = exchange(fmr, f(mr = get(r, l)));
    } else {
      r = exchange(mr, ml);
      fmr = exchange(fml, f(ml = get(l, r)));
    }
  return midpoint(l, r);
}