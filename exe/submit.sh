#!/bin/bash
cd $SLURM_SUBMIT_DIR
# Print the node that starts the process
echo "Master node: $(hostname)"
# Run our program using OpenMPI. OpenMPI will automatically discover resources 
# from SLURM.
mpirun ../buildlinux/Tesselations
