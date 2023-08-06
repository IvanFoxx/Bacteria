#ifndef FOOD_HPP
#define FOOD_HPP

class Food {
 public:
  Food(float x, float y);

  float GetX() const;
  float GetY() const;

 private:
  float x_, y_;
};

#endif
