#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define eps 1e-9

#include <ctime>
#include <QMainWindow>
#include <QLabel>
#include <QSet>
#include <QKeyEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <stdexcept>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QComboBox>
#include <iostream>
#include <set>
#include <QPoint>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QRubberBand>
#include <stack>
#include "Complex.h"

struct state {
    double start_p, step_p, start_q, step_q;

    state() {
        start_p = 2.5;
        step_p = step_q = 0.004;
        start_q = -2;
    }

    state(double a, double b, double c, double d) {
        start_p = a;
        step_p = b;
        start_q = c;
        step_q = d;
    }

    bool operator==(const state &other) {
        return fabs(start_p - other.start_p) < eps &&
               fabs(step_p - other.step_p) < eps &&
               fabs(start_q - other.start_q) < eps &&
               fabs(step_q - other.step_q) < eps;
    }
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QImage *mainScene;

    int mandelbrot(Complex c);

    QRubberBand *selection;
    QPoint start = {0, 0}, end = {1000, 1000};
    QColor color[1000];
    bool changeImage = true, isQuit = false;
    double step_p = 0.004, step_q = 0.004, start_p = -2.5, start_q = -2;
    std::stack<state> states;
    state start_state;

signals:
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event);
};

#endif