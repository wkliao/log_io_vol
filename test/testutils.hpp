#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <hdf5.h>
#include <libgen.h>

#define CHECK_ERR(A) { \
    if (A < 0) { \
        nerrs++; \
        printf("Error at line %d in %s:\n", \
        __LINE__,__FILE__); \
        goto err_out; \
    } \
}

#define EXP_ERR(A,B) { \
    if (A != B) { \
        nerrs++; \
        printf("Error at line %d in %s: expecting %d but got %d\n", \
        __LINE__,__FILE__, A, B); \
        goto err_out; \
    } \
}

#define EXP_VAL(A,B) { \
    if (A != B) { \
        nerrs++; \
        std::cout << "Error at line " << __LINE__ << " in " << __FILE__ << ": expecting " << #A << " = " << (B) << ", but got " << (A) << std::endl; \
        goto err_out; \
    } \
}

#define EXP_VAL_EX(A,B,C) { \
    if (A != B) { \
        nerrs++; \
        std::cout << "Error at line " << __LINE__ << " in " << __FILE__ << ": expecting " << C << " = " << (B) << ", but got " << (A) << std::endl; \
        goto err_out; \
    } \
}

#define SHOW_TEST_INFO(A) { \
    if (rank == 0) { \
        std::cout << "*** TESTING CXX    " << basename(argv[0]) << ": " << A << std::endl; \
    } \
}

#define SHOW_TEST_RESULT { \
    MPI_Allreduce(MPI_IN_PLACE, &nerrs, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD); \
    if (rank == 0) { \
        if (nerrs) std::cout << "fail with " << nerrs << " mismatches." << std::endl; \
        else       std::cout << "pass" << std::endl; \
    } \
}


#define PASS_STR "pass\n"
#define SKIP_STR "skip\n"
#define FAIL_STR "fail with %d mismatches\n"


#define HDfprintf printf
#define HDfree free
#define failure_mssg "Fail"
#define FUNC "func"
#define FALSE 0
#define TRUE 1