/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Call
*/

#include "Call.hpp"

Call::Call(QWidget *parent)
{
    this->app = static_cast<App *>(parent);

    receiveCallName = new QLabel;
    sendCallName = new QLabel;
    QLabel *sendCallWait = new QLabel("Waiting...");
    QLabel *onCallName = new QLabel("On call");
    QPushButton *receiveCallAccept = new QPushButton("Answer");
    QPushButton *receiveCallDeny = new QPushButton("Deny");

    QPushButton *addToCall = new QPushButton("Add");
    QPushButton *removeToCall = new QPushButton("Remove");
    QPushButton *hangup = new QPushButton("Hang Up");

    connect(receiveCallAccept, SIGNAL(clicked()), this, SLOT(takeCall()));
    connect(receiveCallDeny, SIGNAL(clicked()), this, SLOT(refuseCall()));
    receiveCallLayout->addWidget(receiveCallName, 0, 0, 1, 2, Qt::AlignCenter);
    receiveCallLayout->addWidget(receiveCallAccept, 2, 0);
    receiveCallLayout->addWidget(receiveCallDeny, 2, 1);

    sendCallLayout->addWidget(sendCallName, 0, 0, 1, 2, Qt::AlignCenter);
    sendCallWait->setStyleSheet("color: grey; font-size: 14px");
    sendCallLayout->addWidget(sendCallWait, 2, 0, 1, 2, Qt::AlignCenter);
    buttonList->addWidget(addToCall);
    buttonList->addWidget(removeToCall);
    buttonList->addWidget(hangup);
    ContactLabel *label = new ContactLabel({"Himler", "", "", 1});
    label->setText("Himler");
    contactList->addWidget(label);
    QHBoxLayout *row = new QHBoxLayout;
    row->addLayout(contactList);
    row->addStretch();
    row->addLayout(buttonList);
    onCallLayout->addWidget(onCallName, 0, 0, 1, 2, Qt::AlignCenter);
    onCallLayout->addLayout(row, 1, 0);

    onCall->setLayout(onCallLayout);
    receiveCall->setLayout(receiveCallLayout);
    sendCall->setLayout(sendCallLayout);

    scene->addWidget(new QWidget);
    scene->addWidget(onCall);
    scene->addWidget(receiveCall);
    scene->addWidget(sendCall);
}

void Call::setScene(Scene scene, std::string context)
{
    this->scene->setCurrentIndex(static_cast<int>(scene));
    this->contextCall = QString::fromStdString(context);
    if (scene == RECEIVECALL)
        receiveCallName->setText(QString::fromStdString("%1 is calling").arg(this->contextCall));
    if (scene == SENDCALL)
        sendCallName->setText(QString::fromStdString("You're calling %1").arg(this->contextCall));
}

void Call::refuseCall()
{
    this->app->refuseCall();
    setScene(NOCALL, "");
}

void Call::takeCall()
{
    this->app->acceptCall();
    setScene(ONCALL, "");
}
