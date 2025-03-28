#pragma once
//
#include <vector>
//
#include <hdf5.h>
//
#include "H5VL_log_dataset.hpp"
#include "H5VL_logi_meta.hpp"

class H5VL_log_selections {
   public:
	hsize_t **starts;  // Start of selection
	hsize_t **counts;  // Count of selection
	int nsel;		   // Size of the selection (bytes)
	int ndim;		   // Dimension of the data space

	H5VL_log_selections ();
	H5VL_log_selections (int ndim, int nsel);
	H5VL_log_selections (int ndim, int nsel, hsize_t **starts, hsize_t **counts);
	H5VL_log_selections (hid_t dsid);
	H5VL_log_selections (H5VL_log_selections &rhs);
	~H5VL_log_selections ();

	H5VL_log_selections &operator= (H5VL_log_selections &rhs);
	bool operator== (H5VL_log_selections &rhs);

	herr_t get_mpi_type (hsize_t *hsize, size_t esize, MPI_Datatype *type);
	hsize_t get_sel_size ();
	hsize_t get_sel_size (int i);
	void encode (char *mbuf, MPI_Offset *dsteps = NULL, int dimoff = 0);

   private:
	hsize_t *sels_arr = NULL;  // Allocated starts and counts array, if present, need free

	void reserve (int nsel);  // Allocate space for nsel blocks
	void convert_to_deep ();  // Coverts a shallow copy to deep copy
};

typedef struct H5VL_log_selection {
	hsize_t start[H5S_MAX_RANK];  // Start of selection
	hsize_t count[H5S_MAX_RANK];  // Count of selection
	size_t size;				  // Size of the selection (bytes)
} H5VL_log_selection;

typedef struct H5VL_log_selection2 {
	MPI_Offset start;  // Start of selection
	MPI_Offset end;	   // Count of selection
	size_t size;	   // Size of the selection (bytes)
} H5VL_log_selection2;

extern int H5VL_log_dataspace_contig_ref;
extern hid_t H5VL_log_dataspace_conti;
