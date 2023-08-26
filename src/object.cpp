#include "object.hpp"

Object::Object(Field &field, bool primary, bool collider)
    : primary_(primary), collider_(collider), field_(field) {}

bool Object::GetAlive() const { return alive_; }

void Object::SetAlive(bool value) { alive_ = value; }

bool Object::IsPrimary() const { return primary_; }

bool Object::IsCollider() const { return collider_; }

float Object::GetX() const { return x_; }

float Object::GetY() const { return y_; }

float Object::GetRadius() const { return radius_; }

void Object::Collision(std::shared_ptr<Object> _) {}

void Object::PlaceOnField() {}

void Object::SetX(float value) { x_ = value; }

void Object::SetY(float value) { y_ = value; }

void Object::SetRadius(float value) { radius_ = value; }

void Object::Move(float x, float y) {
  x_ += x;
  y_ += y;
}
