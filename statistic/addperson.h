#ifndef ADDPERSON_H
#define ADDPERSON_H

#include <QObject>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class addPerson : public QWidget
{
    Q_OBJECT
public:
    QPlainTextEdit *plainTextEdit;
    QLabel *label_6;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_cancel;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QLabel *label_2;
    QLineEdit *lineEdit_patronymic;
    QLabel *label_3;
    QLineEdit *lineEdit_nameFather;
    QLabel *label_4;
    QLineEdit *lineEdit_born;
    QLabel *label_5;
    QLineEdit *lineEdit_die;
    explicit addPerson(QWidget *parent = nullptr);

signals:

public slots:

private:
    void setupUi(QWidget *Form);
    void retranslateUi(QWidget *Form);
};

#endif // ADDPERSON_H
