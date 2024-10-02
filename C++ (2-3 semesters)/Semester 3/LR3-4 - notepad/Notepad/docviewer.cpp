#include "docviewer.h"

DocViewer::DocViewer(QWidget* pwgt) : QDockWidget(pwgt)
{
    file_model = new QStringListModel;
    QListView* list_view = new QListView;
    list_view->setModel(file_model);
    setWidget(list_view);

    connect(list_view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(slot_clicked(const QModelIndex&)));
}

void DocViewer::slot_clicked(const QModelIndex& index) {
    emit file_selected(index.row());
}

void DocViewer::slot_update_string_list(const QStringList& list){
    file_model->setStringList(list);
}
