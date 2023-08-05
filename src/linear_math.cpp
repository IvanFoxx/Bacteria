#include "linear_math.hpp"

void Vector::operator*(const Matrix& matrix) {
  std::vector<int> sum(x, 0);
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < x; j++) {
      sum[i] = vector[j] * matrix.matrix[i][j];
    }
    vector = sum;
  }
}
