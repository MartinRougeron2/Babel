/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include "GUI/Contact.h"

Contact::Contact(std::string username, std::string address, bool in_list)
{
    name_label = new QLabel(username.c_str());
    call_btn = new QPushButton("Call");
    remove_from_call_btn = new QPushButton("-");
    add_to_list_btn = new QPushButton("+");
    remove_from_list_btn = new QPushButton("-");
    mainLayout = new QGridLayout;

    this->user.username = username;
    this->user.address = address;

    if (in_list)
        this->contact_state = Added;
    else
        this->contact_state = None;

    connect(call_btn, SIGNAL(clicked()), this, SLOT(call()));
    connect(remove_from_call_btn, SIGNAL(clicked()), this, SLOT(removeFromCall
    ()));
    connect(add_to_list_btn, SIGNAL(clicked()), this, SLOT(addToList()));
    connect(remove_from_list_btn, SIGNAL(clicked()), this, SLOT(removeFromList
    ()));
    update();
}


User Contact::call()
{
    contact_context = Call;
    update();
    return this->user;
}

User Contact::addToList()
{
    contact_state = Added;
    update();
    return this->user;
}

void Contact::removeFromList()
{
    contact_state = None;
    update();
}

void Contact::removeFromCall()
{
}

void Contact::setContext(Context newContext)
{
    this->contact_context = newContext;
    update();
}

void Contact::resetLayout() const
{
    QLayoutItem* item;

    while ( ( item = mainLayout->takeAt( 0 ) ) != nullptr )
    {
        delete item->widget();
        delete item;
    }
}

void Contact::update()
{

    resetLayout();

    mainLayout->addWidget(name_label, 0, 0);

    switch (contact_context) {
        case Menu:
        case Adding:
            if (contact_state == None) {
                this->add_to_list_btn->setEnabled(true);
                mainLayout->addWidget(add_to_list_btn, 0, 1);
            }
            else {
                this->remove_from_list_btn->setEnabled(true);
                this->call_btn->setEnabled(true);
                mainLayout->addWidget(remove_from_list_btn, 0, 1);
                mainLayout->addWidget(call_btn, 0, 2);
            }
            break;

        case Call:
            // Nothing to do
            break;
        case ConfCall:
            this->remove_from_call_btn->setEnabled(true);
            mainLayout->addWidget(remove_from_call_btn, 0, 1);

    }
}


QPushButton *Contact::get_call()
{
    return call_btn;
}

QPushButton *Contact::get_remove_from_call()
{
    return remove_from_call_btn;
}

QPushButton *Contact::get_add_to_list()
{
    return add_to_list_btn;
}

QPushButton *Contact::get_remove_from_list() {
    return remove_from_list_btn;
}
