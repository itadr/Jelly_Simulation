#include "spring.hpp"
#include<iostream>
#include "particle.hpp"
#include "vector2.hpp"

spring::spring(particle& pi, particle& pj) : pi_{pi}, pj_{pj} {
  const vector2 relative_pos = this->relative_position();
  initial_length_ = relative_pos.abs();
}

vector2 spring::relative_position() const {
  return pi_.get_position() - pj_.get_position();
}
double spring::length() const {
  const vector2 relative_pos = this->relative_position();
  return relative_pos.abs();
}

void spring::update_acceleration(const double damper_coeff,
                                 const double spring_coeff) {
  const vector2 relative_vel = pi_.get_velocity() - pj_.get_velocity();
  const double len = this->length();
  if(len==0){
	  std::cerr<<"len==0"<<std::endl;
	  std::exit(true);
  }
  const vector2 relative_pos = this->relative_position();
  const vector2 unit_relative_pos = relative_pos / len;
  const double extension = len - initial_length_;
  const vector2 force =
      unit_relative_pos *
      (damper_coeff * (relative_vel.inner_product(unit_relative_pos)) +
       spring_coeff * extension);
  pj_.add_acceleration(force);
  pi_.add_acceleration(force * -1);
}
