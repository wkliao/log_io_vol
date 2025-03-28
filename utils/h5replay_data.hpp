#pragma once

#include "h5replay_meta.hpp"

herr_t h5replay_read_data (MPI_File fin,
						   std::vector<dset_info> &dsets,
						   std::vector<h5replay_idx_t> &reqs);

herr_t h5replay_write_data (hid_t foutid,
							std::vector<dset_info> &dsets,
							std::vector<h5replay_idx_t> &reqs);