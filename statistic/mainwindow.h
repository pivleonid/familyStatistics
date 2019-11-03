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

#include <QCryptographicHash>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct personInfo
    {
        QByteArray id = 0;
        QByteArray id_father = 0;
        QString    name;
        QString    patronymic;
        QString    nameFather;
        QString    born;
        QString    die;
        QString    info;

    };
    QVector<personInfo> m_familly;
    QVector<QVector<personInfo>> m_familly_list;


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
    void on_addPerson();
    void on_deletePerson();
    void on_doubleClicked(QTreeWidgetItem * item, int column);
    void on_Clicked(QTreeWidgetItem * item, int column);
    void acceptPerson(QString str);

    //Сохраняю все данные из дерева
    void on_savePersonStack(void);
    void savePersonStack(personInfo& person_father, QTreeWidgetItem* parent = 0);


private:
    int  treeCount(QTreeWidget *, QTreeWidgetItem *); //подсчёт количества элементов в QTreeWidget
    void deleteItem (QTreeWidgetItem *currentItem); //удаление элемента из QTreeWidget
    void insertItem (QTreeWidgetItem *, QString); //добавление элемента в QTreeWidget
    void showAll(void); //вывод информации о QTreeWidget

    int              m_count;         //переменная для хранения номера очередного узла
    QTreeWidgetItem* m_currentItem;   //текущий элемент, запоминается при клике в QTreeWidget
    int              m_currentColumn; //номер столбца, на самом деле будет = 0, т.к. у нас 1 столбец


};
#endif // MAINWINDOW_H
