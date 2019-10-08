#pragma once

#if defined _WIN32 || defined __CYGWIN__
#define EIGEN_CDDLIB_DLLIMPORT __declspec(dllimport)
#define EIGEN_CDDLIB_DLLEXPORT __declspec(dllexport)
#define EIGEN_CDDLIB_DLLLOCAL
#else
#if __GNUC__ >= 4
#define EIGEN_CDDLIB_DLLIMPORT __attribute__((visibility("default")))
#define EIGEN_CDDLIB_DLLEXPORT __attribute__((visibility("default")))
#define EIGEN_CDDLIB_DLLLOCAL __attribute__((visibility("hidden")))
#else
#define EIGEN_CDDLIB_DLLIMPORT
#define EIGEN_CDDLIB_DLLEXPORT
#define EIGEN_CDDLIB_DLLLOCAL
#endif
#endif

#ifdef EIGEN_CDDLIB_STATIC
#define EIGEN_CDDLIB_DLLAPI
#define EIGEN_CDDLIB_LOCAL
#else
#ifdef EIGEN_CDDLIB_EXPORTS
#define EIGEN_CDDLIB_DLLAPI EIGEN_CDDLIB_DLLEXPORT
#else
#define EIGEN_CDDLIB_DLLAPI EIGEN_CDDLIB_DLLIMPORT
#endif
#define EIGEN_CDDLIB_LOCAL EIGEN_CDDLIB_DLLLOCAL
#endif