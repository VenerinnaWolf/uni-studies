#include "treeview.h"

TreeView::TreeView()
{
}

TreeView::TreeView(ItemModel* treeModel) {
    model = treeModel;
    setModel(model);

    context_menu = new QMenu(this);
    context_menu->addAction("Сделать активным",
                            model,
                            SLOT(slotMakeActive()));
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_show_context_menu(QPoint)));
}

void TreeView::slot_show_context_menu(QPoint point) {
    QModelIndex index = this->indexAt(point);
    model->set_clicked_index(index);
    if (index.isValid() && !index.parent().isValid()){
        context_menu->exec(QCursor::pos());
    }
}
