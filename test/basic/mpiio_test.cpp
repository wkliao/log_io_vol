#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_MPIERR                                                             \
	{                                                                            \
		if (err != MPI_SUCCESS) {                                                \
			int el = 256;                                                        \
			char errstr[256];                                                    \
			MPI_Error_string (err, errstr, &el);                                 \
			printf ("Error at line %d in %s: %s\n", __LINE__, __FILE__, errstr); \
		}                                                                        \
	}

#define CHECK_PTR(A)                                                  \
	{                                                                 \
		if (A == NULL) {                                              \
			printf ("Error at line %d in %s:\n", __LINE__, __FILE__); \
		}                                                             \
	}

// static MPI_Offset dsize[] = {15125911000, 405489372, 7172607130, 2962928490};
static MPI_Offset dsize[] = {128, 256, 512, 1024};

int main (int argc, char **argv) {
	int err = 0;
	int rank, np;
	int i;
	double t1, t2, t3, t4;
	const char *file_name;
	MPI_File fh;
	MPI_Info info;
	int size;
	MPI_Offset off, base = 0;
	MPI_Status stat;
	char *buf = NULL;

	MPI_Init (&argc, &argv);
	MPI_Comm_size (MPI_COMM_WORLD, &np);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	if (argc > 2) {
		if (!rank) printf ("Usage: %s [filename]\n", argv[0]);
		MPI_Finalize ();
		return 1;
	} else if (argc > 1) {
		file_name = argv[1];
	} else {
		file_name = "test.bin";
	}

	MPI_Barrier (MPI_COMM_WORLD);
	t3	= MPI_Wtime ();
	err = MPI_Info_create (&info);
	CHECK_MPIERR
	/* collective write */
	err = MPI_Info_set (info, "romio_cb_write", "enable");
	CHECK_MPIERR
	/* no independent MPI-IO */
	err = MPI_Info_set (info, "romio_no_indep_rw", "true");
	CHECK_MPIERR

	MPI_Barrier (MPI_COMM_WORLD);
	t1	= MPI_Wtime ();
	err = MPI_File_open (MPI_COMM_WORLD, file_name, MPI_MODE_CREATE | MPI_MODE_RDWR, info, &fh);
	CHECK_MPIERR
	t2 = MPI_Wtime ();
	if (rank == 0) { printf ("#%%$: File open time: %lf\n", t2 - t1); }
	MPI_Info_free (&info);

	for (i = 0; i < 4; i++) {
		off	 = dsize[i] * rank / np;
		size = (int)((dsize[i] * (rank + 1) / np) - off);
		off += base;
		base += dsize[i];

		buf = (char *)malloc (size);
		CHECK_PTR (buf)
		memset (buf, 0, size);

		MPI_Barrier (MPI_COMM_WORLD);
		t1	= MPI_Wtime ();
		err = MPI_File_write_at_all (fh, off, buf, size, MPI_BYTE, &stat);
		CHECK_MPIERR
		t2 = MPI_Wtime ();
		if (rank == 0) { printf ("#%%$: MPI_File_write_at_all time %d: %lf\n", i, t2 - t1); }

		free (buf);
	}

	MPI_Barrier (MPI_COMM_WORLD);
	t1	= MPI_Wtime ();
	err = MPI_File_close (&fh);
	CHECK_MPIERR
	t2 = MPI_Wtime ();
	if (rank == 0) { printf ("#%%$: File open time: %lf\n", t2 - t1); }

	t4 = MPI_Wtime ();
	if (rank == 0) { printf ("#%%$: End to end time: %lf\n", t4 - t3); }
err_out:;
	MPI_Finalize ();
	return err == 0;
}
