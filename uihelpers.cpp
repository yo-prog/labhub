#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>

#include "uihelpers.h"

/*!
  Display an confirmation message box and ask what to do
   \param const String& message The message to dispay
   \return true if clicked yes
 */
bool showErrorsAndAskWhatToDo(const QString& message)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Attention !", message + "\n\nRééssayer ?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    return (reply == QMessageBox::No);
}

/*!
  Override a mouse event in our custom widget. Display a msg box to show today
   \param e The mouse event
 */
void ourCalendarWidget::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirmation", "Revenir à aujourd'hui ?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        this->showToday();
    }
}

