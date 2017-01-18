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

#include <Eigen/Core>
#include <cdd/setoper.h>
#include <cdd/cdd.h>

namespace Eigen {

/* Wrapper of Convex Polyhedron
 * This class aims to translate eigen matrix into cddlib matrix.
 * It automatically transforms a v-polyhedron into an h-polyhedron and vice-versa.
 */
class Polyhedron {
public:
    /* Default constructor that set cdd global constants. */
    Polyhedron();
    /* Constructor to call with already known matrix.
     * Compute its dual representation.
     * \param matrix The representation of the polyhedron.
     * \param isVrep true is the matrix is a V-representation of a polyhedron.
     * \throw std::runtime_error if the matrix couldn't compute the dual representation.
     */
    Polyhedron(const Eigen::MatrixXd& matrix, bool isVrep);
    /* Constructor to call with already known matrix.
     * Compute its dual representation.
     * H-polyhedron is such that \f$ Ax \leq b \f$.
     * V-polyhedron is such that \f$ A = [v^T r^T]^T, b=[1^T 0^T]^T \f$
     * with A composed of \f$ v \f$, the vertices, \f$ r \f$, the rays
     * and b is a vector which is 1 for vertices and 0 for rays.
     * \param A The matrix part of the representation of the polyhedron.
     * \param b The vector part of the representation of the polyhedron.
     * \param isVrep true is the matrix is a V-representation of a polyhedron.
     * \throw std::runtime_error if the matrix couldn't compute the dual representation.
     */
    Polyhedron(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, bool isVrep);
    /* Free the pointers and unset the cdd global constants. */
    ~Polyhedron();

    /* Treat the matrix as a V-representation and compute its H-representation.
     * \param matrix The V-representation of the polyhedron.
     * \return true if the H-representation has been computed succefully.
     */
    bool vrep(const Eigen::MatrixXd& matrix);
    /* Treat the inputs as a V-representation and compute its H-representation.
     * \param A The matrix part of the representation of the polyhedron.
     * \param b The vector part of the representation of the polyhedron.
     * \return true if the H-representation has been computed succefully.
     */
    bool vrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
    /* Treat the matrix as a H-representation and compute its V-representation
     * \param matrix The H-representation of the polyhedron.
     * \return true if the V-representation has been computed succefully
     */
    bool hrep(const Eigen::MatrixXd& matrix);
    /* Treat the inputs as a H-representation and compute its V-representation
     * \param A The matrix part of the representation of the polyhedron.
     * \param b The vector part of the representation of the polyhedron.
     * \return true if the V-representation has been computed succefully
     */
    bool hrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
    /* Get the V-representation of the polyhedron
     * \return Eigen matrix of the V-representation
     */
    Eigen::MatrixXd vrep();
    /* Get the H-representation of the polyhedron
     * \return Eigen matrix of the H-representation
     */
    Eigen::MatrixXd hrep();

    /* Print the H-representation of the polyhedron */
    void printHrep();
    /* Print the V-representation of the polyhedron */
    void printVrep();

private:
    void initializeMatrixPtr(std::size_t rows, std::size_t cols);
    bool doubleDescription(const Eigen::MatrixXd& matrix);
    Eigen::MatrixXd concatenateMatrix(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
    Eigen::MatrixXd ddfMatrix2EigenMatrix(dd_MatrixPtr mat);

private:
    bool isFromGenerators_;
    dd_MatrixPtr matPtr_;
    dd_PolyhedraPtr polytope_;
    dd_ErrorType err_;
};

} // namespace Eigen