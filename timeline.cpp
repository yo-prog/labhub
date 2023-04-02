/*#include "timeline.h"
#include "ui_timeline.h"
#include "timelinescene.h"

timeline::timeline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeline)
{
    ui->setupUi(this);
}

timeline::~timeline()
{
    delete ui;
}


void timeline::on_AddEvent_clicked()
{

    // Get the event data from the user input widgets
    QDateTime startTime = ui->m_startTimeEdit->dateTime();
    QDateTime endTime = ui->m_endTimeEdit->dateTime();
    //QString description = m_descriptionLineEdit->text();

    // Add the event to the timeline scene
    TimelineScene t;
    QGraphicsScene *scene=t.addEvent(startTime, endTime);
    ui->graphicsView->setScene(scene);



    // Add the rectangle item to the scene

}
*/
