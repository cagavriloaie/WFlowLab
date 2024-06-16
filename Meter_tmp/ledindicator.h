/**
 * \file ledindicator.h
 * \brief Header file for the LedIndicator class.
 *
 * This file defines the LedIndicator class, which represents an LED indicator widget
 * for displaying states or statuses.
 *
 * \author Constantin
 */

#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QDialog>  // Qt class for creating modal or modeless dialogs.

/**
 * \brief The LedIndicator class represents a custom LED indicator widget.
 *
 * This class provides functionality to display an LED-like indicator with customizable
 * colors, patterns, and size. It inherits from QWidget and overrides paintEvent to
 * customize the rendering of the LED indicator.
 */
class LedIndicator : public QWidget
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a LedIndicator widget.
     * \param parent Optional pointer to the parent widget.
     */
    explicit LedIndicator(QWidget *parent = nullptr);

    /**
     * \brief Sets the state of the LED indicator.
     * \param state true to turn the LED on, false to turn it off.
     */
    void setState(bool state);

    /**
     * \brief Toggles the state of the LED indicator.
     * If the LED is currently on, it will be turned off, and vice versa.
     */
    void toggle();

    /**
     * \brief Sets the color of the LED when it is turned on.
     * \param onColor The color to set when the LED is on.
     */
    void setOnColor(QColor onColor);

    /**
     * \brief Sets the color of the LED when it is turned off.
     * \param offColor The color to set when the LED is off.
     */
    void setOffColor(QColor offColor);

    /**
     * \brief Sets the pattern of the LED when it is turned on.
     * \param onPattern The brush style pattern to set when the LED is on.
     */
    void setOnPattern(Qt::BrushStyle onPattern);

    /**
     * \brief Sets the pattern of the LED when it is turned off.
     * \param offPattern The brush style pattern to set when the LED is off.
     */
    void setOffPattern(Qt::BrushStyle offPattern);

    /**
     * \brief Sets the size of the LED indicator.
     * \param size The size (width and height) to set for the LED.
     */
    void setLedSize(int size);

public slots:
    /**
     * \brief Slot function to switch the state of the LED indicator.
     * This slot is triggered to toggle the state of the LED indicator.
     */
    void switchLedIndicator();

protected:
    /**
     * \brief Overrides the paint event to render the LED indicator.
     * \param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    bool lit;                       ///< Internal state of the LED indicator (on/off).
    QColor ledOnColor;              ///< Color of the LED when it is on.
    QColor ledOffColor;             ///< Color of the LED when it is off.
    QColor ledNeutral;              ///< Neutral color (optional for a neutral state).
    Qt::BrushStyle ledOnPattern;    ///< Pattern of the LED when it is on.
    Qt::BrushStyle ledOffPattern;   ///< Pattern of the LED when it is off.
    Qt::BrushStyle ledNeutralPattern;///< Pattern for a neutral state (if applicable).
    int ledSize;                    ///< Size of the LED indicator.
};

#endif // LEDINDICATOR_H
