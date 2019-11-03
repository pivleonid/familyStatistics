﻿#include "mainwindow.h"
#include "addperson.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    //addPerson* person = new addPerson();
    //person->show();


    //ниже наша часть конструктора
    m_count = 0;
    this->treeWidget->setColumnCount(1);
    QStringList headers;
    headers << tr("Объекты");
    this->treeWidget->setHeaderLabels(headers);
    m_currentItem = NULL;
    m_currentColumn = 0;

    connect(this->pushButton_2, SIGNAL(clicked()), this, SLOT(on_addPerson()));
    connect(this->pushButton_3, SIGNAL(clicked()), this, SLOT(on_deletePerson()));

    connect(treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::on_Clicked);
    connect(treeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::on_doubleClicked);

    connect(pushButton, SIGNAL(clicked()), this, SLOT(on_savePersonStack()));


}
void MainWindow::savePersonStack(personInfo& person_father, QTreeWidgetItem* parent)
{
    //для первой колонки
    if (parent == 0)
    {
        int topCount = treeWidget->topLevelItemCount();
        for (int i = 0; i < topCount; i++)
        {
            QTreeWidgetItem *item = treeWidget->topLevelItem(i);
            if( item->childCount() > 0)
            {
                personInfo father;
                QString allString = item->text(m_currentColumn);
                QStringList splitStr = allString.split("(;)");
                QByteArray b_array;
                b_array.append(allString);
                father.id = QCryptographicHash::hash(b_array, QCryptographicHash::Md5);
                father.id_father = 0;
                father.name = splitStr[0];
                father.patronymic = splitStr[1];
                father.nameFather = splitStr[2];
                father.born = splitStr[3];
                father.die = splitStr[4];
                father.info = splitStr[5];
                m_familly << father;
                savePersonStack(father, item);
            }
            else
            {
                personInfo father;
                QString allString = item->text(m_currentColumn);
                QStringList splitStr = allString.split("(;)");
                QByteArray b_array;
                b_array.append(allString);
                father.id = QCryptographicHash::hash(b_array, QCryptographicHash::Md5);
                father.id_father = 0;
                father.name = splitStr[0];
                father.patronymic = splitStr[1];
                father.nameFather = splitStr[2];
                father.born = splitStr[3];
                father.die = splitStr[4];
                father.info = splitStr[5];
                m_familly << father;
            }
        }
    }
    //для последующих
    else {
        int childCount = parent->childCount();
        for (int i = 0; i < childCount; i++)
        {
            QTreeWidgetItem *item = parent->child(i);
            if( item->childCount() > 0)//если есть вложенные данные
            {
                personInfo son_n;
                QString allString = item->text(m_currentColumn);
                QStringList splitStr = allString.split("(;)");
                QByteArray b_array;
                b_array.append(allString);
                son_n.id = QCryptographicHash::hash(b_array, QCryptographicHash::Md5);
                son_n.id_father = person_father.id;
                son_n.name = splitStr[0];
                son_n.patronymic = splitStr[1];
                son_n.nameFather = splitStr[2];
                son_n.born = splitStr[3];
                son_n.die = splitStr[4];
                son_n.info = splitStr[5];
                savePersonStack(son_n, item);
            }
            else
            {
                personInfo son_n;
                QString allString = item->text(m_currentColumn);
                QStringList splitStr = allString.split("(;)");
                QByteArray b_array;
                b_array.append(allString);
                son_n.id = QCryptographicHash::hash(b_array, QCryptographicHash::Md5);
                son_n.id_father = person_father.id;
                son_n.name = splitStr[0];
                son_n.patronymic = splitStr[1];
                son_n.nameFather = splitStr[2];
                son_n.born = splitStr[3];
                son_n.die = splitStr[4];
                son_n.info = splitStr[5];
                m_familly << son_n;
            }
        }
    }
}
#include <QDebug>
void MainWindow::on_savePersonStack()
{
    /*
    не учтёт свёрнутые ветви; потому что правильно было бы делать через модель
   */
       treeWidget->expandAll(); //а это "костыль"
       personInfo person_father;
       savePersonStack( person_father);
       int a;
       a++;
       foreach (auto var, m_familly) {
           qDebug() << "id = "<< var.id << "; id father = " << var.id_father;
       }
       qDebug() << "//---------------------------------//";
       m_familly_list << m_familly;
       m_familly.clear();

       //удаление из виджета
       treeWidget->clear();
       m_count = 0;
       m_currentItem = NULL;


}


void MainWindow::on_Clicked(QTreeWidgetItem * item, int column)
{
    m_currentItem = item;
    m_currentColumn = column;
}
void MainWindow::on_doubleClicked(QTreeWidgetItem * item, int column)
{
    addPerson person;
    person.setModal(true);
    person.show();
    connect(&person, SIGNAL(s_personAdd(QString)), this, SLOT(acceptPerson(QString)));
    switch( person.exec() ) {
    case QDialog::Accepted:
        qDebug() << "accepted";
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    disconnect(&person, SIGNAL(s_personAdd(QString)), this, SLOT(acceptPerson(QString)));
}

//редактирование поля
void MainWindow::acceptPerson(QString str)
{
    m_currentItem->setText(m_currentColumn, str);
}

MainWindow::~MainWindow()
{
}
int MainWindow::treeCount(QTreeWidget *tree, QTreeWidgetItem *parent = 0) {
 /*
 не учтёт свёрнутые ветви; потому что правильно было бы делать через модель
*/
    tree->expandAll(); //а это "костыль"
    int count = 0;
    if (parent == 0)
    {
        int topCount = tree->topLevelItemCount();
        for (int i = 0; i < topCount; i++)
        {
            QTreeWidgetItem *item = tree->topLevelItem(i);
            if (item->isExpanded()) {
                count += treeCount(tree, item);
            }
        }
        count += topCount;
    }
    else {
        int childCount = parent->childCount();
        for (int i = 0; i < childCount; i++)
        {
            QTreeWidgetItem *item = parent->child(i);
            if (item->isExpanded())
            {
                count += treeCount(tree, item);
            }
        }
        count += childCount;
    }
    return count;
}

void MainWindow::deleteItem (QTreeWidgetItem *currentItem) {
    QTreeWidgetItem *parent = currentItem->parent();
    int index;
    if (parent) {
        index = parent->indexOfChild(this->treeWidget->currentItem());
        delete parent->takeChild(index);
    }
    else {
        index = this->treeWidget->indexOfTopLevelItem(this->treeWidget->currentItem());
        delete this->treeWidget->takeTopLevelItem(index);
    }
}

void MainWindow::insertItem (QTreeWidgetItem *parent, QString text)
{
    if (parent->isExpanded()==false) parent->setExpanded(true);
    QTreeWidgetItem *newItem = new QTreeWidgetItem(parent, this->treeWidget->currentItem());
    newItem->setText (m_currentColumn, text);
    newItem->setExpanded(true);
}


void MainWindow::on_addPerson() { //кнопка Добавить
    if (m_currentItem) {
        QString word;// = m_currentItem->text(m_currentColumn);
        insertItem  (m_currentItem, word + " " + QString("%1").arg(++m_count));
    }
    else {
        QTreeWidgetItem *newItem = new QTreeWidgetItem(this->treeWidget, this->treeWidget->currentItem());
        //указываем 2-м параметром текущий элемент как предшествующий
        newItem->setText (m_currentColumn, "" + QString("%1").arg(++m_count));
        newItem->setExpanded(true);
    }
    //m_currentItem = NULL;
    showAll();
}

void MainWindow::on_deletePerson() { //кнопка Удалить
    if (m_currentItem) {
        deleteItem (m_currentItem);
        m_currentItem = NULL;
    }
    showAll();

}

void MainWindow::showAll(void) {
    int cnt = treeCount (this->treeWidget);
    m_count = cnt;
    QString str(tr("Всего: ")+QString("%1").arg(cnt));
    setWindowTitle(str);
}


//-----------------------------------------------------------------
void MainWindow::setupUi(QMainWindow *MainWindow)
   {
       if (MainWindow->objectName().isEmpty())
           MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
       MainWindow->resize(590, 839);
       action = new QAction(MainWindow);
       action->setObjectName(QString::fromUtf8("action"));
       action_3 = new QAction(MainWindow);
       action_3->setObjectName(QString::fromUtf8("action_3"));
       action_4 = new QAction(MainWindow);
       action_4->setObjectName(QString::fromUtf8("action_4"));
       action_5 = new QAction(MainWindow);
       action_5->setObjectName(QString::fromUtf8("action_5"));
       action_6 = new QAction(MainWindow);
       action_6->setObjectName(QString::fromUtf8("action_6"));
       centralwidget = new QWidget(MainWindow);
       centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
       treeWidget = new QTreeWidget(centralwidget);
       treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
       treeWidget->setGeometry(QRect(10, 40, 561, 741));
       widget = new QWidget(centralwidget);
       widget->setObjectName(QString::fromUtf8("widget"));
       widget->setGeometry(QRect(10, 10, 561, 31));
       horizontalLayout = new QHBoxLayout(widget);
       horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
       horizontalLayout->setContentsMargins(0, 0, 0, 0);
       pushButton = new QPushButton(widget);
       pushButton->setObjectName(QString::fromUtf8("pushButton"));

       horizontalLayout->addWidget(pushButton);

       pushButton_2 = new QPushButton(widget);
       pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

       horizontalLayout->addWidget(pushButton_2);

       pushButton_3 = new QPushButton(widget);
       pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

       horizontalLayout->addWidget(pushButton_3);

       MainWindow->setCentralWidget(centralwidget);
       menubar = new QMenuBar(MainWindow);
       menubar->setObjectName(QString::fromUtf8("menubar"));
       menubar->setGeometry(QRect(0, 0, 590, 26));
       menu = new QMenu(menubar);
       menu->setObjectName(QString::fromUtf8("menu"));
       menu_2 = new QMenu(menubar);
       menu_2->setObjectName(QString::fromUtf8("menu_2"));
       menu_3 = new QMenu(menubar);
       menu_3->setObjectName(QString::fromUtf8("menu_3"));
       MainWindow->setMenuBar(menubar);
       statusbar = new QStatusBar(MainWindow);
       statusbar->setObjectName(QString::fromUtf8("statusbar"));
       MainWindow->setStatusBar(statusbar);

       menubar->addAction(menu->menuAction());
       menubar->addAction(menu_2->menuAction());
       menubar->addAction(menu_3->menuAction());
       menu->addAction(action);
       menu->addSeparator();
       menu->addAction(action_3);
       menu_2->addAction(action_4);
       menu_3->addAction(action_5);
       menu_3->addAction(action_6);

       retranslateUi(MainWindow);

       QMetaObject::connectSlotsByName(MainWindow);
   } // setupUi

   void MainWindow::retranslateUi(QMainWindow *MainWindow)
   {
       MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
       action->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
       action_3->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
       action_4->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\262\321\201\320\265\321\205", nullptr));
       action_5->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
       action_6->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
       QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
       ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\260\321\200\320\264\320\270\320\275\321\213", nullptr));
       pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\273\320\265\320\264\321\203\321\216\321\211\321\203\321\216 \321\201\320\265\320\274\321\214\321\216", nullptr));
       pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\261\321\200\320\260\321\202\320\260", nullptr));
       pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\213\320\275\320\260", nullptr));
       menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
       menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
       menu_3->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
   } // retranslateUi
