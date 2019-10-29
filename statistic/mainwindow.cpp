#include "mainwindow.h"
#include "addperson.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    addPerson* person = new addPerson();
    person->show();


    //ниже наша часть конструктора
    count = 0;
    this->treeWidget->setColumnCount(1);
    QStringList headers;
    headers << tr("Объекты");
    this->treeWidget->setHeaderLabels(headers);
    currentItem = NULL;
    currentColumn = 0;

    connect(this->pushButton_2, SIGNAL(clicked()), this, SLOT(on_addPerson()));
    connect(this->pushButton_3, SIGNAL(clicked()), this, SLOT(on_deletePerson()));
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
 if (parent == 0) {
  int topCount = tree->topLevelItemCount();
  for (int i = 0; i < topCount; i++) {
   QTreeWidgetItem *item = tree->topLevelItem(i);
   if (item->isExpanded()) {
    count += treeCount(tree, item);
   }
  }
  count += topCount;
 }
 else {
  int childCount = parent->childCount();
  for (int i = 0; i < childCount; i++) {
   QTreeWidgetItem *item = parent->child(i);
   if (item->isExpanded()) {
    count += treeCount(tree, item);
   }
  }
  count += childCount;
 }
 return count;
}

void MainWindow::DeleteItem (QTreeWidgetItem *currentItem) {
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

void MainWindow::InsertItem (QTreeWidgetItem *parent, QString text) {
 if (parent->isExpanded()==false) parent->setExpanded(true);
 QTreeWidgetItem *newItem = new QTreeWidgetItem(parent, this->treeWidget->currentItem());
 newItem->setText (currentColumn, text);
 newItem->setExpanded(true);
}


void MainWindow::on_addPerson() { //кнопка Добавить
 if (currentItem) {
  QString word = currentItem->text(currentColumn);
  InsertItem  (currentItem, word + " " + QString("%1").arg(++count));
 }
 else {
  QTreeWidgetItem *newItem = new QTreeWidgetItem(this->treeWidget, this->treeWidget->currentItem());
   //указываем 2-м параметром текущий элемент как предшествующий
  newItem->setText (currentColumn, "" + QString("%1").arg(++count));
  newItem->setExpanded(true);
 }
 currentItem = NULL;
 showAll();
}

void MainWindow::on_deletePerson() { //кнопка Удалить
 if (currentItem) {
  DeleteItem (currentItem);
  currentItem = NULL;
 }
 showAll();
}

void MainWindow::showAll(void) {
 int cnt = treeCount (this->treeWidget);
 QString str(tr("Всего: ")+QString("%1").arg(cnt));
 setWindowTitle(str);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column) {
 currentItem = item;
 currentColumn = column;
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
