#include "qvolumewidget.h"
#include <QtWidgets>
#include <QDebug>
#include "qvolumeslider.h"

QVolumeWidget::QVolumeWidget(QWidget *parent) : QWidget(parent)
{
    volume = 100;
    lastVolume = volume;
    volumeColor = QColor(179, 179, 179);
    iconSize = QSize(24, 24);

    slider = new QVolumeSlider();
    slider->setFixedSize(QSize(100, 15));
    QObject::connect(slider, SIGNAL(volumeChanged(int)), this, SLOT(slotVolumeChanged(int)));

    icon = new QToolButton();
    icon->setAutoRaise(true);
    icon->setCheckable(true);
    QIcon iconVolume(urlVolumeUp);
    icon->setIcon(iconVolume);
    QObject::connect(icon, SIGNAL(clicked()), this, SLOT(clickedVolume()));

    QGridLayout *layoutG = new QGridLayout();
    layoutG->setContentsMargins(0, 0, 0, 0);
    layoutG->setHorizontalSpacing(4);
    layoutG->addWidget(icon, 0, 0, 1, 1);
    layoutG->addWidget(slider, 0, 1, 1, 1);

    this->setLayout(layoutG);
};

void QVolumeWidget::slotVolumeChanged(int v){
    icon->setChecked(false);

    if (v == 0){
        QIcon iconVolume(urlVolumeMute);
        icon->setIcon(iconVolume);
    }
    else if (v > 50){
        QIcon iconVolume(urlVolumeUp);
        icon->setIcon(iconVolume);
    }
    else{
        QIcon iconVolume(urlVolumeDown);
        icon->setIcon(iconVolume);
    }

    emit volumeChanged(v);
}

void QVolumeWidget::clickedVolume(){
    if (!isMuted){
        lastVolume = slider->volume;
        slider->setVolume(0);
        isMuted = true;
    }
    else{
        slider->setVolume(lastVolume);
        isMuted = false;
    }
}
