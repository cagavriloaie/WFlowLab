/*
 *  Author: Constantin
 *  File:   ledindicator.cpp
 */

#include <QPainter>

#include "ledindicator.h"

LedIndicator::LedIndicator(QWidget *parent) : QWidget(parent)
{
    // Set initial size and state
    setFixedSize(28, 28);
    lit = false;

    // Set default colors and patterns
    ledOnColor = Qt::green;
    ledOffColor = Qt::red;
    ledOnPattern = Qt::SolidPattern;
    ledOffPattern = Qt::SolidPattern;
    ledNeutralPattern = Qt::SolidPattern;

    // Set default LED size
    ledSize = 12;
}

void LedIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Set brush and draw filled ellipse
    lit ? painter.setBrush(QBrush(ledOnColor, ledOnPattern))
        : painter.setBrush(QBrush(ledOffColor, ledOffPattern));
    painter.drawEllipse(4, 9, ledSize, ledSize);

    // Set pen color and draw outlined ellipse
    lit ? painter.setPen(ledOnColor) : painter.setPen(ledOffColor);
    painter.drawEllipse(4, 9, ledSize, ledSize);
}

void LedIndicator::switchLedIndicator()
{
    // Toggle the LED state and trigger a repaint
    lit = !lit;
    repaint();
}

void LedIndicator::setState(bool state)
{
    // Set the LED state and trigger a repaint
    lit = state;
    repaint();
}

void LedIndicator::toggle()
{
    // Toggle the LED state and trigger a repaint
    lit = !lit;
    repaint();
}

void LedIndicator::setOnColor(QColor onColor)
{
    // Set the color when the LED is on and trigger a repaint
    ledOnColor = onColor;
    repaint();
}

void LedIndicator::setOffColor(QColor offColor)
{
    // Set the color when the LED is off and trigger a repaint
    ledOffColor = offColor;
    repaint();
}

void LedIndicator::setOnPattern(Qt::BrushStyle onPattern)
{
    // Set the pattern when the LED is on and trigger a repaint
    ledOnPattern = onPattern;
    repaint();
}

void LedIndicator::setOffPattern(Qt::BrushStyle offPattern)
{
    // Set the pattern when the LED is off and trigger a repaint
    ledOffPattern = offPattern;
    repaint();
}

void LedIndicator::setLedSize(int size)
{
    // Set the size of the LED and trigger a repaint
    ledSize = size;
    setFixedSize(size, size);
    repaint();
}
