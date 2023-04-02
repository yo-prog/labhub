#ifndef TIMELINE_H
#define TIMELINE_H

#include <QDialog>
#include <QGraphicsScene>
namespace Ui {
class timeline;
}

class timeline : public QDialog
{
    Q_OBJECT

public:
    explicit timeline(QWidget *parent = nullptr);
    ~timeline();
    void addEvent(QDateTime startTime, QDateTime endTime);

private slots:
    void on_AddEvent_clicked();

private:
    Ui::timeline *ui;
};

#endif // TIMELINE_H
