#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "field.hpp"

class Simulation {
 public:
  Simulation();

  const Field& GetField() const;
  void SetField(const Field& field);

  void Start(float delta);
  void Stop();

  int Generation();

 private:
  int generation_counter = 0;
  Field field_;
  std::vector<std::shared_ptr<Object>> dead_;
};

#endif
