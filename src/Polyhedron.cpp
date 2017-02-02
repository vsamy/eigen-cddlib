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

#include "Polyhedron.h"

namespace Eigen {

Polyhedron::Polyhedron()
    : matPtr_(nullptr)
    , polytope_(nullptr)
{
    dd_set_global_constants();
}

Polyhedron::Polyhedron(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, bool isVrep)
    : matPtr_(nullptr)
    , polytope_(nullptr)
{
    dd_set_global_constants();

    bool success = (isVrep ? hrep(A, b) : vrep(A, b));
    if (!success)
        throw std::runtime_error("The polytope could not be generated properly.");
}

Polyhedron::~Polyhedron()
{
    if (matPtr_ != nullptr)
        dd_FreeMatrix(matPtr_);
    if (polytope_ != nullptr)
        dd_FreePolyhedra(polytope_);
    dd_free_global_constants();
}

bool Polyhedron::vrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{
    isFromGenerators_ = false;
    return hvrep(A, b);
}

bool Polyhedron::hrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{
    isFromGenerators_ = true;
    return hvrep(A, b);
}

std::pair<Eigen::MatrixXd, Eigen::VectorXd> Polyhedron::vrep()
{
    dd_MatrixPtr mat = dd_CopyGenerators(polytope_);
    return ddfMatrix2EigenMatrix(mat);
}

std::pair<Eigen::MatrixXd, Eigen::VectorXd> Polyhedron::hrep()
{
    dd_MatrixPtr mat = dd_CopyInequalities(polytope_);
    return ddfMatrix2EigenMatrix(mat);
}

void Polyhedron::printVrep()
{
    dd_MatrixPtr mat = dd_CopyGenerators(polytope_);
    dd_WriteMatrix(stdout, mat);
}

void Polyhedron::printHrep()
{
    dd_MatrixPtr mat = dd_CopyInequalities(polytope_);
    dd_WriteMatrix(stdout, mat);
}

/**
 * Private functions
 */

bool Polyhedron::hvrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{
    Eigen::MatrixXd cMat = concatenateMatrix(A, b);
    return doubleDescription(cMat);
}

void Polyhedron::initializeMatrixPtr(std::size_t rows, std::size_t cols)
{
    if (matPtr_ != nullptr)
        dd_FreeMatrix(matPtr_);
    matPtr_ = dd_CreateMatrix(rows, cols);
    matPtr_->representation = (isFromGenerators_ ? dd_Generator : dd_Inequality);
}

bool Polyhedron::doubleDescription(const Eigen::MatrixXd& matrix)
{
    initializeMatrixPtr(matrix.rows(), matrix.cols());

    for (auto row = 0; row < matrix.rows(); ++row)
        for (auto col = 0; col < matrix.cols(); ++col)
            matPtr_->matrix[row][col][0] = matrix(row, col);

    if (polytope_ != nullptr)
        dd_FreePolyhedra(polytope_);
    polytope_ = dd_DDMatrix2Poly(matPtr_, &err_);
    return (err_ == dd_NoError) ? true : false;
}

Eigen::MatrixXd Polyhedron::concatenateMatrix(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{
    double sign = (isFromGenerators_ ? 1 : -1);
    Eigen::MatrixXd mat(A.rows(), A.cols() + 1);
    mat.col(0) = b;
    mat.block(0, 1, A.rows(), A.cols()).noalias() = sign * A;
    return mat;
}

std::pair<Eigen::MatrixXd, Eigen::VectorXd> Polyhedron::ddfMatrix2EigenMatrix(dd_MatrixPtr mat)
{
    double sign = (isFromGenerators_ ? -1 : 1);
    auto rows = mat->rowsize;
    auto cols = mat->colsize;
    Eigen::MatrixXd mOut(rows, cols - 1);
    Eigen::VectorXd vOut(rows);
    for (auto row = 0; row < rows; ++row) {
        vOut(row) = mat->matrix[row][0][0];
        for (auto col = 1; col < cols; ++col)
            mOut(row, col - 1) = sign * mat->matrix[row][col][0];
    }

    return std::make_pair(mOut, vOut);
}

} // namespace Eigen