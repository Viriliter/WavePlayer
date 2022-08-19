#include "qmedianavigator.h"
#include <QtWidgets>
#include <QDebug>

QMediaNavigator::QMediaNavigator(QWidget *parent) : QSlider(parent)
{
    value = 0;
    minPoint= 0;
    maxPoint = 100;
    previewPos = 0;
    this->setMouseTracking(true);
}

void QMediaNavigator::setMinimum(const qint64 &min){
    minPoint = min;
    this->repaint();
}

void QMediaNavigator::setMaximum(const qint64 &max){
    maxPoint = max;
    this->repaint();
}

void QMediaNavigator::setValue(const qint64 &val){
    value = val;
    this->repaint();
}

void QMediaNavigator::leaveEvent(QEvent *event){
    previewPos = -1;
    this->repaint();
};

void QMediaNavigator::mousePressEvent(QMouseEvent *event){
    QPoint currentPos = event->pos();
    previewPos = currentPos.x();

    emit timelineChanged(((double) previewPos/((int)this->width()))*((double)maxPoint-(double)minPoint) + (double)minPoint);
    this->repaint();
    isPressed = true;
}

void QMediaNavigator::mouseReleaseEvent(QMouseEvent *event){
    isPressed = false;
}

void QMediaNavigator::mouseMoveEvent(QMouseEvent *event){
    if (isPressed){
        if(event->localPos().x() >= 0 && event->localPos().x() <= this->width()){
            QPoint currentPos = event->pos();
            previewPos = currentPos.x();

            emit timelineChanged(((double) previewPos/((int)this->width()))*((double)maxPoint-(double)minPoint) + (double)minPoint);
            this->repaint();
        }
    }
    else{
        QPoint currentPos = event->pos();
        previewPos = currentPos.x();
        setToolTipInfo(currentPos.x());
        this->repaint();
    }
}

void QMediaNavigator::setToolTipInfo(qint64 position){
    qint64 duration = (maxPoint-minPoint) * (position/(double)this->width());
    qint64 position_sec = duration / (double) 1000;  // Convert ms to seconds
    int minute = ((int)position_sec) / 60;
    int second = ((int)position_sec) % 60;
    QString text = QString::number(minute) + QString(":") + QStringLiteral("%1").arg(second, 2, 10, QLatin1Char('0'));
    this->setToolTip(text);
};

void QMediaNavigator::paintEvent(QPaintEvent *event){
    try{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0, 0);

    int width = this->width();
    int height = this->height();

    // Draw Base
    QRect rect = QRect();
    rect.setSize(QSize(width, height));

    painter.setBrush(QBrush(baseColor));
    painter.drawRoundedRect(rect, rect.height()/2, rect.height()/2);

    if (maxPoint == 0) return;

    // Draw Progress
    QRect rectProgress = QRect();
    double progress = (double) ((int)value - (int)minPoint)/((int)maxPoint);
    rectProgress.setSize(QSize((int)width*progress, height));

    if (this->isEnabled()){
        painter.setBrush(QBrush(progressColor));
    }
    else{
        painter.setBrush(QBrush(disabledProgressColor));
    }
    painter.drawRoundedRect(rectProgress, rectProgress.height()/2, rectProgress.height()/2);

    // Draw Timeline Preview
    if (previewPos > 0) {
        QRect rectPreviewProgress = QRect();
        double previewProgress = ((double) previewPos) / width;
        rectPreviewProgress.setSize(QSize((int)width*previewProgress, height/2));
        rectPreviewProgress.translate(0, height/4);

        painter.setBrush(QBrush(previewProgressColor));
        painter.drawRoundedRect(rectPreviewProgress, rectPreviewProgress.height()/2, rectPreviewProgress.height()/2);
    }

    // Draw Snap Circle
    QRect rectSnapCircle= QRect();
    rectSnapCircle.setSize(QSize(height, height));
    double snapProgress = (int)width*progress - rectSnapCircle.width();

    if (snapProgress < 0) snapProgress = 0;
    rectSnapCircle.translate(snapProgress, 0);

    painter.setBrush(QBrush(snapColor));
    painter.drawRoundedRect(rectSnapCircle, rectSnapCircle.width()/2, rectSnapCircle.height()/2);




    }
    catch (const  std::exception& ex){
        qWarning() << ex.what();
    }

}
