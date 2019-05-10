#include "mouselabel.h"

mouseLabel::mouseLabel(QWidget *parent) : QLabel(parent)
{

}

void mouseLabel::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

