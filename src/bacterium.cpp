#include "bacterium.hpp"

#include "food.hpp"

// Bacterium::Bacterium(const Field &field, std::vector<int> network)
//     : field_(field), network_(network) {}

Bacterium::Bacterium(const Field &field, std::vector<int> network, int fpos,
                     bool hebr, sf::Color color)
    : field_(field), network_(network) {
  fpos_ = fpos;
  hebr_ = hebr;
  color_ = color;
}

float Bacterium::GetX() const { return x_; }

float Bacterium::GetY() const { return y_; }

int Bacterium::GetEaten() const { return eaten_; }

sf::Color Bacterium::GetColor() const { return color_; }

int Bacterium::GetFoodPos() const { return fpos_; }

bool Bacterium::IsHebr() const { return hebr_; }

float Bacterium::GetEnergy() const { return energy_; }

void Bacterium::PushEnergy(float energy) {
  energy_ += energy;
  energy_ = std::min<float>(energy_, 210);
  eaten_++;
}

const Field &Bacterium::GetField() const { return field_; }

Network Bacterium::GetNetwork() const { return network_; }

Eigen::VectorXf Bacterium::GetInput() {
  Eigen::VectorXf input(6);
  // input(0) = energy_;
  // input(0) = x_ / field_.GetRange();
  // input(1) = y_ / field_.GetRange();
  float mind = std::numeric_limits<float>::max();
  if (field_.GetEats().size() != 0) {
    std::shared_ptr<Food> cFood;
    for (auto food : field_.GetEats()) {
      float d = sqrt(pow(x_ - food->GetX(), 2) + pow(y_ - food->GetY(), 2));
      if (d < mind) {
        mind = d;
        cFood = food;
      }
    }
    float size = field_.GetRange();
    input(0) = (cFood->GetX() - x_) / (mind + 0.001);
    input(1) = (cFood->GetY() - y_) / (mind + 0.001);
  } else {
    input(0) = 0;
    input(1) = 0;
  }

  mind = std::numeric_limits<float>::max();
  input(2) = 0;
  input(3) = 0;
  if (field_.GetBacterium().size() != 0) {
    std::shared_ptr<Bacterium> cBFood;
    for (auto bfood : field_.GetBacterium()) {
      if (bfood->GetFoodPos() < fpos_) {
        float d = sqrt(pow(x_ - bfood->GetX(), 2) + pow(y_ - bfood->GetY(), 2));
        if (d < mind) {
          mind = d;
          cBFood = bfood;
        }
      }
    }
    if (cBFood) {
      input(2) = (cBFood->GetX() - x_) / (mind + 0.001);
      input(3) = (cBFood->GetY() - y_) / (mind + 0.001);
    }
  }

  mind = std::numeric_limits<float>::max();
  input(4) = 0;
  input(5) = 0;
  if (field_.GetBacterium().size() != 0) {
    std::shared_ptr<Bacterium> cEnemy;
    for (auto enemy : field_.GetBacterium()) {
      if (enemy->GetFoodPos() > fpos_) {
        float d = sqrt(pow(x_ - enemy->GetX(), 2) + pow(y_ - enemy->GetY(), 2));
        if (d < mind) {
          mind = d;
          cEnemy = enemy;
        }
      }
    }
    if (cEnemy) {
      input(4) = (cEnemy->GetX() - x_) / (mind + 0.001);
      input(5) = (cEnemy->GetY() - y_) / (mind + 0.001);
    }
  }
  return input;
}

void Bacterium::Play(float delta_time) {
  Eigen::VectorXf input = GetInput();
  auto output = network_.Calculate(input);
  auto speed_x = 100 * output(0) * delta_time;
  auto speed_y = 100 * output(1) * delta_time;

  x_ += speed_x;
  y_ += speed_y;

  x_ = std::min<float>(x_, field_.GetRange());
  y_ = std::min<float>(y_, field_.GetRange());

  x_ = std::max<float>(x_, -field_.GetRange());
  y_ = std::max<float>(y_, -field_.GetRange());

  energy_ -= 5 * delta_time;
  // energy_ = std::min<float>(energy_, 1000);
  energy_ = std::max<float>(energy_, 0);
}

void Bacterium::PlaceRandomly() {
  x_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  y_ = rand() % (2 * field_.GetRange()) - field_.GetRange();
  x_ /= 1.1;
  y_ /= 1.1;
  energy_ = 100;
}

void Bacterium::Mutation() { network_.GenerateMutation(); }

void Bacterium::RandomGen() { network_.GenerateRandomly(); }

void Bacterium::Double() {}
