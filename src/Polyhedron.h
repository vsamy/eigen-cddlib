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

#pragma once

#include "typedefs.h"
#include <Eigen/Core>
#include <cdd/setoper.h> // Must be included before cdd.h (wtf)
#include <cdd/cdd.h>
#include <utility>

namespace Eigen {

/* Wrapper of Convex Polyhedron
 * This class aims to translate eigen matrix into cddlib matrix.
 * It automatically transforms a v-polyhedron into an h-polyhedron and vice-versa.
 */
class Polyhedron {
public:
    /* Default constructor that set cdd global constants. */
    Polyhedron();
    /* Free the pointers and unset the cdd global constants. */
    ~Polyhedron();

    /* Treat the inputs as a H-representation and compute its V-representation.
     * H-polyhedron is such that \f$ Ax \leq b \f$.
     * \param A The matrix part of the representation of the polyhedron.
     * \param b The vector part of the representation of the polyhedron.
     */
    void vrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
    /* Treat the inputs as a V-representation and compute its H-representation
     * V-polyhedron is such that \f$ A = [v^T r^T]^T, b=[1^T 0^T]^T \f$
     * with A composed of \f$ v \f$, the vertices, \f$ r \f$, the rays
     * and b is a vector which is 1 for vertices and 0 for rays.
     * \param A The matrix part of the representation of the polyhedron.
     * \param b The vector part of the representation of the polyhedron.
     */
    void hrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
    /* Get the V-representation of the polyhedron
     * V-polyhedron is such that \f$ A = [v^T r^T]^T, b=[1^T 0^T]^T \f$
     * with A composed of \f$ v \f$, the vertices, \f$ r \f$, the rays
     * and b is a vector which is 1 for vertices and 0 for rays.
     * \return Pair of vertices and rays matrix and identification vector of vertices and rays for the V-representation
     */
    std::pair<Eigen::MatrixXd, Eigen::VectorXd> vrep();
    /* Get the H-representation of the polyhedron
     * H-polyhedron is such that \f$ Ax \leq b \f$.
     * \return Pair of inequality matrix and inequality vector for the H-representation
     */
    std::pair<Eigen::MatrixXd, Eigen::VectorXd> hrep();

    /* Print the H-representation of the polyhedron */
    void printHrep();
    /* Print the V-representation of the polyhedron */
    void printVrep();

private:
    bool hvrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, bool isFromGenerators);
    void initializeMatrixPtr(Eigen::Index rows, Eigen::Index cols, bool isFromGenerators);
    bool doubleDescription(const Eigen::MatrixXd& matrix, bool isFromGenerators);
    Eigen::MatrixXd concatenateMatrix(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, bool isFromGenerators);
    std::pair<Eigen::MatrixXd, Eigen::VectorXd> ddfMatrix2EigenMatrix(dd_MatrixPtr mat, bool isOuputVRep);

private:
    dd_MatrixPtr matPtr_;
    dd_PolyhedraPtr polytope_;
    dd_ErrorType err_;

private:
    static int counter;
};

} // namespace Eigen