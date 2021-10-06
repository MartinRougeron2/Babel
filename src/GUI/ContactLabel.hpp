/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** ContactLabel
*/

#include <QLabel>
#include <QWidget>
#include <Qt>

class ContactLabel : public QLabel {
    Q_OBJECT

    public:
        explicit ContactLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()) : QLabel(parent, f){}
        ~ContactLabel() {};

    signals:
        void clicked(const QString &);

    protected:
        void mousePressEvent(QMouseEvent* event) { emit clicked(this->text());};
};