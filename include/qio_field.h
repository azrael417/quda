#ifndef _GAUGE_QIO_H
#define _GAUGE_QIO_H

#ifdef HAVE_QIO
void read_gauge_field(const char *filename, void *gauge[], QudaPrecision prec, const int *X,
		      int argc, char *argv[]);
void read_spinor_field(const char *filename, void *V[], QudaPrecision precision, const int *X,
		       int nColor, int nSpin, int Nvec, int argc, char *argv[]);
void write_spinor_field(const char *filename, void *V[], QudaPrecision precision, const int *X,
			int nColor, int nSpin, int Nvec, int argc, char *argv[]);
#else
static void read_gauge_field(const char *filename, void *gauge[], QudaPrecision prec,
		      const int *X, int argc, char *argv[]) {
  printf("QIO support has not been enabled\n");
  exit(-1);
}
static void read_spinor_field(const char *filename, void *V[], QudaPrecision precision, const int *X,
			int nColor, int nSpin, int Nvec, int argc, char *argv[]) {
  printf("QIO support has not been enabled\n");
  exit(-1);
}
static void write_spinor_field(const char *filename, void *V[], QudaPrecision precision, const int *X,
			       int nColor, int nSpin, int Nvec, int argc, char *argv[]) {
  printf("QIO support has not been enabled\n");
  exit(-1);
}

#endif

#endif // _GAUGE_QIO_H
