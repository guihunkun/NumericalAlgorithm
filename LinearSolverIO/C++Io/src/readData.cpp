#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <map>
#include "mmio.h"
#include <stdio.h>

using namespace std;
 
int main(int argc, char *argv[])
{
#if 1
		// read data
		string fileName = "../data/bcsstk14.mtx"; 
    int ret_code;
    MM_typecode matcode;
    FILE *f;
    int M, N, nz;   
    int i, *I, *J;
    double *val;

		map<unsigned int, map<unsigned int, double> > A; // Storage in triplet mode， <row <col val> > ; A's id from zero

    if ((f = fopen(fileName.c_str(), "r")) == NULL) {
    	cerr<<"read file error, please check."<<endl;
      exit(1);
    }

    if (mm_read_banner(f, &matcode) != 0){
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }

    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */
    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) ) {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }

    /* find out size of sparse matrix .... */
    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0) {
        exit(1);
		}

    /* reseve memory for matrices */
    I = (int *) malloc(nz * sizeof(int));
    J = (int *) malloc(nz * sizeof(int));
    val = (double *) malloc(nz * sizeof(double));

    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */
    for (i=0; i<nz; i++) {
        fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
        I[i]--;  /* adjust from 1-based to 0-based */
        J[i]--;
    }

    if (f != stdin)  {
			fclose(f);
		}
    /************************/
    /* now write out matrix */
    /************************/
    mm_write_banner(stdout, matcode);
    mm_write_mtx_crd_size(stdout, M, N, nz);
    for (i=0; i<nz; i++) {
        //fprintf(stdout, "%d %d %20.19g\n", I[i]+1, J[i]+1, val[i]);
	A[I[i]][J[i]] = val[i];
	if(mm_is_symmetric(matcode)) {
          A[J[i]][I[i]] = val[i];
        }    
    }

#endif

#if 0
		// write data
		    
		const int nz = 4;
		const int M = 10;
		const int N = 10;

		MM_typecode matcode;                        
		int I[nz] = { 0, 4, 2, 8 };
    int J[nz] = { 3, 8, 7, 5 };
    double val[nz] = {1.1, 2.2, 3.2, 4.4};
    int i;

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);

    mm_write_banner(stdout, matcode); 
    mm_write_mtx_crd_size(stdout, M, N, nz);

    /* NOTE: matrix market files use 1-based indices, i.e. first element
      of a vector has index 1, not 0.  */

    for (i=0; i<nz; i++) {
        //fprintf(stdout, "%d %d %10.3g\n", I[i]+1, J[i]+1, val[i]);
		}
#endif
		return 0;
}

