#ifndef INCLUDED_spring_hpp
#define INCLUDED_spring_hpp
#include "particle.hpp"

class spring {
 private:
  // ばねが結ぶ2つの粒子の参照
  particle &pi_, &pj_;
  // ばねの自然長
  double initial_length_;

 public:
  // ばねの現在の長さを求める
  double length() const;
  // 2つの粒子の相対位置ベクトルを求める
  vector2 relative_position() const;
  spring(particle& pi, particle& pj);
  // ばねの力による加速
  void update_acceleration(const double damper_coeff,
                           const double spring_coeff);
};
#endif
