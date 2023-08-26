#include "simulation.hpp"

#include <algorithm>
#include <array>
#include <iostream>

Simulation::Simulation() {}

void Simulation::SetCore(std::shared_ptr<Core> core) { core_ = core; }

void Simulation::ReStart() { field_.GetObjects() = core_->FirstGeneration(); }

void Simulation::Start(float delta_time) {
  /*
  // for (auto &bactery : field_.GetObjects()) bactery->Play(delta_time);
  auto it =
      std::partition(field_.GetBacterium().begin(), field_.GetBacterium().end(),
                     [](const auto &b) { return b->GetEnergy() > 0; });

  for (auto i = it; i != field_.GetBacterium().end(); ++i) {
    assert(*it != nullptr);
    dead_.push_back(*i);
  }

  field_.GetBacterium().erase(it, field_.GetBacterium().end());

  for (auto b : field_.GetBacterium()) {
    for (auto e : field_.GetEats()) {
      if (abs(b->GetX() - e->GetX()) < radius &&
          abs(b->GetY() - e->GetY()) < radius && e->GetAlive()) {
        e->SetAlive(false);
        b->PushEnergy(50);
        b->Eat();
      }
    }
  }

  auto ite = std::remove_if(field_.GetEats().begin(), field_.GetEats().end(),
                            [](auto b) { return b->GetAlive() == false; });
  field_.GetEats().erase(ite, field_.GetEats().end());

  // if (from_last_food_spawn_ > 2) {
  //  auto f = Food(GetField());
  //  f.PlaceRandomly();
  //  PushFood(f);
  // from_last_food_spawn_ = 0;
  // }
  if (field_.GetBacterium().empty()) InitNewGeneration();
*/
}

const Field &Simulation::GetField() const { return field_; }

void Simulation::SetField(const Field &field) { field_ = field; }

void Simulation::Stop() {}

int Simulation::GetGeneration() const { return generation_; }
