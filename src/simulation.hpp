#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "field.hpp"

class Core {
 public:
  virtual std::vector<std::shared_ptr<Object>> FirstGeneration() const;
  virtual std::vector<std::shared_ptr<Object>> Step(
      std::vector<std::shared_ptr<Object>> last_gen) const;
};

class Simulation {
 public:
  Simulation();

  void SetCore(std::shared_ptr<Core> core);
  void ReStart();

  const Field& GetField() const;
  void SetField(const Field& field);

  void Start(float delta);
  void Stop();

  int GetGeneration() const;

 private:
  int generation_ = 0;
  Field field_;
  std::shared_ptr<Core> core_;
  std::vector<std::shared_ptr<Object>> dead_;
};

#endif
