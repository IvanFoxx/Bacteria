#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "field.hpp"
#include "network.hpp"

class Bacterium {
 public:
  Bacterium(const Field &field, std::vector<int> network, int fpos, bool hebr,
            sf::Color color);
  // Bacterium(const Bacterium &other);

  float GetX() const;
  float GetY() const;
  int GetEaten() const;
  sf::Color GetColor() const;
  int GetFoodPos() const;
  bool IsHebr() const;
  float GetEnergy() const;
  void PushEnergy(float energy);

  const Field &GetField() const;
  Network GetNetwork() const;

  Eigen::VectorXf virtual GetInput();
  void Play(float delta_time);
  void PlaceRandomly();
  void Mutation();
  void RandomGen();
  void Double();

 protected:
  const Field &field_;
  float x_, y_;
  float energy_ = 100;
  int eaten_;
  sf::Color color_;
  int fpos_;
  bool hebr_;
  Network network_;
};

#endif
