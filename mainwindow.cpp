#include "mainwindow.h"

#define N 1000
#define M 1000

int field[1013][1013];
int ITERATIONS = 300, INF_BORDER = 10;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setFixedSize(N, M);
    setWindowTitle(QString("Mandelbrot"));
    selection = new QRubberBand(QRubberBand::Rectangle, this);
    mainScene = new QImage(N, M, QImage::Format_RGB32);
    for (int i = 0, j = 1; j <= ITERATIONS; i+=3, ++j) {
        if (i <= 217) {
            color[j] = QColor::fromHsl(i, 250, 107).name();
        } else {
            color[j] = color[j - 1];
        }
    }
    color[0] = color[1];
    start_state = state();
    states.push(start_state);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    start = event->pos();
    changeImage = false;
    selection->setGeometry((QRect(start, start)).normalized());
    selection->show();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    selection->setGeometry((QRect(start,event->pos())).normalized());
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    selection->hide();
    end = event->pos();
    changeImage = true;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->text() == "q" && states.size() > 2) {
        if (states.top() == start_state)
            return;
        states.pop();
        isQuit = true;
        update();
    }
}

int MainWindow::mandelbrot(Complex c) {
    auto z = Complex(0, 0);
    int i;
    for (i = 0; i < ITERATIONS; ++i) {
        z = z * z + c;
        if (fabs(z) > INF_BORDER) {
            break;
        }
    }
    return i;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (changeImage) {
        QPoint p1 = QPoint(std::min(start.x(), end.x()), std::min(start.y(), end.y()));
        QPoint p2 = QPoint(std::max(start.x(), end.x()), std::max(start.y(), end.y()));
        double side = std::min(p2.x() - p1.x(), p2.y() - p1.y());
        p2 = QPoint(p1.x() + side, p1.y() + side);
        if (!isQuit) {
            start_p = start_p + p1.x() * step_p, start_q = start_q + p1.y() * step_q;
            step_p = step_p * (p2.x() - p1.x()) / 1000, step_q = step_q * (p2.y() - p1.y()) / 1000;
            auto cur_state = state(start_p, step_p, start_q, step_q);
            if (cur_state == states.top()) {} else {
                states.push(cur_state);
            }
        } else {
            auto st = states.top();
            start_p = st.start_p, step_p = st.step_p;
            start_q = st.start_q, step_q = st.step_q;
            isQuit = false;
        }
        int i, j;
        double p, q;
        for (i = 0, p = start_p; i < N; i++, p += step_p) {
            for (j = 0, q = start_q; j < M; j++, q += step_q) {
                auto c = Complex(p, q);
                field[i][j] = mandelbrot(c);
            }
        }
        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
                mainScene->setPixelColor(i, j, color[field[i][j]].toRgb());
            }
        }
    } else {
        QMainWindow::paintEvent(event);
    }
    painter.drawImage(QPoint(0, 0), *mainScene);
}