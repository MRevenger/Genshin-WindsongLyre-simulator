#ifndef BUTTON_H
#define BUTTON_H
#include <QPushButton>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QSvgRenderer>
class Button: public QPushButton
{
    Q_OBJECT
signals:
    void sgnPressed(char);
    void sgnReleased(char);
public:
    Button(QWidget*, int _noteType, int _sz);
    char keys[21] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
    QString key[7] = {"do", "re", "mi", "fa", "so", "la", "ti"};
    QPixmap* cs_down;
    QPixmap* cs;
    QPixmap* note;
    QPixmap* animation;
    bool isPressed;
    int noteType, sz;
    QRect animationRect;
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
protected slots:
    void pressed(char);
    void released(char);
};

#endif // BUTTON_H
