#include "network.hpp"

#include <cmath>

Network::Network(std::vector<int> layers_sizes) : layers_size_(layers_sizes) {
  matrixes_.resize(layers_size_.size());
  offsets_.resize(layers_size_.size());
  for (size_t i = 0; i < layers_sizes.size() - 1; i++) {
    matrixes_[i] = Eigen::MatrixXf(layers_sizes[i + 1], layers_sizes[i]);
    offsets_[i] = Eigen::VectorXf(layers_sizes[i + 1]);
  }
}

Eigen::VectorXf Network::Calculate(Eigen::VectorXf input) const {
  assert(input.size() == layers_size_.front());

  /*
  for (int i = 0; i < input.size(); i++) input(i) = std::tanh(input(i));
*/

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

void Network::GenerateRandomly() {
  for (size_t i = 0; i < matrixes_.size() - 1; i++)
    for (int y = 0; y < matrixes_[i].rows(); y++)
      for (int x = 0; x < matrixes_[i].cols(); x++)
        matrixes_[i](y, x) = ((rand() % 2000) - 1000) / 1000.0;

  for (size_t i = 0; i < offsets_.size() - 1; i++)
    for (int y = 0; y < offsets_[i].size(); y++)
      offsets_[i](y) = ((rand() % 2000) - 1000) / 1000.0;
}

void Network::GenerateMutation() {
  for (size_t i = 0; i < 2; i++) {
    auto delta = ((rand() % 2000) - 1000) / 5000.0;
    auto id = rand() % (matrixes_.size() - 1);
    auto y = rand() % matrixes_[id].rows();
    auto x = rand() % matrixes_[id].cols();

    matrixes_[id](y, x) += delta;
  }

  for (size_t i = 0; i < 1; i++) {
    auto delta = ((rand() % 2000) - 1000) / 5000.0;
    auto id = rand() % (offsets_.size() - 1);
    auto y = rand() % matrixes_[id].rows();
    offsets_[id](y) += delta;
  }
}
