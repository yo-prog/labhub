/*#include "timelinescene.h"

QGraphicsScene* TimelineScene::addEvent(QDateTime startTime, QDateTime endTime)
{
    QGraphicsScene* scene = new QGraphicsScene();
    // Calculate the position and size of the rectangle based on the start and end times
    qreal x = startTime.toMSecsSinceEpoch();
    qreal y = 0;
    qreal width = endTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();
    qreal height = 50; // Or whatever size you want the rectangles to be

    // Create the rectangle item
    QGraphicsRectItem* rect = new QGraphicsRectItem(80, 120, 200, 10);
    rect->setBrush(QBrush(Qt::red)); // Or whatever color you want
    // Add the rectangle item to the scene
    scene->addItem(rect);
    return scene;
    printf("true");
}*/

