#include "svgpushbutton.h"

#include <QtCore>
#include <QPushButton>
#include <QHBoxLayout>
#include <QtGui>
#include <QtSvg/QSvgWidget>

SVGPushButton::SVGPushButton(QString svgPath): QPushButton()
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(new QSvgWidget(svgPath, this));
}
