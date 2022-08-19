#ifndef SVGPUSHBUTTON_H
#define SVGPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QtSvg/QSvgWidget>

class SVGPushButton : public QPushButton
{
    Q_OBJECT
public:
    SVGPushButton(QString path);

signals:

};

#endif // SVGPUSHBUTTON_H
