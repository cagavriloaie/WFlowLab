#include <QPainter>

#include "ledindicator.h"

LedIndicator::LedIndicator(QWidget *parent) : QWidget(parent) {
    setFixedSize(28, 28);
    lit = false;
    ledOnColor = Qt::green;
    ledOffColor = Qt::red;
    ledOnPattern = Qt::SolidPattern;
    ledOffPattern = Qt::SolidPattern;
    ledNeutralPattern = Qt::SolidPattern;
    ledSize = 12;
}

void LedIndicator::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    lit ? painter.setBrush(QBrush(ledOnColor, ledOnPattern))
        : painter.setBrush(QBrush(ledOffColor, ledOffPattern));
    painter.drawEllipse(4, 9, ledSize, ledSize);
    lit ? painter.setPen(ledOnColor) : painter.setPen(ledOffColor);
    painter.drawEllipse(4, 9, ledSize, ledSize);
}

void LedIndicator::switchLedIndicator() {
    lit = !lit;
    repaint();
}

void LedIndicator::setState(bool state) {
    lit = state;
    repaint();
}

void LedIndicator::toggle() {
    lit = !lit;
    repaint();
}

void LedIndicator::setOnColor(QColor onColor) {
    ledOnColor = onColor;
    repaint();
}

void LedIndicator::setOffColor(QColor offColor) {
    ledOffColor = offColor;
    repaint();
}

void LedIndicator::setOnPattern(Qt::BrushStyle onPattern) {
    ledOnPattern = onPattern;
    repaint();
}

void LedIndicator::setOffPattern(Qt::BrushStyle offPattern) {
    ledOffPattern = offPattern;
    repaint();
}

void LedIndicator::setLedSize(int size) {
    ledSize = size;
    setFixedSize(size, size);
    repaint();
}
