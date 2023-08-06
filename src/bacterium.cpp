#include "bacterium.hpp"

Bacterium::Bacterium(const Field &field)
    : field_(field), network_({2, 12, 16, 2}) {}

float Bacterium::GetX() const { return x_; }

float Bacterium::GetY() const { return y_; }

float Bacterium::GetEnergy() const { return energy_; }

void Bacterium::PushEnergy(float energy) {
  energy_ += energy;
  energy_ = std::min<float>(energy_, 150);
}

void Bacterium::Play(float delta_time) {
  Eigen::VectorXf input(2);
  // input(0) = energy_;
  input(0) = x_ / field_.GetRange();
  input(1) = y_ / field_.GetRange();

  auto output = network_.Calculate(input);
  auto speed_x = 100 * output(0) * delta_time;
  auto speed_y = 100 * output(1) * delta_time;

  x_ += speed_x;
  y_ += speed_y;

  x_ = std::min<float>(x_, field_.GetRange());
  y_ = std::min<float>(y_, field_.GetRange());

  x_ = std::max<float>(x_, -field_.GetRange());
  y_ = std::max<float>(y_, -field_.GetRange());

  energy_ -= 5 * delta_time;
  // energy_ = std::min<float>(energy_, 1000);
  energy_ = std::max<float>(energy_, 0);
}

void Bacterium::PlaceRandomly() {
  x_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  y_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  x_ /= 1.1;
  y_ /= 1.1;
  energy_ = 100;
}

void Bacterium::Mutation() { network_.GenerateMutation(); }

void Bacterium::RandomGen() { network_.GenerateRandomly(); }
