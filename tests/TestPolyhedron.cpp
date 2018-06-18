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
        : AVrep(4, 3)
        , AHrep(4, 3)
        , bVrep(4)
        , bHrep(4)
    {
        AVrep << 1, 1, 2,
            1, -1, 2,
            -1, -1, 2,
            -1, 1, 2; // Friction cone inequality * 2
        AHrep << -2, 0, -1,
            0, -2, -1,
            2, 0, -1,
            0, 2, -1;
        bVrep << 0, 0, 0, 0;
        bHrep << 0, 0, 0, 0;
    }

    Eigen::MatrixXd AVrep, AHrep;
    Eigen::VectorXd bVrep, bHrep;
};

BOOST_FIXTURE_TEST_CASE(Vrep2Hrep, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    Eigen::Polyhedron poly;
    poly.setVrep(AVrep, bVrep);
    auto hrep = poly.hrep();
    BOOST_CHECK(AHrep.isApprox(hrep.first));
    BOOST_CHECK(bHrep.isApprox(hrep.second));
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;

    poly.printHrep();
}

BOOST_FIXTURE_TEST_CASE(Hrep2Vrep, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    Eigen::Polyhedron poly;
    poly.setHrep(AHrep, bHrep);
    auto vrep = poly.vrep();
    BOOST_CHECK(AVrep.isApprox(vrep.first));
    BOOST_CHECK(bVrep.isApprox(vrep.second));
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;

    poly.printVrep();
}
