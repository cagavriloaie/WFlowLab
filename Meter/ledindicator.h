/*
 *  Author: Constantin
 *  File:   ledindicator.h
 */

#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>

class LedIndicator: public QWidget
{
    Q_OBJECT

public:
    explicit LedIndicator(QWidget *parent = 0);

    // Set the state of the LED
    void setState(bool state);

    // Toggle the state of the LED
    void toggle();

    // Set the color when the LED is on
    void setOnColor(QColor onColor);

    // Set the color when the LED is off
    void setOffColor(QColor offColor);

    // Set the pattern when the LED is on
    void setOnPattern(Qt::BrushStyle onPattern);

    // Set the pattern when the LED is off
    void setOffPattern(Qt::BrushStyle offPattern);

    // Set the size of the LED
    void setLedSize(int size);

public slots:
    // Switch the state of the LED when the slot is triggered
    void switchLedIndicator();

protected:
    // Override paintEvent to customize the rendering of the LED
    void paintEvent(QPaintEvent *);

private:
    // Internal state of the LED (lit or not)
    bool lit;

    // Colors for when the LED is on and off
    QColor ledOnColor;
    QColor ledOffColor;

    // Neutral color (potentially for a neutral state)
    QColor ledNeutral;

    // Patterns for when the LED is on and off
    Qt::BrushStyle ledOnPattern;
    Qt::BrushStyle ledOffPattern;

    // Pattern for a neutral state (if applicable)
    Qt::BrushStyle ledNeutralPattern;

    // Size of the LED
    int ledSize;
};

#endif // LEDINDICATOR_H
