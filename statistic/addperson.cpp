#include "addperson.h"

#define SPR "(;)"

addPerson::addPerson(QDialog *parent) : QDialog(parent)
{
    setupUi(this);
    connect(pushButton_Add, SIGNAL(clicked()), this, SLOT(slt_add()));
    connect(pushButton_cancel, SIGNAL(clicked()), this, SLOT(slt_cancel()));
    pushButton_Add->setDefault(true);// Enter по умолчанию

    this->setWindowTitle("Введите параметры");

}
void addPerson::slt_add()
{
    QString str = lineEdit_name->text() + SPR + lineEdit_patronymic->text()
            + SPR +  lineEdit_nameFather->text() + SPR +  lineEdit_born->text()
            + SPR +  lineEdit_die->text() + SPR +  plainTextEdit->toPlainText();
    emit s_personAdd(str);
    //this->close();
    this->accept();

}
void addPerson::slt_cancel()
{
    emit s_personCancel();
    this->reject();
}

//-----------------------------------------------------
void addPerson::setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(247, 500);
        plainTextEdit = new QPlainTextEdit(Form);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 200, 231, 231));
        label_6 = new QLabel(Form);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 170, 131, 21));
        pushButton_Add = new QPushButton(Form);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));
        pushButton_Add->setGeometry(QRect(10, 460, 93, 28));
        pushButton_cancel = new QPushButton(Form);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(140, 460, 93, 28));
        widget = new QWidget(Form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 230, 150));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_name);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_patronymic = new QLineEdit(widget);
        lineEdit_patronymic->setObjectName(QString::fromUtf8("lineEdit_patronymic"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_patronymic);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEdit_nameFather = new QLineEdit(widget);
        lineEdit_nameFather->setObjectName(QString::fromUtf8("lineEdit_nameFather"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_nameFather);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEdit_born = new QLineEdit(widget);
        lineEdit_born->setObjectName(QString::fromUtf8("lineEdit_born"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_born);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineEdit_die = new QLineEdit(widget);
        lineEdit_die->setObjectName(QString::fromUtf8("lineEdit_die"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_die);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void addPerson::retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("Form", "\320\236\320\261\321\211\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217:", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("Form", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        label->setText(QCoreApplication::translate("Form", "\320\230\320\274\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "\320\230\320\274\321\217 \320\276\321\202\321\206\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "\320\223\320\276\320\264 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "\320\223\320\276\320\264 \321\201\320\274\320\265\321\200\321\202\320\270", nullptr));
    } // retranslateUi
