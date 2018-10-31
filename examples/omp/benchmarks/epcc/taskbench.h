/****************************************************************************
 *                                                                           *
 *             OpenMP MicroBenchmark Suite - Version 3.0                     *
 *                                                                           *
 *                            produced by                                    *
 *                                                                           *
 *             Mark Bull, Fiona Reid and Nix Mc Donnell                      *
 *                                                                           *
 *                                at                                         *
 *                                                                           *
 *                Edinburgh Parallel Computing Centre                        *
 *                                                                           *
 *         email: markb@epcc.ed.ac.uk or fiona@epcc.ed.ac.uk                 *
 *                                                                           *
 *                                                                           *
 *      This version copyright (c) The University of Edinburgh, 2011.        *
 *                                                                           *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *      http://www.apache.org/licenses/LICENSE-2.0                           *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#include "common.h"

void stats(double*, double*);
void testParallelTaskGeneration(int inner_reps, int delay_reps);
void testMasterTaskGeneration(int inner_reps, int delay_reps);
void testMasterTaskGenerationWithBusySlaves(int inner_reps, int delay_reps);
void testNestedTaskGeneration(int inner_reps, int delay_reps);
void testNestedMasterTaskGeneration(int inner_reps, int delay_reps);
void testTaskWait(int inner_reps, int delay_reps);
void testTaskBarrier(int inner_reps, int delay_reps);
void testBranchTaskGeneration(int inner_reps, int delay_reps);
void branchTaskTree(int tree_level, int delay_reps);
void testLeafTaskGeneration(int inner_reps, int delay_reps);
void leafTaskTree(int tree_level, int delay_reps);
