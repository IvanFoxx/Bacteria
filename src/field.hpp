#ifndef FIELD_HPP
#define FIELD_HPP

#include <memory>
#include <vector>

class Object;

class Field {
  friend class Simulation;

 public:
  std::vector<std::shared_ptr<Object>> &GetObjects();

  const std::vector<std::shared_ptr<Object>> &GetObjects() const;

  int GetRange() const;

 private:
  int map_range_ = 1000;
  std::vector<std::shared_ptr<Object>> objects_;
};

#endif
