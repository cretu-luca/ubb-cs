/****************************************************************************
** Meta object code from reading C++ file 'adminGUI.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/GUI/adminGUI.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adminGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSAdminMenuWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSAdminMenuWidgetENDCLASS = QtMocHelpers::stringData(
    "AdminMenuWidget",
    "addMovieGUI",
    "",
    "removeMovieGUI",
    "updateMovieGUI",
    "listMoviesGUI",
    "SetUpAddMoviePushButton",
    "SetUpRemoveMoviePushButton",
    "SetUpUpdateMoviePushButton",
    "setUpListMoviesPushButton",
    "addMovieDetails",
    "removeMovieDetails",
    "updateMovieDetails",
    "backToAdminMenu"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAdminMenuWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x10a,    1 /* Public | MethodIsConst  */,
       3,    0,   87,    2, 0x10a,    2 /* Public | MethodIsConst  */,
       4,    0,   88,    2, 0x10a,    3 /* Public | MethodIsConst  */,
       5,    0,   89,    2, 0x10a,    4 /* Public | MethodIsConst  */,
       6,    0,   90,    2, 0x0a,    5 /* Public */,
       7,    0,   91,    2, 0x0a,    6 /* Public */,
       8,    0,   92,    2, 0x0a,    7 /* Public */,
       9,    0,   93,    2, 0x0a,    8 /* Public */,
      10,    0,   94,    2, 0x10a,    9 /* Public | MethodIsConst  */,
      11,    0,   95,    2, 0x10a,   10 /* Public | MethodIsConst  */,
      12,    0,   96,    2, 0x10a,   11 /* Public | MethodIsConst  */,
      13,    0,   97,    2, 0x10a,   12 /* Public | MethodIsConst  */,

 // slots: parameters
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

Q_CONSTINIT const QMetaObject AdminMenuWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSAdminMenuWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAdminMenuWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAdminMenuWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AdminMenuWidget, std::true_type>,
        // method 'addMovieGUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeMovieGUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateMovieGUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'listMoviesGUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetUpAddMoviePushButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetUpRemoveMoviePushButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetUpUpdateMoviePushButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setUpListMoviesPushButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addMovieDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeMovieDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateMovieDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backToAdminMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AdminMenuWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AdminMenuWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addMovieGUI(); break;
        case 1: _t->removeMovieGUI(); break;
        case 2: _t->updateMovieGUI(); break;
        case 3: _t->listMoviesGUI(); break;
        case 4: _t->SetUpAddMoviePushButton(); break;
        case 5: _t->SetUpRemoveMoviePushButton(); break;
        case 6: _t->SetUpUpdateMoviePushButton(); break;
        case 7: _t->setUpListMoviesPushButton(); break;
        case 8: _t->addMovieDetails(); break;
        case 9: _t->removeMovieDetails(); break;
        case 10: _t->updateMovieDetails(); break;
        case 11: _t->backToAdminMenu(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *AdminMenuWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminMenuWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAdminMenuWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AdminMenuWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
