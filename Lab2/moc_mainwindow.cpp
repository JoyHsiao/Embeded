/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata[454];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 26),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 21),
QT_MOC_LITERAL(4, 61, 23),
QT_MOC_LITERAL(5, 85, 23),
QT_MOC_LITERAL(6, 109, 4),
QT_MOC_LITERAL(7, 114, 26),
QT_MOC_LITERAL(8, 141, 21),
QT_MOC_LITERAL(9, 163, 23),
QT_MOC_LITERAL(10, 187, 25),
QT_MOC_LITERAL(11, 213, 26),
QT_MOC_LITERAL(12, 240, 21),
QT_MOC_LITERAL(13, 262, 23),
QT_MOC_LITERAL(14, 286, 22),
QT_MOC_LITERAL(15, 309, 21),
QT_MOC_LITERAL(16, 331, 22),
QT_MOC_LITERAL(17, 354, 25),
QT_MOC_LITERAL(18, 380, 23),
QT_MOC_LITERAL(19, 404, 25),
QT_MOC_LITERAL(20, 430, 22)
    },
    "MainWindow\0on_OpenImageButton_clicked\0"
    "\0on_GrayButton_clicked\0on_EqHistButton_clicked\0"
    "on_lineEdit_textChanged\0arg1\0"
    "on_ThresholdButton_clicked\0"
    "on_BlurButton_clicked\0on_MedianButton_clicked\0"
    "on_GaussianButton_clicked\0"
    "on_BilateralButton_clicked\0"
    "on_OtsuButton_clicked\0on_DilateButton_clicked\0"
    "on_ErodeButton_clicked\0on_OpenButton_clicked\0"
    "on_CloseButton_clicked\0on_GradientButton_clicked\0"
    "on_TopHatButton_clicked\0"
    "on_BlackHatButton_clicked\0"
    "on_ClearButton_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08,
       3,    0,  105,    2, 0x08,
       4,    0,  106,    2, 0x08,
       5,    1,  107,    2, 0x08,
       7,    0,  110,    2, 0x08,
       8,    0,  111,    2, 0x08,
       9,    0,  112,    2, 0x08,
      10,    0,  113,    2, 0x08,
      11,    0,  114,    2, 0x08,
      12,    0,  115,    2, 0x08,
      13,    0,  116,    2, 0x08,
      14,    0,  117,    2, 0x08,
      15,    0,  118,    2, 0x08,
      16,    0,  119,    2, 0x08,
      17,    0,  120,    2, 0x08,
      18,    0,  121,    2, 0x08,
      19,    0,  122,    2, 0x08,
      20,    0,  123,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_OpenImageButton_clicked(); break;
        case 1: _t->on_GrayButton_clicked(); break;
        case 2: _t->on_EqHistButton_clicked(); break;
        case 3: _t->on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_ThresholdButton_clicked(); break;
        case 5: _t->on_BlurButton_clicked(); break;
        case 6: _t->on_MedianButton_clicked(); break;
        case 7: _t->on_GaussianButton_clicked(); break;
        case 8: _t->on_BilateralButton_clicked(); break;
        case 9: _t->on_OtsuButton_clicked(); break;
        case 10: _t->on_DilateButton_clicked(); break;
        case 11: _t->on_ErodeButton_clicked(); break;
        case 12: _t->on_OpenButton_clicked(); break;
        case 13: _t->on_CloseButton_clicked(); break;
        case 14: _t->on_GradientButton_clicked(); break;
        case 15: _t->on_TopHatButton_clicked(); break;
        case 16: _t->on_BlackHatButton_clicked(); break;
        case 17: _t->on_ClearButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
