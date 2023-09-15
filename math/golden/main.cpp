template <int step> f64 golden_search(function<f64(f64)> f, f64 l, f64 r) {
  f64 ml = (numbers::phi - 1) * l + (2 - numbers::phi) * r;
  f64 mr = l + r - ml;
  f64 fml = f(ml), fmr = f(mr);
  for (int i = 0; i < step; i += 1)
    if (fml > fmr) {
      l = ml;
      ml = mr;
      fml = fmr;
      fmr = f(mr = (numbers::phi - 1) * r + (2 - numbers::phi) * l);
    } else {
      r = mr;
      mr = ml;
      fmr = fml;
      fml = f(ml = (numbers::phi - 1) * l + (2 - numbers::phi) * r);
    }
  return midpoint(l, r);
}