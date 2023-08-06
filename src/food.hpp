#ifndef FOOD_HPP
#define FOOD_HPP

#include "field.hpp"

class Food {
 public:
  Food(const Field &field);

  float GetX() const;
  float GetY() const;

  void PlaceRandomly();

 private:
  float x_, y_;
  const Field &field_;
};

#endif
