#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "field.hpp"

class Simulation {
 public:
  Simulation();

  void PushBactery();

  void Run();

  const Field& GetField() const;

 private:
  Field field_;
};

#endif
