/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Contor/dialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_Dialog_t {
    uint offsetsAndSizes[24];
    char stringdata0[7];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[15];
    char stringdata5[19];
    char stringdata6[29];
    char stringdata7[19];
    char stringdata8[25];
    char stringdata9[14];
    char stringdata10[12];
    char stringdata11[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Dialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
        QT_MOC_LITERAL(0, 6),  // "Dialog"
        QT_MOC_LITERAL(7, 18),  // "onCalculateClicked"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 14),  // "onCleanClicked"
        QT_MOC_LITERAL(42, 14),  // "onCloseClicked"
        QT_MOC_LITERAL(57, 18),  // "onTypeMeterChanged"
        QT_MOC_LITERAL(76, 28),  // "onNumberOfWaterMetersChanged"
        QT_MOC_LITERAL(105, 18),  // "onSelectAllChanged"
        QT_MOC_LITERAL(124, 24),  // "onMeasurementTypeChanged"
        QT_MOC_LITERAL(149, 13),  // "onPrintPdfDoc"
        QT_MOC_LITERAL(163, 11),  // "onCbClicked"
        QT_MOC_LITERAL(175, 6)   // "status"
    },
    "Dialog",
    "onCalculateClicked",
    "",
    "onCleanClicked",
    "onCloseClicked",
    "onTypeMeterChanged",
    "onNumberOfWaterMetersChanged",
    "onSelectAllChanged",
    "onMeasurementTypeChanged",
    "onPrintPdfDoc",
    "onCbClicked",
    "status"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Dialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    1,   76,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject Dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Dialog.offsetsAndSizes,
    qt_meta_data_Dialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Dialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Dialog, std::true_type>,
        // method 'onCalculateClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCleanClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCloseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTypeMeterChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNumberOfWaterMetersChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSelectAllChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMeasurementTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPrintPdfDoc'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCbClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCalculateClicked(); break;
        case 1: _t->onCleanClicked(); break;
        case 2: _t->onCloseClicked(); break;
        case 3: _t->onTypeMeterChanged(); break;
        case 4: _t->onNumberOfWaterMetersChanged(); break;
        case 5: _t->onSelectAllChanged(); break;
        case 6: _t->onMeasurementTypeChanged(); break;
        case 7: _t->onPrintPdfDoc(); break;
        case 8: _t->onCbClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
