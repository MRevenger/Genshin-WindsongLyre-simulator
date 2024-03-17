#include "button.h"
Button::Button(QWidget* _parent, int _noteType, int _sz): QPushButton(_parent)  {
    this->noteType = _noteType, this->sz = _sz, this->isPressed = false;
    QPainter painter;
    // 加载SVG图
    QSvgRenderer render_up(QString(":/res/picture/cs.svg")); cs = new QPixmap(QSize(sz, sz)); cs->fill(Qt::transparent); // 加载常态背景图
    QSvgRenderer render_down(QString(":/res/picture/cs_down.svg")); cs_down = new QPixmap(QSize(sz, sz)); cs_down->fill(Qt::transparent); // 加载按下背景图
    QSvgRenderer render_note(QString(":/res/picture/").append(key[noteType % 7]).append(".svg")); note = new QPixmap(QSize(50, 50)); note->fill(Qt::transparent); // 加载音符
    // 渲染SVG图
    painter.begin(cs); painter.setRenderHint(QPainter::Antialiasing, true); painter.setRenderHint(QPainter::SmoothPixmapTransform, true); render_up.render(&painter); painter.end();
    painter.begin(cs_down); painter.setRenderHint(QPainter::Antialiasing, true); painter.setRenderHint(QPainter::SmoothPixmapTransform, true); render_down.render(&painter); painter.end();
    painter.begin(note); painter.setRenderHint(QPainter::Antialiasing, true); painter.setRenderHint(QPainter::SmoothPixmapTransform, true); render_note.render(&painter); painter.end();

    // 加载并渲染外围环的SVG图, 用于制作动画
    QSvgRenderer render_animation(QString(":/res/picture/animation.svg")); animation = new QPixmap(QSize(80, 80)); animation->fill(Qt::transparent);
    painter.begin(animation); painter.setRenderHint(QPainter::Antialiasing, true); painter.setRenderHint(QPainter::SmoothPixmapTransform, true); render_animation.render(&painter); painter.end();

    this->resize(cs->size());
    // 设置有效区域
    setMask(QBitmap(cs->mask()));
    animationRect = QRect(7, 9, 80, 80);
}

void Button::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // 绘制背景图
    if(!isPressed) painter.drawPixmap(0, 0, sz, sz, *cs);
    else painter.drawPixmap(0, 0, sz, sz, *cs_down);

    // 绘制外围环
    painter.drawPixmap(animationRect, *animation);
    // 绘制音符
    painter.drawPixmap(26, 27, 50, 50, *note);

    // 绘制音符字
    painter.setPen(QColor(164, 166, 120));
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(11);
    font.setBold(true);
    font.setItalic(false);
    painter.setFont(font);
    painter.drawText(QRect(24,47,44,50), Qt::AlignCenter, key[noteType % 7]);
}

void Button::mousePressEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    isPressed = true;
    update();
    emit sgnPressed(keys[noteType]); // 发送信号给SoundPlayer播放音频
}

void Button::mouseReleaseEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    isPressed = false;
    update();
    emit sgnReleased(keys[noteType]);
}

void Button::pressed(char key) {
    if(keys[noteType] == key) isPressed = true;
    update();
}
void Button::released(char key) {
    if(keys[noteType] == key) isPressed = false;
    update();
}
