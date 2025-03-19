#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


private slots:
    void openNewWindow();
    void reverseTable();
    void processTreeData();
    void filterOddRows();

private:
    // 表格相关
    QTableView *tableView;
    QStandardItemModel *model;
    bool reverse = false;

    // 树形视图相关
    QTreeView *treeView;
    QStandardItemModel *treeModel;

    // 初始化函数
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    void setupTable();
    void setupTree();
    void createCustomWidget();
};

#endif // MAINWINDOW_H
