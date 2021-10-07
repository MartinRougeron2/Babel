/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Call
*/

#ifndef CALL_HPP_
#define CALL_HPP_

#include "App.h"
#include "ContactLabel.hpp"

class Call : public QWidget {
    Q_OBJECT
    public:
        enum Scene {NOCALL, ONCALL, RECEIVECALL, SENDCALL};
        Call(QWidget *parent = 0);

        void setScene(Scene, std::string user);
        QStackedLayout *getLayout() const { return this->scene;};
    public slots:
        void takeCall();
        void refuseCall();
    protected:
    private:
        App *app;
        QString contextCall = "";
        QLabel *receiveCallName;
        QLabel *sendCallName;
        QStackedLayout *scene = new QStackedLayout;
        QGridLayout *onCallLayout = new QGridLayout;
        QGridLayout *receiveCallLayout = new QGridLayout;
        QGridLayout *sendCallLayout = new QGridLayout;
        QVBoxLayout *contactList = new QVBoxLayout;
        QVBoxLayout *buttonList = new QVBoxLayout;
        QWidget *onCall = new QWidget;
        QWidget *receiveCall = new QWidget;
        QWidget *sendCall = new QWidget;
};

#endif /* !CALL_HPP_ */
