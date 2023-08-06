#include "bacterium.hpp"

Bacterium::Bacterium(const Field &field) : field_(field) {}

float Bacterium::GetX() const { return x_; }

float Bacterium::GetY() const { return y_; }

float Bacterium::GetEnergy() const { return energy_; }

void Bacterium::PushEnergy(float energy) { energy_ += energy; }

void Bacterium::Play(float delta_time) {
  //  x_ += (rand() % 101 - 50) * delta_time;
  //  y_ += (rand() % 101 - 50) * delta_time;

  auto angle = (rand() % 360) / 360.0 * 2 * 3.14;
  auto speed = 100.0;

  x_ += speed * sin(angle) * delta_time;
  y_ += speed * cos(angle) * delta_time;

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
