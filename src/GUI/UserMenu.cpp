/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include <QtGui>
#include "UserMenu.h"
#include <iostream>

UserMenu::UserMenu(QWidget *parent)
{
    this->app = static_cast<App *>(parent);
    QLabel *nameLabel = new QLabel(this);
    nameLabel->setFrameStyle(QFrame::Panel);
    nameLabel->setText(QString::fromStdString(app->getUser().username + " : " + app->getUser().address));

    QLabel *addressLabel = new QLabel(tr("Contact:"));
    contactDraw = QList<ContactLabel *>();

    addButton = new QPushButton(tr("&Add"));

    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);

    dialog = new ModifyPopup;

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findContact()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addStretch();

    contactLayout = new QVBoxLayout;
    contactLayout->addWidget(addressLabel);

    mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addLayout(contactLayout, 1, 0, Qt::AlignTop);
    mainLayout->addLayout(buttonLayout1, 1, 2);

    parent->setLayout(mainLayout);
    fetchContact();
}

void UserMenu::fetchContact()
{
    for (auto a : contactDraw)
        delete a;
    this->contactDraw.clear();
    /*for ()
    */
    ContactLabel *label = new ContactLabel;
    label->setText("dddd");
    contactLayout->addWidget(label);
    connect(label, SIGNAL(clicked(const QString &)), this, SLOT(setSelectioned(const QString &)));
}

void UserMenu::setSelectioned(const QString &username)
{
    this->selection = username.toStdString();
    std::cout << selection << std::endl;
}

void UserMenu::addContact()
{
    oldName = nameLine->text();

    nameLine->clear();
}

void UserMenu::removeContact()
{
    QString name = nameLine->text();

    if (contacts.contains(name)) {
        int button = QMessageBox::question(this,
                                           tr("Confirm Remove"),
                                           tr("Are you sure you want to remove \"%1\"?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {

            contacts.remove(name);

            QMessageBox::information(this, tr("Remove Successful"),
                                     tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }
}

void UserMenu::findContact()
{
    dialog->show();

    if (dialog->exec() == 1) {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName)) {
            nameLine->setText(contactName);
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                                     tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }
}