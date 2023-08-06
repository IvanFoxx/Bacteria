#include "simulation.hpp"

Simulation::Simulation() {}

void Simulation::PushBactery(const Bacterium &bacterium) {
  std::shared_ptr<Bacterium> b(new Bacterium(bacterium));
  field_.GetBacterium().push_back(b);
}

void Simulation::PushFood(const Food &bacterium) {
  std::shared_ptr<Food> b(new Food(bacterium));
  field_.GetEats().push_back(b);
}

void Simulation::Run(float delta_time) {
  for (auto &bactery : field_.GetBacterium()) bactery->Play(delta_time);
  auto it =
      std::remove_if(field_.GetBacterium().begin(), field_.GetBacterium().end(),
                     [](auto b) { return b->GetEnergy() <= 0; });

  for (auto i = it; i != field_.GetBacterium().end(); ++i) dead_.push_back(*it);

  field_.GetBacterium().erase(it, field_.GetBacterium().end());
}

void Simulation::InitRandomly() {
  for (size_t i = 0; i < 100; i++) {
    auto b = Bacterium(GetField());
    b.PlaceRandomly();
    PushBactery(b);
  }
  for (size_t i = 0; i < 100; i++) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
  }
}

const Field &Simulation::GetField() const { return field_; }
