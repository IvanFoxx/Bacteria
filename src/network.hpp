#pragma once
#include <vector>

#include "lmath.hpp"

class Network {
 public:
  int Layer_Count;
  std::vector<int> Layers_Dim;
  std::vector<Eigen::MatrixXf> network;
  std::vector<Eigen::VectorXf> offset;

  Network(int layers, std::vector<int> layers_d);
  Network(const Network& other);

  Eigen::VectorXf execute(Eigen::VectorXf input);
};
