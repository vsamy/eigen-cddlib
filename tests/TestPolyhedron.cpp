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

#include "Polyhedron.h"

struct Rep {
    Rep()
        : mat1Vrep(5, 4)
        , mat1Hrep(5, 4)
        , mat2Vrep(4, 4)
        , mat2Hrep(4, 4)
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
    }

    Eigen::MatrixXd mat1Vrep, mat1Hrep, mat2Vrep, mat2Hrep;
};

BOOST_FIXTURE_TEST_CASE(Vrep2Hrep, Rep)
{
    Eigen::Polyhedron polyhedron;
    BOOST_REQUIRE(polyhedron.vrep(mat1Vrep));
    Eigen::MatrixXd matHrep = polyhedron.hrep();
    BOOST_CHECK(matHrep.isApprox(mat1Hrep));
    Eigen::MatrixXd matVrep = polyhedron.vrep();
    BOOST_CHECK(matVrep.isApprox(mat1Vrep));

    polyhedron.printHrep();
}

BOOST_FIXTURE_TEST_CASE(Hrep2Vrep, Rep)
{
    Eigen::Polyhedron polyhedron(mat2Hrep, false);

    Eigen::MatrixXd matVrep = polyhedron.vrep();
    BOOST_CHECK(matVrep.isApprox(mat2Vrep));
    Eigen::MatrixXd matHrep = polyhedron.hrep();
    BOOST_CHECK(matHrep.isApprox(mat2Hrep));

    polyhedron.printVrep();
}