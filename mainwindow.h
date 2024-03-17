#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QThread>
#include "button.h"
#include <QMouseEvent>
#include "soundplayer.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void keyPressed(char); // 按下信号
    void keyReleased(char); // 松开信号
protected slots:
    void closeBtn_clicked(); // 点击关闭按钮
    void minBtn_clicked(); // 点击最小化按钮
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<Button*> btn;
    char keys[21] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U'};
    QPushButton* closeBtn, *minBtn;
    SoundPlayer *player;
    bool pressed; QPoint pre;


    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
