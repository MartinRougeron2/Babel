/****************************************************************************
** Meta object code from reading C++ file 'App.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/client/GUI/App.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'App.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_App_t {
    QByteArrayData data[21];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_App_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_App_t qt_meta_stringdata_App = {
    {
QT_MOC_LITERAL(0, 0, 3), // "App"
QT_MOC_LITERAL(1, 4, 4), // "call"
QT_MOC_LITERAL(2, 9, 0), // ""
QT_MOC_LITERAL(3, 10, 7), // "UserApp"
QT_MOC_LITERAL(4, 18, 12), // "user_to_call"
QT_MOC_LITERAL(5, 31, 10), // "acceptCall"
QT_MOC_LITERAL(6, 42, 10), // "refuseCall"
QT_MOC_LITERAL(7, 53, 7), // "dismiss"
QT_MOC_LITERAL(8, 61, 16), // "addContactToCall"
QT_MOC_LITERAL(9, 78, 11), // "user_to_add"
QT_MOC_LITERAL(10, 90, 19), // "removeContactToCall"
QT_MOC_LITERAL(11, 110, 14), // "user_to_remove"
QT_MOC_LITERAL(12, 125, 10), // "addContact"
QT_MOC_LITERAL(13, 136, 13), // "removeContact"
QT_MOC_LITERAL(14, 150, 10), // "getContext"
QT_MOC_LITERAL(15, 161, 5), // "login"
QT_MOC_LITERAL(16, 167, 9), // "loginCode"
QT_MOC_LITERAL(17, 177, 11), // "std::string"
QT_MOC_LITERAL(18, 189, 8), // "username"
QT_MOC_LITERAL(19, 198, 8), // "password"
QT_MOC_LITERAL(20, 207, 6) // "update"

    },
    "App\0call\0\0UserApp\0user_to_call\0"
    "acceptCall\0refuseCall\0dismiss\0"
    "addContactToCall\0user_to_add\0"
    "removeContactToCall\0user_to_remove\0"
    "addContact\0removeContact\0getContext\0"
    "login\0loginCode\0std::string\0username\0"
    "password\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_App[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
      10,    1,   78,    2, 0x0a /* Public */,
      12,    1,   81,    2, 0x0a /* Public */,
      13,    1,   84,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,
      15,    2,   88,    2, 0x0a /* Public */,
      20,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 3,   11,
    0x80000000 | 3,
    0x80000000 | 16, 0x80000000 | 17, 0x80000000 | 17,   18,   19,
    QMetaType::Void,

       0        // eod
};

void App::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<App *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->call((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 1: _t->acceptCall(); break;
        case 2: _t->refuseCall(); break;
        case 3: _t->dismiss(); break;
        case 4: _t->addContactToCall((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 5: _t->removeContactToCall((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 6: _t->addContact((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 7: _t->removeContact((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 8: { UserApp _r = _t->getContext();
            if (_a[0]) *reinterpret_cast< UserApp*>(_a[0]) = std::move(_r); }  break;
        case 9: { loginCode _r = _t->login((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< loginCode*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->update(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject App::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_App.data,
    qt_meta_data_App,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *App::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *App::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_App.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int App::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
