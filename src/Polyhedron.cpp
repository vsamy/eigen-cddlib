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

Polyhedron::Polyhedron(const Eigen::MatrixXd& matrix, bool isVrep)
    : isFromGenerators_(isVrep)
    , matPtr_(nullptr)
    , polytope_(nullptr)
{
    dd_set_global_constants();

    bool success = (isFromGenerators_ ? vrep(matrix) : hrep(matrix));
    if (!success)
        throw std::runtime_error("The polytope could not be generated properly.");
}

Polyhedron::Polyhedron(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, bool isVrep)
    : isFromGenerators_(isVrep)
    , matPtr_(nullptr)
    , polytope_(nullptr)
{
    dd_set_global_constants();

    bool success = (isFromGenerators_ ? vrep(A, b) : hrep(A, b));
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

bool Polyhedron::vrep(const Eigen::MatrixXd& matrix)
{
    isFromGenerators_ = true;
    initializeMatrixPtr(matrix.rows(), matrix.cols());
    return doubleDescription(matrix);
}

bool Polyhedron::vrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{
    isFromGenerators_ = true;
    return vrep(concatenateMatrix(A, b));
}

bool Polyhedron::hrep(const Eigen::MatrixXd& matrix)
{
    isFromGenerators_ = false;
    initializeMatrixPtr(matrix.rows(), matrix.cols());
    return doubleDescription(matrix);
}

bool Polyhedron::hrep(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{
    isFromGenerators_ = false;
    return hrep(concatenateMatrix(A, b));
}

Eigen::MatrixXd Polyhedron::vrep()
{
    dd_MatrixPtr mat = dd_CopyGenerators(polytope_);
    return ddfMatrix2EigenMatrix(mat);
}

Eigen::MatrixXd Polyhedron::hrep()
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

void Polyhedron::initializeMatrixPtr(std::size_t rows, std::size_t cols)
{
    if (matPtr_ != nullptr)
        dd_FreeMatrix(matPtr_);
    matPtr_ = dd_CreateMatrix(rows, cols);
    matPtr_->representation = (isFromGenerators_ ? dd_Generator : dd_Inequality);
}

bool Polyhedron::doubleDescription(const Eigen::MatrixXd& matrix)
{
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
    mat.block(0, 1, A.rows(), A.cols()) = sign * A;
    return mat;
}

Eigen::MatrixXd Polyhedron::ddfMatrix2EigenMatrix(dd_MatrixPtr mat)
{
    auto rows = mat->rowsize;
    auto cols = mat->colsize;
    Eigen::MatrixXd out(rows, cols);
    for (auto row = 0; row < rows; ++row)
        for (auto col = 0; col < cols; ++col)
            out(row, col) = mat->matrix[row][col][0];

    return out;
}

} // namespace Eigen