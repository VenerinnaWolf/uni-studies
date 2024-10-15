#pragma once

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include "itemmodel.h"

class TreeView : public QTreeView
{
    Q_OBJECT
private:
    QMenu* context_menu;
    ItemModel* model;

public:
    TreeView();
    TreeView(ItemModel*);

public slots:
    void slot_show_context_menu(QPoint);
};

#endif // TREEVIEW_H
