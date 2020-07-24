#include "particle.hpp"

#include "vector2.hpp"

void particle::update_position(const double dt) { pos_ = pos_ + vel_ * dt; }
void particle::set_position(const vector2 pos) { pos_ = pos; }
void particle::update_velocity(const double dt) { vel_ = vel_ + acc_ * dt; }
void particle::set_velocity(const vector2 vel) { vel_ = vel; }
void particle::set_acceleration(const vector2 acc) { acc_ = acc; }
void particle::add_acceleration(const vector2 acc) { acc_ = acc_ + acc; }
vector2 particle::get_position() const { return pos_; }
vector2 particle::get_velocity() const { return vel_; }
