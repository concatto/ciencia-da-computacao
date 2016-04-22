/****************************************************************************
** Meta object code from reading C++ file 'processor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "processor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Processor_t {
    QByteArrayData data[10];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Processor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Processor_t qt_meta_stringdata_Processor = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Processor"
QT_MOC_LITERAL(1, 10, 21), // "programCounterChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "newIndex"
QT_MOC_LITERAL(4, 42, 13), // "memoryChanged"
QT_MOC_LITERAL(5, 56, 7), // "address"
QT_MOC_LITERAL(6, 64, 8), // "newValue"
QT_MOC_LITERAL(7, 73, 15), // "registerChanged"
QT_MOC_LITERAL(8, 89, 5), // "index"
QT_MOC_LITERAL(9, 95, 14) // "beginExecution"

    },
    "Processor\0programCounterChanged\0\0"
    "newIndex\0memoryChanged\0address\0newValue\0"
    "registerChanged\0index\0beginExecution"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Processor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,
       7,    2,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    5,    6,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    8,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Processor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Processor *_t = static_cast<Processor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->programCounterChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->memoryChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->registerChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->beginExecution(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Processor::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Processor::programCounterChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Processor::*_t)(unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Processor::memoryChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (Processor::*_t)(unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Processor::registerChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Processor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Processor.data,
      qt_meta_data_Processor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Processor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Processor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Processor.stringdata0))
        return static_cast<void*>(const_cast< Processor*>(this));
    return QObject::qt_metacast(_clname);
}

int Processor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Processor::programCounterChanged(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Processor::memoryChanged(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Processor::registerChanged(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
