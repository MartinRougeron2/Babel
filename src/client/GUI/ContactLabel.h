/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** ContactLabel
*/

#include <QLabel>
#include <QWidget>
#include <Qt>
#include "common/User.h"

class ContactLabel : public QLabel {
    Q_OBJECT

    public:
        explicit ContactLabel(User user, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()) : QLabel(parent, f), _user(user){}
        ~ContactLabel() {};
        User getUser() { return _user;}

    // signals:
        void clicked(User);

    protected:
        void mousePressEvent(QMouseEvent* event) { emit clicked(_user);};

    private:
        User _user;
};
