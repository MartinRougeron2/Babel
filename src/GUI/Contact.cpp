/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include "../../include/GUI/Contact.h"

Contact::Contact(std::string username, std::string address, bool in_list)
{
    name_label = new QLabel(username.c_str());
    call = new QPushButton("\uD83D\uDCDE");
    remove_from_call = new QPushButton("-");
    add_to_list = new QPushButton("+");
    remove_from_list = new QPushButton("-");
    QGridLayout *mainLayout = new QGridLayout;

    this->user.username = username;
    this->user.address = address;

    if (in_list)
        this->contact_state = Added;
    else
        this->contact_state = None;

    connect(call, SIGNAL(clicked()), this, SLOT(call()));
    connect(remove_from_call, SIGNAL(clicked()), this, SLOT(removeFromCall()));
    connect(add_to_list, SIGNAL(clicked()), this, SLOT(addToList()));
    connect(remove_from_list, SIGNAL(clicked()), this, SLOT(removeFromList()));
    update();
}


Contact Contact::call()
{
    contact_context = Call;
    upadte();
    return this;
}

Contact Contact::addToList()
{
    contact_state = Added;
    upadte();
    return this;
}

void Contact::removeFromList()
{
    contact_state = None;
    upadte();
}

void Contact::removeFromCall()
{
}

void Contact::setContext(Context newContext)
{
    this->contact_context = newContext;
    upadte();
}

void Contact::update()
{
    this->call->setEnabled(false);
    this->add_to_list->setEnabled(false);
    this->remove_from_list->setEnabled(false);
    this->remove_from_call->setEnabled(false);

    mainLayout->addWidget(name_label, 0, 0);
    switch (contact_context) {
        case Menu:
        case Adding:
            if (contact_state == None) {
                this->add_to_list->setEnabled(true);
                mainLayout->addWidget(add_to_list, 0, 1)
            }
            else {
                this->remove_from_list->setEnabled(true);
                this->call->setEnabled(true);
                mainLayout->addWidget(remove_from_list, 0, 1);
                mainLayout->addWidget(call, 0, 2);
            }
            break;

        case Call:
            // Nothing to do
            break;
        case ConfCall:
            this->remove_from_call->setEnabled(true);
            mainLayout->addWidget(remove_from_call, 0, 1);

    }
}


QPushButton *Contact::get_call()
{
    return call;
}

QPushButton *Contact::get_remove_from_call()
{
    return remove_from_call;
}

QPushButton *Contact::get_add_to_list()
{
    return add_to_list;
}

QPushButton Contact::get_remove_from_list() {
    return remove_from_list;
}
