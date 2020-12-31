/****************************************************************************
** Meta object code from reading C++ file 'frame_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Clipping/frame_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frame_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frame_widget_t {
    QByteArrayData data[17];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frame_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frame_widget_t qt_meta_stringdata_frame_widget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "frame_widget"
QT_MOC_LITERAL(1, 13, 9), // "sendCoord"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 1), // "x"
QT_MOC_LITERAL(4, 26, 1), // "y"
QT_MOC_LITERAL(5, 28, 9), // "sendPress"
QT_MOC_LITERAL(6, 38, 14), // "sendColorLebel"
QT_MOC_LITERAL(7, 53, 1), // "a"
QT_MOC_LITERAL(8, 55, 1), // "b"
QT_MOC_LITERAL(9, 57, 1), // "c"
QT_MOC_LITERAL(10, 59, 18), // "sendFillColorLebel"
QT_MOC_LITERAL(11, 78, 8), // "sendTime"
QT_MOC_LITERAL(12, 87, 17), // "displayPolygonEnd"
QT_MOC_LITERAL(13, 105, 19), // "displayPolygonStart"
QT_MOC_LITERAL(14, 125, 12), // "startPolygon"
QT_MOC_LITERAL(15, 138, 10), // "endPolygon"
QT_MOC_LITERAL(16, 149, 8) // "sendSeed"

    },
    "frame_widget\0sendCoord\0\0x\0y\0sendPress\0"
    "sendColorLebel\0a\0b\0c\0sendFillColorLebel\0"
    "sendTime\0displayPolygonEnd\0"
    "displayPolygonStart\0startPolygon\0"
    "endPolygon\0sendSeed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frame_widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       5,    2,   69,    2, 0x06 /* Public */,
       6,    3,   74,    2, 0x06 /* Public */,
      10,    3,   81,    2, 0x06 /* Public */,
      11,    1,   88,    2, 0x06 /* Public */,
      12,    2,   91,    2, 0x06 /* Public */,
      13,    2,   96,    2, 0x06 /* Public */,
      14,    0,  101,    2, 0x06 /* Public */,
      15,    0,  102,    2, 0x06 /* Public */,
      16,    2,  103,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

       0        // eod
};

void frame_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<frame_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCoord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sendPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendColorLebel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->sendFillColorLebel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->sendTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->displayPolygonEnd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->displayPolygonStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->startPolygon(); break;
        case 8: _t->endPolygon(); break;
        case 9: _t->sendSeed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (frame_widget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::sendCoord)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::sendPress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::sendColorLebel)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::sendFillColorLebel)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::sendTime)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::displayPolygonEnd)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::displayPolygonStart)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::startPolygon)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::endPolygon)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (frame_widget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frame_widget::sendSeed)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject frame_widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_frame_widget.data,
    qt_meta_data_frame_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frame_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frame_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frame_widget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int frame_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void frame_widget::sendCoord(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void frame_widget::sendPress(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void frame_widget::sendColorLebel(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void frame_widget::sendFillColorLebel(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void frame_widget::sendTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void frame_widget::displayPolygonEnd(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void frame_widget::displayPolygonStart(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void frame_widget::startPolygon()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void frame_widget::endPolygon()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void frame_widget::sendSeed(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
