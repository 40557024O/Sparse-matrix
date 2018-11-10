#define SMTX_ERROR -1
#define MAX_SMTX_SIZE 100

typedef struct Matrixtype
{
    int row;
    int col;
    int value;
}Matrix;
typedef struct SMatrix
{
    int Max_row;
    int Max_col;
    int Non_zero;
    Matrix R[MAX_SMTX_SIZE];
}SMatrixType;


int SMTX_read (SMatrixType *p);

int SMTX_print(const SMatrixType *p);

int SMTX_add(const SMatrixType *a,const SMatrixType *b,SMatrixType *c);

int SMTX_subtract(const SMatrixType *a,const SMatrixType *b,SMatrixType *c);

int SMTX_transpose(const SMatrixType *a,SMatrixType *b);

int SMTX_multiply(SMatrixType *a,const SMatrixType *b,SMatrixType *c);


