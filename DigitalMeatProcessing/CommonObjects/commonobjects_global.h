#ifndef COMMONOBJECTS_GLOBAL_H
#define COMMONOBJECTS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMONOBJECTS_LIBRARY)
#  define COMMONOBJECTSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COMMONOBJECTSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMONOBJECTS_GLOBAL_H