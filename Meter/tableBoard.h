/*
 *  Author: Constantin
 */

#ifndef TABLEBOARD_H
#define TABLEBOARD_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QKeyEvent>
#include <sstream>

namespace Ui
{
    class Dialog;
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

class Dialog : public QDialog
{
    Q_OBJECT

  public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void ValidatorInput();
    void PopulateTable();
    static void printPdfThread(QString report);
    void Translate();

  private:
    Ui::Dialog *ui;
    size_t entries {0};
    double minimumFlowMain {0};
    double transitoriuFlowMain {0};
    double nominalFlowMain {0};
    double nominalError {0};
    double maximumError {0};

    std::vector<QLabel *> vectorNumber;
    std::vector<QCheckBox *> vectorCheckNumber;
    std::vector<QLineEdit *> vectorSerialNumber;
    std::vector<QLineEdit *> vectorFirstIndexStart;
    std::vector<QLineEdit *> vectorFirstIndexStop;
    std::vector<QLineEdit *> vectorFirstError;
    std::vector<QLineEdit *> vectorSecondIndexStart;
    std::vector<QLineEdit *> vectorSecondIndexStop;
    std::vector<QLineEdit *> vectorSecondError;
    std::vector<QLineEdit *> vectorThirdIndexStart;
    std::vector<QLineEdit *> vectorThirdIndexStop;
    std::vector<QLineEdit *> vectorThirdError;

    static QString report;

    bool eventFilter(QObject *, QEvent *);

  private slots:

    void onTypeMeterChanged();
    void onNumberOfWaterMetersChanged();
    void onMeasurementTypeChanged();
    void onSelectAllChanged();
    void onCbClicked(bool status);
    void onCalculateClicked();
    void onCleanClicked();
    void onCloseClicked();
    void onSaveCurrentInputDataClicked();
    void onOpenInputDataClicked();
    void onPrintPdfDocClicked();
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

  protected:
    void showEvent(QShowEvent *event);

};

#endif // TABLEBOARD_H
