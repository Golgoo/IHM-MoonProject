/****************************************************************************
** Meta object code from reading C++ file 'random_generation_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT-src/random_generation_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'random_generation_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RandomGenerationDialog_t {
    QByteArrayData data[12];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RandomGenerationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RandomGenerationDialog_t qt_meta_stringdata_RandomGenerationDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "RandomGenerationDialog"
QT_MOC_LITERAL(1, 23, 15), // "columns_changed"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "nb_cols"
QT_MOC_LITERAL(4, 48, 14), // "column_renamed"
QT_MOC_LITERAL(5, 63, 24), // "update_current_generator"
QT_MOC_LITERAL(6, 88, 24), // "change_current_generator"
QT_MOC_LITERAL(7, 113, 21), // "change_generator_type"
QT_MOC_LITERAL(8, 135, 18), // "type_clicked_index"
QT_MOC_LITERAL(9, 154, 4), // "done"
QT_MOC_LITERAL(10, 159, 1), // "r"
QT_MOC_LITERAL(11, 161, 26) // "apply_to_another_generator"

    },
    "RandomGenerationDialog\0columns_changed\0"
    "\0nb_cols\0column_renamed\0"
    "update_current_generator\0"
    "change_current_generator\0change_generator_type\0"
    "type_clicked_index\0done\0r\0"
    "apply_to_another_generator"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RandomGenerationDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       9,    1,   58,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void RandomGenerationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RandomGenerationDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->columns_changed((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->column_renamed(); break;
        case 2: _t->update_current_generator(); break;
        case 3: _t->change_current_generator(); break;
        case 4: _t->change_generator_type((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->done((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->apply_to_another_generator(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RandomGenerationDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_RandomGenerationDialog.data,
    qt_meta_data_RandomGenerationDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RandomGenerationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RandomGenerationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RandomGenerationDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RandomGenerationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
