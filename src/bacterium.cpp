#include "bacterium.hpp"

Bacterium::Bacterium(const Field &field, const Network &net)
    : Object(field, true, true), network_(net) {}

Bacterium::~Bacterium() {}

Network Bacterium::GetNetwork() { return network_; }

void Bacterium::SetNetwork(const Network &net) { network_ = net; }

void Bacterium::Collision(std::shared_ptr<Object> with) {}

void Bacterium::Tick(float delta) {
  /*
   Eigen::VectorXf input(2);
   input(0) = energy_;
   input(0) = x_ / field_.GetRange();
    input(1) = y_ / field_.GetRange();
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

  auto output = network_.Calculate(input);
  auto speed_x = 100 * output(0) * delta_time;
  auto speed_y = 100 * output(1) * delta_time;

  x_ += speed_x;
  y_ += speed_y;
  */

  SetX(std::min<float>(GetX(), GetField().GetRange()));
  SetY(std::min<float>(GetY(), GetField().GetRange()));

  SetX(std::max<float>(GetX(), -GetField().GetRange()));
  SetY(std::max<float>(GetY(), -GetField().GetRange()));

  energy_ -= 5 * delta;
  energy_ = std::max<float>(energy_, 0);
  if (energy_ == 0) SetAlive(false);
}
