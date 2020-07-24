#ifndef INCLUDED_particle_hpp
#define INCLUDED_particle_hpp
#include "vector2.hpp"
//ゼリーを構成する粒子のクラス
class particle {
 private:
  //位置
  vector2 pos_;
  //速度
  vector2 vel_ = vector2(0, 0);
  //加速度
  vector2 acc_ = vector2(0, 0);

 public:
  particle(){};
  //速度に基づいてdt時間の分位置を更新する
  void update_position(const double dt);
  //粒子の位置を設定する
  void set_position(const vector2 pos);
  //加速度に基づいてdt時間の分速度を更新する
  void update_velocity(const double dt);
  //粒子の速度を設定する
  void set_velocity(const vector2 vel);
  //粒子の加速度を設定する
  void set_acceleration(const vector2 acc);
  //粒子の加速度をaccだけ加える
  void add_acceleration(const vector2 acc);
  //位置を得る
  vector2 get_position() const;
  //速度を得る
  vector2 get_velocity() const;
};

#endif
