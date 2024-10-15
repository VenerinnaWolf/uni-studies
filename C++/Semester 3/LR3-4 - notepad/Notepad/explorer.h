#ifndef EXPLORER_H
#define EXPLORER_H

#include <QtWidgets>

class Explorer : public QDockWidget
{
    Q_OBJECT
private:
    QFileSystemModel* file_model;

public:
    Explorer(QWidget* pwgt = 0);

signals:
    void file_selected(QString);

public slots:
    void slot_double_clicked(const QModelIndex&);
};

#endif // EXPLORER_H
