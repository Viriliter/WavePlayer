#ifndef QVOLUMESLIDER_H
#define QVOLUMESLIDER_H

#include <QWidget>

class QVolumeSlider : public QWidget
{
    Q_OBJECT

private:
    QColor baseColor;
    QColor volumeColor;
    QColor snapColor;

    bool isPressed = false;

public:
    explicit QVolumeSlider(QWidget *parent = nullptr);

    int volume = 0;

    void setVolume(int volume);

signals:
    void volumeChanged(int volume);

protected:
    void paintEvent(QPaintEvent *event);
    void eventFilter(QEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // QVOLUMESLIDER_H
