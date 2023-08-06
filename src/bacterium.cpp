#include "bacterium.hpp"

Bacterium::Bacterium(const Field &field) : field_(field) {}

float Bacterium::GetX() const { return x_; }

float Bacterium::GetY() const { return y_; }

float Bacterium::GetEnergy() const { return energy_; }

void Bacterium::Play(float delta_time) {
  x_ += (rand() % 101 - 50) * delta_time;
  y_ += (rand() % 101 - 50) * delta_time;

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
