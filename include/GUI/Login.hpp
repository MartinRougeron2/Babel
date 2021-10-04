/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Login
*/

#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QGridLayout>
#include <QtWidgets>
#include <QWidget>

class Login : public QWidget{
    Q_OBJECT

    public:
        Login();
        ~Login();

        void proceed_login();
        //void update();
    protected:
    private:
        QLineEdit *username_edit;
        QLineEdit *password_edit;
        QLabel *username_info;
        QLabel *password_info;
        QLabel *username_error;
        QLabel *password_error;
        QButton *login_button;
};

#endif /* !LOGIN_HPP_ */
