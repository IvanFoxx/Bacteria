#ifndef FOOD_HPP
#define FOOD_HPP

#include "field.hpp"
#include "object.hpp"

class Food : public Object {
 public:
  Food(const Field &field);
};

#endif
