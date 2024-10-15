#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,400);
    model = new ItemModel;
    treeView = new TreeView(model);

    setCentralWidget(treeView);

    QMenu* file_menu = new QMenu("Файл");
    file_menu->addAction("Открыть файл", model, SLOT(slot_open_file()), QKeySequence("CTRL+O"));
    file_menu->addAction("Закрыть все", model, SLOT(slot_close_all()), QKeySequence("CTRL+SHIFT+W"));
    file_menu->addAction("Выход", qApp, SLOT(quit()), QKeySequence("CTRL+Q"));

    menuBar()->addMenu(file_menu);
}

MainWindow::~MainWindow()
{
}

