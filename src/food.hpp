#ifndef FOOD_HPP
#define FOOD_HPP

#include "field.hpp"
#include "object.hpp"

class Food : public Object {
 public:
  Food(const Field &field);
  ~Food();

  virtual void Collision(std::shared_ptr<Object> with);
  virtual void Tick(float delta);
};

#endif
