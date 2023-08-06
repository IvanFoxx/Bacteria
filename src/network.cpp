#include "network.hpp"

#include <cmath>

Network::Network(int layers, std::vector<int> layers_d) {
  srand(time(NULL));
  Layer_Count = layers;
  Layers_Dim = layers_d;
  for (int i = 0; i < layers - 1; i++) {
    network[i] = Eigen::MatrixXf(layers_d[i], layers_d[i + 1]);
    offset[i] = Eigen::VectorXf(layers_d[i + 1]);
  }
}

Network::Network(const Network &other) {
  Layer_Count = other.Layer_Count;
  Layers_Dim = other.Layers_Dim;
  network = other.network;
  offset = other.offset;
}

Eigen::VectorXf Network::execute(Eigen::VectorXf input) {
  Eigen::VectorXf output = input;
  for (int layer = 0; layer < Layer_Count - 1; layer++) {
    output = network[layer] * output + offset[layer];
    for (int i = 0; i < Layers_Dim[layer + 1]; i++) {
      output(i) = std::tanh(output(i));
    }
  }
  return output;
}
