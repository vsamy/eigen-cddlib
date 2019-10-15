// eigen-cddlib: wraps cddlib with Eigen matrix
// Copyright (C) 2019 Vincent Samy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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