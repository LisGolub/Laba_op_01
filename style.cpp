#include "style.h"

void setBtnEnabled(int status, QPushButton *btn) {
    btn->setEnabled(status);
    if (status) {
        btn->setStyleSheet("QPushButton{border-radius: 5px;background-color: white;color: black; border: 1px solid black}");
    } else {
        btn->setStyleSheet("QPushButton{border-radius: 5px;background-color: white;color: gray;}");
    }
}

void setRadioButtonStyles(QRadioButton *radio){
    radio->setStyleSheet("QRadioButton {"
                         "    color: black;"
                         "}"
                         "QRadioButton::indicator {"
                         "    width: 11px;"
                         "    height: 11px;"
                         "    border: 1px solid white;"
                         "    border-radius:6px;"
                         "}"
                         "QRadioButton::indicator:checked {"
                         "    background-color: pink;"
                         "}"
                         "QRadioButton::indicator:unchecked {"
                         "    background-color: white;" // Замените на цвет, который хотите видеть при отмене выбора
                         "}");
}
