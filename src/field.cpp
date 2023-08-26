#include "field.hpp"

std::vector<std::shared_ptr<Object> > &Field::GetObjects() { return objects_; }

const std::vector<std::shared_ptr<Object> > &Field::GetObjects() const {
  return objects_;
}

int Field::GetRange() const { return map_range_; }
