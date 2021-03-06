/**
 * @file Canvas2D.cpp
 *
 * CS123 2-dimensional canvas. Contains support code necessary for Brush, Filter, Intersect, and
 * Ray.
 *
 * YOU WILL NEED TO FILL THIS IN!
 *
 */

// For your convenience, a few headers are included for you.
#include <assert.h>
#include <iostream>
#include <math.h>
#include <memory>
#include <unistd.h>
#include "Canvas2D.h"
#include "Settings.h"
#include "RayScene.h"

#include <QCoreApplication>
#include <QPainter>

#include <iostream>
#include <memory>

Canvas2D::Canvas2D() :
    // @TODO: Initialize any pointers in this class here.
    m_rayScene(nullptr)
{
}

Canvas2D::~Canvas2D()
{
}


// This is called when the canvas size is changed. You can change the canvas size by calling
// resize(...). You probably won't need to fill this in, but you can if you want to.
void Canvas2D::notifySizeChanged(int w, int h) {
}

void Canvas2D::paintEvent(QPaintEvent *e) {
    // You probably won't need to fill this in, but you can if you want to override any painting
    // events for the 2D canvas. For now, we simply call the superclass.
    SupportCanvas2D::paintEvent(e);

}

/**
 * @brief Canvas2D::settingsChanged --> detects changes in settings
 */
void Canvas2D::settingsChanged() {

}

// ********************************************************************************************
// ** BRUSH
// ********************************************************************************************

/**
 * @brief Canvas2D::mouseDown --> performs an action when the mouse is down
 * @param x --> int
 * @param y --> int
 */
void Canvas2D::mouseDown(int x, int y) {


//    bool fixAlphaBlending = settings.fixAlphaBlending; // for extra/half credit

}

/**
 * @brief Canvas2D::mouseDragged --> performs an action when the mouse is dragged
 * @param x --> int
 * @param y --> int
 */
void Canvas2D::mouseDragged(int x, int y) {

}

/**
 * @brief Canvas2D::mouseUp --> performs an action when the mouse is up
 * @param x --> int
 * @param y --> int
 */
void Canvas2D::mouseUp(int x, int y) {
//    m_brush->brushUp(x, y, this);
}

// ********************************************************************************************
// ** RAY
// ********************************************************************************************

void Canvas2D::setScene(RayScene *scene) {
    m_rayScene.reset(scene);
}

void Canvas2D::renderImage(Camera *camera, int width, int height) {
    if (m_rayScene) {
        // @TODO: raytrace the scene based on settings
        //        YOU MUST FILL THIS IN FOR INTERSECT/RAY

        // If you want the interface to stay responsive, make sure to call
        // QCoreApplication::processEvents() periodically during the rendering.

    }
}

void Canvas2D::cancelRender() {
    // TODO: cancel the raytracer (optional)
}




