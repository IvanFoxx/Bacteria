#include "simulation.hpp"

const float radius = 10;

Simulation::Simulation() {}

void Simulation::PushBactery(std::shared_ptr<Bacterium> b) {
  assert(b.get() != nullptr);
  b->PlaceRandomly();
  field_.GetBacterium().push_back(b);
}

void Simulation::PushFood(const Food &bacterium) {
  std::shared_ptr<Food> b(new Food(bacterium));
  field_.GetEats().push_back(b);
}

void Simulation::Run(float delta_time) {
  for (auto &bactery : field_.GetBacterium()) bactery->Play(delta_time);
  auto it =
      std::partition(field_.GetBacterium().begin(), field_.GetBacterium().end(),
                     [](const auto &b) { return b->GetEnergy() >= 0; });

  // std::copy(it, field_.GetBacterium().end(), std::back_inserter(dead_));

  for (auto i = it; i != field_.GetBacterium().end(); ++i) {
    assert(*it != nullptr);
    dead_.push_back(*i);
  }

  field_.GetBacterium().erase(it, field_.GetBacterium().end());

  for (auto b : field_.GetBacterium()) {
    for (auto e : field_.GetEats()) {
      if (abs(b->GetX() - e->GetX()) < radius &&
          abs(b->GetY() - e->GetY()) < radius) {
        e->SetAlive(false);
        b->PushEnergy(100);
      }
    }
  }

  auto ite = std::remove_if(field_.GetEats().begin(), field_.GetEats().end(),
                            [](auto b) { return b->GetAlive() == false; });
  field_.GetEats().erase(ite, field_.GetEats().end());

  from_last_food_spawn_ += delta_time;

  if (from_last_food_spawn_ > 2) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
    from_last_food_spawn_ = 0;
  }
  if (field_.GetBacterium().empty()) InitNewGeneration();
}

void Simulation::InitRandomly() {
  for (size_t i = 0; i < 100; i++) {
    auto b = Bacterium(GetField());
    b.RandomGen();
    PushBactery(std::shared_ptr<Bacterium>(new Bacterium(b)));
  }
  for (size_t i = 0; i < 100; i++) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
  }
}

void Simulation::InitNewGeneration() {
  field_.GetBacterium().clear();
  field_.GetEats().clear();

  // for (auto dead : dead_) PushBactery(dead);
  dead_.erase(dead_.begin() + 10, dead_.end());
  for (size_t i = 0; i < 10; ++i)
    for (size_t j = 0; j < 10; ++j) PushBactery(dead_[i]);

  for (size_t i = 0; i < 100; i++) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
  }

  for (auto &elem : field_.GetBacterium()) elem->Mutation();
  dead_.clear();

  assert(dead_.size() == 0);
  assert(field_.bacteria_.size() == 100);
}

const Field &Simulation::GetField() const { return field_; }
