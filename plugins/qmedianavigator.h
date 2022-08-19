#ifndef QMEDIANAVIGATOR_H
#define QMEDIANAVIGATOR_H

#include <QWidget>
#include <QSlider>

class QMediaNavigator : public QSlider
{
    Q_OBJECT

private:
    qint64 minPoint;
    qint64 maxPoint;
    qint64 value;
    qint64 previewPos;
    bool isPressed = false;

    QColor baseColor = QColor(42, 42, 42);
    QColor progressColor = QColor(1, 131, 233);
    QColor disabledProgressColor = QColor(179, 179, 179);
    QColor previewProgressColor = QColor(229, 243, 255, 180);
    QColor snapColor = QColor(247, 247, 247);

    void setToolTipInfo(qint64 position);

public:
    explicit QMediaNavigator(QWidget *parent = nullptr);

    void setMinimum(const qint64 &min);
    void setMaximum(const qint64 &max);
    void setValue(const qint64 &val);

signals:
    void timelineChanged(const qint64 &duration_ms);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // QMEDIANAVIGATOR_H
