#pragma once

#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>

#include "syntaxhighlighter.h"

class DocWindow : public QTextEdit
{
    Q_OBJECT
private:
    QString m_strFileName;
    bool saved;
    SyntaxHighlighter* myHighlighter;

public:
    DocWindow(QWidget* pwgt = 0);
    const QString get_file_name();
    bool was_saved();

signals:
    void change_tab_title();

public slots:
    bool slot_load();
    bool slot_save();
    bool slot_save_as();
    void slot_text_changed();

    void slot_open_file(const QString&);

    void make_saved();
};
