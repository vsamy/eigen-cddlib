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
#include <iostream>
#include <chrono>
#include <Eigen/Core>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>

#include "Polyhedron.h"


struct Rep {
    Rep()
        : mat1Vrep(5, 4)
        , mat1Hrep(5, 4)
        , mat2Vrep(4, 4)
        , mat2Hrep(4, 4)
        , AVrep(5, 3)
        , AHrep(4, 3)
        , bVrep(5)
        , bHrep(4)
    {
        mat1Vrep << 0, 0.5, 0.5, 1,
            0, 0.5, -0.5, 1,
            0, -0.5, 0.5, 1,
            0, -0.5, -0.5, 1,
            1, 0, 0, 0;
        mat1Hrep << 0, 2, 0, 1,
            0, 0, 2, 1,
            0, -2, 0, 1,
            0, 0, -2, 1,
            1, 0, 0, 0;
        mat2Vrep << 0, 1, 1, 2,
            0, 1, -1, 2,
            0, -1, -1, 2,
            0, -1, 1, 2;
        mat2Hrep << 0, 2, 0, 1,
            0, 0, 2, 1,
            0, -2, 0, 1,
            0, 0, -2, 1;
        AVrep << 0.5, 0.5, 1,
            0.5, -0.5, 1,
            -0.5, 0.5, 1,
            -0.5, -0.5, 1,
            0, 0, 0;
        AHrep << -2, 0, -1,
            0, -2, -1,
            2, 0, -1,
            0, 2, -1;
        bVrep << 0, 0, 0, 0, 1;
        bHrep << 0, 0, 0, 0;
    }

    Eigen::MatrixXd mat1Vrep, mat1Hrep, mat2Vrep, mat2Hrep;
    Eigen::MatrixXd AVrep, AHrep;
    Eigen::VectorXd bVrep, bHrep;
};

BOOST_FIXTURE_TEST_CASE(Vrep2Hrep, Rep)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    
    Eigen::Polyhedron polyhedron;
    BOOST_REQUIRE(polyhedron.vrep(mat1Vrep));
    
    auto t_end = std::chrono::high_resolution_clock::now();    
    std::cout << "Wall time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << std::endl;


    Eigen::MatrixXd matHrep = polyhedron.hrep();
    BOOST_CHECK(matHrep.isApprox(mat1Hrep));
    Eigen::MatrixXd matVrep = polyhedron.vrep();
    BOOST_CHECK(matVrep.isApprox(mat1Vrep));

    Eigen::Polyhedron poly(AVrep, bVrep, true);
    Eigen::MatrixXd mat = poly.hrep();
    BOOST_CHECK(matHrep.isApprox(mat));

    Eigen::Polyhedron poly2;
    poly2.vrep(AVrep, bVrep);
    mat = poly2.hrep();
    BOOST_CHECK(matHrep.isApprox(mat));

    polyhedron.printHrep();
}

BOOST_FIXTURE_TEST_CASE(Hrep2Vrep, Rep)
{
    Eigen::Polyhedron polyhedron(mat2Hrep, false);

    Eigen::MatrixXd matVrep = polyhedron.vrep();
    BOOST_CHECK(matVrep.isApprox(mat2Vrep));
    Eigen::MatrixXd matHrep = polyhedron.hrep();
    BOOST_CHECK(matHrep.isApprox(mat2Hrep));

    Eigen::Polyhedron poly(AHrep, bHrep, false);
    Eigen::MatrixXd mat = poly.vrep();
    poly.printVrep();
    BOOST_CHECK(matVrep.isApprox(mat));

    Eigen::Polyhedron poly2;
    poly2.hrep(AHrep, bHrep);
    mat = poly2.vrep();
    BOOST_CHECK(matVrep.isApprox(mat));

    polyhedron.printVrep();
}