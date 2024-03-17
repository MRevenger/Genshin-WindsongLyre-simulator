#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(QSize(1024, 600));
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground, true);//设置窗口背景透明
    pressed = false;
    // 设置按钮样式
    closeBtn = new QPushButton(this); closeBtn->setGeometry(QRect(960, 64, 50, 50)); closeBtn->setStyleSheet(QString("background-color: white; border-radius: 25px; border-style: outset; border: 2px solid transparent; font-size: 32px; color: brown;")); closeBtn->setText("✕");
    minBtn = new QPushButton(this); minBtn->setGeometry(QRect(890, 64, 50, 50)); minBtn->setStyleSheet(QString("background-color: white; border-radius: 25px; border-style: outset; border: 2px solid transparent; font-size: 32px; color: brown;")); minBtn->setText("一");
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeBtn_clicked())); connect(minBtn, SIGNAL(clicked()), this, SLOT(minBtn_clicked()));

    // SoundPlayer相关
    player = new SoundPlayer();
    connect(this, SIGNAL(keyPressed(char)), player, SLOT(on_keyPressed(char)));
    connect(this, SIGNAL(keyReleased(char)), player, SLOT(on_keyReleased(char)));
    QThread* thread_player = new QThread;
    player->moveToThread(thread_player);
    thread_player->start();
    // Button相关
    btn.resize(21, nullptr);
    int gap = 120, startX = 120, startY = 150, width = 124, height = 124, sz = 124;
    for(int i = 0; i < 21; ++i) {
        btn[i] = new Button(this, i, sz);
        btn[i]->setGeometry(i % 7 * gap + startX, i / 7 * gap + startY, width, height);
        // 按键动画
        connect(this, SIGNAL(keyPressed(char)), btn[i], SLOT(pressed(char)));
        connect(this, SIGNAL(keyReleased(char)), btn[i], SLOT(released(char)));
        // 鼠标点击
        connect(btn[i], SIGNAL(sgnPressed(char)), player, SLOT(on_keyPressed(char)));
        connect(btn[i], SIGNAL(sgnReleased(char)), player, SLOT(on_keyReleased(char)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(!event->isAutoRepeat()) {
        int key = event->key();
        emit this->keyPressed(key);

    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if(!event->isAutoRepeat()) {
        int key = event->key();
        emit this->keyReleased(key);
    }
}

void MainWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    // 绘制背景图
    QPainter painter(this);
    QPixmap bg(QString(":/res/picture/bg.png"));
    bg.scaled(this->size());
    painter.drawPixmap(0, 0, bg);
}
void MainWindow::mousePressEvent(QMouseEvent* event) {
    if(event->pos().y() < 100) {
        pre = QCursor::pos();
        pressed = true;
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    if(pressed && event->pos().y() < 100) {
        // 鼠标在距离窗口上方100px内时可以拖动窗口
        // 记录点击时的坐标，减去当前坐标即为移动的距离
        QPoint now = QCursor::pos();
        QPoint delta = now - pre;
        move(this->pos() + delta);
        pre = now;
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    pressed = false;
}

// 槽函数
void MainWindow::closeBtn_clicked() {
    this->close();
}
void MainWindow::minBtn_clicked() {
    this->setWindowState(Qt::WindowMinimized);
}
