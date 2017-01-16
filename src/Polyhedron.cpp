#include "Polyhedron.h"

namespace Eigen {

Polyhedron::Polyhedron()
    : matPtr_(nullptr)
    , polytope_(nullptr)
{
    dd_set_global_constants();
}

Polyhedron::Polyhedron(const Eigen::MatrixXd& matrix, bool isVrep)
    : matPtr_(nullptr)
    , polytope_(nullptr)
{
    dd_set_global_constants();

    initializeMatrixPtr(matrix.rows(), matrix.cols(), isVrep);
    bool success = doubleDescription(matrix);
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
    initializeMatrixPtr(matrix.rows(), matrix.cols(), true);
    return doubleDescription(matrix);
}

bool Polyhedron::hrep(const Eigen::MatrixXd& matrix)
{
    initializeMatrixPtr(matrix.rows(), matrix.cols(), false);
    return doubleDescription(matrix);
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

void Polyhedron::initializeMatrixPtr(std::size_t rows, std::size_t cols, bool isVrep)
{
    if (matPtr_ != nullptr)
        dd_FreeMatrix(matPtr_);
    matPtr_ = dd_CreateMatrix(rows, cols);
    matPtr_->representation = (isVrep ? dd_Generator : dd_Inequality);
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