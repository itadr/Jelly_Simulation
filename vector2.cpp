#include "vector2.hpp"

#include <cmath>
#include <iostream>

vector2::vector2(const double x, const double y) {
  x_ = x;
  y_ = y;
}
void vector2::set(const double x, const double y) {
  x_ = x;
  y_ = y;
}
double vector2::square() const { return x_ * x_ + y_ * y_; }
double vector2::abs() const { return sqrt(x_ * x_ + y_ * y_); }
//内積
double vector2::inner_product(const vector2 &v) const {
  return x_ * v.x_ + y_ * v.y_;
}
vector2 vector2::operator+(const vector2 &v) const {
  return vector2(x_ + v.x_, y_ + v.y_);
}
vector2 vector2::operator-(const vector2 &v) const {
  return vector2(x_ - v.x_, y_ - v.y_);
}
vector2 vector2::operator*(const double r) const {
  return vector2(r * x_, r * y_);
}
vector2 vector2::operator/(const double r) const {
  if (r == 0) {
    std::cerr << "zero division" << std::endl;
    exit(true);
  }
  return vector2(x_ / r, y_ / r);
}
