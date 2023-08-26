#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>

#include "lmath.hpp"

class Network {
 public:
  Network(std::vector<int> layers_sizes);
  Network(const Network& other) = default;

  Eigen::VectorXf Calculate(Eigen::VectorXf input) const;

  void GenerateRandomly();
  void GenerateMutation();

 private:
  std::vector<int> layers_size_;
  std::vector<Eigen::MatrixXf> matrixes_;
  std::vector<Eigen::VectorXf> offsets_;
  int mrate, mrate2;
};

#endif
