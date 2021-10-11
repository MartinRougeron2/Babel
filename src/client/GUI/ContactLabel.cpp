/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ContactLabel
*/

#include "ContactLabel.h"

ContactLabel::ContactLabel(User user, QWidget* parent, Qt::WindowFlags f) : QLabel(parent, f), _user(user)
{
}

ContactLabel::~ContactLabel()
{
}

User ContactLabel::getUser()
{
    return _user;
}

void ContactLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(_user);
}
