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
    char stringdata0[228];
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
QT_MOC_LITERAL(7, 53, 16), // "addContactToCall"
QT_MOC_LITERAL(8, 70, 11), // "user_to_add"
QT_MOC_LITERAL(9, 82, 19), // "removeContactToCall"
QT_MOC_LITERAL(10, 102, 14), // "user_to_remove"
QT_MOC_LITERAL(11, 117, 10), // "addContact"
QT_MOC_LITERAL(12, 128, 13), // "removeContact"
QT_MOC_LITERAL(13, 142, 10), // "getContext"
QT_MOC_LITERAL(14, 153, 5), // "login"
QT_MOC_LITERAL(15, 159, 9), // "loginCode"
QT_MOC_LITERAL(16, 169, 11), // "std::string"
QT_MOC_LITERAL(17, 181, 8), // "username"
QT_MOC_LITERAL(18, 190, 8), // "password"
QT_MOC_LITERAL(19, 199, 6), // "update"
QT_MOC_LITERAL(20, 206, 21) // "convertUserFromString"

    },
    "App\0call\0\0UserApp\0user_to_call\0"
    "acceptCall\0refuseCall\0addContactToCall\0"
    "user_to_add\0removeContactToCall\0"
    "user_to_remove\0addContact\0removeContact\0"
    "getContext\0login\0loginCode\0std::string\0"
    "username\0password\0update\0convertUserFromString"
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
       7,    1,   74,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      11,    1,   80,    2, 0x0a /* Public */,
      12,    1,   83,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    2,   87,    2, 0x0a /* Public */,
      19,    0,   92,    2, 0x0a /* Public */,
      20,    1,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Bool, 0x80000000 | 3,    8,
    QMetaType::Bool, 0x80000000 | 3,   10,
    0x80000000 | 3,
    0x80000000 | 15, 0x80000000 | 16, 0x80000000 | 16,   17,   18,
    QMetaType::Void,
    0x80000000 | 3, 0x80000000 | 16,   17,

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
        case 3: _t->addContactToCall((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 4: _t->removeContactToCall((*reinterpret_cast< UserApp(*)>(_a[1]))); break;
        case 5: { bool _r = _t->addContact((*reinterpret_cast< UserApp(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->removeContact((*reinterpret_cast< UserApp(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { UserApp _r = _t->getContext();
            if (_a[0]) *reinterpret_cast< UserApp*>(_a[0]) = std::move(_r); }  break;
        case 8: { loginCode _r = _t->login((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< loginCode*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->update(); break;
        case 10: { UserApp _r = _t->convertUserFromString((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< UserApp*>(_a[0]) = std::move(_r); }  break;
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
