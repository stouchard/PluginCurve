/****************************************************************************
** Meta object code from reading C++ file 'plugincurveview.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plugincurve/plugincurveview.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugincurveview.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PluginCurveView_t {
    QByteArrayData data[19];
    char stringdata[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PluginCurveView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PluginCurveView_t qt_meta_stringdata_PluginCurveView = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 13),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 25),
QT_MOC_LITERAL(4, 57, 12),
QT_MOC_LITERAL(5, 70, 10),
QT_MOC_LITERAL(6, 81, 13),
QT_MOC_LITERAL(7, 95, 10),
QT_MOC_LITERAL(8, 106, 10),
QT_MOC_LITERAL(9, 117, 11),
QT_MOC_LITERAL(10, 129, 16),
QT_MOC_LITERAL(11, 146, 15),
QT_MOC_LITERAL(12, 162, 27),
QT_MOC_LITERAL(13, 190, 24),
QT_MOC_LITERAL(14, 215, 22),
QT_MOC_LITERAL(15, 238, 29),
QT_MOC_LITERAL(16, 268, 11),
QT_MOC_LITERAL(17, 280, 12),
QT_MOC_LITERAL(18, 293, 6)
    },
    "PluginCurveView\0doubleClicked\0\0"
    "QGraphicsSceneMouseEvent*\0mousePressed\0"
    "mouseMoved\0mouseReleased\0keyPressed\0"
    "QKeyEvent*\0keyReleased\0viewSceneChanged\0"
    "QGraphicsScene*\0startDrawSelectionRectangle\0"
    "originSelectionRectangle\0"
    "drawSelectionrectangle\0"
    "destinationSelectionRectangle\0selectItems\0"
    "changeCursor\0cursor\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginCurveView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x05,
       4,    1,   72,    2, 0x05,
       5,    1,   75,    2, 0x05,
       6,    1,   78,    2, 0x05,
       7,    1,   81,    2, 0x05,
       9,    1,   84,    2, 0x05,
      10,    1,   87,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      12,    1,   90,    2, 0x0a,
      14,    2,   93,    2, 0x0a,
      16,    0,   98,    2, 0x0a,
      17,    1,   99,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 11,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,   13,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QCursor,   18,

       0        // eod
};

void PluginCurveView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PluginCurveView *_t = static_cast<PluginCurveView *>(_o);
        switch (_id) {
        case 0: _t->doubleClicked((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mousePressed((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseMoved((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->mouseReleased((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->keyPressed((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 5: _t->keyReleased((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 6: _t->viewSceneChanged((*reinterpret_cast< QGraphicsScene*(*)>(_a[1]))); break;
        case 7: _t->startDrawSelectionRectangle((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 8: _t->drawSelectionrectangle((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 9: _t->selectItems(); break;
        case 10: _t->changeCursor((*reinterpret_cast< QCursor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PluginCurveView::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::doubleClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (PluginCurveView::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::mousePressed)) {
                *result = 1;
            }
        }
        {
            typedef void (PluginCurveView::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::mouseMoved)) {
                *result = 2;
            }
        }
        {
            typedef void (PluginCurveView::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::mouseReleased)) {
                *result = 3;
            }
        }
        {
            typedef void (PluginCurveView::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::keyPressed)) {
                *result = 4;
            }
        }
        {
            typedef void (PluginCurveView::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::keyReleased)) {
                *result = 5;
            }
        }
        {
            typedef void (PluginCurveView::*_t)(QGraphicsScene * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginCurveView::viewSceneChanged)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject PluginCurveView::staticMetaObject = {
    { &QGraphicsObject::staticMetaObject, qt_meta_stringdata_PluginCurveView.data,
      qt_meta_data_PluginCurveView,  qt_static_metacall, 0, 0}
};


const QMetaObject *PluginCurveView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginCurveView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PluginCurveView.stringdata))
        return static_cast<void*>(const_cast< PluginCurveView*>(this));
    return QGraphicsObject::qt_metacast(_clname);
}

int PluginCurveView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PluginCurveView::doubleClicked(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PluginCurveView::mousePressed(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PluginCurveView::mouseMoved(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PluginCurveView::mouseReleased(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PluginCurveView::keyPressed(QKeyEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PluginCurveView::keyReleased(QKeyEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PluginCurveView::viewSceneChanged(QGraphicsScene * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
