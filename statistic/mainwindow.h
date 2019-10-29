#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QAction *action;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QWidget *centralwidget;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void retranslateUi(QMainWindow *MainWindow);
    void setupUi(QMainWindow *MainWindow);

private slots:
//    void addFamily();
//    void addBrother();
//    void addSon();

private slots:
    void on_addPerson();
    void on_deletePerson();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    int treeCount(QTreeWidget *, QTreeWidgetItem *); //подсчёт количества элементов в QTreeWidget
    void DeleteItem (QTreeWidgetItem *currentItem); //удаление элемента из QTreeWidget
    void InsertItem (QTreeWidgetItem *, QString); //добавление элемента в QTreeWidget
    void showAll(void); //вывод информации о QTreeWidget
    int count; //переменная для хранения номера очередного узла
    QTreeWidgetItem *currentItem; //текущий элемент, запоминается при клике в QTreeWidget
    int currentColumn; //номер столбца, на самом деле будет = 0, т.к. у нас 1 столбец
};
#endif // MAINWINDOW_H
