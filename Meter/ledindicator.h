/*
 *  Author: Constantin
 *  File: ledindicator.h
 */

#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>

class LedIndicator: public QWidget
{
    Q_OBJECT
  public:
    explicit LedIndicator(QWidget *parent = 0);
    void setState(bool state);
    void toggle();
    void setOnColor(QColor onColor);
    void setOffColor(QColor offColor);
    void setOnPattern(Qt::BrushStyle onPattern);
    void setOffPattern(Qt::BrushStyle offPattern);
    void setLedSize(int size);

  public slots:
    void switchLedIndicator();

  protected:
    void paintEvent(QPaintEvent *);

  private:
    bool lit;
    QColor ledOnColor;
    QColor ledOffColor;
    QColor ledNeutral;
    Qt::BrushStyle ledOnPattern;
    Qt::BrushStyle ledOffPattern;
    Qt::BrushStyle ledNeutralPattern;
    int ledSize;
};

#endif // LEDINDICATOR_H

