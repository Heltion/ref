struct NimProduct {
  array<array<u64, 64>, 64> mem;
  NimProduct() {
    for (int i = 0; i < 64; i += 1) {
      for (int j = 0; j < 64; j += 1) {
        int k = i & j;
        if (k == 0) {
          mem[i][j] = u64(1) << (i | j);
        } else {
          int x = k & -k;
          mem[i][j] = mem[i ^ x][j] ^
                      mem[(i ^ x) | (x - 1)][(j ^ x) | (i & (x - 1))];
        }
      }
    }
  }
  u64 nim_product(u64 x, u64 y) {
    u64 res = 0;
    for (int i = 0; i < 64 and x >> i; i += 1) {
      if ((x >> i) % 2) {
        for (int j = 0; j < 64 and y >> j; j += 1) {
          if ((y >> j) % 2) { res ^= mem[i][j]; }
        }
      }
    }
    return res;
  }
};