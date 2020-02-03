/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT-src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[452];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "testSignal"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "color"
QT_MOC_LITERAL(4, 29, 27), // "on_actionGenerate_triggered"
QT_MOC_LITERAL(5, 57, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(6, 81, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(7, 108, 25), // "on_actionExport_triggered"
QT_MOC_LITERAL(8, 134, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(9, 158, 23), // "on_actionUndo_triggered"
QT_MOC_LITERAL(10, 182, 23), // "on_actionRedo_triggered"
QT_MOC_LITERAL(11, 206, 34), // "on_actionChanger_couleur_trig..."
QT_MOC_LITERAL(12, 241, 20), // "onColorTabletChanged"
QT_MOC_LITERAL(13, 262, 22), // "updateLastSelectedNode"
QT_MOC_LITERAL(14, 285, 9), // "id_sommet"
QT_MOC_LITERAL(15, 295, 22), // "updateLastSelectedEdge"
QT_MOC_LITERAL(16, 318, 5), // "Edge&"
QT_MOC_LITERAL(17, 324, 1), // "e"
QT_MOC_LITERAL(18, 326, 18), // "getEveryEdgeOfLine"
QT_MOC_LITERAL(19, 345, 12), // "QList<Edge*>"
QT_MOC_LITERAL(20, 358, 8), // "num_line"
QT_MOC_LITERAL(21, 367, 28), // "on_actionTabulaire_triggered"
QT_MOC_LITERAL(22, 396, 28), // "on_actionGraphique_triggered"
QT_MOC_LITERAL(23, 425, 26) // "on_actionGlobale_triggered"

    },
    "MainWindow\0testSignal\0\0color\0"
    "on_actionGenerate_triggered\0"
    "on_actionOpen_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_actionExport_triggered\0"
    "on_actionExit_triggered\0on_actionUndo_triggered\0"
    "on_actionRedo_triggered\0"
    "on_actionChanger_couleur_triggered\0"
    "onColorTabletChanged\0updateLastSelectedNode\0"
    "id_sommet\0updateLastSelectedEdge\0Edge&\0"
    "e\0getEveryEdgeOfLine\0QList<Edge*>\0"
    "num_line\0on_actionTabulaire_triggered\0"
    "on_actionGraphique_triggered\0"
    "on_actionGlobale_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   97,    2, 0x08 /* Private */,
       5,    0,   98,    2, 0x08 /* Private */,
       6,    0,   99,    2, 0x08 /* Private */,
       7,    0,  100,    2, 0x08 /* Private */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    1,  105,    2, 0x08 /* Private */,
      13,    1,  108,    2, 0x08 /* Private */,
      15,    1,  111,    2, 0x08 /* Private */,
      18,    1,  114,    2, 0x08 /* Private */,
      21,    0,  117,    2, 0x08 /* Private */,
      22,    0,  118,    2, 0x08 /* Private */,
      23,    0,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    0x80000000 | 19, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testSignal((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->on_actionGenerate_triggered(); break;
        case 2: _t->on_actionOpen_triggered(); break;
        case 3: _t->on_actionSave_as_triggered(); break;
        case 4: _t->on_actionExport_triggered(); break;
        case 5: _t->on_actionExit_triggered(); break;
        case 6: _t->on_actionUndo_triggered(); break;
        case 7: _t->on_actionRedo_triggered(); break;
        case 8: _t->on_actionChanger_couleur_triggered(); break;
        case 9: _t->onColorTabletChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 10: _t->updateLastSelectedNode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateLastSelectedEdge((*reinterpret_cast< Edge(*)>(_a[1]))); break;
        case 12: { QList<Edge*> _r = _t->getEveryEdgeOfLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<Edge*>*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->on_actionTabulaire_triggered(); break;
        case 14: _t->on_actionGraphique_triggered(); break;
        case 15: _t->on_actionGlobale_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::testSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::testSignal(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
