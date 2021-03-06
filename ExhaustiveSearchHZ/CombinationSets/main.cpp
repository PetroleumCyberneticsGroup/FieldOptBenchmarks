/******************************************************************************
   Copyright (C) 2017 Mathias C. Bellout <mathias.bellout@ntnu.no>

   This file is part of the FieldOpt-Benchmarks project,
   an NTNU Petroleum Cybernetics Group project.

   FieldOpt-Benchmarks is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   FieldOpt-Benchmarks is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with FieldOpt-Benchmarks.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>

#include "src/permutation_string_writer.h"
#include "src/f_at_each_combination.h"
#include "src/for_each_combination.h"
#include "src/utilities.hpp"
#include "src/sample_point_ranges.h"

using namespace std;
using namespace Eigen;

// ============================================================
QString compute_combinations(int p, int r, int n, int N, int Z,
                             QString &log_file) {

    // ------------------------------------------------------------
    // Print to log: date, hostname, cpu info, combination set info
    auto t_start = printToLog(r, n, N, Z, log_file);

    // ------------------------------------------------------------
    // Find point selection ranges
    auto point_range = new sample_point_ranges(p, r, n, N, Z);
    point_range->get_sample_point_ranges();

    // ------------------------------------------------------------
    // Prepare output file and and permutation writer
    auto output_file = getfSetFilename(n, Z);
    PermutationStringWriter *writer =
        new PermutationStringWriter(output_file);

    // ------------------------------------------------------------
    // Compute combinations: prints to disk after each combination
    std::uint64_t count =
        for_each_reversible_permutation(
            point_range->range_vec_std_.begin(),
            point_range->range_vec_std_.begin() + r,
            point_range->range_vec_std_.end(),
            f_at_each_combination(
                point_range->range_vec_std_.size(), writer));

    // ------------------------------------------------------------
    // Flush remaining data, if any
    if (writer->temp_str_.size()>0)
        writer->flushToDisk();

    // ------------------------------------------------------------
    // Print to log: file size + elapsed time
    Utilities::FileHandling::WriteLineToFile(
        getFileSize(output_file) + get_elapsed_time(t_start),
        log_file);

    // ------------------------------------------------------------
    // Sanity check
    // assert(count == count_each_reversible_permutation(v.begin(),
    //                                                   v.begin() + r,
    //                                                   v.end()));

    // ------------------------------------------------------------
    // Summary
    // std::cout << "Found " << count << " permutations of " << v.size()
    //           << " objects taken " << r << " at a time.\n\n";

    return output_file;
}


// ============================================================
int main() {

    // --------------------------------------------------------
    // log file name
    auto log_file = getLogName();

    /*
    n_points=>   in_reg: 201  before:  0  after:  0
    n_points=>   in_reg: 185  before:  8  after:  8
    n_points=>   in_reg: 169  before: 16  after: 16
    n_points=>   in_reg: 153  before: 24  after: 24
    n_points=>   in_reg: 137  before: 32  after: 32
    n_points=>   in_reg: 121  before: 40  after: 40
    n_points=>   in_reg: 105  before: 48  after: 48
    n_points=>   in_reg:  89  before: 56  after: 56
    n_points=>   in_reg:  73  before: 64  after: 64
    n_points=>   in_reg:  57  before: 72  after: 72
    n_points=>   in_reg:  41  before: 80  after: 80
    n_points=>   in_reg:  17  before: 92  after: 92
    n_points=>   in_reg:   9  before: 96  after: 96

    ncells=>   in_reg: 50  before:  0  after:  0
    ncells=>   in_reg: 46  before:  2  after:  2
    ncells=>   in_reg: 42  before:  4  after:  4
    ncells=>   in_reg: 38  before:  6  after:  6
    ncells=>   in_reg: 34  before:  8  after:  8
    ncells=>   in_reg: 30  before: 10  after: 10
    ncells=>   in_reg: 26  before: 12  after: 12
    ncells=>   in_reg: 22  before: 14  after: 14
    ncells=>   in_reg: 18  before: 16  after: 16
    ncells=>   in_reg: 14  before: 18  after: 18
    ncells=>   in_reg: 10  before: 20  after: 20
    ncells=>   in_reg:  4  before: 23  after: 23
    ncells=>   in_reg:  2  before: 24  after: 24

    ==================================================================
     n  | N=n^2 |     Z     |     sz(B)   | sz(KiB) | sz(MiB)|sz(GiB)|
    ------------------------------------------------------------------
      2 |     4 |         6 |          0  |       0 |    0.0 |   0.0 |
      3 |     9 |        36 |          0  |       0 |    0.0 |   0.0 |
    ------------------------------------------------------------------
      9 |    81 |      3240 |          0  |       0 |    0.0 |   0.0 |
     17 |   289 |     41616 |          0  |       0 |    0.0 |   0.0 |
     41 |  1681 |   1412040 |   13161528  |   12853 |   12.6 |   0.0 |
    ------------------------------------------------------------------
     57 |  3249 |   5276376 |   50939387  |   49745 |   48.6 |   0.0 |
     73 |  5329 |  14196456 |  138142342  |  134905 |  131.7 |   0.1 |
     89 |  7921 |  31367160 |  306003631  |  298832 |  291.8 |   0.3 |
    ------------------------------------------------------------------
    105 | 11025 |  60769800 |  593444674  |  579536 |  566.0 |   0.6 |
    121 | 14641 | 107172120 | 1047075070  | 1022534 |  998.6 |   1.0 |
    137 | 18769 | 176128296 | 1721192603  | 1680852 | 1641.5 |   1.6 |
    ------------------------------------------------------------------
    153 | 23409 | 273978936 | 2677783235  | 2615023 | 2553.7 |   2.5 |
    169 | 28561 | 407851080 | 3986521113  | 3893087 | 3801.8 |   3.7 |
    185 | 34225 | 585658200 | 5724768561  | 5590594 | 5459.6 |   5.3 |
    201 | 40401 | 816100200 | 7977576090  | 7790602 | 7608.0 |   7.4 |
    ==================================================================

    ===========================================================
     n  | N=n^2 |     Z     |    Z[1e6]  |  cSet  | cSet[1e6] |
    -----------------------------------------------------------
      2 |     4 |         6 |      0  |         6 |         0 |
      3 |     9 |        36 |      0  |        30 |         0 |
    -----------------------------------------------------------
      9 |    81 |      3240 |      0  |      3204 |         0 |
     17 |   289 |     41616 |      0  |     38376 |         0 |
     41 |  1681 |   1412040 |      1  |   1370424 |         1 |
    -----------------------------------------------------------
     57 |  3249 |   5276376 |      5  |   3864336 |         4 |
     73 |  5329 |  14196456 |     14  |   8920080 |         9 |
     89 |  7921 |  31367160 |     31  |  17170704 |        17 |
    -----------------------------------------------------------
    105 | 11025 |  60769800 |     61  |  29402640 |        29 |
    121 | 14641 | 107172120 |    107  |  46402320 |        46 |
    137 | 18769 | 176128296 |    176  |  68956176 |        69 |
    -----------------------------------------------------------
    137 | 18769 | 176128296 |    176  |  68956176 |        69 |
    153 | 23409 | 273978936 |    274  |  97850640 |        98 |
    169 | 28561 | 407851080 |    408  | 133872144 |       134 |
    185 | 34225 | 585658200 |    586  | 177807120 |       178 |
    201 | 40401 | 816100200 |    816  | 230442000 |       230 |
    -----------------------------------------------------------
    sum of cSets:    816
    ===========================================================
    */

    int p, r, n, N, Z;


    // --------------------------------------------------------
    // TEST SPACE: n002
    // Select combination attributes:
    p = 1;          // start
    r = 2;          // selection
    n = 2;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(p, r, n, N, Z, log_file);

    // --------------------------------------------------------
    // TEST SPACE: n003
    // Select combination attributes
    p = 1;          // start
    r = 2;          // selection
    n = 3;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(p, r, n, N, Z, log_file);

    // --------------------------------------------------------
    // TEST SPACE: n009
    // n_points=>   in_reg:   9  before: 96  after: 96
    // Select combination attributes
    p = 97;         // start
    r = 2;          // selection
    n = 9;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(p, r, n, N, Z, log_file);

    // --------------------------------------------------------
    // TEST SPACE: n017
    // n_points=>   in_reg:  17  before: 92  after: 92
    // Select combination attributes
    p = 93;         // start
    r = 2;          // selection
    n = 17;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(p, r, n, N, Z, log_file);

    // --------------------------------------------------------
    // TEST SPACE: n041
    // n_points=>   in_reg:  41  before: 80  after: 80
    // Select combination attributes
    p = 81;         // start
    r = 2;          // selection
    n = 41;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(p, r, n, N, Z, log_file);

    // --------------------------------------------------------
    // SET {A}: n057
    // n_points:  57  np_before: 72  np_after: 72
    // Select combination attributes
    p = 73;         // start
    r = 2;          // selection
    n = 57;         // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(p, r, n, N, Z, log_file);

    if( startPrompt(1)==1 ){

        // --------------------------------------------------------
        // SET {B}: n073
        // n_points:  73  np_before: 64  np_after: 64
        // Select combination attributes
        p = 65;         // start
        r = 2;          // selection
        n = 73;         // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {C}: n089
        // n_points:  89  np_before: 56  np_after: 56
        // Select combination attributes
        p = 57;          // start
        r = 2;          // selection
        n = 89;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {D}: n105
        // n_points: 105  np_before: 48  np_after: 48
        // Select combination attributes
        p = 49;          // start
        r = 2;          // selection
        n = 105;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {E}: n121
        // n_points: 121  np_before: 40  np_after: 40
        // Select combination attributes
        p = 41;          // start
        r = 2;          // selection
        n = 121;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {F}: n137
        // n_points: 137  np_before: 32  np_after: 32
        // Select combination attributes
        p = 33;          // start
        r = 2;          // selection
        n = 137;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {G}: n153
        // n_points: 153  np_before: 24  np_after: 24
        // Select combination attributes
        p = 25;          // start
        r = 2;          // selection
        n = 153;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {H}: n169
        // n_points: 169  np_before: 16  np_after: 16
        // Select combination attributes
        p = 17;          // start
        r = 2;          // selection
        n = 169;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {I}: n185
        // n_points: 185  np_before:  8  np_after:  8
        // Select combination attributes
        p = 9;          // start
        r = 2;          // selection
        n = 185;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {J}: n200
        // n_points: 201  np_before:  0  np_after:  0
        // Select combination attributes
        p = 1;          // start
        r = 2;          // selection
        n = 200;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(p, r, n, N, Z, log_file);

    }

    return 0;
}