/****************************************************************************
** Meta object code from reading C++ file 'plugincurvemodel.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plugincurve/plugincurvemodel.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugincurvemodel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PluginCurveModel_t {
    QByteArrayData data[16];
    char stringdata[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PluginCurveModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PluginCurveModel_t qt_meta_stringdata_PluginCurveModel = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 8),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 1),
QT_MOC_LITERAL(4, 29, 11),
QT_MOC_LITERAL(5, 41, 5),
QT_MOC_LITERAL(6, 47, 17),
QT_MOC_LITERAL(7, 65, 5),
QT_MOC_LITERAL(8, 71, 14),
QT_MOC_LITERAL(9, 86, 9),
QT_MOC_LITERAL(10, 96, 6),
QT_MOC_LITERAL(11, 103, 6),
QT_MOC_LITERAL(12, 110, 13),
QT_MOC_LITERAL(13, 124, 19),
QT_MOC_LITERAL(14, 144, 7),
QT_MOC_LITERAL(15, 152, 16)
    },
    "PluginCurveModel\0setState\0\0b\0pointInsert\0"
    "index\0PluginCurvePoint*\0point\0"
    "pointRemoveOne\0pointSwap\0index1\0index2\0"
    "sectionAppend\0PluginCurveSection*\0"
    "section\0sectionRemoveOne\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginCurveModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a,
       4,    2,   47,    2, 0x0a,
       8,    1,   52,    2, 0x0a,
       9,    2,   55,    2, 0x0a,
      12,    1,   60,    2, 0x0a,
      15,    1,   63,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void PluginCurveModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PluginCurveModel *_t = static_cast<PluginCurveModel *>(_o);
        switch (_id) {
        case 0: _t->setState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->pointInsert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< PluginCurvePoint*(*)>(_a[2]))); break;
        case 2: _t->pointRemoveOne((*reinterpret_cast< PluginCurvePoint*(*)>(_a[1]))); break;
        case 3: _t->pointSwap((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sectionAppend((*reinterpret_cast< PluginCurveSection*(*)>(_a[1]))); break;
        case 5: _t->sectionRemoveOne((*reinterpret_cast< PluginCurveSection*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginCurvePoint* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginCurvePoint* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginCurveSection* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginCurveSection* >(); break;
            }
            break;
        }
    }
}

const QMetaObject PluginCurveModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PluginCurveModel.data,
      qt_meta_data_PluginCurveModel,  qt_static_metacall, 0, 0}
};


const QMetaObject *PluginCurveModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginCurveModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PluginCurveModel.stringdata))
        return static_cast<void*>(const_cast< PluginCurveModel*>(this));
    return QObject::qt_metacast(_clname);
}

int PluginCurveModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
