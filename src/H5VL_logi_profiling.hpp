/* Do not edit this file. It is produced from the corresponding .m4 source */
/*
 *  Copyright (C) 2021, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */




#pragma once

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/*
 * Report performance profiling
 */
#ifdef LOGVOL_PROFILING

#define H5VL_LOG_NTIMER 92

#define TIMER_H5VL_LOG_FILE_CREATE 0
#define TIMER_H5VL_LOG_FILE_OPEN 1
#define TIMER_H5VL_LOG_FILE_GET 2
#define TIMER_H5VL_LOG_FILE_SPECIFIC 3
#define TIMER_H5VL_LOG_FILE_OPTIONAL 4
#define TIMER_H5VL_LOG_FILE_CLOSE 5
#define TIMER_H5VL_LOG_GROUP_CREATE 6
#define TIMER_H5VL_LOG_GROUP_OPEN 7
#define TIMER_H5VL_LOG_GROUP_GET 8
#define TIMER_H5VL_LOG_GROUP_SPECIFIC 9
#define TIMER_H5VL_LOG_GROUP_OPTIONAL 10
#define TIMER_H5VL_LOG_GROUP_CLOSE 11
#define TIMER_H5VL_LOG_ATT_CREATE 12
#define TIMER_H5VL_LOG_ATT_OPEN 13
#define TIMER_H5VL_LOG_ATT_READ 14
#define TIMER_H5VL_LOG_ATT_WRITE 15
#define TIMER_H5VL_LOG_ATT_GET 16
#define TIMER_H5VL_LOG_ATT_SPECIFIC 17
#define TIMER_H5VL_LOG_ATT_OPTIONAL 18
#define TIMER_H5VL_LOG_ATT_CLOSE 19
#define TIMER_H5VL_LOG_DATASET_CREATE 20
#define TIMER_H5VL_LOG_DATASET_OPEN 21
#define TIMER_H5VL_LOG_DATASET_READ 22
#define TIMER_H5VL_LOG_DATASET_READ_INIT 23
#define TIMER_H5VL_LOG_DATASET_WRITE 24
#define TIMER_H5VL_LOG_DATASET_WRITE_INIT 25
#define TIMER_H5VL_LOG_DATASET_WRITE_START_COUNT 26
#define TIMER_H5VL_LOG_DATASET_WRITE_ENCODE 27
#define TIMER_H5VL_LOG_DATASET_WRITE_META_DEFLATE 28
#define TIMER_H5VL_LOG_DATASET_WRITE_PACK 29
#define TIMER_H5VL_LOG_DATASET_WRITE_CONVERT 30
#define TIMER_H5VL_LOG_DATASET_WRITE_FILTER 31
#define TIMER_H5VL_LOG_DATASET_WRITE_FINALIZE 32
#define TIMER_H5VL_LOG_DATASET_GET 33
#define TIMER_H5VL_LOG_DATASET_SPECIFIC 34
#define TIMER_H5VL_LOG_DATASET_OPTIONAL 35
#define TIMER_H5VL_LOG_DATASET_CLOSE 36
#define TIMER_H5VLFILE_CREATE 37
#define TIMER_H5VLFILE_OPEN 38
#define TIMER_H5VLFILE_GET 39
#define TIMER_H5VLFILE_SPECIFIC 40
#define TIMER_H5VLFILE_OPTIONAL 41
#define TIMER_H5VLFILE_CLOSE 42
#define TIMER_H5VLGROUP_CREATE 43
#define TIMER_H5VLGROUP_OPEN 44
#define TIMER_H5VLGROUP_GET 45
#define TIMER_H5VLGROUP_SPECIFIC 46
#define TIMER_H5VLGROUP_OPTIONAL 47
#define TIMER_H5VLGROUP_CLOSE 48
#define TIMER_H5VLATT_CREATE 49
#define TIMER_H5VLATT_OPEN 50
#define TIMER_H5VLATT_READ 51
#define TIMER_H5VLATT_WRITE 52
#define TIMER_H5VLATT_GET 53
#define TIMER_H5VLATT_SPECIFIC 54
#define TIMER_H5VLATT_OPTIONAL 55
#define TIMER_H5VLATT_CLOSE 56
#define TIMER_H5VLDATASET_CREATE 57
#define TIMER_H5VLDATASET_OPEN 58
#define TIMER_H5VLDATASET_READ 59
#define TIMER_H5VLDATASET_WRITE 60
#define TIMER_H5VLDATASET_GET 61
#define TIMER_H5VLDATASET_SPECIFIC 62
#define TIMER_H5VLDATASET_OPTIONAL 63
#define TIMER_H5VLDATASET_CLOSE 64
#define TIMER_H5VL_LOG_FILEI_FLUSH 65
#define TIMER_H5VL_LOG_FILEI_METAFLUSH 66
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_INIT 67
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_PACK 68
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_ZIP 69
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_SYNC 70
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_CREATE 71
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE 72
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_CLOSE 73
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_BARRIER 74
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_FINALIZE 75
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_SIZE 76
#define TIMER_H5VL_LOG_FILEI_METAFLUSH_SIZE_ZIP 77
#define TIMER_H5VL_LOG_FILEI_METAUPDATE 78
#define TIMER_H5VL_LOG_DATASETI_READI_GEN_RTYPES 79
#define TIMER_H5VL_LOG_DATASETI_OPEN_WITH_UO 80
#define TIMER_H5VL_LOG_DATASETI_WRAP 81
#define TIMER_H5VL_LOGI_GET_DATASPACE_SEL_TYPE 82
#define TIMER_H5VL_LOGI_GET_DATASPACE_SELECTION 83
#define TIMER_H5VL_LOG_NB_FLUSH_READ_REQS 84
#define TIMER_H5VL_LOG_NB_FLUSH_WRITE_REQS 85
#define TIMER_H5VL_LOG_NB_FLUSH_WRITE_REQS_INIT 86
#define TIMER_H5VL_LOG_NB_FLUSH_WRITE_REQS_SYNC 87
#define TIMER_H5VL_LOG_NB_FLUSH_WRITE_REQS_CREATE 88
#define TIMER_H5VL_LOG_NB_FLUSH_WRITE_REQS_WR 89
#define TIMER_H5VL_LOG_NB_WRITE_REQS_ALIGNED 90
#define TIMER_H5VL_LOG_NB_FLUSH_WRITE_REQS_SIZE 91
#endif

#ifdef LOGVOL_PROFILING
#include "H5VL_logi_profiling.hpp"
#define H5VL_LOGI_PROFILING_TIMER_START          \
	{                        \
		double tstart, tend; \
		tstart = MPI_Wtime ();
#define H5VL_LOGI_PROFILING_TIMER_STOP(A, B)                             \
	tend = MPI_Wtime ();                             \
	H5VL_log_profile_add_time (A, B, tend - tstart); \
	}
#else
#define H5VL_LOGI_PROFILING_TIMER_START \
	{}
#define H5VL_LOGI_PROFILING_TIMER_STOP(A, B) \
	{}
#endif

#ifdef LOGVOL_PROFILING
void H5VL_log_profile_add_time (void *file, int id, double t);
void H5VL_log_profile_sub_time (void *file, int id, double t);
void H5VL_log_profile_print (void *file);
void H5VL_log_profile_reset (void *file);
#endif