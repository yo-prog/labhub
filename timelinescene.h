#ifndef TIMELINESCENE_H
#define TIMELINESCENE_H
#include <QDateTime>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class TimelineScene
{
public:
    TimelineScene();

   QGraphicsScene* addEvent(QDateTime startTime, QDateTime endTime);
};

#endif // TIMELINESCENE_H
