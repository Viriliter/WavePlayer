# WavePlayer
This project is about to create a desktop media player using Qt framework. It features to show music lyric of your music contents. It consists of a python script that requests for the music lyrics from azlyrics.com.

![WavePlayer](./resources/logo.png?raw=true "WavePlayer")

## Preview
UI of the program is as follows:

![ScreenShot1](./screenshots/ss1.png?raw=true "ScreenShot1")
![ScreenShot2](./screenshots/ss1.png?raw=true "ScreenShot1")
![ScreenShot3](./screenshots/ss1.png?raw=true "ScreenShot1")
![ScreenShot4](./screenshots/ss1.png?raw=true "ScreenShot1")

## Dependencies
* MinGW32 8.1
* Qt 5.15.2
* K-Lite Codec Pack (for playing content)
* Python 3.7 or above


## Installation
```
git clone https://github.com/Viriliter/WavePlayer.git
```

## Known Issues
* azlyrics.com may block the ip address after some lyric search. Restarting the router is necessary if you are using dynamic IP.
* Web scraping is very costly operation so loading time of the lyrics is high. 
* Random media playing is not working.
