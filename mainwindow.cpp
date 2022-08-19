#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QtMultimediaWidgets>
#include <QMediaPlaylist>
#include <QProcess>
#include <QtNetwork>
#include "plugins/qmedianavigator.h"
#include "plugins/qvolumewidget.h"

#include <iostream>
#include <random>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadUI();

    currentMediaID = -1;
        mediaTotalDuration = 0;
        is_playing = false;

        player = new QMediaPlayer();
        playlist = new QMediaPlaylist();
        player->setPlaylist(this->playlist);

        videoWidget = new QVideoWidget();
        player->setVideoOutput(videoWidget);

        QGridLayout *layoutVideoPlayer = new QGridLayout();
        layoutVideoPlayer->addWidget(videoWidget, 0, 0);
        ui->pageVideoPlayer->setLayout(layoutVideoPlayer);

        this->videoWidget->show();

        QGridLayout *layoutMusicPlayer = new QGridLayout();
        textLyrics = new QTextEdit();
        textLyrics->setStyleSheet("color:rgb(255,255,255, 255);");
        textLyrics->setReadOnly(true);
        textLyrics->setAlignment(Qt::AlignCenter);

        comboBLyrics = new QComboBox();
        comboBLyrics->setStyleSheet("color:rgb(255,255,255, 255);");

        layoutMusicPlayer->addWidget(comboBLyrics, 0, 0);
        layoutMusicPlayer->addWidget(textLyrics, 1, 0);
        ui->pageMusicPlayer->setLayout(layoutMusicPlayer);

        progressMedia = new QMediaNavigator(ui->frameNavigator);
        progressMedia->setObjectName(QString::fromUtf8("progressMedia"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(progressMedia->sizePolicy().hasHeightForWidth());
        progressMedia->setSizePolicy(sizePolicy4);
        progressMedia->setMinimumSize(QSize(0, 10));
        progressMedia->setMaximumSize(QSize(16777215, 10));
        progressMedia->setValue(100);
        progressMedia->setEnabled(false);
        ui->gridLayout_2->addWidget(progressMedia, 1, 1, 1, 1);

        volumeWidget = new QVolumeWidget();
        volumeWidget->setFixedSize(QSize(150, 30));
        ui->gridLayout_4->addWidget(volumeWidget, 0, 7, 1, 1);

        connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadUI(){


    QIcon iconPlay(urlPlay);
    QIcon iconPause(urlPause);
    QIcon iconSkipNext(urlSkipNext);
    QIcon iconSkipPrevious(urlSkipPrevious);
    QIcon iconStop(urlStop);
    QIcon iconShuffle(urlShuffle);
    QIcon iconRepeat(urlRepeat);

    ui->pushPlay->setIcon(iconPlay);
    ui->pushPlay->setIconSize(QSize(30, 30));
    ui->pushNext->setIcon(iconSkipNext);
    ui->pushNext->setIconSize(QSize(24, 24));
    ui->pushPrevious->setIcon(iconSkipPrevious);
    ui->pushPrevious->setIconSize(QSize(24, 24));
    ui->buttonShuffle->setIcon(iconShuffle);
    ui->buttonShuffle->setIconSize(QSize(24, 24));
    ui->buttonRepeat->setIcon(iconRepeat);
    ui->buttonRepeat->setIconSize(QSize(24, 24));
}


void MainWindow::connectSignals(){
    QObject::connect(ui->pushBrowse, SIGNAL(clicked()),
                     this, SLOT(clickedBrowse()));
    QObject::connect(ui->listWMedia, SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(clickedMediaItem(QListWidgetItem*)));
    QObject::connect(ui->listWMedia, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                     this, SLOT(clickedDoubleMediaItem(QListWidgetItem*)));

    QObject::connect(ui->pushPlay, SIGNAL(clicked()),
                     this, SLOT(clickedPlay()));

    QObject::connect(ui->pushPrevious, SIGNAL(clicked()),
                     this, SLOT(clickedPrev()));

    QObject::connect(ui->pushNext, SIGNAL(clicked()),
                     this, SLOT(clickedNext()));

    QObject::connect(ui->buttonShuffle, SIGNAL(toggled(bool)),
                     this, SLOT(toggledShuffle(bool)));

    QObject::connect(ui->buttonRepeat, SIGNAL(toggled(bool)),
                     this, SLOT(toggledRepeat(bool)));

    QObject::connect(player, SIGNAL(durationChanged(qint64)),
            this, SLOT(mediaDurationChanged(qint64)));

    QObject::connect(player, SIGNAL(positionChanged(qint64)),
            this, SLOT(mediaPositionChanged(qint64)));

    QObject::connect(player, SIGNAL(error(QMediaPlayer::Error)),
            this, SLOT(onMediaError(QMediaPlayer::Error)));

    QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(onMediaStateChanged(QMediaPlayer::State)));

    QObject::connect(player, SIGNAL(videoAvailableChanged(bool)),
            this, SLOT(onVideoAvailabilityChanged(bool)));

    QObject::connect(playlist, SIGNAL(currentMediaChanged(const QMediaContent &)),
            this, SLOT(onCurrentMediaChanged(const QMediaContent&)));

    QObject::connect(progressMedia, SIGNAL(timelineChanged(qint64)),
                     this, SLOT(mediaTimelineChanged(qint64)));

    QObject::connect(volumeWidget, SIGNAL(volumeChanged(int)),
                     this, SLOT(changeVolume(int)));

    QObject::connect(comboBLyrics, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(comboBLyricsChanged(int)));

    QObject::connect(ui->actionAbout_App, SIGNAL(triggered()),
                     this, SLOT(triggeredAboutApp()));

    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered()),
                     this, SLOT(triggeredAboutQt()));
}


void MainWindow::triggeredAboutApp(){
    QString title("About WavePlayer");
    QString appName = QCoreApplication::applicationName();
    QString appVersion = QCoreApplication::applicationVersion();
    //QString buildDate = QCoreApplication::application();

    QString text;
    text = text + appName + "\n\n" + "Version " + appVersion + "\n" + appName + " is a media player that searches music lyrics on internet.";


    QMessageBox::about(this, title, text);
};


void MainWindow::triggeredAboutQt(){
    QString title("About Qt");
    QMessageBox::aboutQt(this, title);
};


void MainWindow::clickedBrowse(){
    /*
    QDir directory = QFileDialog::getExistingDirectory(this, "Select Directory");
    QString folder_path = directory.path();
    QStringList files = directory.entryList((QStringList() << "*.mp3", QDir::Files));
    */

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory("~/Documents/");

    if (dialog.exec()){
        QDir directory = dialog.directory();
        QString folder_path = directory.path();
        QStringList files = directory.entryList((QStringList() << "*.*", QDir::Files));

        ui->lineBrowse->setText(folder_path);

        // Update media list
        ui->listWMedia->clear();
        playlist->clear();

        for (auto &file:files){
            std::cout << (QString("file:///") + folder_path + QString("/") + file).toStdString() << std::endl;;
            ui->listWMedia->addItem(file);
            mediaList.push_back(folder_path + file);

            playlist->addMedia(QUrl::fromLocalFile(folder_path + QString("/") + file));
            currentMediaID = 0;
        }
        for(int i=0; i<playlist->mediaCount(); i++){
            std::cout << playlist->media(i).request().url().toString().toStdString() << std::endl;
        }
    }
};


void MainWindow::clickedMediaItem(QListWidgetItem *item){
    currentMediaID = ui->listWMedia->row(item);

    std::cout << item->text().toStdString() << std::endl;
};


void MainWindow::clickedDoubleMediaItem(QListWidgetItem *item){
    currentMediaID = ui->listWMedia->row(item);
    this->playMedia();
}


void MainWindow::clickedPlay(){
    if (!ui->pushPlay->isChecked()){
        QIcon iconPlay(urlPlay);
        ui->pushPlay->setIcon(iconPlay);
        ui->pushPlay->setToolTip("Play");
        this->pauseMedia();
    }
    else{
        QIcon iconPause(urlPause);
        ui->pushPlay->setIcon(iconPause);
        ui->pushPlay->setToolTip("Stop");
        this->playMedia();
    }
};


void MainWindow::clickedNext(){
    nextMedia();
};


void MainWindow::clickedPrev(){
    prevMedia();
};


void MainWindow::toggledShuffle(bool isToggled){
    ui->buttonRepeat->setChecked(!isToggled);
    isShuffled = isToggled;
    isRepeat = !isToggled;
}


void MainWindow::toggledRepeat(bool isToggled){
    ui->buttonShuffle->setChecked(!isToggled);
    isShuffled = !isToggled;
    isRepeat = isToggled;
}


void MainWindow::mediaDurationChanged(qint64 currentDuration_ms){
    std::cout << "Current Duration: " << currentDuration_ms/1000 << std::endl;
    int currentDuration = currentDuration_ms / 1000;  // Convert ms to seconds
    int minute = ((int)currentDuration) / 60;
    int second = ((int)currentDuration) % 60;
    QString text = QString::number(minute) + QString(":") + QString::number(second);
    ui->labelMediaTotalDuration->setText(text);

    progressMedia->setMinimum(0);
    progressMedia->setMaximum(currentDuration_ms);

};


void MainWindow::mediaPositionChanged(qint64 position){
    qint64 position_sec = position / 1000;  // Convert ms to seconds
    int minute = ((int)position_sec) / 60;
    int second = ((int)position_sec) % 60;
    QString text = QString::number(minute) + QString(":") + QStringLiteral("%1").arg(second, 2, 10, QLatin1Char('0'));
    ui->labelMediaElapsedTime->setText(text);

    qint64 mediaTotalDuration = player->duration();

    if (mediaTotalDuration==0){
        progressMedia->setValue(0);
    }
    else{
        //qDebug() << QString("Progress: ") << ((double)position/(double)mediaTotalDuration)*100;
        progressMedia->setValue(position);
    }
}


void MainWindow::onMediaError(QMediaPlayer::Error error){
    stopMedia();
    QUrl url( playlist->media(currentMediaID).request().url().toString());

    QString message = QString("Error: ") + url.fileName() + QString(" - ") + QString(error);
    ui->statusbar->showMessage(message);
};


void MainWindow::onMediaStateChanged(QMediaPlayer::State state){
    std::cout << "Media State Changed:" << state << std::endl;
    if (state == 0 && ui->pushPlay->isChecked()){
        if (!isRepeat){
            // Move to next media in the list
            currentMediaID ++;
        }

        if (currentMediaID >= playlist->mediaCount()){
            currentMediaID = 0;
        }

        QIcon iconPlay(urlPlay);
        ui->pushPlay->setIcon(iconPlay);
        ui->pushPlay->setToolTip("Play");

        playlist->setCurrentIndex(currentMediaID);
        player->play();
    }
    else if(state == 1){
        QIcon iconPause(urlPause);
        ui->pushPlay->setIcon(iconPause);
        ui->pushPlay->setToolTip("Stop");

    }
    else{}

};


void MainWindow::onCurrentMediaChanged(const QMediaContent &content){
    QUrl url(content.request().url().toString());


    QString message = QString("Playing: ") + url.fileName();
    ui->statusbar->showMessage(message);

    ui->listWMedia->selectionModel()->selectedRows(currentMediaID);

    comboBLyrics->clear();
    textLyrics->clear();

};


void MainWindow::onVideoAvailabilityChanged(bool isAvailable){

    if (isAvailable){
        ui->stackedPlayer->setCurrentIndex(0);  // VideoViewer
    }
    else{
        ui->stackedPlayer->setCurrentIndex(1);  // LyricViewer
        QString keywords = player->currentMedia().request().url().fileName();
        searchLyrics(keywords);
    }
    is_playing = true;
};


void MainWindow::mediaTimelineChanged(qint64 mediaPosition){
    if (currentMediaID >= 0){
        player->setPosition(mediaPosition);
    }
};


void MainWindow::changeVolume(int volume){
    qDebug() << "Volume Changed: " << volume;
    player->setVolume(volume);
}


void MainWindow::comboBLyricsChanged(int index){
    qInfo() << "comboBLyricsChanged: " << index;
    QString url = comboBLyrics->currentData().toString();
    getLyrics(url);
}


void MainWindow::playMedia(){
    if (currentMediaID >= 0 || true)
        {
            progressMedia->setEnabled(true);

            if (isShuffled){
                std::random_device rand_dev;
                std::mt19937 rng(rand_dev());
                std::uniform_int_distribution<int> uni(0, playlist->mediaCount()-1);
                currentMediaID = uni(rng);
            }

            playlist->setCurrentIndex(currentMediaID);
            player->setVideoOutput(videoWidget);

            if (player->state() == 2){

            }
            else{
                player->setPosition(0);
            }

            player->play();
            std::cout << "Media playing... " << currentMediaID << std::endl;
            std::cout << player->mediaStatus() << std::endl;
            std::cout << player->state() << std::endl;
        }
    else{
        progressMedia->setEnabled(false);
        std::cout << "No media loaded" << std::endl;
    }

};


void MainWindow::stopMedia(){
    this->player->stop();
    is_playing = false;

    playlist->setCurrentIndex(currentMediaID);

    QUrl url(playlist->media(currentMediaID).request().url().toString());

    QString message = QString("Stopped: ") + url.fileName();
    ui->statusbar->showMessage(message);
};


void MainWindow::pauseMedia(){
    QUrl url(playlist->media(currentMediaID).request().url().toString());

    QString message = QString("Paused: ") + url.fileName();
    ui->statusbar->showMessage(message);
    player->pause();
};


void MainWindow::nextMedia(){
    if (currentMediaID < playlist->mediaCount()-1){
        if (!isRepeat){
            currentMediaID++;
        }
    }
    else{
        currentMediaID = 0;
    }
    playMedia();
};


void MainWindow::prevMedia(){
    if (currentMediaID > 0){
        if (!isRepeat){
            currentMediaID--;
        }
    }
    else{
        currentMediaID = playlist->mediaCount()-1;
    }
    playMedia();
};


void MainWindow::keywordCombiner(QStringList &keywords, QStringList &result, int iter){
    QStringList c_keywords = QStringList(keywords);
    if (iter > 0){
        keywords.removeAt(0);
    }
    int size = keywords.size();

    if (iter == size)
        return;

    for (int i=size-1; i>=0; i--){
        QString s;
        for (int j=keywords.size()-1; j>=0; j--){
            s = keywords.at(j) + " " + s;
        }
        keywords.removeAt(i);
        result.push_back(s);
    }
    iter += 1;

    keywordCombiner(c_keywords, result, iter);

};


void MainWindow::searchLyrics(QString keyword){
    qInfo() << "keyword: " << keyword;
    if (keyword.trimmed().isEmpty()) return;

    QStringList items = keyword.split('.');
    items.removeLast();

    QString fileName = items.join("");

    QRegExp separator("([.,-\\s]+)");
    QStringList keywords = fileName.split(separator, Qt::SkipEmptyParts);  //.split("\\ |\\-");
    QStringList args;
    qInfo() << "keywords: " << keywords;

    if (keywords.size() > 1){
        keywordCombiner(keywords, args, 0);
        // Remove duplicate charaters
        args.removeDuplicates();
        // Sort arguments from longest to shortest word order
        std::sort(args.begin(), args.end(),  [](const QString& a, const QString& b) -> bool
        {
            return a.size() > b.size();
        });
    }
    else{
        args = keywords;
    }

    qInfo() << "Combination: " << args;

    if (process == nullptr){
        process = new QProcess(nullptr);
    }

    QString script_path = QApplication::applicationDirPath() + "/3rdParty/lyrics.py";

    QFile file(script_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    connect(process, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    connect(process, SIGNAL(finished(int)), this, SLOT(processFinished(int)));

    QString keywords2 = "gripin yalnızlığın";

    qInfo() << "start process: " << "python" << " " << (QStringList() << script_path << args);

    process->start("python", QStringList() << script_path
                                           << args);
};


void MainWindow::processReadyRead(){
    qInfo() << "processReadyRead";
    QString strReply = static_cast<QString>(process->readAll());
    qInfo() << "strReply: " << strReply;

    lastLyricList.clear();
    // strReply.replace("'", "\"");
      QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
      QJsonArray jsonArray = jsonResponse.array();

      if (jsonArray.count() > 0) {

        foreach (const QJsonValue &value, jsonArray) {
          QJsonObject obj = value.toObject();
          QString id = obj.value("song_id").toString();
          QString url = obj.value("song_url").toString();
          QString artist = obj.value("song_artist").toString();
          QString title = obj.value("song_name").toString();
          QStringList item;
          item << id << url << artist << title;
          lastLyricList.append(item);

          comboBLyrics->addItem(title + " - " + artist, url);
        }
      }
      else {

      }
};

void MainWindow::processFinished(int exitCode){
    qInfo() << "ProcessFinished: " << exitCode;
    if(process != nullptr) process->deleteLater();
    process = nullptr;
    Q_UNUSED(exitCode);
};

void MainWindow::getLyrics(QString url){
    QNetworkAccessManager *m_netwManager = new QNetworkAccessManager(this);
    connect(m_netwManager, SIGNAL(finished(QNetworkReply *)), this,
              SLOT(netwManagerFinished(QNetworkReply *)));
    QNetworkRequest request((QUrl(url)));

    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) "
                                         "AppleWebKit/537.36 (KHTML, like Gecko) "
                                         "Chrome/73.0.3683.103 Safari/537.36");
      m_netwManager->get(request);
};

void MainWindow::netwManagerFinished(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (v >= 200 && v < 300) // Success
        {
          QString html = reply->readAll();

          QString lyric;
          QStringList divs = html.split("<div>");
          for (auto &div:divs){
              if(div.contains("<!-- Usage of azlyrics.com content by any third-party lyrics provider is prohibited by our licensing agreement. Sorry about that. -->\r\n")){

                  lyric = div.split("</div>").at(0);
                  break;
              }
          }
          textLyrics->setHtml("<center>" +
                              lyric +
                              "</center>");

          //qInfo() << "lyric: "  << lyric;

        } else if (v >= 300 && v < 400) // Redirection
        {
          QUrl newUrl =
              reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
          newUrl = reply->url().resolved(newUrl);
          qDebug() << "request redirected to new url" << newUrl;

          QNetworkAccessManager *manager = new QNetworkAccessManager();
          connect(manager, SIGNAL(finished(QNetworkReply *)), this,
                  SLOT(netwManagerFinished(QNetworkReply *)));
          QNetworkRequest request((QUrl(newUrl)));
          request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) "
                                             "AppleWebKit/537.36 (KHTML, like "
                                             "Gecko) Chrome/73.0.3683.103 "
                                             "Safari/537.36");
          manager->get(request);
        }
      } else {
        qDebug() << reply->errorString();
      }
}
