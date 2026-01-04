/**
 * \file colors.h
 * \brief Centralized color management for WStreamLab application.
 *
 * This file defines all colors used throughout the application.
 * Colors are consistent with app.qss stylesheet.
 *
 * \author Constantin
 */

#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

#include <QColor>

/**
 * \namespace AppColors
 * \brief Color definitions for the entire application.
 *
 * All colors match the traditional styling defined in app.qss.
 */
namespace AppColors {

// ============================================
// Primary Brand Colors
// ============================================

/// Primary action color
const QColor Primary(0, 120, 215);  // #0078D7

/// Primary hover state
const QColor PrimaryHover(0, 102, 204);  // Slightly darker

/// Primary pressed state
const QColor PrimaryPressed(0, 90, 180);  // Darker

/// Focus indicator
const QColor Focus(0, 120, 215);  // #0078D7

// ============================================
// State Colors
// ============================================

/// Success state - Light green
const QColor Success(220, 235, 220);  // #DCEBDC - rgb(220, 235, 220)

/// Success background
const QColor SuccessBackground(220, 235, 220);  // #DCEBDC

/// Warning state
const QColor Warning(255, 200, 0);  // Yellow-orange

/// Warning background
const QColor WarningBackground(255, 245, 200);  // Light yellow

/// Error state - Red
const QColor Error(255, 0, 0);  // red

/// Error pressed
const QColor ErrorPressed(200, 0, 0);  // Darker red

// ============================================
// Background Colors
// ============================================

/// Main application background
const QColor Background(240, 240, 240);  // #F0F0F0

/// Surface color (cards, dialogs)
const QColor Surface(255, 255, 255);  // #FFFFFF

/// Hover background - Light gray
const QColor BackgroundHover(215, 217, 215);  // #D7D9D7

/// Disabled background
const QColor BackgroundDisabled(200, 200, 200);  // Light gray

/// Selection background
const QColor SelectionBackground(173, 216, 230);  // #ADD8E6

/// Alternating row background
const QColor BackgroundAlternate(250, 250, 250);  // #FAFAFA

/// Very light background for normal/inactive state
const QColor BackgroundNormal(250, 250, 250);  // #FAFAFA

/// Light background for standard elements
const QColor BackgroundLight(240, 240, 240);  // #F0F0F0

/// Group box background
const QColor BackgroundGroupBox(230, 230, 255);  // #E6E6FF

/// Error row background
const QColor BackgroundError(245, 220, 220);  // #F5DCDC

// ============================================
// Border Colors
// ============================================

/// Standard border - Light blue
const QColor Border(173, 216, 230);  // #ADD8E6

/// Border hover - Medium gray
const QColor BorderHover(170, 170, 170);  // #AAA

/// Border focus - Primary blue
const QColor BorderFocus(0, 120, 215);  // #0078D7

/// Standard border - Gray
const QColor BorderStandard(204, 204, 204);  // #CCC

/// Group box border
const QColor BorderGroupBox(0, 0, 0, 92);  // rgba(0, 0, 0, 0.36)

/// Divider/separator color
const QColor Divider(204, 204, 204);  // #CCC

// ============================================
// Text Colors
// ============================================

/// Primary text - Black
const QColor TextPrimary(0, 0, 0);  // black

/// Secondary text - Gray
const QColor TextSecondary(100, 100, 100);  // Gray

/// Disabled text - Light gray
const QColor TextDisabled(153, 153, 153);  // #999

/// Text on colored backgrounds - White
const QColor TextOnColor(255, 255, 255);  // white

/// Link text - Primary blue
const QColor TextLink(0, 120, 215);  // #0078D7

/// Error text - Red
const QColor TextError(255, 0, 0);  // red

// ============================================
// Helper Functions
// ============================================

/**
 * \brief Converts a QColor to a hex string for use in stylesheets.
 * \param color The QColor to convert
 * \return QString in format "#RRGGBB"
 */
inline QString toHex(const QColor& color) {
    return QString("#%1%2%3")
        .arg(color.red(), 2, 16, QChar('0'))
        .arg(color.green(), 2, 16, QChar('0'))
        .arg(color.blue(), 2, 16, QChar('0'))
        .toUpper();
}

/**
 * \brief Converts a QColor to an RGB string for use in stylesheets.
 * \param color The QColor to convert
 * \return QString in format "rgb(r, g, b)"
 */
inline QString toRgb(const QColor& color) {
    return QString("rgb(%1, %2, %3)")
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue());
}

/**
 * \brief Converts a QColor to an RGBA string for use in stylesheets.
 * \param color The QColor to convert
 * \return QString in format "rgba(r, g, b, a)"
 */
inline QString toRgba(const QColor& color) {
    return QString("rgba(%1, %2, %3, %4)")
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue())
        .arg(color.alphaF(), 0, 'f', 2);
}

/**
 * \brief Creates a lighter version of a color (for hover effects).
 * \param color The base color
 * \param factor Lightness factor (0.0 to 1.0, default 0.2)
 * \return Lighter QColor
 */
inline QColor lighter(const QColor& color, qreal factor = 0.2) {
    return color.lighter(static_cast<int>(100 + factor * 100));
}

/**
 * \brief Creates a darker version of a color (for pressed effects).
 * \param color The base color
 * \param factor Darkness factor (0.0 to 1.0, default 0.2)
 * \return Darker QColor
 */
inline QColor darker(const QColor& color, qreal factor = 0.2) {
    return color.darker(static_cast<int>(100 + factor * 100));
}

}  // namespace AppColors

#endif  // COLORS_H_INCLUDED
