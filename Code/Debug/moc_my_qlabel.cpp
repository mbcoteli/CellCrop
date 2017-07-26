/****************************************************************************
** Meta object code from reading C++ file 'my_qlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../my_qlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_qlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_my_qlabel_t {
    QByteArrayData data[6];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_my_qlabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_my_qlabel_t qt_meta_stringdata_my_qlabel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "my_qlabel"
QT_MOC_LITERAL(1, 10, 13), // "Mouse_Pressed"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "number"
QT_MOC_LITERAL(4, 32, 16), // "Select_Rectangle"
QT_MOC_LITERAL(5, 49, 7) // "m_point"

    },
    "my_qlabel\0Mouse_Pressed\0\0number\0"
    "Select_Rectangle\0m_point"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_my_qlabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QPoint,    5,

       0        // eod
};

void my_qlabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        my_qlabel *_t = static_cast<my_qlabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Mouse_Pressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->Select_Rectangle((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (my_qlabel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&my_qlabel::Mouse_Pressed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (my_qlabel::*_t)(QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&my_qlabel::Select_Rectangle)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject my_qlabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_my_qlabel.data,
      qt_meta_data_my_qlabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *my_qlabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *my_qlabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_my_qlabel.stringdata0))
        return static_cast<void*>(const_cast< my_qlabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int my_qlabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void my_qlabel::Mouse_Pressed(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void my_qlabel::Select_Rectangle(QPoint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
