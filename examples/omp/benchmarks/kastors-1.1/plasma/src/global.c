/**
 *
 * @file global.c
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Piotr Luszczek
 * @date 2010-11-15
 *
 **/

/***************************************************************************//**
 *  LAPACK Constants
 **/
char *plasma_lapack_constants[] =
{
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "",                     // 100
    "Row",                  // 101: PlasmaRowMajor
    "Column",               // 102: PlasmaColMajor
    "CCRB",                 // 103: PlasmaCCRB
    "CRRB",                 // 104: PlasmaCRRB
    "RCRB",                 // 105: PlasmaRCRB
    "RRRB",                 // 106: PlasmaRRRB
    "", "", "", "",
    "No transpose",         // 111: PlasmaNoTrans
    "Transpose",            // 112: PlasmaTrans
    "Conjugate transpose",  // 113: PlasmaConjTrans
    "", "", "", "", "", "", "",
    "Upper",                // 121: PlasmaUpper
    "Lower",                // 122: PlasmaLower
    "All",                  // 123: PlasmaUpperLower
    "", "", "", "", "", "", "",
    "Non-unit",             // 131: PlasmaNonUnit
    "Unit",                 // 132: PlasmaUnit
    "", "", "", "", "", "", "", "",
    "Left",                 // 141: PlasmaLeft
    "Right",                // 142: PlasmaRight
    "", "", "", "", "", "", "", "",
    "",                     // 151: 
    "",                     // 152: 
    "",                     // 153: 
    "",                     // 154: 
    "",                     // 155: 
    "",                     // 156: 
    "Epsilon",              // 157: PlasmaEps
    "",                     // 158: 
    "",                     // 159: 
    "",                     // 160: 
    "", "", "", "", "", "", "", "", "", "",
    "One norm",             // 171: PlasmaOneNorm       
    "",                     // 172: PlasmaRealOneNorm  
    "",                     // 173: PlasmaTwoNorm       
    "Frobenius norm",       // 174: PlasmaFrobeniusNorm 
    "Infinity norm",        // 175: PlasmaInfNorm       
    "",                     // 176: PlasmaRealInfNorm  
    "Maximum norm",         // 177: PlasmaMaxNorm       
    "",                     // 178: PlasmaRealMaxNorm  
    "",                     // 179
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "",                     // 200
    "Uniform",              // 201: PlasmaDistUniform
    "Symmetric",            // 202: PlasmaDistSymmetric
    "Normal",               // 203: PlasmaDistNormal
    "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "",                     // 240
    "Hermitian",            // 241 PlasmaHermGeev
    "Positive ev Hermitian",// 242 PlasmaHermPoev 
    "NonSymmetric pos sv",  // 243 PlasmaNonsymPosv
    "Symmetric pos sv",     // 244 PlasmaSymPosv 
    "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "",                     // 290 
    "No Packing",           // 291 PlasmaNoPacking
    "U zero out subdiag",   // 292 PlasmaPackSubdiag
    "L zero out superdiag", // 293 PlasmaPackSupdiag
    "C",                    // 294 PlasmaPackColumn
    "R",                    // 295 PlasmaPackRow
    "B",                    // 296 PlasmaPackLowerBand
    "Q",                    // 297 PlasmaPackUpeprBand
    "Z",                    // 298 PlasmaPackAll
    "",                     // 299

    "",                     // 300
    "No vectors",           // 301 PlasmaNoVec
    "Vectors needed",       // 302 PlasmaVec
    "I",                    // 303 PlasmaIvec
    "A",                    // 304 PlasmaAllVec 
    "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "",                     // 390
    "Forward",              // 391
    "Backward",             // 392
    "", "", "", "", "", "", "", "",
    "Columnwise",           // 401
    "Rowwise",              // 402
    "", "", "", "", "", "", "", ""  // Remember to add a comma!
};
