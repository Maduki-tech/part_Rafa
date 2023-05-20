//
//  main.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 26.04.23.
//
#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>

#include "orbitcontroller.hpp"
#include "particle.hpp"
#include "plane.hpp"

using namespace std;

static vector<particle> array_parts;
orbitcontroller OrbitController;

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(45, 1.0, 1.0, 100.0); // Set up a perspective projection
    // matrix gluLookAt(0.0, 0.0, 20.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0); // Set
    // the camera position and orientation
    gluPerspective(30, 1.0, 0.5,
                   40.0); // Set up a perspective projection matrix
    OrbitController.updateCamera();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPointSize(3);
    for (int i = 0; i < 1; i++) {
        particle part(random_point(), point3(0.0f, 0.0f, 0.0f), 1.0f,
                      point3(0.0f, 0.0f, 0.0f));
        array_parts.push_back(part);
    }

    glBegin(GL_POINTS);

    for (int i = 0; i < array_parts.size(); i++) {
        for (int j = i + 1; j < array_parts.size(); j++) {
            if (array_parts[i].intersects(array_parts[j])) {
                // Calculate the direction of the force
                point3 dir = array_parts[i].x_ - array_parts[j].x_;
                dir.normalize();

                // Change their velocities
                array_parts[i].v_ = array_parts[i].v_ - dir;
                array_parts[j].v_ = array_parts[j].v_ + dir;
            }
        }

        // glColor3f(random_double(), random_double(), random_double());
        glColor3f(0.3f, 0.7f, 1.0f);

        std::vector<point3> s_alt = array_parts[i].get_State();
        point3 s_altx = s_alt[0];

        if (s_altx.x() < -7.0) {
            array_parts.erase(array_parts.begin() + i);
        }

        point3 s_altv = s_alt[1];
        point3 deriv_v = array_parts[i].derivEval()[0];
        point3 deriv_de = array_parts[i].derivEval()[1];
        point3 s_newx = s_altx + 0.01 * deriv_v;
        point3 s_newv = s_altv + 0.01 * deriv_de;

        array_parts[i].set_State(s_newx, s_newv);
        array_parts[i].draw_part();
    }

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.8f, 1.0f);

    plane planes;
    planes.draw_plane();

    glEnd();

    glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {
    OrbitController.mouseButton(button, state, x, y);
}

void mouseMotion(int x, int y) { OrbitController.mouseMotion(x, y); }

void keyboard(unsigned char key, int x, int y) {
    OrbitController.keyboard(key);
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Partikelsystem");

    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutSetKeyRepeat(false);
    glutIdleFunc(display);

    glutMainLoop();
}
