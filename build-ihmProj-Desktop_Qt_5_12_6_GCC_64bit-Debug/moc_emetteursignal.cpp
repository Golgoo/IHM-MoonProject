/****************************************************************************
** Meta object code from reading C++ file 'emetteursignal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT-src/emetteursignal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emetteursignal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EmetteurSignal_t {
    QByteArrayData data[7];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EmetteurSignal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EmetteurSignal_t qt_meta_stringdata_EmetteurSignal = {
    {
QT_MOC_LITERAL(0, 0, 14), // "EmetteurSignal"
QT_MOC_LITERAL(1, 15, 16), // "lastSelectedNode"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "id_sommet"
QT_MOC_LITERAL(4, 43, 16), // "lastSelectedEdge"
QT_MOC_LITERAL(5, 60, 5), // "Edge&"
QT_MOC_LITERAL(6, 66, 1) // "e"

    },
    "EmetteurSignal\0lastSelectedNode\0\0"
    "id_sommet\0lastSelectedEdge\0Edge&\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EmetteurSignal[] = {

 // content:
       8,       // revision
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
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void EmetteurSignal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EmetteurSignal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lastSelectedNode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->lastSelectedEdge((*reinterpret_cast< Edge(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EmetteurSignal::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EmetteurSignal::lastSelectedNode)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EmetteurSignal::*)(Edge & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EmetteurSignal::lastSelectedEdge)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EmetteurSignal::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_EmetteurSignal.data,
    qt_meta_data_EmetteurSignal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EmetteurSignal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmetteurSignal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EmetteurSignal.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EmetteurSignal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void EmetteurSignal::lastSelectedNode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EmetteurSignal::lastSelectedEdge(Edge & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
