/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Meter/interface.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
    #include <QtCore/qtmochelpers.h>
#else
    QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
    #error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
    #error "This file was generated using the moc from 6.5.0. It"
    #error "cannot be used with the include files from this version of Qt."
    #error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
    #define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace
{

#ifdef QT_MOC_HAS_STRINGDATA
    struct qt_meta_stringdata_CLASSInterfaceENDCLASS_t {};
    static constexpr auto qt_meta_stringdata_CLASSInterfaceENDCLASS =
        QtMocHelpers::stringData(
            "Interface",
            "onCloseClicked",
            "",
            "onSaveClicked",
            "onRefreshClicked",
            "showEvent",
            "QShowEvent*",
            "event",
            "onSelectSerialChanged",
            "onBaudRateChanged",
            "onSelectDataBitsnChanged",
            "onSelectParityChanged",
            "onSelectStopBitsChanged"
        );
#else  // !QT_MOC_HAS_STRING_DATA
    struct qt_meta_stringdata_CLASSInterfaceENDCLASS_t
    {
        uint offsetsAndSizes[26];
        char stringdata0[10];
        char stringdata1[15];
        char stringdata2[1];
        char stringdata3[14];
        char stringdata4[17];
        char stringdata5[10];
        char stringdata6[12];
        char stringdata7[6];
        char stringdata8[22];
        char stringdata9[18];
        char stringdata10[25];
        char stringdata11[22];
        char stringdata12[24];
    };
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSInterfaceENDCLASS_t::offsetsAndSizes) + ofs), len
    Q_CONSTINIT static const qt_meta_stringdata_CLASSInterfaceENDCLASS_t
    qt_meta_stringdata_CLASSInterfaceENDCLASS =
    {
        {
            QT_MOC_LITERAL(0, 9),  // "Interface"
            QT_MOC_LITERAL(10, 14),  // "onCloseClicked"
            QT_MOC_LITERAL(25, 0),  // ""
            QT_MOC_LITERAL(26, 13),  // "onSaveClicked"
            QT_MOC_LITERAL(40, 16),  // "onRefreshClicked"
            QT_MOC_LITERAL(57, 9),  // "showEvent"
            QT_MOC_LITERAL(67, 11),  // "QShowEvent*"
            QT_MOC_LITERAL(79, 5),  // "event"
            QT_MOC_LITERAL(85, 21),  // "onSelectSerialChanged"
            QT_MOC_LITERAL(107, 17),  // "onBaudRateChanged"
            QT_MOC_LITERAL(125, 24),  // "onSelectDataBitsnChanged"
            QT_MOC_LITERAL(150, 21),  // "onSelectParityChanged"
            QT_MOC_LITERAL(172, 23)   // "onSelectStopBitsChanged"
        },
        "Interface",
        "onCloseClicked",
        "",
        "onSaveClicked",
        "onRefreshClicked",
        "showEvent",
        "QShowEvent*",
        "event",
        "onSelectSerialChanged",
        "onBaudRateChanged",
        "onSelectDataBitsnChanged",
        "onSelectParityChanged",
        "onSelectStopBitsChanged"
    };
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInterfaceENDCLASS[] =
{

// content:
    11,       // revision
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
    5,    1,   71,    2, 0x08,    4 /* Private */,
    8,    0,   74,    2, 0x08,    6 /* Private */,
    9,    0,   75,    2, 0x08,    7 /* Private */,
    10,    0,   76,    2, 0x08,    8 /* Private */,
    11,    0,   77,    2, 0x08,    9 /* Private */,
    12,    0,   78,    2, 0x08,   10 /* Private */,

// slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

    0        // eod
};

Q_CONSTINIT const QMetaObject Interface::staticMetaObject = { {
        QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
        qt_meta_stringdata_CLASSInterfaceENDCLASS.offsetsAndSizes,
        qt_meta_data_CLASSInterfaceENDCLASS,
        qt_static_metacall,
        nullptr,
        qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInterfaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Interface, std::true_type>,
        // method 'onCloseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRefreshClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QShowEvent *, std::false_type>,
        // method 'onSelectSerialChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBaudRateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSelectDataBitsnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSelectParityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSelectStopBitsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
        >,
        nullptr
    }
};

void Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c,
                                   int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto *_t = static_cast<Interface *>(_o);
        (void)_t;
        switch (_id)
        {
            case 0: _t->onCloseClicked(); break;
            case 1: _t->onSaveClicked(); break;
            case 2: _t->onRefreshClicked(); break;
            case 3: _t->showEvent((
                                          *reinterpret_cast< std::add_pointer_t<QShowEvent *>>(_a[1]))); break;
            case 4: _t->onSelectSerialChanged(); break;
            case 5: _t->onBaudRateChanged(); break;
            case 6: _t->onSelectDataBitsnChanged(); break;
            case 7: _t->onSelectParityChanged(); break;
            case 8: _t->onSelectStopBitsChanged(); break;
            default: ;
        }
    }
}

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ?
           QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname)
    {
        return nullptr;
    }
    if (!strcmp(_clname,
                qt_meta_stringdata_CLASSInterfaceENDCLASS.stringdata0))
    {
        return static_cast<void *>(this);
    }
    return QDialog::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
    {
        return _id;
    }
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 9)
        {
            qt_static_metacall(this, _c, _id, _a);
        }
        _id -= 9;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 9)
        {
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        }
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
