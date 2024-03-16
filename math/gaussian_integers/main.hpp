struct GaussInteger {
  i64 x, y;
  i64 norm() { return x * x + y * y; }
  bool operator!=(i64 r) { return y or x != r; }
  GaussInteger operator~() { return {x, -y}; }
  GaussInteger operator-(GaussInteger gi) { return {x - gi.x, y - gi.y}; }
  GaussInteger operator*(GaussInteger gi) { return {x * gi.x - y * gi.y, x * gi.y + y * gi.x}; }
  GaussInteger operator/(GaussInteger gi) {
    auto [x, y] = operator*(~gi);
    auto div_floor = [&](i64 x, i64 y) { return x / y - (x % y < 0); };
    auto div_round = [&](i64 x, i64 y) { return div_floor(2 * x + y, 2 * y); };
    return {div_round(x, gi.norm()), div_round(y, gi.norm())};
  }
  GaussInteger operator%(GaussInteger gi) { return operator-(gi*(operator/(gi))); }
};