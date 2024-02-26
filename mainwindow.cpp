#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "style.h"
#include "businesslogic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->convertButton, &QPushButton::clicked, this, [this]{MainWindow::onConvertButtonClicked();});

    connect(ui->copyButton, &QPushButton::clicked, this, [this]{MainWindow::onCopyButtonClicked();});
    connect(ui->newCCButton, &QPushButton::clicked, this, [this]{MainWindow::onNewCCButtonClicked();});
    connect(ui->swapButton, &QPushButton::clicked, this, [this]{MainWindow::onSwapButtonClicked();});
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::getTextEdit() {
    return ui->textEdit->toPlainText().toStdString();
}

void MainWindow::setText(const std::string &result) {
    ui->labelResult->setText(QString::fromStdString(result));
}

void MainWindow::onConvertButtonClicked() {
    std::string number = getTextEdit();
    std::string radioButtonIn = getSelectedRadioButtonText(ui->groupBoxIn);
    std::string radioButtonOut = getSelectedRadioButtonText(ui->groupBoxOut);
    if (radioButtonIn == "" || radioButtonOut == "") {
        QMessageBox::critical(this, "Error", "Fill indicator of radio buttons");
    } else {
        int checkText = checkTextEdit(number, radioButtonIn);
        if (checkText == TRUE) {
            //Здесь конвертор
        } else {
            QMessageBox::critical(this, "Error", "Validate error");
        }
    }
}

void MainWindow::converter(const std::string &radioButtonIn, const std::string &radioButtonOut, const std::string &number) {

}

int MainWindow::handleLengthError(const std::string &number) {
    int flag = TRUE;
    size_t length = number.size();
    if (length > MAXLENGTH) {
        flag = FALSE;
    }
    return flag;
}

std::string MainWindow::getAllowedChars(const std::string &radioButtonIn) {
    std::string allowedChars;
    int base;
    base = std::stoi(radioButtonIn);

    for (int i = 0; i < base; i++) {
        allowedChars += std::to_string(i);
    }

    return allowedChars;
}

int MainWindow::handleValidateNumber(const std::string &number, const std::string &radioButtonIn) {
    int flag = TRUE;
    std::string allowedChars = getAllowedChars(radioButtonIn);
    for (size_t i = 0; i < number.size(); i++) {
        if (allowedChars.find(number.at(i)) == std::string::npos) {
            flag = FALSE;
        }
    }
    return flag;
}

int MainWindow::checkTextEdit(const std::string &number, const std::string &radioButtonIn) {
    int flag = TRUE;
    int validateLength = handleLengthError(number);
    int validateNumber = handleValidateNumber(number, radioButtonIn);
    if (validateLength == FALSE || validateNumber == FALSE) {
        flag = FALSE;
    }
    return flag;
}

std::string MainWindow::getSelectedRadioButtonText(QGroupBox *groupBox) {
    std::string radioButtonText;
    QList<QObject *> children = groupBox->children();
    for (int i = 0; i < children.size(); i++) {
        QRadioButton *radioButton = qobject_cast<QRadioButton *>(children.at(i));
        if (radioButton) {
            if (radioButton->isChecked()) {
                radioButtonText = radioButton->text().toStdString();
                break;
            }
        } else {
            QMessageBox::critical(this, "Error", "Delete not radio button");
        }
    }
    return radioButtonText;
}

void MainWindow::on_textEdit_textChanged() {
    std::string number = getTextEdit();
    if (number.empty()){
        setBtnEnabled(0, ui->convertButton);
    } else {
        setBtnEnabled(1, ui->convertButton);
    }
}

void MainWindow::onCopyButtonClicked() {
    std::string labelText = ui->labelResult->text().toStdString();
    QClipboard *clipboard = QApplication::clipboard();
    if (clipboard) {
        clipboard->setText(QString::fromStdString(labelText));
        QMessageBox::information(this, "Copy to Clipboard", "Text copied to clipboard");
    } else {
        QMessageBox::critical(this, "Error", "Unable to access clipboard");
    }
}

void MainWindow::onNewCCButtonClicked() {
    bool ok;
    QString newCC = QInputDialog::getText(this, "New CC", "Enter a new numbering system:", QLineEdit::Normal, "", &ok);

    if (ok && !newCC.isEmpty()) {
        if (!isRadioButtonExist(ui->groupBoxIn, newCC.toStdString()) && !isRadioButtonExist(ui->groupBoxOut, newCC.toStdString())) {
            setRadioButtonStyles(ui->radioButtonXIn);
            setRadioButtonStyles(ui->radioButtonXOut);
            ui->radioButtonXIn->setText(newCC);
            ui->radioButtonXOut->setText(newCC);
        } else {
            QMessageBox::warning(this, "Error", "Numbering system already exists in the group box");
        }
    }
}

int MainWindow::isRadioButtonExist(QGroupBox *groupBox, const std::string &newCC) {
    QList<QObject *> children = groupBox->children();
    for (int i = 0; i < children.size(); i++) {
        QRadioButton *radioButton = qobject_cast<QRadioButton *>(children.at(i));
        if (radioButton && radioButton->text() == QString::fromStdString(newCC)) {
            return TRUE;
        }
    }
    return FALSE;
}

void MainWindow::onSwapButtonClicked() {
    std::string labelText = ui->labelResult->text().toStdString();
    std::string textEditContent = ui->textEdit->toPlainText().toStdString();

    std::string radioButtonInText = getSelectedRadioButtonText(ui->groupBoxIn);
    std::string radioButtonOutText = getSelectedRadioButtonText(ui->groupBoxOut);

    if (!radioButtonInText.empty() && !radioButtonInText.empty() && !labelText.empty() && !textEditContent.empty()){

        ui->textEdit->setPlainText(QString::fromStdString(labelText));
        ui->labelResult->setText(QString::fromStdString(textEditContent));

        resetRadioButtons(ui->groupBoxIn);
        resetRadioButtons(ui->groupBoxOut);

        setRadioButtonByText(ui->groupBoxIn, radioButtonOutText);
        setRadioButtonByText(ui->groupBoxOut, radioButtonInText);

    } else {
        QMessageBox::critical(this, "Error", "Insert all");
    }
}

void MainWindow::resetRadioButtons(QGroupBox *groupBox) {
    QList<QObject *> children = groupBox->children();
    for (int i = 0; i < children.size(); i++) {
        QRadioButton *radioButton = qobject_cast<QRadioButton *>(children.at(i));
        if (radioButton) {
            radioButton->setChecked(false);
        }
    }
}

void MainWindow::setRadioButtonByText(QGroupBox *groupBox, const std::string &text) {
    QList<QObject *> children = groupBox->children();
    for (int i = 0; i < children.size(); i++) {
        QRadioButton *radioButton = qobject_cast<QRadioButton *>(children.at(i));
        if (radioButton && radioButton->text() == QString::fromStdString(text)) {
            radioButton->setChecked(true);
            break;
        }
    }
}

