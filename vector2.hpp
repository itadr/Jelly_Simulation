#ifndef INCLUDED_vector2_hpp
#define INCLUDED_vector2_hpp

struct vector2 {
  double x_, y_;
  vector2() {}
  vector2(const double x, const double y);
  void set(const double x, const double y);
  double square() const;
  double abs() const;
  double inner_product(const vector2 &v) const;
  vector2 operator+(const vector2 &v) const;
  vector2 operator-(const vector2 &v) const;
  vector2 operator*(const double r) const;
  vector2 operator/(const double r) const;
};

#endif
