#pragma once

#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include <QDomDocument>
#include <QtWidgets>

class ItemModel : public QStandardItemModel
{
    Q_OBJECT
private:
    QModelIndex active_index;
    QModelIndex clicked_index;

    void add_new_file(const QString&);
    void add_element(const QDomNode&, QStandardItem*);
    void error_happened(const QString&);
    void set_active_index(const QModelIndex& new_index);

public:
    explicit ItemModel(QObject *parent = nullptr);

    void set_clicked_index(const QModelIndex& new_index);

public slots:
    void slot_open_file();
    void slot_close_all();
    void slotMakeActive();
};

#endif // ITEMMODEL_H
