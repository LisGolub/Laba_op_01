#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QInputDialog>
#include <qlayout.h>

enum flagValidate {
    FALSE = 0,
    TRUE,
};

#define MAXLENGTH 4

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::string getTextEdit();
    void setText(const std::string &result);
    std::string getSelectedRadioButtonText(QGroupBox *groupBox);

    std::string getAllowedChars(const std::string &radioButtonIn);
    int handleValidateNumber(const std::string &number, const std::string &radioButtonIn);
    int handleLengthError(const std::string &number);
    int checkTextEdit(const std::string &number, const std::string &radioButtonIn);
    void converter(const std::string &radioButtonIn, const std::string &radioButtonOut, const std::string &number);

    int isRadioButtonExist(QGroupBox *groupBox, const std::string &newCC);
    void resetRadioButtons(QGroupBox *groupBox);
    void setRadioButtonByText(QGroupBox *groupBox, const std::string &text);

private slots:
    void onConvertButtonClicked();
    void onCopyButtonClicked();
    void onNewCCButtonClicked();
    void onSwapButtonClicked();

    void on_textEdit_textChanged();
};

#endif // MAINWINDOW_H
