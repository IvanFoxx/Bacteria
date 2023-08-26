#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "bacterium.hpp"
#include "field.hpp"
#include "food.hpp"

class Simulation {
 public:
  Simulation();

  // void PushBactery(Bacterium b);
  // void PushFood(const Food& bacterium);

  // void Run(float delta_time);
  // void InitRandomly();
  // void InitNewGeneration();

  const Field& GetField() const;
  void SetField(const Field& field);

  void Start(float delta);
  void Stop();

  int Generation();

 private:
  // float from_last_food_spawn_ = 0;
  // float from_epoch_start = 0;
  Field field_;
  // std::vector<std::shared_ptr<Bacterium>> dead_;
};

#endif
