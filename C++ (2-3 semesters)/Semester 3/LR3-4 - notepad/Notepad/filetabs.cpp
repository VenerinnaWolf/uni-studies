#include "filetabs.h"

FileTabs::FileTabs(QWidget* pwgt) : QTabWidget(pwgt)
{
    setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_close(int)));
    slot_create_new();
}

void FileTabs::save_with_delay(DocWindow* cur_doc) {
    QTimer::singleShot(10, cur_doc, SLOT(make_saved()));
}

void FileTabs::update_file_list() {
    opened_files.clear();
    for (int i = 0; i < count(); ++i) {
        opened_files.push_back(tabText(i));
    }
    emit list_changed(opened_files);
}

// FILE SLOTS

void FileTabs::slot_create_new() {
    DocWindow* doc_window = new DocWindow;
    int cur_index = addTab(doc_window, new_tab_name);
    setCurrentIndex(cur_index);
    connect(doc_window, SIGNAL(change_tab_title()),
            this, SLOT(slot_change_tab_name()));
    update_file_list();
}

void FileTabs::slot_load() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    if (cur_doc->get_file_name().isEmpty() && cur_doc->toPlainText().isEmpty()) {
        if (cur_doc->slot_load()) {
            QString fileName = cur_doc->get_file_name().split("/").last();
//            setTabText(currentIndex(), fileName);
            slot_change_tab_name();
            save_with_delay(cur_doc);
        }
    }
    else {
        cur_doc = new DocWindow;
        if (cur_doc->slot_load()) {
            QString fileName = cur_doc->get_file_name().split("/").last();
            int cur_index = addTab(cur_doc, fileName);
            setCurrentIndex(cur_index);
            connect(cur_doc, SIGNAL(change_tab_title()),
                    this, SLOT(slot_change_tab_name()));
            save_with_delay(cur_doc);
        }
    }
    update_file_list();
}

void FileTabs::slot_save() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    if (cur_doc->slot_save()) {
        QString fileName = cur_doc->get_file_name().split("/").last();
//        setTabText(currentIndex(), fileName);
        slot_change_tab_name();
        save_with_delay(cur_doc);
    }
}

void FileTabs::slot_save_as() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    if (cur_doc->slot_save_as()) {
        QString fileName = cur_doc->get_file_name().split("/").last();
//        setTabText(currentIndex(), fileName);
        slot_change_tab_name();
        save_with_delay(cur_doc);
    }
    update_file_list();
}

void FileTabs::slot_save_all() {
    for (int i = 0; i < count(); ++i) {
        setCurrentIndex(i);
        slot_save();
    }
}

bool FileTabs::slot_close() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    if (!cur_doc->was_saved()) {
        QMessageBox* save_before_exit_box =
                new QMessageBox(QMessageBox::Warning,
                                "Файл был изменен",
                                "Сохранить <b>\"" + tabText(currentIndex()) + "\"</b> перед закрытием?",
                                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int answer = save_before_exit_box->exec();
        delete save_before_exit_box;

        if (answer == QMessageBox::Yes) {
            slot_save();
        }
        else if (answer == QMessageBox::Cancel) {
            return false;
        }
    }
    removeTab(currentIndex());
    if (currentIndex() == -1) {
        slot_create_new();
        return false;
    }
    update_file_list();
    return true;
}

void FileTabs::slot_close(int tab_index){
    int cur_index = currentIndex();
    setCurrentIndex(tab_index);
    slot_close();
    if (tab_index < cur_index) setCurrentIndex(cur_index-1);
    else setCurrentIndex(cur_index);
}

void FileTabs::slot_close_all() {
    while (currentIndex() != -1){
        if (!slot_close()) break;
    }
}

void FileTabs::slot_quit() {
    slot_close_all();
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    if (cur_doc->get_file_name().isEmpty() && cur_doc->toPlainText().isEmpty()) {
        qApp->quit();
    }
}

// EDIT SLOTS

void FileTabs::slot_cut() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    cur_doc->cut();
}
void FileTabs::slot_copy() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    cur_doc->copy();
}
void FileTabs::slot_paste(){
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    cur_doc->paste();
}
void FileTabs::slot_delete(){
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    cur_doc->textCursor().removeSelectedText();
}
void FileTabs::slot_select_all(){
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    cur_doc->selectAll();
}

// FOR EXPLORER

void FileTabs::slot_open_file(QString name) {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    if (cur_doc->get_file_name().isEmpty() && cur_doc->toPlainText().isEmpty()) {
        cur_doc->slot_open_file(name);
        QString fileName = name.split("/").last();
        setTabText(currentIndex(), fileName);
        save_with_delay(cur_doc);
    }
    else {
        cur_doc = new DocWindow;
        cur_doc->slot_open_file(name);
        QString fileName = name.split("/").last();
        int cur_index = addTab(cur_doc, fileName);
        setCurrentIndex(cur_index);
        connect(cur_doc, SIGNAL(change_tab_title()),
                this, SLOT(slot_change_tab_name()));
        save_with_delay(cur_doc);
    }
    update_file_list();
}

void FileTabs::slot_change_tab(int index) {
    setCurrentIndex(index);
}

// OTHER SLOTS

void FileTabs::slot_change_tab_name() {
    DocWindow* cur_doc = ((DocWindow*)currentWidget());
    QString tabName = cur_doc->get_file_name().split("/").last();
    if (tabName.isEmpty()) tabName = new_tab_name;
    if (!cur_doc->was_saved()) {
        tabName += "*";
    }
    setTabText(currentIndex(), tabName);
    update_file_list();
}
