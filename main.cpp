#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "jelly.hpp"
#include "vector2.hpp"

void collision_particle(particle& pi, particle& pj,
                        const double collision_dist_sq,
                        const double collision_dist,
                        const double collision_coeff) {
  const vector2 pi_pos = pi.get_position();
  const vector2 pj_pos = pj.get_position();
  const vector2 relative_pos = pi_pos - pj_pos;
  const double dist_sq = relative_pos.square();
  if (dist_sq < collision_dist_sq) {
    const double dist = std::sqrt(dist_sq);
    const vector2 pi_vel = pi.get_velocity();
    const vector2 pj_vel = pj.get_velocity();
    const vector2 relative_vel = pi_vel - pj_vel;
    if (dist == 0) {
      std::cerr << "dist==0" << std::endl;
      std::exit(true);
    }
    const vector2 unit_relative_pos = relative_pos / dist;
    const double collision_vel = unit_relative_pos.inner_product(relative_vel);
    if (collision_vel < 0) {
      const vector2 update_vel =
          unit_relative_pos * collision_vel * (1 + collision_coeff);
      pi.set_velocity(pi_vel - update_vel);
      pj.set_velocity(pj_vel + update_vel);
    }
  }
}
bool collision_jelly(jelly& j1, jelly& j2, const double collision_dist_sq,
                     const double collision_dist,
                     const double collision_coeff) {
  for (auto& itr1 : j1.particle_) {
    for (auto& itr2 : j2.particle_) {
      collision_particle(itr1, itr2, collision_dist_sq, collision_dist,
                         collision_coeff);
    }
  }
}

void print_csv(const int time_step, std::vector<jelly>& j) {
  std::ofstream ofs("jelly" + std::to_string(time_step) + ".csv");
  if (!ofs) {
    std::cout << "file open failed" << std::endl;
    exit(true);
  }
  ofs << "x,y" << std::endl;
  for (auto& j_itr : j) {
    for (auto& itr : j_itr.particle_) {
      const vector2 pos = itr.get_position();
      ofs << pos.x_ << "," << pos.y_ << std::endl;
    }
  }

  ofs.close();
}

int main() {
  const double dt = 0.001;
  const double collision_coeff = 0.3;
  const double damper_coeff = 2;
  const double spring_coeff = 300;
  const double spring_length = 1.5;
  const vector2 corner1 = vector2(0.0, 1.0);
  const vector2 corner2 = vector2(1.0, 3.0);
  const vector2 v1 = vector2(0.1, 0);
  const vector2 v2 = vector2(0, 0.1);
  const vector2 g = vector2(0, -2);
  const int side_number1 = 15;
  const int side_number2 = 10;
  const int interval = 10;
  const int end_time = 25000;
  const double collision_dist_sq = v1.square();
  const double collision_dist = std::sqrt(collision_dist);
  std::vector<jelly> j(2);
  j[0] = jelly(corner1, v1, v2, side_number1, side_number2),
  j[1] = jelly(corner2, v2, v1, side_number1, side_number2);
  for (int i = 0; i < 2; i++) {
    j[i].construct_spring(spring_length);
  }
  int time_step = 0;
  while (time_step < end_time) {
    for (int i = 0; i < 2; i++) {
      j[i].simulation_update(g, damper_coeff, spring_coeff, dt,
                             collision_coeff);
    }
    collision_jelly(j[0], j[1], collision_dist_sq, collision_dist,
                    collision_coeff);
    if (time_step % interval == 0) {
      print_csv(time_step / interval, j);
      std::cout << "time=" << time_step / interval << std::endl;
    }
    time_step++;
  }
  return 0;
}
