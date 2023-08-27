#include "food.hpp"

Food::Food(const Field &field) : Object(field, false, true) {}

Food::~Food() {}

void Food::Collision(std::shared_ptr<Object> with) { SetAlive(false); }

void Food::Tick(float delta) {}
