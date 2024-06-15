/**
 * \file ledindicator.cpp
 * \brief Implementation file for the LedIndicator class.
 *
 * This file contains the implementation of the LedIndicator class, which
 * provides functionality for displaying LED indicators in a graphical user interface.
 *
 * \author Constantin
 * \date Insert date
 */
#include <QPainter>                 // Qt class for performing low-level painting on widgets

#include "ledindicator.h"           // Include header for LedIndicator class
/*!
 * \brief Constructs a LedIndicator widget with default settings.
 *
 * \param parent The parent widget (optional).
 */
LedIndicator::LedIndicator(QWidget *parent) : QWidget(parent)
{
    // Set initial size and state
    setFixedSize(28, 28);
    lit = false;

    // Set default colors and patterns
    ledOnColor = Qt::green;        ///< Color of the LED when it is on
    ledOffColor = Qt::red;         ///< Color of the LED when it is off
    ledOnPattern = Qt::SolidPattern;   ///< Pattern of the LED when it is on (solid)
    ledOffPattern = Qt::SolidPattern;  ///< Pattern of the LED when it is off (solid)
    ledNeutralPattern = Qt::SolidPattern; ///< Neutral pattern of the LED (solid)

    // Set default LED size
    ledSize = 12;
}

/*!
 * \brief Paints the LED indicator widget.
 *
 * This function is called automatically whenever the widget needs to be repainted.
 * It draws an ellipse representing the LED, filled with a color and pattern based on
 * the current state (`lit`), and outlines it with a corresponding color.
 *
 * \param event A paint event (unused).
 */
void LedIndicator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Set brush and draw filled ellipse
    lit ? painter.setBrush(QBrush(ledOnColor, ledOnPattern))
        : painter.setBrush(QBrush(ledOffColor, ledOffPattern));
    painter.drawEllipse(4, 9, ledSize, ledSize);

    // Set pen color and draw outlined ellipse
    lit ? painter.setPen(ledOnColor) : painter.setPen(ledOffColor);
    painter.drawEllipse(4, 9, ledSize, ledSize);

    Q_UNUSED(event); // Unused parameter (suppresses compiler warning)
}

/**
 * \brief Toggles the state of the LED indicator and triggers a repaint.
 */
void LedIndicator::switchLedIndicator()
{
    // Toggle the LED state and trigger a repaint
    lit = !lit;
    repaint();
}

/**
 * \brief Sets the state of the LED indicator and triggers a repaint.
 *
 * \param state The state to set (`true` for on, `false` for off).
 */
void LedIndicator::setState(bool state)
{
    // Set the LED state and trigger a repaint
    lit = state;
    repaint();
}

/**
 * \brief Toggles the state of the LED indicator and triggers a repaint.
 */
void LedIndicator::toggle()
{
    // Toggle the LED state and trigger a repaint
    lit = !lit;
    repaint();
}

/**
 * \brief Sets the color of the LED when it is on and triggers a repaint.
 *
 * \param onColor The color to set when the LED is on.
 */
void LedIndicator::setOnColor(QColor onColor)
{
    // Set the color when the LED is on and trigger a repaint
    ledOnColor = onColor;
    repaint();
}

/**
 * \brief Sets the color of the LED when it is off and triggers a repaint.
 *
 * \param offColor The color to set when the LED is off.
 */
void LedIndicator::setOffColor(QColor offColor)
{
    // Set the color when the LED is off and trigger a repaint
    ledOffColor = offColor;
    repaint();
}

/**
 * \brief Sets the pattern of the LED when it is on and triggers a repaint.
 *
 * \param onPattern The pattern to set when the LED is on (e.g., solid, dense, etc.).
 */
void LedIndicator::setOnPattern(Qt::BrushStyle onPattern)
{
    // Set the pattern when the LED is on and trigger a repaint
    ledOnPattern = onPattern;
    repaint();
}

/**
 * \brief Sets the pattern of the LED when it is off and triggers a repaint.
 *
 * \param offPattern The pattern to set when the LED is off (e.g., solid, dense, etc.).
 */
void LedIndicator::setOffPattern(Qt::BrushStyle offPattern)
{
    // Set the pattern when the LED is off and trigger a repaint
    ledOffPattern = offPattern;
    repaint();
}

/**
 * \brief Sets the size of the LED and triggers a repaint.
 *
 * \param size The size to set for the LED.
 */
void LedIndicator::setLedSize(int size)
{
    // Set the size of the LED and trigger a repaint
    ledSize = size;
    setFixedSize(size, size);
    repaint();
}
