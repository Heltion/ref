f64 simpson(function<f64(f64)> f, f64 l, f64 r) {
  return (r - l) * (f(l) + f(r) + 4 * f(midpoint(l, r))) / 6;
}
f64 adaptive_simpson(const function<f64(f64)>& f, f64 l, f64 r, f64 eps) {
  f64 m = midpoint(l, r);
  f64 s = simpson(f, l, r);
  f64 sl = simpson(f, l, m);
  f64 sr = simpson(f, m, r);
  f64 d = sl + sr - s;
  if (abs(d) < 15 * eps) {
    return (sl + sr) + d / 15;
  }
  return adaptive_simpson(f, l, m, eps / 2) +
         adaptive_simpson(f, m, r, eps / 2);
}