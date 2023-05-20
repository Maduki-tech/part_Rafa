//
//  orbitcontroller.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 30.04.23.
//

#include "orbitcontroller.hpp"

float zoom = 1.0f; // Initial zoom level
float zoomStep = 1.0f; // The amount of zoom to apply on each step
float minZoom = 0.1f; // The minimum allowed zoom level
float maxZoom = 2.0f; // The maximum allowed zoom level
bool isZooming = false; // Track the zooming state

void orbitcontroller::mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
       if (state == GLUT_DOWN) {
           isDragging = true;
           mouseX = x;
           mouseY = y;
       } else {
           isDragging = false;
       }
   }
}

void orbitcontroller::mouseMotion(int x, int y) {
    if (isDragging) {
           float dx = (x - mouseX) * sensitivity;
           float dy = (y - mouseY) * sensitivity;

           float newAzimuth = azimuth - dx;
           float newElevation = elevation + dy;

           azimuth = newAzimuth;
           elevation = newElevation;

           mouseX = x;
           mouseY = y;

           updateCamera();
       }
}

void orbitcontroller::updateCamera() {
    float rElevation = elevation * M_PI / 180.0f;
    float rAzimuth = azimuth * M_PI / 180.0f;
    
    float x = cameraTarget.x() + distance * cos(rElevation) * sin(rAzimuth);
    float y = cameraTarget.y() + distance * sin(rElevation);
    float z = cameraTarget.z() + distance * cos(rElevation) * cos(rAzimuth);
    
    cameraPosition = point3(x, y, z);
    
    gluLookAt(
        cameraPosition.x(), cameraPosition.y(), cameraPosition.z(),
        cameraTarget.x(), cameraTarget.y(), cameraTarget.z(),
        0.0f, 1.0f, 0.0f
    );
}

void orbitcontroller::zoomIn() {

    float rElevation = elevation * M_PI / 180.0f;
    float rAzimuth = azimuth * M_PI / 180.0f;
    
    cameraTarget[0] = cameraTarget.x() - zoomStep * cos(rElevation) * sin(rAzimuth);
    cameraTarget[1] = cameraTarget.y() - zoomStep * sin(rElevation);
    cameraTarget[2] = cameraTarget.z() - zoomStep * cos(rElevation) * cos(rAzimuth);
//    cameraTarget[2] = cameraTarget[2] - zoomStep;
    gluLookAt(
        cameraPosition.x(), cameraPosition.y(), cameraPosition.z(),
        cameraTarget.x(), cameraTarget.y(), cameraTarget.z(),
        0.0f, 1.0f, 0.0f
    );
}

void orbitcontroller::zoomOut() {
    float rElevation = elevation * M_PI / 180.0f;
    float rAzimuth = azimuth * M_PI / 180.0f;
    
    cameraTarget[0] = cameraTarget.x() + zoomStep * cos(rElevation) * sin(rAzimuth);
    cameraTarget[1] = cameraTarget.y() + zoomStep * sin(rElevation);
    cameraTarget[2] = cameraTarget.z() + zoomStep * cos(rElevation) * cos(rAzimuth);
    //cameraTarget[2] = cameraTarget[2] + zoomStep;

    gluLookAt(
        cameraPosition.x(), cameraPosition.y(), cameraPosition.z(),
        cameraTarget.x(), cameraTarget.y(), cameraTarget.z(),
        0.0f, 1.0f, 0.0f
    );
}

void orbitcontroller::keyboard(unsigned char key) {
    switch (key) {
        case '+':
            isZooming = true; // Start zooming
            zoomIn();
            break;
        case '-':
            isZooming = true; // Start zooming
            zoomOut();
            break;
        // Add additional cases for other keys if needed
    }
    
}


