#ifndef DOCVIEWER_H
#define DOCVIEWER_H

#include <QtWidgets>

class DocViewer: public QDockWidget
{
    Q_OBJECT
private:
    QStringListModel* file_model;

public:
    DocViewer(QWidget* pwgt = 0);

signals:
    void file_selected(int);

public slots:
    void slot_clicked(const QModelIndex&);
    void slot_update_string_list(const QStringList&);
};

#endif // DOCVIEWER_H
