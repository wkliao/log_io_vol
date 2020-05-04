#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <mpi.h>
#include <hdf5.h>
#include <H5VLpublic.h>
#include "logvol.h"

#ifdef LOGVOL_DEBUG
#include <iostream>
#endif

#define LOG_GROUP_NAME "_LOG"
#ifdef LOGVOL_DEBUG
#define LOG_VOL_ASSERT(A) assert(A); 
#else
#define LOG_VOL_ASSERT(A) {} 
#endif


#define CHECK_ERR { \
    if (err < 0) { \
        printf("Error at line %d in %s:\n", \
        __LINE__,__FILE__); \
        H5Eprint1(stdout); \
        goto err_out; \
    } \
}

#define CHECK_MPIERR { \
    if (mpierr != MPI_SUCCESS) { \
        int el = 256; \
        char errstr[256]; \
        MPI_Error_string(mpierr, errstr, &el); \
        printf("Error at line %d in %s: %s\n", __LINE__, __FILE__, errstr); \
        goto err_out; \
    } \
}

#define CHECK_ID(A) { \
    if (A < 0) { \
        printf("Error at line %d in %s:\n", \
        __LINE__,__FILE__); \
        H5Eprint1(stdout); \
        goto err_out; \
    } \
}

#define CHECK_NERR(A) { \
    if (A == NULL) { \
        printf("Error at line %d in %s:\n", \
        __LINE__,__FILE__); \
        H5Eprint1(stdout); \
        goto err_out; \
    } \
}

#define RET_ERR(A) { \
    printf("Error at line %d in %s: %s\n", \
    __LINE__,__FILE__, A); \
    goto err_out; \
}

#define H5VL_log_delete_arr(A) {delete[] A; A = NULL;}
#define H5VL_log_free(A) {free(A); A = NULL;}
#define H5VL_log_Sclose(A) {if (A != -1) H5Sclose(A);}
#define H5VL_log_Tclose(A) {if (A != -1) H5Tclose(A);}

typedef struct H5VL_log_search_ret_t{
    int ndim;
    int fsize[LOG_VOL_MAX_NDIM];
    int fstart[LOG_VOL_MAX_NDIM];
    int msize[LOG_VOL_MAX_NDIM];
    int mstart[LOG_VOL_MAX_NDIM];
    int count[LOG_VOL_MAX_NDIM];
    size_t esize;
    MPI_Offset foff, moff;

    bool operator < (const H5VL_log_search_ret_t &rhs) const {
        int i;

        if (foff < rhs.foff) return true;
        else if (foff > rhs.foff) return false;

        for(i = 0; i < ndim; i++){
            if (fstart[i] < rhs.fstart[i]) return true;
            else if (fstart[i] > rhs.fstart[i]) return false;
        }
        
        return false;
    }
} H5VL_log_search_ret_t;

typedef struct H5VL_log_copy_ctx{
    char *src;
    char *dst;
    size_t size;
} H5VL_log_copy_ctx;

typedef struct H5VL_log_metaentry_t{
    int did;
    MPI_Offset start[LOG_VOL_MAX_NDIM];
    MPI_Offset count[LOG_VOL_MAX_NDIM];
    MPI_Offset ldoff;
    size_t rsize;
} H5VL_log_metaentry_t;

typedef struct H5VL_log_wreq_t{  
    int did;    // Source dataset ID
    int ndim;
    MPI_Offset start[LOG_VOL_MAX_NDIM];
    MPI_Offset count[LOG_VOL_MAX_NDIM];

    int ldid;   // Log dataset ID
    MPI_Offset ldoff;   // Offset in log dataset

    size_t rsize;
    char *buf;
    int buf_alloc;  // Whether the buffer is allocated or 
} H5VL_log_wreq_t;

typedef struct H5VL_log_rreq_t{  
    int did;    // Source dataset ID
    
    int ndim;
    MPI_Offset start[LOG_VOL_MAX_NDIM];
    MPI_Offset count[LOG_VOL_MAX_NDIM];

    hid_t dtype;
    hid_t mtype;

    size_t rsize;
    size_t esize;

    char *ibuf;
    char *xbuf;
} H5VL_log_rreq_t;

typedef struct H5VL_log_obj_t {
    H5I_type_t type;
    void *uo;   // Under obj
    hid_t uvlid; // Under VolID
} H5VL_log_obj_t;

typedef struct H5VL_log_dset_meta_t{
    //H5VL_log_file_t *fp;
    //int id;
    hsize_t ndim;
    //hsize_t dims[LOG_VOL_MAX_NDIM];
    //hsize_t mdims[LOG_VOL_MAX_NDIM];
    hid_t dtype;
    //hsize_t esize;
} H5VL_log_dset_meta_t;

/* The log VOL file object */
typedef struct H5VL_log_file_t : H5VL_log_obj_t {
    int rank;
    MPI_Comm comm;

    int refcnt;
    bool closing;
    unsigned flag;

    hid_t dxplid;

    void *lgp;
    int ndset;
    int nldset;

    MPI_File fh;

    std::vector<H5VL_log_wreq_t> wreqs;
    int nflushed;
    std::vector<H5VL_log_rreq_t> rreqs;

    // Should we do metadata caching?
    //std::vector<int> ndim;
    //std::vector<H5VL_log_dset_meta_t> mdc;

    size_t bsize;
    size_t bused;

    //std::vector<int> lut;
    std::vector<std::vector<H5VL_log_metaentry_t>> idx;
    bool idxvalid;
    bool metadirty;
} H5VL_log_file_t;

/* The log VOL group object */
typedef struct H5VL_log_group_t : H5VL_log_obj_t {
    H5VL_log_file_t *fp;
} H5VL_log_group_t;

/* The log VOL dataset object */
typedef struct H5VL_log_dset_t : H5VL_log_obj_t {
    H5VL_log_file_t *fp;
    int id;
    hsize_t ndim;
    hsize_t dims[LOG_VOL_MAX_NDIM];
    hsize_t mdims[LOG_VOL_MAX_NDIM];
    hid_t dtype;
    hsize_t esize;
} H5VL_log_dset_t;

/* The log VOL wrapper context */
typedef struct H5VL_log_wrap_ctx_t {
    hid_t uvlid;         /* VOL ID for under VOL */
    void *under_wrap_ctx;       /* Object wrapping context for under VOL */
} H5VL_log_wrap_ctx_t;

extern H5VL_log_obj_t* H5VL_log_new_obj(void *under_obj, hid_t uvlid);
extern herr_t H5VL_log_free_obj(H5VL_log_obj_t *obj);
extern herr_t H5VL_log_init(hid_t vipl_id);
extern herr_t H5VL_log_obj_term(void);
extern void* H5VL_log_info_copy(const void *_info);
extern herr_t H5VL_log_info_cmp(int *cmp_value, const void *_info1, const void *_info2);
extern herr_t H5VL_log_info_free(void *_info);
extern herr_t H5VL_log_info_to_str(const void *_info, char **str);
extern herr_t H5VL_log_str_to_info(const char *str, void **_info);
extern void* H5VL_log_get_object(const void *obj);
extern herr_t H5VL_log_get_wrap_ctx(const void *obj, void **wrap_ctx);
extern void* H5VL_log_wrap_object(void *obj, H5I_type_t obj_type, void *_wrap_ctx);
extern void* H5VL_log_unwrap_object(void *obj);
extern herr_t H5VL_log_free_wrap_ctx(void *_wrap_ctx);

// APIs
extern const H5VL_file_class_t H5VL_log_file_g;
extern const H5VL_dataset_class_t H5VL_log_dataset_g;
extern const H5VL_attr_class_t H5VL_log_attr_g;
extern const H5VL_group_class_t H5VL_log_group_g;
extern const H5VL_introspect_class_t H5VL_log_introspect_g;

// Utils
extern MPI_Datatype h5t_to_mpi_type(hid_t type_id);
extern void sortreq(int ndim, hssize_t len, MPI_Offset **starts, MPI_Offset **counts);
extern int intersect(int ndim, MPI_Offset *sa, MPI_Offset *ca, MPI_Offset *sb);
extern void mergereq(int ndim, hssize_t *len, MPI_Offset **starts, MPI_Offset **counts);
extern void sortblock(int ndim, hssize_t len, hsize_t **starts);
extern bool hlessthan(int ndim, hsize_t *a, hsize_t *b);

template <class A, class B>
int H5VL_logi_vector_cmp(int ndim, A *l, B *r);

extern herr_t H5VLattr_get_wrapper(void *obj, hid_t connector_id, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, ...);
extern herr_t H5VL_logi_add_att(H5VL_log_obj_t *op, char *name, hid_t atype, hid_t mtype, hsize_t len, void *buf, hid_t dxpl_id);
extern herr_t H5VL_logi_put_att(H5VL_log_obj_t *op, char *name, hid_t mtype, void *buf, hid_t dxpl_id);
extern herr_t H5VL_logi_get_att(H5VL_log_obj_t *op, char *name, hid_t mtype, void *buf, hid_t dxpl_id);
extern herr_t H5VL_logi_get_att_ex(H5VL_log_obj_t *op, char *name, hid_t mtype, hsize_t *len, void *buf, hid_t dxpl_id);

// File internals
extern herr_t H5VL_log_filei_flush(H5VL_log_file_t *fp, hid_t dxplid);
extern herr_t H5VL_log_filei_metaflush(H5VL_log_file_t *fp);
extern herr_t H5VL_log_filei_metaupdate(H5VL_log_file_t *fp);
extern herr_t H5VL_log_filei_balloc(H5VL_log_file_t *fp, size_t size, void **buf);
extern herr_t H5VL_log_filei_bfree(H5VL_log_file_t *fp, void *buf);

// Wraper
extern herr_t H5VLdataset_specific_wrapper(void *obj, hid_t connector_id, H5VL_dataset_specific_t specific_type, hid_t dxpl_id, void **req, ...);
extern herr_t H5VLdataset_get_wrapper(void *obj, hid_t connector_id, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, ...);
extern herr_t H5VLdataset_optional_wrapper(void *obj, hid_t connector_id, H5VL_dataset_optional_t opt_type, hid_t dxpl_id, void **req, ...);
extern herr_t H5VLfile_optional_wrapper(void *obj, hid_t connector_id, H5VL_file_optional_t opt_type, hid_t dxpl_id, void **req, ...);
extern herr_t H5VLlink_specific_wrapper(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, H5VL_link_specific_t specific_type, hid_t dxpl_id, void **req, ...);

// Dataset util
extern herr_t H5VL_logi_get_selection(hid_t sid, int &n, MPI_Offset **&starts, MPI_Offset **&counts);
extern herr_t H5VL_log_dataset_readi_idx_search_ex(H5VL_log_file_t *fp, H5VL_log_dset_t *dp, void *buf, int n, MPI_Offset **starts, MPI_Offset **counts, std::vector<H5VL_log_search_ret_t> &ret);
extern herr_t H5VL_log_dataset_readi_idx_search(H5VL_log_file_t *fp, int did, int ndim, MPI_Offset esize, void *buf, MPI_Offset *start, MPI_Offset *count, std::vector<H5VL_log_search_ret_t> &ret);
extern herr_t H5VL_log_dataset_readi_gen_rtypes(std::vector<H5VL_log_search_ret_t> blocks, MPI_Datatype *ftype, MPI_Datatype *mtype, std::vector<H5VL_log_copy_ctx> &overlaps);

// Nonblocking
extern herr_t H5VL_log_nb_flush_read_reqs(H5VL_log_file_t *fp, std::vector<H5VL_log_rreq_t> reqs, hid_t dxplid);
extern herr_t H5VL_log_nb_flush_write_reqs(H5VL_log_file_t *fp, hid_t dxplid);

// Datatype
//extern herr_t H5VL_log_dtypei_convert_core(void *inbuf, void *outbuf, hid_t intype, hid_t outtype, int N);
//extern herr_t H5VL_log_dtypei_convert(void *inbuf, void *outbuf, hid_t intype, hid_t outtype, int N);
extern MPI_Datatype H5VL_log_dtypei_mpitype_by_size(size_t size);

// Property
extern herr_t H5Pset_nb_buffer_size(hid_t plist, size_t size);
extern herr_t H5Pget_nb_buffer_size(hid_t plist, size_t *size);
extern herr_t H5Pset_nonblocking(hid_t plist, int nonblocking);
extern herr_t H5Pget_nonblocking(hid_t plist, int *nonblocking);


#ifdef LOGVOL_DEBUG
extern int H5VL_log_debug_MPI_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype * newtype);
extern void hexDump(char *desc, void *addr, size_t len, char *fname);
extern void hexDump(char *desc, void *addr, size_t len);
extern void hexDump(char *desc, void *addr, size_t len, FILE *fp);
#else
#define H5VL_log_debug_MPI_Type_create_subarray MPI_Type_create_subarray
#endif