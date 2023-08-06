#include "bacterium.hpp"

Bacterium::Bacterium(const Field &field)
    : field_(field), network_({10, 8, 8, 2}) {}

float Bacterium::GetX() const { return x_; }

float Bacterium::GetY() const { return y_; }

float Bacterium::GetEnergy() const { return energy_; }

void Bacterium::PushEnergy(float energy) { energy_ += energy; }

void Bacterium::Play(float delta_time) {
  Eigen::VectorXf input(10);
  input(0) = energy_;
  input(1) = x_;
  input(2) = y_;

  auto output = network_.Calculate(input);
  auto speed_x = 5 * output(0);
  auto speed_y = 5 * output(1);

  x_ += speed_x;
  y_ += speed_y;

  x_ = std::min<float>(x_, field_.GetRange());
  y_ = std::min<float>(y_, field_.GetRange());

  x_ = std::max<float>(x_, -field_.GetRange());
  y_ = std::max<float>(y_, -field_.GetRange());

  energy_ -= 5 * delta_time;
}

void Bacterium::PlaceRandomly() {
  x_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  y_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  x_ /= 1.1;
  y_ /= 1.1;
  energy_ = rand() % 60 + 40;
}

void Bacterium::Mutation() { network_.GenerateMutation(); }

void Bacterium::RandomGen() { network_.GenerateRandomly(); }
