int __attribute__((pascal)) func(int a, int b, int c, int d) {
  return a + b + c + d;
}

int main() {
  return func(1, 2, 3, 4); // break here
}
