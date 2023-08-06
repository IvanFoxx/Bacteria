#include "food.hpp"

Food::Food(float x, float y) : x_(x), y_(y) {}

float Food::GetX() const { return x_; }

float Food::GetY() const { return y_; }
