#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include <memory>
#include <vector>

#include "network.hpp"
#include "object.hpp"

class Bacterium : public Object {
 public:
  Bacterium(const Field &field, const Network &net);
  virtual ~Bacterium();

  Network GetNetwork();
  void SetNetwork(const Network &);

  virtual void Collision(std::shared_ptr<Object> with);
  virtual void Tick(float delta);

 private:
  float energy_ = 100;
  Network network_;
};

#endif
