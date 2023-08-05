#include <vector>
class Matrix {
  int x, y;

 public:
  std::vector<std::vector<int>> matrix;
  Matrix(int size_x, int size_y) : matrix(size_x, std::vector<int>(size_y)) {}
};
class Vector {
  int x;

 public:
  std::vector<int> vector;
  Vector(int size_x) : vector(size_x) {}
  void operator*(const Matrix& matrix);
};
