#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H
#include <SFML/Audio.hpp>
#include <QList>
#include <QFile>
#include <QMap>
#include <QObject>
// #include <QMainWindow> // for debug
class SoundPlayer: public QObject
{
    Q_OBJECT
public:
    SoundPlayer();
    QString path = ":/res/audio/";
    char keys[21] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
    QMap<char, int> mp, isPlaying;
    QList<sf::SoundBuffer*> buffer;
    QList<sf::Sound*> sound;

    void loadBuffer(const char& key);
    void playSound(const char&);
protected slots:
    void on_keyPressed(char);
    void on_keyReleased(char);
};

#endif // SOUNDPLAYER_H
