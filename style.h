#ifndef STYLE_H
#define STYLE_H

#include <QPushButton>
#include <QRadioButton>

enum EnabledFlag {
    FALSESTYLE = 0,
    TRUESTYLE
};

void setBtnEnabled(int status, QPushButton *btn);
void setRadioButtonStyles(QRadioButton *radio);

#endif // STYLE_H
