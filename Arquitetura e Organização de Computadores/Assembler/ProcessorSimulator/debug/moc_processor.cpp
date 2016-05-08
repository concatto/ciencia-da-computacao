/****************************************************************************
** Meta object code from reading C++ file 'processor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../processor.h"
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
    QByteArrayData data[17];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Processor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Processor_t qt_meta_stringdata_Processor = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Processor"
QT_MOC_LITERAL(1, 10, 18), // "instructionDecoded"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "Instruction"
QT_MOC_LITERAL(4, 42, 11), // "instruction"
QT_MOC_LITERAL(5, 54, 14), // "programCounter"
QT_MOC_LITERAL(6, 69, 13), // "memoryChanged"
QT_MOC_LITERAL(7, 83, 7), // "address"
QT_MOC_LITERAL(8, 91, 8), // "newValue"
QT_MOC_LITERAL(9, 100, 15), // "registerChanged"
QT_MOC_LITERAL(10, 116, 5), // "index"
QT_MOC_LITERAL(11, 122, 19), // "executionTerminated"
QT_MOC_LITERAL(12, 142, 19), // "instructionNotFound"
QT_MOC_LITERAL(13, 162, 14), // "beginExecution"
QT_MOC_LITERAL(14, 177, 21), // "executeProcessorCycle"
QT_MOC_LITERAL(15, 199, 13), // "stopExecution"
QT_MOC_LITERAL(16, 213, 10) // "resetState"

    },
    "Processor\0instructionDecoded\0\0Instruction\0"
    "instruction\0programCounter\0memoryChanged\0"
    "address\0newValue\0registerChanged\0index\0"
    "executionTerminated\0instructionNotFound\0"
    "beginExecution\0executeProcessorCycle\0"
    "stopExecution\0resetState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Processor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       6,    2,   64,    2, 0x06 /* Public */,
       9,    2,   69,    2, 0x06 /* Public */,
      11,    0,   74,    2, 0x06 /* Public */,
      12,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   78,    2, 0x0a /* Public */,
      14,    0,   79,    2, 0x0a /* Public */,
      15,    0,   80,    2, 0x0a /* Public */,
      16,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    7,    8,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   10,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Processor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Processor *_t = static_cast<Processor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->instructionDecoded((*reinterpret_cast< Instruction(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 1: _t->memoryChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->registerChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->executionTerminated(); break;
        case 4: _t->instructionNotFound((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 5: _t->beginExecution(); break;
        case 6: _t->executeProcessorCycle(); break;
        case 7: _t->stopExecution(); break;
        case 8: _t->resetState(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Processor::*_t)(Instruction , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Processor::instructionDecoded)) {
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
        {
            typedef void (Processor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Processor::executionTerminated)) {
                *result = 3;
            }
        }
        {
            typedef void (Processor::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Processor::instructionNotFound)) {
                *result = 4;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Processor::instructionDecoded(Instruction _t1, unsigned int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
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

// SIGNAL 3
void Processor::executionTerminated()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Processor::instructionNotFound(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
