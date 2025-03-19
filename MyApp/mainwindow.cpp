#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QDebug> // 必须包含此头文件QDateTime
#include <QDateTime>
#include "mywidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口标题
    setWindowTitle("界面程序-蒋志桐-2025.03.17");
    resize(1200, 800);

    // 创建界面元素
    createMenuBar();
    createToolBar();
    createStatusBar();
    setupTable();
    setupTree();
    createCustomWidget();

    // 主布局
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 表格区域
    QHBoxLayout *tableLayout = new QHBoxLayout;
    QPushButton *reverseBtn = new QPushButton("倒序表格");
    connect(reverseBtn, &QPushButton::clicked, this, &MainWindow::reverseTable);
    tableLayout->addWidget(tableView);
    tableLayout->addWidget(reverseBtn);

    // 树形区域
    QHBoxLayout *treeLayout = new QHBoxLayout;
    QVBoxLayout *treeBtnLayout = new QVBoxLayout;
    QPushButton *btn1 = new QPushButton("清除小于等于25的值");
    QPushButton *btn2 = new QPushButton("过滤奇数行");
    connect(btn1, &QPushButton::clicked, this, &MainWindow::processTreeData);
    connect(btn2, &QPushButton::clicked, this, &MainWindow::filterOddRows);
    treeBtnLayout->addWidget(btn1);
    treeBtnLayout->addWidget(btn2);
    treeBtnLayout->addStretch();
    treeLayout->addWidget(treeView);
    treeLayout->addLayout(treeBtnLayout);

    // 自定义控件
    MyWidget *myWidget = new MyWidget;
    myWidget->setFixedSize(400, 200);

    // 组合布局
    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(treeLayout);
    mainLayout->addWidget(myWidget);

    centralWidget->setLayout(mainLayout);
}

// 菜单栏实现
void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("文件");
    QMenu *viewMenu = menuBar->addMenu("视图");
    QMenu *settingMenu = menuBar->addMenu("设置");
    QMenu *helpMenu = menuBar->addMenu("帮助");

    // 添加"打开新页面"动作
    QAction *newWinAction = viewMenu->addAction("打开新页面");
    connect(newWinAction, &QAction::triggered, this, &MainWindow::openNewWindow);
}

// 工具栏实现
void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("主工具栏");

    QStringList iconPaths = {
        ":/icons/new.png",
        ":/icons/save.png",
        ":/icons/cut.png",
        ":/icons/copy.png",
        ":/icons/paste.png"
    };

    for(int i=0; i<5; i++){
        QAction *action = new QAction(QIcon(iconPaths[i]), QString("操作%1").arg(i+1), this);
        toolBar->addAction(action);
        connect(action, &QAction::triggered, [=](){
            qDebug() << "工具栏操作" << i+1 << "被触发";
        });
    }
}

// 状态栏实现
void MainWindow::createStatusBar()
{
    QStatusBar *sb = statusBar();

    QLabel *leftLabel = new QLabel("左侧状态信息");
    QLabel *rightLabel1 = new QLabel("系统就绪");
    QLabel *rightLabel2 = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    sb->addWidget(leftLabel); // 左对齐
    sb->addPermanentWidget(rightLabel1); // 右对齐
    sb->addPermanentWidget(rightLabel2);
}

// 表格初始化
void MainWindow::setupTable()
{
    tableView = new QTableView;
    model = new QStandardItemModel(8, 5, this);

    QStringList headers = {"坐标1", "坐标2", "坐标3", "坐标4", "坐标5"};
    model->setHorizontalHeaderLabels(headers);

    // 填充示例数据
    for(int row=0; row<8; row++){
        for(int col=0; col<5; col++){
            QStandardItem *item = new QStandardItem(QString("%1-%2").arg(row).arg(col));
            model->setItem(row, col, item);
        }
    }
    tableView->setModel(model);
}

// 树形视图初始化
void MainWindow::setupTree()
{
    treeView = new QTreeView;
    treeModel = new QStandardItemModel;

    QStringList headers = {"节点(列1)", "数据1(列2)", "数据2(列3)", "数据3(列4)", "数据4(列5)"};
    treeModel->setHorizontalHeaderLabels(headers);

    // 生成树形数据
    for(int i=0; i<8; i++){
        QStandardItem *parentItem = new QStandardItem(QString("树形图%1行").arg(i));
        for(int j=0; j<3; j++){
            QList<QStandardItem*> childItems;
            childItems << new QStandardItem(QString("子节点%1").arg(j))
                       << new QStandardItem(QString::number(QRandomGenerator::global()->bounded(50)))
                       << new QStandardItem(QString::number(QRandomGenerator::global()->bounded(50)))
                       << new QStandardItem(QString::number(QRandomGenerator::global()->bounded(50)))
                       << new QStandardItem(QString::number(QRandomGenerator::global()->bounded(50)));
            parentItem->appendRow(childItems);
        }
        treeModel->appendRow(parentItem);
    }

    treeView->setModel(treeModel);
    treeView->expandAll();
}

// 自定义控件创建
void MainWindow::createCustomWidget()
{
    // 在布局中已创建
}

// 槽函数实现
void MainWindow::openNewWindow()
{
    QMainWindow *newWindow = new QMainWindow;
    newWindow->setWindowTitle("新窗口");
    newWindow->resize(400, 300);
    newWindow->show();
}

void MainWindow::reverseTable()
{
    QList<QList<QStandardItem*>> rows;

    // 取出所有行数据
    for(int i=0; i<model->rowCount(); i++){
        QList<QStandardItem*> row;
        for(int j=0; j<model->columnCount(); j++){
            row.append(model->takeItem(i, j));
        }
        rows.append(row);
    }

    // 反转数据
    std::reverse(rows.begin(), rows.end());

    // 清除原有数据并重新插入
    model->removeRows(0, model->rowCount());
    foreach(auto row, rows){
        model->appendRow(row);
    }
}

void MainWindow::processTreeData()
{
    for(int i=0; i<treeModel->rowCount(); i++){
        QStandardItem *parent = treeModel->item(i);
        for(int j=0; j<parent->rowCount(); j++){
            for(int col=1; col<=3; col++){ // 处理数据列
                QStandardItem *item = parent->child(j, col);
                int value = item->text().toInt();
                if(value <= 25){
                    item->setText("0");
                }
            }
        }
    }
}

void MainWindow::filterOddRows()
{
    // 从后往前删除避免索引变化问题
    for(int row = treeModel->rowCount()-1; row >=0; row--){
        if(row % 2 == 0){ // 保留奇数行（索引从0开始）
            treeModel->removeRow(row);
        }
    }
}
