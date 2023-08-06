#include "food.hpp"

Food::Food(const Field &field) : field_(field) {}

float Food::GetX() const { return x_; }

float Food::GetY() const { return y_; }

bool Food::GetAlive() const { return alive_; }

void Food::SetAlive(bool alive) { alive_ = alive; }

void Food::PlaceRandomly() {
  x_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  y_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  x_ /= 1.1;
  y_ /= 1.1;
}
