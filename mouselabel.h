#ifndef MOUSELABEL_H
#define MOUSELABEL_H

#include <QLabel>
#include <QMouseEvent>

class mouseLabel : public QLabel
{
    Q_OBJECT

public:
    mouseLabel(QWidget* parent = 0);


signals:
    void mousePressed(QMouseEvent *event);

public slots:
    void mousePressEvent(QMouseEvent *event);

};

#endif // MOUSELABEL_H
