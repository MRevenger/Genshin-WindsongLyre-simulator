#include "soundplayer.h"

SoundPlayer::SoundPlayer() {
    buffer.resize(21, nullptr);
    sound.resize(21, nullptr);
    for(int i = 0; i < 21; ++i) {
        mp[keys[i]] = i;
        isPlaying[keys[i]] = 0;
        loadBuffer(keys[i]);
    }
}


void SoundPlayer::loadBuffer(const char& key) {
    QFile file(QString(":/res/audio/").append(key).append(".wav"));
    file.open(QIODevice::ReadOnly);
    int _size = file.size();
    char* p = new char[_size];
    file.read(p, _size);
    buffer[mp[key]] = new sf::SoundBuffer;
    buffer[mp[key]]->loadFromMemory((void*)p, _size);
    sound[mp[key]] = new sf::Sound;
    sound[mp[key]]->setBuffer(*buffer[mp[key]]);
    file.close();
}

void SoundPlayer::playSound(const char& key) {
    if(!isPlaying[key]) sound[mp[key]]->play();
}


void SoundPlayer::on_keyPressed(char key) {
    if(this->mp.find(key) != this->mp.end()){
        this->playSound(key);
        this->isPlaying[key] = 1;
    }
}

void SoundPlayer::on_keyReleased(char key) {
    if(this->mp.find(key) != this->mp.end()){
        this->isPlaying[key] = 0;
    }
}
