#include "docwindow.h"

DocWindow::DocWindow(QWidget* pwgt) : QTextEdit(pwgt)
{
    make_saved();
    connect(this, SIGNAL(textChanged()), this, SLOT(slot_text_changed()));
    myHighlighter = new SyntaxHighlighter(this->document());
}

// FUNCTIONS

const QString DocWindow::get_file_name() {
    return m_strFileName;
}

bool DocWindow::was_saved() {
    return saved;
}

void DocWindow::make_saved() {
    saved = true;
    emit change_tab_title();
}

// SLOTS

bool DocWindow::slot_load() {
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) {
        return false;
    }

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
        m_strFileName = fileName;
//        emit changeWindowTitle(m_strFileName);
        QString extention = fileName.split(".").last();
        delete myHighlighter;
        myHighlighter = new SyntaxHighlighter(this->document(), extention);
        make_saved();
    }
    else {
        QMessageBox* file_not_open_box =
                new QMessageBox(QMessageBox::Critical,
                                "Ошибка открытия файла",
                                "Не удалось открыть файл <b>\"" + fileName.split(".").last() + "\"</b>!",
                                QMessageBox::Ok);
        file_not_open_box->exec();
        delete file_not_open_box;
    }
    return true;
}

bool DocWindow::slot_save() {
    if (m_strFileName.isEmpty()){
        return slot_save_as();
    }

    QFile file(m_strFileName);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream(&file) << toPlainText();
        file.close();
        make_saved();
    }
    else {
        QMessageBox* file_not_saved_box =
                new QMessageBox(QMessageBox::Critical,
                                "Ошибка сохранения файла",
                                "Не удалось сохранить файл <b>\"" + m_strFileName.split(".").last() + "\"</b>!",
                                QMessageBox::Ok);
        file_not_saved_box->exec();
        delete file_not_saved_box;
    }

    return true;
}

bool DocWindow::slot_save_as(){
    QString fileName = QFileDialog::getSaveFileName(this, m_strFileName,
                                                    m_strFileName,
                                                    "*."+m_strFileName.split(".").last()+";;All files (*.*)");
    if (!fileName.isEmpty()){
        m_strFileName = fileName;
        slot_save();
        QString extention = fileName.split(".").last();
        delete myHighlighter;
        myHighlighter = new SyntaxHighlighter(this->document(), extention);
        make_saved();
        return true;
    }
    return false;
}

void DocWindow::slot_text_changed() {
    saved = false;
    emit change_tab_title();
}

void DocWindow::slot_open_file(const QString& name) {
    QFile file(name);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
        m_strFileName = name;
//        emit changeWindowTitle(m_strFileName);
        QString extention = name.split(".").last();
        delete myHighlighter;
        myHighlighter = new SyntaxHighlighter(this->document(), extention);
        make_saved();
    }
    else {
        QMessageBox* file_not_open_box =
                new QMessageBox(QMessageBox::Critical,
                                "Ошибка открытия файла",
                                "Не удалось открыть файл <b>\"" + name.split(".").last() + "\"</b>!",
                                QMessageBox::Ok);
        file_not_open_box->exec();
        delete file_not_open_box;
    }
}
