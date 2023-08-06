#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include <memory>
#include <vector>

#include "field.hpp"
#include "network.hpp"

class Bacterium {
 public:
  Bacterium(const Field &field);

  float GetX() const;
  float GetY() const;
  float GetEnergy() const;

  void Play(float delta_time);
  void PlaceRandomly();

 private:
  const Field &field_;
  float x_, y_;
  float energy_;
  Network network_ = Network(3, {5, 10, 2});
};

#endif
