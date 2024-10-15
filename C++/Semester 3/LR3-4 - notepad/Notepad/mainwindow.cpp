#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resize(1200,600);

    tab = new FileTabs;
    QToolBar* tool_bar = new QToolBar;

    QMenu* menu_file = new QMenu("&Файл");
    QMenu* menu_edit = new QMenu("&Правка");
    QMenu* menu_view = new QMenu("&Вид");

    explorer = new Explorer;
    addDockWidget(Qt::LeftDockWidgetArea, explorer);
    connect(explorer, SIGNAL(file_selected(QString)), tab, SLOT(slot_open_file(QString)));
    explorer->hide();

    QAction* action_show_explorer = new QAction("Show explorer action", 0);
    action_show_explorer->setText("Показать &проводник");
    action_show_explorer->setShortcut(QKeySequence("CTRL+E"));
    action_show_explorer->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    connect(action_show_explorer, SIGNAL(triggered()), explorer, SLOT(show()));
    menu_view->addAction(action_show_explorer);

    docViewer = new DocViewer;
    addDockWidget(Qt::RightDockWidgetArea, docViewer);
    connect(tab, SIGNAL(list_changed(const QStringList&)), docViewer, SLOT(slot_update_string_list(const QStringList&)));
    connect(docViewer, SIGNAL(file_selected(int)), tab, SLOT(slot_change_tab(int)));
    tab->update_file_list();
    docViewer->hide();

    QAction* action_show_docViewer = new QAction("Show docViewer action", 0);
    action_show_docViewer->setText("Показать &обозреватель открытых документов");
    action_show_docViewer->setShortcut(QKeySequence("CTRL+T"));
    action_show_docViewer->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView));
    connect(action_show_docViewer, SIGNAL(triggered()), docViewer, SLOT(show()));
    menu_view->addAction(action_show_docViewer);

    QAction* action_new = new QAction("New file action", 0);
    action_new->setText("&Новый");
    action_new->setShortcut(QKeySequence("CTRL+N"));
    action_new->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    connect(action_new, SIGNAL(triggered()), tab, SLOT(slot_create_new()));
    menu_file->addAction(action_new);
    tool_bar->addAction(action_new);

    QAction* action_load = new QAction("File load action", 0);
    action_load->setText("&Открыть...");
    action_load->setShortcut(QKeySequence("CTRL+O"));
    action_load->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    connect(action_load, SIGNAL(triggered()), tab, SLOT(slot_load()));
    menu_file->addAction(action_load);
    tool_bar->addAction(action_load);

    QAction* action_save = new QAction("File save action", 0);
    action_save->setText("&Сохранить");
    action_save->setShortcut(QKeySequence("CTRL+S"));
    action_save->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(action_save, SIGNAL(triggered()), tab, SLOT(slot_save()));
    menu_file->addAction(action_save);
    tool_bar->addAction(action_save);

    QAction* action_save_as = new QAction("File save as action", 0);
    action_save_as->setText("Сох&ранить как...");
    connect(action_save_as, SIGNAL(triggered()), tab, SLOT(slot_save_as()));
    menu_file->addAction(action_save_as);

    QAction* action_save_all = new QAction("File save all action", 0);
    action_save_all->setText("Сохра&нить все");
    action_save_all->setShortcut(QKeySequence("CTRL+SHIFT+S"));
    action_save_all->setIcon(style()->standardIcon(QStyle::SP_DriveFDIcon));
    connect(action_save_all, SIGNAL(triggered()), tab, SLOT(slot_save_all()));
    menu_file->addAction(action_save_all);
    tool_bar->addAction(action_save_all);

    QAction* action_close = new QAction("File close action", 0);
    action_close->setText("&Закрыть");
    action_close->setShortcut(QKeySequence("CTRL+W"));
//    action_close->setIcon(...);
    connect(action_close, SIGNAL(triggered()), tab, SLOT(slot_close()));
    menu_file->addAction(action_close);

    QAction* action_close_all = new QAction("File close all action", 0);
    action_close_all->setText("Закры&ть все");
    action_close_all->setShortcut(QKeySequence("CTRL+SHIFT+W"));
//    action_close_all->setIcon(...);
    connect(action_close_all, SIGNAL(triggered()), tab, SLOT(slot_close_all()));
    menu_file->addAction(action_close_all);

    menu_file->addSeparator();

    QAction* action_quit = new QAction("Quit action", 0);
    action_quit->setText("Вы&ход");
    action_quit->setShortcut(QKeySequence("CTRL+Q"));
//    action_quit->setIcon(...);
    connect(action_quit, SIGNAL(triggered()), tab, SLOT(slot_quit()));
    menu_file->addAction(action_quit);

    QAction* action_cut = new QAction("Cut text action", 0);
    action_cut->setText("В&ырезать");
    action_cut->setShortcut(QKeySequence("CTRL+X"));
    connect(action_cut, SIGNAL(triggered()), tab, SLOT(slot_cut()));
    menu_edit->addAction(action_cut);

    QAction* action_copy = new QAction("Copy text action", 0);
    action_copy->setText("&Копировать");
    action_copy->setShortcut(QKeySequence("CTRL+C"));
    connect(action_copy, SIGNAL(triggered()), tab, SLOT(slot_copy()));
    menu_edit->addAction(action_copy);

    QAction* action_paste = new QAction("Paste text action", 0);
    action_paste->setText("&Вставить");
    action_paste->setShortcut(QKeySequence("CTRL+V"));
    connect(action_paste, SIGNAL(triggered()), tab, SLOT(slot_paste()));
    menu_edit->addAction(action_paste);

    QAction* action_delete = new QAction("Delete text action", 0);
    action_delete->setText("У&далить");
    action_delete->setShortcut(QKeySequence("CTRL+D"));
    connect(action_delete, SIGNAL(triggered()), tab, SLOT(slot_delete()));
    menu_edit->addAction(action_delete);

    QAction* action_select_all = new QAction("Select all text action", 0);
    action_select_all->setText("Выбр&ать все");
    action_select_all->setShortcut(QKeySequence("CTRL+A"));
    connect(action_select_all, SIGNAL(triggered()), tab, SLOT(slot_select_all()));
    menu_edit->addAction(action_select_all);

    addToolBar(Qt::TopToolBarArea, tool_bar);
    menuBar()->addMenu(menu_file);
    menuBar()->addMenu(menu_edit);
    menuBar()->addMenu(menu_view);

    setCentralWidget(tab);
}

void MainWindow::slotChangeWindowTitle(const QString& fileName) {
    setWindowTitle(fileName);
}

void MainWindow::closeEvent(QCloseEvent* event){
    tab->slot_quit();
    event->ignore();
}
