#!/bin/bash
# Begin LSF Directives
#BSUB -P csc332
#BSUB -W 00:04
#BSUB -nnodes 516
#BSUB -J MPI_TEST
#BSUB -o MPI_TEST.txt
#BSUB -e MPI_TEST.err
#BSUB -q batch

let NP=21600
let NN=516
OUTFILE=/gpfs/alpine/csc332/scratch/khl7265/FS_EVAL/e3sm/output/test.bin

for i in $(seq 3);
do
    echo "===================================== Run ${i} ====================================="
    >&2 echo "===================================== Run ${i} ====================================="
    echo "rm -f ${OUTFILE}"
    rm -f ${OUTFILE}
    echo "jsrun -X 1 -p ${NP} -n ${NN} -r 1 -d plane:42 -c 42 -g 0 -b packed:smt:1 -l cpu-cpu --stdio_mode collected ./mpiio_test ${OUTFILE}"
    jsrun -p ${NP} -n ${NN} -r 1 -d plane:42 -c 42 -g 0 -b packed:smt:1 -l cpu-cpu --stdio_mode collected ./mpiio_test ${OUTFILE}
    echo "ls -lat ${OUTFILE}"
    ls -lat ${OUTFILE}
done
