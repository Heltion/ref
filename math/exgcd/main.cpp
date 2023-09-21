tuple<i64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x = 1, y = 0, x1 = 0, y1 = 1;
  while (b) {
    i64 q = a / b;
    tie(x, x1) = pair(x1, x - q * x1);
    tie(y, y1) = pair(y1, x - q * y1);
    tie(a, b) = pair(b, a - q * b);
  }
  return {a, x, y};
}