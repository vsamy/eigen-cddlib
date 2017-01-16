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
    /* Default constructor that set cdd global constants */
    Polyhedron();
    /* Constructor to call with already known matrix.
     * Compute its dual representation.
     * \param matrix The representation of the polyhedron.
     * \param isVrep true is the matrix is a V-representation of a polyhedron
     * \throw std::runtime_error if the matrix couldn't compute the dual representation
     */
    Polyhedron(const Eigen::MatrixXd& matrix, bool isVrep);
    /* Free the pointers and unset the cdd global constants */
    ~Polyhedron();

    /* Treat a matrix as a V-representation and compute its H-representation
     * \param matrix The V-representation of the polyhedron
     * \return true if the H-representation has been computed succefully
     */
    bool vrep(const Eigen::MatrixXd& matrix);
    /* Treat a matrix as a H-representation and compute its V-representation
     * \param matrix The H-representation of the polyhedron
     * \return true if the V-representation has been computed succefully
     */
    bool hrep(const Eigen::MatrixXd& matrix);
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
    void initializeMatrixPtr(std::size_t rows, std::size_t cols, bool isVrep);
    bool doubleDescription(const Eigen::MatrixXd& matrix);
    Eigen::MatrixXd ddfMatrix2EigenMatrix(dd_MatrixPtr mat);

private:
    dd_MatrixPtr matPtr_;
    dd_PolyhedraPtr polytope_;
    dd_ErrorType err_;
};

} // namespace Eigen