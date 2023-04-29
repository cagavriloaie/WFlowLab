/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modbus/mainwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
    #include <QtCore/qtmochelpers.h>
#else
    QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
    #error "The header file 'mainwindow.h' doesn't include <QObject>."
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
    struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
    static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS =
        QtMocHelpers::stringData(
            "MainWindow",
            "readRegisters",
            "",
            "QModbusDataUnit::RegisterType",
            "table",
            "address",
            "size",
            "onPushTemperature",
            "onPushHumidity"
        );
#else  // !QT_MOC_HAS_STRING_DATA
    struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t
    {
        uint offsetsAndSizes[18];
        char stringdata0[11];
        char stringdata1[14];
        char stringdata2[1];
        char stringdata3[30];
        char stringdata4[6];
        char stringdata5[8];
        char stringdata6[5];
        char stringdata7[18];
        char stringdata8[15];
    };
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len
    Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t
    qt_meta_stringdata_CLASSMainWindowENDCLASS =
    {
        {
            QT_MOC_LITERAL(0, 10),  // "MainWindow"
            QT_MOC_LITERAL(11, 13),  // "readRegisters"
            QT_MOC_LITERAL(25, 0),  // ""
            QT_MOC_LITERAL(26, 29),  // "QModbusDataUnit::RegisterType"
            QT_MOC_LITERAL(56, 5),  // "table"
            QT_MOC_LITERAL(62, 7),  // "address"
            QT_MOC_LITERAL(70, 4),  // "size"
            QT_MOC_LITERAL(75, 17),  // "onPushTemperature"
            QT_MOC_LITERAL(93, 14)   // "onPushHumidity"
        },
        "MainWindow",
        "readRegisters",
        "",
        "QModbusDataUnit::RegisterType",
        "table",
        "address",
        "size",
        "onPushTemperature",
        "onPushHumidity"
    };
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[]
=
{

// content:
    11,       // revision
    0,       // classname
    0,    0, // classinfo
    3,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    0,       // signalCount

// slots: name, argc, parameters, tag, flags, initial metatype offsets
    1,    3,   32,    2, 0x08,    1 /* Private */,
    7,    0,   39,    2, 0x08,    5 /* Private */,
    8,    0,   40,    2, 0x08,    6 /* Private */,

// slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

    0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
        QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
        qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
        qt_meta_data_CLASSMainWindowENDCLASS,
        qt_static_metacall,
        nullptr,
        qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'readRegisters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModbusDataUnit::RegisterType, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onPushTemperature'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPushHumidity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
        >,
        nullptr
    }
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c,
                                    int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id)
        {
            case 0: _t->readRegisters((
                                              *reinterpret_cast< std::add_pointer_t<QModbusDataUnit::RegisterType>>
                                              (_a[1])), (*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),
                                          (*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
            case 1: _t->onPushTemperature(); break;
            case 2: _t->onPushHumidity(); break;
            default: ;
        }
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        switch (_id)
        {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                switch (*reinterpret_cast<int *>(_a[1]))
                {
                    default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
                    case 0:
                        *reinterpret_cast<QMetaType *>(_a[0]) =
                            QMetaType::fromType< QModbusDataUnit::RegisterType >(); break;
                }
                break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ?
           QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname)
    {
        return nullptr;
    }
    if (!strcmp(_clname,
                qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
    {
        return static_cast<void *>(this);
    }
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
    {
        return _id;
    }
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 3)
        {
            qt_static_metacall(this, _c, _id, _a);
        }
        _id -= 3;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 3)
        {
            qt_static_metacall(this, _c, _id, _a);
        }
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
