/****************************************************************************
** Meta object code from reading C++ file 'quitreeuihelper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/quitreeuihelper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quitreeuihelper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_YCQUiTreeUiHelper_t {
    QByteArrayData data[10];
    char stringdata[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_YCQUiTreeUiHelper_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_YCQUiTreeUiHelper_t qt_meta_stringdata_YCQUiTreeUiHelper = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 17),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 6),
QT_MOC_LITERAL(4, 44, 18),
QT_MOC_LITERAL(5, 63, 7),
QT_MOC_LITERAL(6, 71, 24),
QT_MOC_LITERAL(7, 96, 13),
QT_MOC_LITERAL(8, 110, 24),
QT_MOC_LITERAL(9, 135, 13)
    },
    "YCQUiTreeUiHelper\0onItemChangedSize\0"
    "\0roSize\0onItemChangedBound\0roBound\0"
    "onItemChangedLayerWeight\0riLayerWeight\0"
    "onItemChangedImageSource\0rsImageSource\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YCQUiTreeUiHelper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a,
       4,    1,   37,    2, 0x0a,
       6,    1,   40,    2, 0x0a,
       8,    1,   43,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::QSize,    3,
    QMetaType::Void, QMetaType::QRect,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void YCQUiTreeUiHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        YCQUiTreeUiHelper *_t = static_cast<YCQUiTreeUiHelper *>(_o);
        switch (_id) {
        case 0: _t->onItemChangedSize((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 1: _t->onItemChangedBound((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        case 2: _t->onItemChangedLayerWeight((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onItemChangedImageSource((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject YCQUiTreeUiHelper::staticMetaObject = {
    { &YCQUiTreeHelper::staticMetaObject, qt_meta_stringdata_YCQUiTreeUiHelper.data,
      qt_meta_data_YCQUiTreeUiHelper,  qt_static_metacall, 0, 0}
};


const QMetaObject *YCQUiTreeUiHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YCQUiTreeUiHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_YCQUiTreeUiHelper.stringdata))
        return static_cast<void*>(const_cast< YCQUiTreeUiHelper*>(this));
    return YCQUiTreeHelper::qt_metacast(_clname);
}

int YCQUiTreeUiHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = YCQUiTreeHelper::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE