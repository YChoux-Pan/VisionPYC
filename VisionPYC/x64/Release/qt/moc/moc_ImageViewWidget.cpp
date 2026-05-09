/****************************************************************************
** Meta object code from reading C++ file 'ImageViewWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/Tools/ImageViewWidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSImageViewWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSImageViewWidgetENDCLASS = QtMocHelpers::stringData(
    "ImageViewWidget",
    "imageLoaded",
    "",
    "image",
    "imageLoadCV",
    "cv::Mat",
    "Image",
    "measurePointsUpdated",
    "std::vector<MeasurePoint>",
    "points",
    "rectangleUpdated",
    "id",
    "center",
    "width",
    "height",
    "angle",
    "arcMeasureUpdated",
    "radius",
    "startAngle",
    "endAngle",
    "thickness",
    "InputImg",
    "mode",
    "cv::Mat&",
    "Img"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSImageViewWidgetENDCLASS_t {
    uint offsetsAndSizes[50];
    char stringdata0[16];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[12];
    char stringdata5[8];
    char stringdata6[6];
    char stringdata7[21];
    char stringdata8[26];
    char stringdata9[7];
    char stringdata10[17];
    char stringdata11[3];
    char stringdata12[7];
    char stringdata13[6];
    char stringdata14[7];
    char stringdata15[6];
    char stringdata16[18];
    char stringdata17[7];
    char stringdata18[11];
    char stringdata19[9];
    char stringdata20[10];
    char stringdata21[9];
    char stringdata22[5];
    char stringdata23[9];
    char stringdata24[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSImageViewWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSImageViewWidgetENDCLASS_t qt_meta_stringdata_CLASSImageViewWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "ImageViewWidget"
        QT_MOC_LITERAL(16, 11),  // "imageLoaded"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 5),  // "image"
        QT_MOC_LITERAL(35, 11),  // "imageLoadCV"
        QT_MOC_LITERAL(47, 7),  // "cv::Mat"
        QT_MOC_LITERAL(55, 5),  // "Image"
        QT_MOC_LITERAL(61, 20),  // "measurePointsUpdated"
        QT_MOC_LITERAL(82, 25),  // "std::vector<MeasurePoint>"
        QT_MOC_LITERAL(108, 6),  // "points"
        QT_MOC_LITERAL(115, 16),  // "rectangleUpdated"
        QT_MOC_LITERAL(132, 2),  // "id"
        QT_MOC_LITERAL(135, 6),  // "center"
        QT_MOC_LITERAL(142, 5),  // "width"
        QT_MOC_LITERAL(148, 6),  // "height"
        QT_MOC_LITERAL(155, 5),  // "angle"
        QT_MOC_LITERAL(161, 17),  // "arcMeasureUpdated"
        QT_MOC_LITERAL(179, 6),  // "radius"
        QT_MOC_LITERAL(186, 10),  // "startAngle"
        QT_MOC_LITERAL(197, 8),  // "endAngle"
        QT_MOC_LITERAL(206, 9),  // "thickness"
        QT_MOC_LITERAL(216, 8),  // "InputImg"
        QT_MOC_LITERAL(225, 4),  // "mode"
        QT_MOC_LITERAL(230, 8),  // "cv::Mat&"
        QT_MOC_LITERAL(239, 3)   // "Img"
    },
    "ImageViewWidget",
    "imageLoaded",
    "",
    "image",
    "imageLoadCV",
    "cv::Mat",
    "Image",
    "measurePointsUpdated",
    "std::vector<MeasurePoint>",
    "points",
    "rectangleUpdated",
    "id",
    "center",
    "width",
    "height",
    "angle",
    "arcMeasureUpdated",
    "radius",
    "startAngle",
    "endAngle",
    "thickness",
    "InputImg",
    "mode",
    "cv::Mat&",
    "Img"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSImageViewWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    1,   53,    2, 0x06,    3 /* Public */,
       7,    1,   56,    2, 0x06,    5 /* Public */,
      10,    5,   59,    2, 0x06,    7 /* Public */,
      16,    6,   70,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      21,    2,   83,    2, 0x08,   20 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,   13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,   17,   18,   19,   20,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 23,   22,   24,

       0        // eod
};

Q_CONSTINIT const QMetaObject ImageViewWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSImageViewWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSImageViewWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSImageViewWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ImageViewWidget, std::true_type>,
        // method 'imageLoaded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'imageLoadCV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const cv::Mat &, std::false_type>,
        // method 'measurePointsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<MeasurePoint> &, std::false_type>,
        // method 'rectangleUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'arcMeasureUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'InputImg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<cv::Mat &, std::false_type>
    >,
    nullptr
} };

void ImageViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageViewWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->imageLoaded((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 1: _t->imageLoadCV((*reinterpret_cast< std::add_pointer_t<cv::Mat>>(_a[1]))); break;
        case 2: _t->measurePointsUpdated((*reinterpret_cast< std::add_pointer_t<std::vector<MeasurePoint>>>(_a[1]))); break;
        case 3: _t->rectangleUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5]))); break;
        case 4: _t->arcMeasureUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[6]))); break;
        case 5: _t->InputImg((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<cv::Mat&>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageViewWidget::*)(const QImage & );
            if (_t _q_method = &ImageViewWidget::imageLoaded; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageViewWidget::*)(const cv::Mat & );
            if (_t _q_method = &ImageViewWidget::imageLoadCV; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ImageViewWidget::*)(const std::vector<MeasurePoint> & );
            if (_t _q_method = &ImageViewWidget::measurePointsUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ImageViewWidget::*)(int , const QPointF & , double , double , double );
            if (_t _q_method = &ImageViewWidget::rectangleUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ImageViewWidget::*)(int , const QPointF & , double , double , double , double );
            if (_t _q_method = &ImageViewWidget::arcMeasureUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *ImageViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSImageViewWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ImageViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ImageViewWidget::imageLoaded(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageViewWidget::imageLoadCV(const cv::Mat & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImageViewWidget::measurePointsUpdated(const std::vector<MeasurePoint> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ImageViewWidget::rectangleUpdated(int _t1, const QPointF & _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ImageViewWidget::arcMeasureUpdated(int _t1, const QPointF & _t2, double _t3, double _t4, double _t5, double _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
