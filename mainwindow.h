#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QListWidgetItem>
#include <QtMultimediaWidgets>
#include <QProcess>
#include <QtNetwork>
#include "plugins/qmedianavigator.h"
#include "plugins/qvolumewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString urlPlay = "./resources/ic_play_arrow_24px.svg";
    QString urlPause = "./resources/ic_pause_24px.svg";
    QString urlSkipNext = "./resources/ic_skip_next_24px.svg";
    QString urlSkipPrevious = "./resources/ic_skip_previous_24px.svg";
    QString urlStop = "./resources/ic_stop_24px.svg";
    QString urlShuffle = "./resources/ic_shuffle_24px.svg";
    QString urlRepeat = "./resources/ic_repeat_24px.svg";

    QMediaNavigator *progressMedia;
    QVolumeWidget *volumeWidget;
    QTextEdit *textLyrics;
    QComboBox *comboBLyrics;

    bool isShuffled = false;
    bool isRepeat = false;

    QProcess *process = nullptr;
    QStringList mediaList;
    QMediaPlaylist *playlist;
    QList<QStringList> lastLyricList;

    int currentMediaID;
    bool is_playing;
    qint64 mediaTotalDuration;

    QVideoWidget *videoWidget;
    QMediaPlayer *player;

    void loadUI();

    void connectSignals();

    void playMedia();

    void stopMedia();

    void pauseMedia();

    void nextMedia();

    void prevMedia();

    void searchLyrics(QString keyword);

    void getLyrics(QString keyword);

    void keywordCombiner(QStringList &keywords, QStringList &result, int iter);

private slots:
    void triggeredAboutApp();

    void triggeredAboutQt();

    void clickedBrowse();

    void clickedMediaItem(QListWidgetItem *item);

    void clickedDoubleMediaItem(QListWidgetItem *item);

    void clickedPlay();

    void clickedNext();

    void clickedPrev();

    void toggledShuffle(bool isToggled);

    void toggledRepeat(bool isToggled);

    void mediaDurationChanged(qint64 currentDuration);

    void mediaPositionChanged(qint64 position);

    void onMediaError(QMediaPlayer::Error);

    void onMediaStateChanged(QMediaPlayer::State);

    void onCurrentMediaChanged(const QMediaContent &item);

    void onVideoAvailabilityChanged(bool isAvailable);

    void mediaTimelineChanged(qint64 mediaPosition);

    void changeVolume(int volume);

    void comboBLyricsChanged(int index);

    void processReadyRead();

    void processFinished(int exitCode);

    void netwManagerFinished(QNetworkReply *reply);

};
#endif // MAINWINDOW_H
