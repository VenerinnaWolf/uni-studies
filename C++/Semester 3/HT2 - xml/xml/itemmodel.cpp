#include "itemmodel.h"

ItemModel::ItemModel(QObject *parent) : QStandardItemModel(parent)
{
}

// FUNCTIONS

void ItemModel::error_happened(const QString& error) {
    QMessageBox* error_box = new QMessageBox (
                QMessageBox::Critical,
                "Critical error",
                error,
                QMessageBox::Ok);
    error_box->exec();
    delete error_box;
}

void ItemModel::set_active_index(const QModelIndex& new_index) {
    active_index = new_index;
}

void ItemModel::set_clicked_index(const QModelIndex& new_index) {
    clicked_index = new_index;
}

void ItemModel::add_new_file(const QString& fileName) {
    QFile file(fileName);
    QDomDocument domDocument;

    if (file.open(QIODevice::ReadOnly)) {
        if (domDocument.setContent(&file)) {
            QDomElement element = domDocument.documentElement();
            QStandardItem* item = new QStandardItem(fileName.split("/").last());
            appendRow(item);
            if (!active_index.isValid()) {
                clicked_index = index(0,0);
                slotMakeActive();
            }
            add_element(element, item);
        }
        else {
            error_happened("Ошибка парсинга файла " + fileName.split("/").last());
        }

        file.close();
    }
    else {
        error_happened("Не удалось открыть файл " + fileName.split("/").last());
    }
}

void ItemModel::add_element(const QDomNode& parent, QStandardItem* item) {
    QDomNode node = parent.firstChild();
    while (!node.isNull()){
        QStandardItem* subItem = new QStandardItem(node.toElement().tagName());
        if (node.isText())
            item->appendRow(new QStandardItem(node.toText().data()));
        else {
            item->appendRow(subItem);
            add_element(node, subItem);
        }
        node = node.nextSibling();
    }
}

// SLOTS

void ItemModel::slot_open_file() {
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) {
        return;
    }
    add_new_file(fileName);
}

void ItemModel::slotMakeActive() {
    QFont font;
    font.setBold(false);
    if (active_index.isValid()) itemFromIndex(active_index)->setFont(font);
    font.setBold(true);
    itemFromIndex(clicked_index)->setFont(font);
    active_index = clicked_index;
}

void ItemModel::slot_close_all() {
    this->clear();
}

//void ItemModel::slot_close_all() {
//    clear();
//}
