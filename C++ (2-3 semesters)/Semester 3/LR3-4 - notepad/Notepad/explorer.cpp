#include "explorer.h"

Explorer::Explorer(QWidget* pwgt) : QDockWidget(pwgt)
{
    file_model = new QFileSystemModel;
    QTreeView* tree_view = new QTreeView;
    file_model->setRootPath(QDir::rootPath());
    tree_view->setModel(file_model);
    tree_view->setColumnWidth(0,200);
    setWidget(tree_view);

    connect(tree_view, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slot_double_clicked(const QModelIndex&)));
}

void Explorer::slot_double_clicked(const QModelIndex& index) {
    if (!file_model->fileInfo(index).isDir()) {
        QString fileName = file_model->filePath(index);
        emit file_selected(fileName);
    }
}
