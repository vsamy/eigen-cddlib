// This file is part of eigen-cddlib.

// eigen-cddlib is free software: you can redistribute it and/or
// modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eigen-cddlib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with eigen-cddlib.  If not, see
// <http://www.gnu.org/licenses/>.

#define BOOST_TEST_MODULE TestPolyhedron
#include <Eigen/Core>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <chrono>
#include <iostream>
#include <utility>

#include "Polyhedron.h"

struct Rep {
    Rep()
        : AVrepCone(4, 3)
        , AHrepCone(4, 3)
        , bVrepCone(4)
        , bHrepCone(4)
        , AVrepSquare(4, 2)
        , AHrepSquare(4, 2)
        , bVrepSquare(4)
        , bHrepSquare(4)
    {
        AVrepCone << 1, 1, 2,
            1, -1, 2,
            -1, -1, 2,
            -1, 1, 2;
        AHrepCone << -2, 0, -1,
            0, -2, -1,
            2, 0, -1,
            0, 2, -1;
        bVrepCone << 0, 0, 0, 0;
        bHrepCone << 0, 0, 0, 0;
        AVrepSquare << 1, 1,
            1, -1,
            -1, -1,
            -1, 1;
        AHrepSquare << 0, -1,
            -1, 0,
            0, 1,
            1, 0;
        bVrepSquare << 1, 1, 1, 1;
        bHrepSquare << 1, 1, 1, 1;
    }

    Eigen::MatrixXd AVrepCone, AHrepCone;
    Eigen::VectorXd bVrepCone, bHrepCone;

    Eigen::MatrixXd AVrepSquare, AHrepSquare;
    Eigen::VectorXd bVrepSquare, bHrepSquare;
};

BOOST_FIXTURE_TEST_CASE(Vrep2Hrep, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    Eigen::Polyhedron poly;
    poly.setVrep(AVrepCone, bVrepCone);
    auto hrep = poly.hrep();
    BOOST_CHECK(AHrepCone.isApprox(hrep.first));
    BOOST_CHECK(bHrepCone.isApprox(hrep.second));
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;

    poly.printHrep();
}

BOOST_FIXTURE_TEST_CASE(Hrep2Vrep, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    Eigen::Polyhedron poly;
    poly.setHrep(AHrepCone, bHrepCone);
    auto vrep = poly.vrep();
    BOOST_CHECK(AVrepCone.isApprox(vrep.first));
    BOOST_CHECK(bVrepCone.isApprox(vrep.second));
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;

    poly.printVrep();
}

BOOST_FIXTURE_TEST_CASE(setRays, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    Eigen::Polyhedron poly;
    poly.setRays(AVrepCone);
    auto hrep = poly.hrep();
    BOOST_CHECK(AHrepCone.isApprox(hrep.first));
    BOOST_CHECK(bHrepCone.isApprox(hrep.second));
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;

    poly.printHrep();
}

BOOST_FIXTURE_TEST_CASE(setVertices, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    Eigen::Polyhedron poly;
    poly.setVertices(AVrepSquare);
    auto hrep = poly.hrep();
    BOOST_CHECK(AHrepSquare.isApprox(hrep.first));
    BOOST_CHECK(bHrepSquare.isApprox(hrep.second));
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;

    poly.printHrep();
}
