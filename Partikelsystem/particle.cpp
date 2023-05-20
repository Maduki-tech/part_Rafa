//
//  particle.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 26.04.23.
//

#include "particle.hpp"

particle::particle(){}

particle::particle(point3 x, point3 v, float m, point3 f) : x_(x), v_(v), m_(m), f_(f) {};

void particle::draw_part(){
    glVertex3f(x_.x(), x_.y(), x_.z());
}

std::vector<point3> particle::get_State(){
    std::vector<point3> state;
    state.push_back(x_);
    state.push_back(v_);
    
    return state;
}

std::vector<point3> particle::derivEval(){
    std::vector<point3> derivation;
    
    f_ *= 0.0f;
    f_[1] += m_ * (-9.81f);
     
    derivation.push_back(v_);
    derivation.push_back(f_ / m_);
    
    return derivation;
}


void particle::set_State(point3 new_x, point3 new_v) {
    x_ = new_x;
    v_ = new_v;
    
    // Check for collision with the ground
    point3 hit_normal;
    if (Plane.plane_hit(x_, hit_normal)) {
        // Compute the reflection direction
        point3 reflection_dir = reflect(v_, hit_normal);

        // Coefficient of restitution
        float restitution = 1.0f;
        reflection_dir *= restitution;

        // Update the velocity with the reflection direction
        v_ = reflection_dir;
    }
    else {
       // Update the position using the velocity and the time step
       x_ = x_ + v_ * 0.001;
    }
}

