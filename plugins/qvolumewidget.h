#ifndef QVOLUMEWIDGET_H
#define QVOLUMEWIDGET_H

#include <QWidget>
#include <QToolButton>
#include "qvolumeslider.h"

class QVolumeWidget : public QWidget
{
    Q_OBJECT

private:
    QVolumeSlider *slider;
    QToolButton *icon;
    QSize iconSize;
    bool isMuted;

    QString urlVolumeMute = "./resources/ic_volume_mute_24px.svg";
    QString urlVolumeUp = "./resources/ic_volume_up_24px.svg";
    QString urlVolumeDown = "./resources/ic_volume_down_24px.svg";

public:
    explicit QVolumeWidget(QWidget *parent = nullptr);

    int volume = 0;
    int lastVolume;
    QColor volumeColor;
    void setVolume(int volume);

signals:
    void volumeChanged(int v);

protected slots:
    void slotVolumeChanged(int v);
    void clickedVolume();
};

#endif // QVOLUMEWIDGET_H
