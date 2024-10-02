#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "treeview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    TreeView* treeView;
    ItemModel* model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
