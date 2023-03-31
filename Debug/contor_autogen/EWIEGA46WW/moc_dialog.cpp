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
    uint offsetsAndSizes[28];
    char stringdata0[7];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[29];
    char stringdata4[25];
    char stringdata5[19];
    char stringdata6[12];
    char stringdata7[7];
    char stringdata8[19];
    char stringdata9[15];
    char stringdata10[15];
    char stringdata11[30];
    char stringdata12[23];
    char stringdata13[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Dialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
        QT_MOC_LITERAL(0, 6),  // "Dialog"
        QT_MOC_LITERAL(7, 18),  // "onTypeMeterChanged"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 28),  // "onNumberOfWaterMetersChanged"
        QT_MOC_LITERAL(56, 24),  // "onMeasurementTypeChanged"
        QT_MOC_LITERAL(81, 18),  // "onSelectAllChanged"
        QT_MOC_LITERAL(100, 11),  // "onCbClicked"
        QT_MOC_LITERAL(112, 6),  // "status"
        QT_MOC_LITERAL(119, 18),  // "onCalculateClicked"
        QT_MOC_LITERAL(138, 14),  // "onCleanClicked"
        QT_MOC_LITERAL(153, 14),  // "onCloseClicked"
        QT_MOC_LITERAL(168, 29),  // "onSaveCurrentInputDataClicked"
        QT_MOC_LITERAL(198, 22),  // "onOpenInputDataClicked"
        QT_MOC_LITERAL(221, 20)   // "onPrintPdfDocClicked"
    },
    "Dialog",
    "onTypeMeterChanged",
    "",
    "onNumberOfWaterMetersChanged",
    "onMeasurementTypeChanged",
    "onSelectAllChanged",
    "onCbClicked",
    "status",
    "onCalculateClicked",
    "onCleanClicked",
    "onCloseClicked",
    "onSaveCurrentInputDataClicked",
    "onOpenInputDataClicked",
    "onPrintPdfDocClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Dialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    1,   84,    2, 0x08,    5 /* Private */,
       8,    0,   87,    2, 0x08,    7 /* Private */,
       9,    0,   88,    2, 0x08,    8 /* Private */,
      10,    0,   89,    2, 0x08,    9 /* Private */,
      11,    0,   90,    2, 0x08,   10 /* Private */,
      12,    0,   91,    2, 0x08,   11 /* Private */,
      13,    0,   92,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
        // method 'onTypeMeterChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNumberOfWaterMetersChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMeasurementTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSelectAllChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCbClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onCalculateClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCleanClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCloseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveCurrentInputDataClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onOpenInputDataClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPrintPdfDocClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onTypeMeterChanged(); break;
        case 1: _t->onNumberOfWaterMetersChanged(); break;
        case 2: _t->onMeasurementTypeChanged(); break;
        case 3: _t->onSelectAllChanged(); break;
        case 4: _t->onCbClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->onCalculateClicked(); break;
        case 6: _t->onCleanClicked(); break;
        case 7: _t->onCloseClicked(); break;
        case 8: _t->onSaveCurrentInputDataClicked(); break;
        case 9: _t->onOpenInputDataClicked(); break;
        case 10: _t->onPrintPdfDocClicked(); break;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
