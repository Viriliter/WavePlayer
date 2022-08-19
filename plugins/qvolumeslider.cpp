#include "qvolumeslider.h"
#include <QtWidgets>
#include <QDebug>

QVolumeSlider::QVolumeSlider(QWidget *parent) : QWidget(parent)
{
    volume = 100;

    baseColor = QColor(83, 83, 83);
    volumeColor = QColor(179, 179, 179);
    snapColor = QColor(255, 255, 255);
    this->installEventFilter(this);
    this->setMouseTracking(true);
};


void QVolumeSlider::enterEvent(QEvent *event){
    volumeColor = QColor(51, 153, 255);
    this->repaint();
};

void QVolumeSlider::leaveEvent(QEvent *event){
    volumeColor = QColor(179, 179, 179);
    this->repaint();
};

void QVolumeSlider::mousePressEvent(QMouseEvent *event){
    QPoint currentPos = event->pos();

    volume = ((double)currentPos.x() / (double)this->width())*100;
    emit volumeChanged(volume);
    this->repaint();
    isPressed = true;
}

void QVolumeSlider::mouseReleaseEvent(QMouseEvent *event){
    isPressed = false;
}

void QVolumeSlider::mouseMoveEvent(QMouseEvent *event){
    if (isPressed){
        if(event->localPos().x() >= 0 && event->localPos().x() <= this->width()){
            QPoint currentPos = event->pos();

            volume = ((double)currentPos.x() / (double)this->width())*100;
            emit volumeChanged(volume);
            this->repaint();
        }
    }
}

void QVolumeSlider::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0, 0);

    int width = this->width();
    int height = this->height();

    // Draw Base Slider
    QRect rectBase = QRect();
    rectBase.setSize(QSize(width, height/2));
    rectBase.translate(0, height/4);

    painter.setBrush(QBrush(baseColor));

    painter.drawRoundedRect(rectBase, rectBase.height()/2, rectBase.height()/2);

    // Draw Volume Indicator
    QRect rectVol = QRect();
    rectVol.setSize(QSize((volume/(double)100)*width, height/2));
    rectVol.translate(0, height/4);

    painter.setBrush(QBrush(volumeColor));
    painter.drawRoundedRect(rectVol, rectVol.height()/2, rectVol.height()/2);

    // Draw Snap Circle
    QRect rectSnapCircle= QRect();
    rectSnapCircle.setSize(QSize(height, height));
    double snapProgress = (volume/(double)100)*width - rectSnapCircle.width();

    if (snapProgress < 0) snapProgress = 0;
    rectSnapCircle.translate(snapProgress, 0);

    painter.setBrush(QBrush(QColor(247, 247, 247)));
    painter.drawRoundedRect(rectSnapCircle, rectSnapCircle.width()/2, rectSnapCircle.height()/2);


};

void QVolumeSlider::setVolume(int v){
    if (v>100){
        v = 100;
    }
    if (v<0){
        v = 0;
    }
    qDebug() << v << "->" << volume;
    volume = v;
    this->repaint();
    emit volumeChanged(volume);
};
