#include <stdio.h>
#include <stdlib.h>

#include <hdf5.h>
#include "H5VL_log.h"
#include "testutils.hpp"

#define N 10
#define M 10

int main(int argc, char **argv) {   
    int err, nerrs = 0;
    int rank, np;
    const char *file_name;  
    int ndim;
    hid_t fid, gid, did, gdid, sid;
    hid_t faplid, dxplid;
    hid_t log_vlid;  
    hsize_t dims[2] = {N, M};
    hsize_t mdims[2];
  
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
    SHOW_TEST_INFO("Creating datasets")

    //Register LOG VOL plugin 
    log_vlid = H5VLregister_connector(&H5VL_log_g, H5P_DEFAULT); 

    faplid = H5Pcreate(H5P_FILE_ACCESS); 
    // MPI and collective metadata is required by LOG VOL
    H5Pset_fapl_mpio(faplid, MPI_COMM_WORLD, MPI_INFO_NULL);
    H5Pset_all_coll_metadata_ops(faplid, 1);   
    H5Pset_vol(faplid, log_vlid, NULL);

    // Create file
    fid = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, faplid);    CHECK_ERR(fid)
    // Create group
    gid = H5Gcreate2(fid, "G", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); CHECK_ERR(gid)

    // Create datasets
    sid = H5Screate_simple(2, dims, dims); CHECK_ERR(sid);
    did = H5Dcreate2(fid, "D", H5T_STD_I32LE, sid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); CHECK_ERR(did)
    gdid = H5Dcreate2(gid, "D", H5T_STD_I32LE, sid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); CHECK_ERR(gdid)
    err = H5Dclose(did); CHECK_ERR(err)
    err = H5Dclose(gdid); CHECK_ERR(err)
    err = H5Sclose(sid); CHECK_ERR(err)


    // Open datasets
    did = H5Dopen2(fid, "D", H5P_DEFAULT); CHECK_ERR(did)
    gdid = H5Dopen2(gid, "D", H5P_DEFAULT); CHECK_ERR(gdid)

    // Get dataspace
    sid = H5Dget_space(did); CHECK_ERR(sid)
    ndim = H5Sget_simple_extent_dims(sid, dims, mdims); CHECK_ERR(ndim);
    EXP_VAL(ndim, 2)
    EXP_VAL(dims[0], N)
    EXP_VAL(dims[1], N)
    EXP_VAL(mdims[0], N)
    EXP_VAL(mdims[1], N)

    err = H5Sclose(sid); CHECK_ERR(err)

    err = H5Dclose(did); CHECK_ERR(err)
    err = H5Dclose(gdid); CHECK_ERR(err)

    err = H5Gclose(gid); CHECK_ERR(err)
    err = H5Fclose(fid); CHECK_ERR(err)

    err = H5Pclose(faplid); CHECK_ERR(err)

err_out:  
    SHOW_TEST_RESULT

    MPI_Finalize();

    return (nerrs > 0);
}  


