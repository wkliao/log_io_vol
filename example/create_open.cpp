/*********************************************************************
 *
 *  Copyright (C) 2021, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 *
 *********************************************************************/
/* $Id$ */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This example shows how to opee file using Log-based VOL VOL.
 *
 *    To compile:
 *        mpicc -O2 create_open.c -o create_open -lH5VL_log -lhdf5
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#include <hdf5.h>
#include "H5VL_log.h"

int main(int argc, char **argv) {  
    int rank, np;
    const char *file_name;  
    hid_t fapl_id, log_vol_id;
    hid_t file_id;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc > 1){
        file_name = argv[1];
    }
    else{
        file_name = "test.h5";
    }
    if(rank == 0) printf("Writing file_name = %s at rank 0 \n", file_name);

    // Log-based VOL VOL require MPI-IO and parallel access
    // Set MPI-IO and parallel access proterty.
    fapl_id = H5Pcreate(H5P_FILE_ACCESS); 
    H5Pset_fapl_mpio(fapl_id, MPI_COMM_WORLD, MPI_INFO_NULL);
    H5Pset_all_coll_metadata_ops(fapl_id, 1);
    H5Pset_coll_metadata_write(fapl_id, 1);

    // Resgiter Log-based VOL VOL
    log_vol_id = H5VLregister_connector(&H5VL_log_g, H5P_DEFAULT); 
    H5Pset_vol(fapl_id, log_vol_id, NULL);

    // Create file
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);     
    
    /*
     * Use HDF5 as ususal.
     * Log-based VOL VOL supports attribute, datasest, and group.
     */

    // Close file
    H5Fclose(file_id);

    // Open file
    file_id = H5Fopen(file_name, H5F_ACC_RDONLY, fapl_id);     
    
    /*
     * Use HDF5 as ususal.
     * Log-based VOL VOL supports attribute, datasest, and group.
     */

    // Close file
    H5Fclose(file_id);

    H5VLclose(log_vol_id);
    H5Pclose(fapl_id);
    
    MPI_Finalize();

    return 0;  
}  
