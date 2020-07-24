#include "jelly.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include "particle.hpp"
#include "spring.hpp"
#include "vector2.hpp"

jelly::jelly(const vector2 corner, const vector2 v1, const vector2 v2,
             const int side_number1, const int side_number2) {
  particle_number_ = side_number1 * side_number2;
  particle_ = std::vector<particle>(particle_number_);
  for (int i = 0; i < side_number1; i++) {
    vector2 pos_tmp = corner + v1 * i;
    for (int j = 0; j < side_number2; j++) {
      pos_tmp = pos_tmp + v2;
      particle_[i * side_number2 + j].set_position(pos_tmp);
    }
  }
}
void jelly::construct_spring(const double spring_length) {
  const double spring_length_square = spring_length * spring_length;
  for (int i = 0; i < particle_number_; i++) {
    const vector2 pos_i = particle_[i].get_position();
    for (int j = i + 1; j < particle_number_; j++) {
      const vector2 pos_j = particle_[j].get_position();
      const vector2 relative_pos = pos_i - pos_j;
      const double length_square = relative_pos.square();
      if (length_square < spring_length_square) {
        spring_.push_back(spring(particle_[i], particle_[j]));
      }
    }
  }
}
void jelly::update_spring(const double damper_coeff,
                          const double spring_coeff) {
  for (auto& itr : spring_) {
    itr.update_acceleration(damper_coeff, spring_coeff);
  }
}
void jelly::update_gravity(const vector2 g) {
  for (auto& itr : particle_) {
    itr.set_acceleration(g);
  }
}
void jelly::update_velocity(const double dt) {
  for (auto& itr : particle_) {
    itr.update_velocity(dt);
  }
}
void jelly::update_position(const double dt) {
  for (auto& itr : particle_) {
    itr.update_position(dt);
  }
}
void jelly::collision_floor(const double collision_coeff) {
  for (auto& itr : particle_) {
    const vector2 pos = itr.get_position();
    if (pos.y_ < 0) {
      const vector2 new_position = vector2(pos.x_, 0);
      const vector2 vel = itr.get_velocity();
      const vector2 new_velocity =
          vector2(vel.x_ * collision_coeff, -vel.y_ * collision_coeff);
      itr.set_position(new_position);
      itr.set_velocity(new_velocity);
    }
  }
}

void jelly::simulation_update(const vector2 g, const double damper_coeff,
                            const double spring_coeff, const double dt,
                            const double collision_coeff) {
  update_gravity(g);
  update_spring(damper_coeff, spring_coeff);
  update_velocity(dt);
  update_position(dt);
  collision_floor(collision_coeff);
}
