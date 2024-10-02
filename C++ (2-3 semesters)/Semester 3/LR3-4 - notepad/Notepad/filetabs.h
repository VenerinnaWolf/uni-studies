#ifndef FILETABS_H
#define FILETABS_H

#include "docwindow.h"
#include <QtWidgets>

class FileTabs : public QTabWidget
{
    Q_OBJECT
private:
    QStringList opened_files;
    const QString new_tab_name = "Новый документ";

    void save_with_delay(DocWindow*);

public:
    FileTabs(QWidget* pwgt = 0);

    void update_file_list();

signals:
    void list_changed(const QStringList&);

public slots:
    void slot_create_new();
    void slot_load();
    void slot_save();
    void slot_save_as();
    void slot_save_all();
    bool slot_close();
    void slot_close(int);
    void slot_close_all();
    void slot_quit();

    void slot_cut();
    void slot_copy();
    void slot_paste();
    void slot_delete();
    void slot_select_all();

    void slot_open_file(QString);
    void slot_change_tab(int);
    void slot_change_tab_name();
};

#endif // FILETABS_H
