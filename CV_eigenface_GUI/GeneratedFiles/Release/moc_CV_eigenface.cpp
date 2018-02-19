/****************************************************************************
** Meta object code from reading C++ file 'CV_eigenface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CV_eigenface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CV_eigenface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CV_eigenface_t {
    QByteArrayData data[22];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CV_eigenface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CV_eigenface_t qt_meta_stringdata_CV_eigenface = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CV_eigenface"
QT_MOC_LITERAL(1, 13, 8), // "MatStore"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "MatRead"
QT_MOC_LITERAL(4, 31, 10), // "difference"
QT_MOC_LITERAL(5, 42, 4), // "Mat&"
QT_MOC_LITERAL(6, 47, 4), // "mat1"
QT_MOC_LITERAL(7, 52, 4), // "mat2"
QT_MOC_LITERAL(8, 57, 1), // "m"
QT_MOC_LITERAL(9, 59, 9), // "prehandle"
QT_MOC_LITERAL(10, 69, 3), // "src"
QT_MOC_LITERAL(11, 73, 11), // "reconstruct"
QT_MOC_LITERAL(12, 85, 7), // "retrive"
QT_MOC_LITERAL(13, 93, 13), // "myreconstruct"
QT_MOC_LITERAL(14, 107, 3), // "Mat"
QT_MOC_LITERAL(15, 111, 3), // "pic"
QT_MOC_LITERAL(16, 115, 14), // "calculateEigen"
QT_MOC_LITERAL(17, 130, 6), // "covMat"
QT_MOC_LITERAL(18, 137, 14), // "eigenfaceSpace"
QT_MOC_LITERAL(19, 152, 4), // "Load"
QT_MOC_LITERAL(20, 157, 12), // "testRetrival"
QT_MOC_LITERAL(21, 170, 10) // "myRetrival"

    },
    "CV_eigenface\0MatStore\0\0MatRead\0"
    "difference\0Mat&\0mat1\0mat2\0m\0prehandle\0"
    "src\0reconstruct\0retrive\0myreconstruct\0"
    "Mat\0pic\0calculateEigen\0covMat\0"
    "eigenfaceSpace\0Load\0testRetrival\0"
    "myRetrival"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CV_eigenface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    3,   71,    2, 0x0a /* Public */,
       9,    1,   78,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    0,   82,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,
      16,    2,   86,    2, 0x0a /* Public */,
      19,    0,   91,    2, 0x0a /* Public */,
      20,    0,   92,    2, 0x0a /* Public */,
      21,    1,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Float, 0x80000000 | 5, 0x80000000 | 5, QMetaType::Int,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 5,   10,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 14, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 5,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void CV_eigenface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CV_eigenface *_t = static_cast<CV_eigenface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->MatStore(); break;
        case 1: _t->MatRead(); break;
        case 2: { float _r = _t->difference((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 3: _t->prehandle((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 4: _t->reconstruct(); break;
        case 5: _t->retrive(); break;
        case 6: { Mat _r = _t->myreconstruct((*reinterpret_cast< Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Mat*>(_a[0]) = _r; }  break;
        case 7: _t->calculateEigen((*reinterpret_cast< const Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 8: _t->Load(); break;
        case 9: _t->testRetrival(); break;
        case 10: _t->myRetrival((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CV_eigenface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CV_eigenface.data,
      qt_meta_data_CV_eigenface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CV_eigenface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CV_eigenface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CV_eigenface.stringdata0))
        return static_cast<void*>(const_cast< CV_eigenface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CV_eigenface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
