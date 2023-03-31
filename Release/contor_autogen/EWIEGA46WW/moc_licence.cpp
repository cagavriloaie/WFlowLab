/****************************************************************************
** Meta object code from reading C++ file 'licence.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Contor/licence.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'licence.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_License_t {
    uint offsetsAndSizes[12];
    char stringdata0[8];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[6];
    char stringdata5[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_License_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_License_t qt_meta_stringdata_License = {
    {
        QT_MOC_LITERAL(0, 7),  // "License"
        QT_MOC_LITERAL(8, 9),  // "showEvent"
        QT_MOC_LITERAL(18, 0),  // ""
        QT_MOC_LITERAL(19, 11),  // "QShowEvent*"
        QT_MOC_LITERAL(31, 5),  // "event"
        QT_MOC_LITERAL(37, 14)   // "onCloseClicked"
    },
    "License",
    "showEvent",
    "",
    "QShowEvent*",
    "event",
    "onCloseClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_License[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x08,    1 /* Private */,
       5,    0,   29,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject License::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_License.offsetsAndSizes,
    qt_meta_data_License,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_License_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<License, std::true_type>,
        // method 'showEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QShowEvent *, std::false_type>,
        // method 'onCloseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void License::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<License *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showEvent((*reinterpret_cast< std::add_pointer_t<QShowEvent*>>(_a[1]))); break;
        case 1: _t->onCloseClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *License::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *License::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_License.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int License::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
