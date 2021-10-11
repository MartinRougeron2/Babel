/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
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

void ContactLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(_user);
}

User ContactLabel::getUser()
{
    return _user;
}
