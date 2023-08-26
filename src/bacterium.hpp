#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include <memory>
#include <vector>

#include "network.hpp"
#include "object.hpp"

class Bacterium : Object {
 public:
  Bacterium(const Field &field, const Network &net);

  float GetEnergy() const;

  Network GetNetwork();
  void SetNetwork(const Network &);

  void Play(float delta_time);

 private:
  float energy_ = 100;
  Network network_;
};

#endif
