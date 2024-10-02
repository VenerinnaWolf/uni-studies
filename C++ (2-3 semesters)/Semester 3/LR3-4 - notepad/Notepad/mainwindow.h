#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include "filetabs.h"
#include "explorer.h"
#include "docviewer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Explorer* explorer;
    DocViewer* docViewer;
    FileTabs* tab;
public:
    MainWindow(QWidget* parent = 0);
    virtual void closeEvent(QCloseEvent* event);

public slots:
    void slotChangeWindowTitle(const QString&);
};
#endif // MAINWINDOW_H
