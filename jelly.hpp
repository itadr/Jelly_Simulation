#ifndef INCLUDED_jelly_hpp
#define INCLUDED_jelly_hpp
#include <vector>

#include "particle.hpp"
#include "spring.hpp"
#include "vector2.hpp"

class jelly {
 public:
  int particle_number_;
  std::vector<particle> particle_;
  std::vector<spring> spring_;
  jelly() {}
  jelly(const vector2 corner, const vector2 v1, const vector2 v2,
        const int side_number1, const int side_number2);
  //距離がspring_length以下の粒子のペアに対してバネを構成する
  void construct_spring(const double spring_length);
  // 重力gだけ粒子を加速する
  void update_gravity(const vector2 g);
  // ダンパー係数をdamper_coeff,バネ係数をspring_coeffとしてバネとダンパーによる加速を行う
  void update_spring(const double damper_coeff, const double spring_coeff);
  // 速度を時間刻み幅dt更新する
  void update_velocity(const double dt);
  // 位置を時間刻み幅dt更新する
  void update_position(const double dt);
  // 床との衝突処理
  void collision_floor(const double collision_coeff);
  // シミュレーションを実行する
  void simulation_update(const vector2 g, const double damper_coeff,
                         const double spring_coeff, const double dt,
                         const double collision_coeff);
};

#endif
