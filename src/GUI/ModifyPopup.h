/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#ifndef BABEL_MODIFYPOPUP_H
#define BABEL_MODIFYPOPUP_H

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>


class ModifyPopup : public QDialog
{

    Q_OBJECT
    public:
        ModifyPopup(QWidget *parent = 0);
        QString getFindText();

    public slots:
        void findClicked();

    private:
        QPushButton *findButton;
        QLineEdit *lineEdit;
        QString findText;
};


#endif //BABEL_MODIFYPOPUP_H
