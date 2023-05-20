//
//  plane.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 30.04.23.
//

#include "plane.hpp"

plane::plane(){

}

void plane::draw_plane()
{
    // plane bottom
    glVertex3f(-5.5f, -0.2f, -3.0f);
    glVertex3f(-2.5f, 0.0f, -3.0f);
    glVertex3f(-2.5f, 0.0f, 3.0f);
    glVertex3f(-5.5f, -0.2f, 3.0f);
    
    // plane diagonal
    glVertex3f(-2.5f, 0.0f, -3.0);
    glVertex3f(2.5f, 3.0f, -3.0f);
    glVertex3f(2.5f, 3.0f, 3.0f);
    glVertex3f(-2.5f, 0.0f, 3.0);
    
    // plane top
    glVertex3f(2.5f, 3.0f, -3.0f);
    glVertex3f(4.0f, 3.2f, -3.0f);
    glVertex3f(4.0f, 3.2f, 3.0f);
    glVertex3f(2.5f, 3.0f, 3.0f);

}

bool plane::plane_hit(const point3& position, point3& hit_normal) {

    // Define the plane vertices
    point3 bottom_v1(-5.5f, -0.2f, -3.0f);
    point3 bottom_v2(-2.5f, 0.0f, -3.0f);
    point3 bottom_v3(-2.5f, 0.0f, 3.0f);
    point3 bottom_v4(-5.5f, -0.2f, 3.0f);

    point3 top_v1(3.5f, 3.0f, -3.0f);
    point3 top_v2(5.0f, 3.2f, -3.0f);
    point3 top_v3(5.0f, 3.2f, 3.0f);
    point3 top_v4(3.5f, 3.0f, 3.0f);

    point3 diag_v1(-2.5f, 0.0f, -3.0f);
    point3 diag_v2(2.5f, 3.0f, -3.0f);
    point3 diag_v3(2.5f, 3.0f, 3.0f);
    point3 diag_v4(-2.5f, 0.0f, 3.0f);

    // Compute the plane normals
    point3 bottom_normal = cross(bottom_v2 - bottom_v1, bottom_v3 - bottom_v1);
    bottom_normal.normalize();

    point3 top_normal = cross(top_v2 - top_v1, top_v3 - top_v1);
    top_normal.normalize();

    point3 diag_normal = cross(diag_v2 - diag_v1, diag_v3 - diag_v1);
    diag_normal.normalize();

    if(std::abs(dot(position - bottom_v1, bottom_normal)) <= 0.25f){
        if (position.y() < bottom_v2.y()) {
            hit_normal = bottom_normal;
            return true;
        }
    }
    if(std::abs(dot(position - top_v1, top_normal)) <= 0.25f){
        if (position.y() > 3.1) {
            hit_normal = top_normal;
            return true;
        }
    }
    if(std::abs(dot(position - diag_v1, diag_normal)) <= 0.25f){
        if (position.y() < diag_v2.y()) {
            hit_normal = diag_normal;
        }
        return true;
    }

    hit_normal = point3(0, 0, 0);
    return false;
}






