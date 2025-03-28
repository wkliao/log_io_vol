#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <hdf5.h>
#include "H5VL_log.h"
#include "testutils.hpp"

int main(int argc, char **argv) {   
    herr_t err = 0;
    int nerrs = 0;
    int i;
    int rank, np;
    const char *file_name;  
    int ndim;
    hid_t fid, did, sid, msid;
    hid_t faplid, dxplid;
    hid_t log_vlid;  
    hsize_t dims[2];
    hsize_t start[2], count[2];
    int *buf = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc > 2) {
        if (!rank)
            printf("Usage: %s [filename]\n", argv[0]);
        MPI_Finalize();
        return 1;
    }
    else if (argc > 1){
        file_name = argv[1];
    }
    else{
        file_name = "test.h5";
    }
    SHOW_TEST_INFO("Blocking read on datasets")

    //Register LOG VOL plugin 
    log_vlid = H5VLregister_connector(&H5VL_log_g, H5P_DEFAULT); 

    faplid = H5Pcreate(H5P_FILE_ACCESS); 
    // MPI and collective metadata is required by LOG VOL
    H5Pset_fapl_mpio(faplid, MPI_COMM_WORLD, MPI_INFO_NULL);
    H5Pset_all_coll_metadata_ops(faplid, 1);   
    H5Pset_vol(faplid, log_vlid, NULL);

    // Create file
    fid = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, faplid);    CHECK_ERR(fid)

    // Create datasets
    dims[0] = dims[1] = np;
    sid = H5Screate_simple(2, dims, dims); CHECK_ERR(sid);
    did = H5Dcreate2(fid, "D", H5T_STD_I32LE, sid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); CHECK_ERR(did)

    // Allocate buffer
    buf = new int[np];

    // Write columns
    for(i = 0; i < np; i++){
        buf[i] = rank + i + 1;
    }
    start[0] = 0;
    start[1] = rank;
    count[0] = np;
    count[1] = 1;
    err = H5Sselect_hyperslab(sid, H5S_SELECT_SET, start, NULL, count, NULL); CHECK_ERR(err)
    msid = H5Screate_simple(1, dims + 1, dims + 1); CHECK_ERR(msid);
    err = H5Dwrite(did, H5T_NATIVE_INT, msid, sid, H5P_DEFAULT, buf); CHECK_ERR(err)

    // Flush
    err = H5Fflush(fid, H5F_SCOPE_LOCAL); CHECK_ERR(err)

    // Read rows
    start[0] = rank;
    start[1] = 0;
    count[0] = 1;
    count[1] = np;
    err = H5Sselect_hyperslab(sid, H5S_SELECT_SET, start, NULL, count, NULL); CHECK_ERR(err)
    err = H5Dread(did, H5T_NATIVE_INT, msid, sid, H5P_DEFAULT, buf); CHECK_ERR(err)
    for(i = 0; i < np; i++){
        EXP_VAL_EX(buf[i], (rank + i + 1), "buf[" << i << "]")
    }

    err = H5Sclose(sid); CHECK_ERR(err)
    err = H5Dclose(did); CHECK_ERR(err)
    err = H5Fclose(fid); CHECK_ERR(err)

    err = H5Pclose(faplid); CHECK_ERR(err)

err_out:  
    SHOW_TEST_RESULT

    MPI_Finalize();

    if (buf){
        delete[] buf;
    }

    return (nerrs > 0);
}  


