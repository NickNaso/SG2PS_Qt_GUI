// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include "Option.hpp"
#include "OptionWidget.hpp"


OptionWidget::OptionWidget(QWidget* parent, const Option& option)
    : QWidget(parent), opt(option)
{
    label = new QLabel(opt.key, this);

    comboBox = new QComboBox(this);
    comboBox->addItems(opt.values);
    comboBox->setCurrentIndex(opt.defaultElem);

//    QFont labelFont = label->font();
//    labelFont.setStretch(QFont::SemiCondensed);
//    label->setFont(labelFont);
//    comboBox->setFont(labelFont);

    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->setMargin(0);
    layout->setSpacing(10);
    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addStretch(1);

    setLayout(layout);

    label->setFocusPolicy(Qt::NoFocus);
    comboBox->setFocusPolicy(Qt::StrongFocus);
}

void OptionWidget::selectDefault() {
    comboBox->setCurrentIndex(opt.defaultElem);
}

void OptionWidget::setCurrentIndex(int i) {
    comboBox->setCurrentIndex(i);
}

int OptionWidget::getCurrentIndex() const {
    return comboBox->currentIndex();
}

QString OptionWidget::selection2CLI() const {
    int i = comboBox->currentIndex();
    return opt.toCLIString(i);
}

const QString& OptionWidget::cliKey() const {
    return opt.cliKey;
}

int OptionWidget::indexOf(const QString& s) {
    return opt.cliValues.indexOf(s);
}

void OptionWidget::setForbidden(bool flag) {

    comboBox->setDisabled(flag);
}
