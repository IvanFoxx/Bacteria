#include "network.hpp"

#include <cmath>

Network::Network(std::vector<int> layers_sizes) : layers_size_(layers_sizes) {
  for (size_t i = 0; i < layers_sizes.size() - 1; i++) {
    matrixes_[i] = Eigen::MatrixXf(layers_sizes[i], layers_sizes[i + 1]);
    offsets_[i] = Eigen::VectorXf(layers_sizes[i + 1]);
  }
}

Eigen::VectorXf Network::Calculate(Eigen::VectorXf input) const {
  assert(input.size() == layers_size_.front());

  Eigen::VectorXf output = input;
  for (size_t layer = 0; layer < layers_size_.size() - 1; layer++) {
    output = matrixes_[layer] * output;
    output += offsets_[layer];

    for (int i = 0; i < output.size(); i++) {
      output(i) = std::tanh(output(i));
    }
  }
  return output;
}

void Network::GenerateRandomly() {}

void Network::GenerateMutation() {}
