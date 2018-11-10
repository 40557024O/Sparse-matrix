#include "SMatrixADT.h"
#include<stdio.h>

int SMTX_read (SMatrixType *p)
{
    int rows=0,cols=0;
    scanf("%d%d",&rows,&cols);

    /*check if the matrix over the correct size*/
    if(rows<0&&cols<0)
    {
        return  SMTX_ERROR;
    }

    /*record maximum rows,cols*/
    p->Max_row=rows;
    p->Max_col=cols;
    /*set no zero value to 0*/
    p->Non_zero=0;

    /*read the matrix*/
    int i=0;
    for(i=0; i<rows; i++)
    {
        int j=0;
        for(j=0; j<cols; j++)
        {
            int tem=0;
            scanf("%d",&tem);
            if(tem!=0)//determine if it's a nonzero value or not
            {
                /*record triplets <row,col,value>*/
                p->R[p->Non_zero].col=j;
                p->R[p->Non_zero].row=i;
                p->R[p->Non_zero].value=tem;

                /*record # nonzero value*/
                p->Non_zero+=1;
                if(p->Non_zero>MAX_SMTX_SIZE)
                    return SMTX_ERROR;

            }
        }
    }
    return 1;

}

int SMTX_print(const SMatrixType *p)
{
    /*print maximum rows,cols,# of non zero entries*/
    printf("Rows = %2d, Cols = %2d, # of non zero entries = %2d\n",p->Max_row,p->Max_col,p->Non_zero);

    /*print non zero triplets*/
    int i=0;
    for(i=0; i<p->Non_zero; i++)
    {
        printf("<%2d,%2d,%2d>\n",p->R[i].row,p->R[i].col,p->R[i].value);
    }
    return 1;
}

int SMTX_add(const SMatrixType *a,const SMatrixType *b,SMatrixType *c)
{
    /*check if A's and B's dimension are the same*/
    if(a->Max_row!=b->Max_row||a->Max_col!=b->Max_col)
    {
        return SMTX_ERROR;
    }

    /*point to each matrix's head*/
    Matrix *ptr_a=&(a->R[0]);
    Matrix *ptr_b=&(b->R[0]);
    Matrix *ptr_c=&(c->R[0]);

    /* A+B->C */
    int a_count=a->Non_zero;
    int b_count=b->Non_zero;
    int c_count=0;
    while(a_count&&b_count)
    {

        /*row and col of a ,b are equal*/
        if(ptr_a->row==ptr_b->row&&ptr_a->col==ptr_b->col)
        {
            ptr_c->value=ptr_a->value+ptr_b->value;
            ptr_c->row=ptr_a->row;
            ptr_c->col=ptr_a->col;
            ptr_a=ptr_a+1;
            ptr_b=ptr_b+1;
            ptr_c=ptr_c+1;
            a_count-=1;
            b_count-=1;
        }
        /*a smaller than b*/
        else if (ptr_a->row<ptr_b->row||(ptr_a->row==ptr_b->row&&ptr_a->col<ptr_b->col))
        {
            ptr_c->row=ptr_a->row;
            ptr_c->col=ptr_a->col;
            ptr_c->value=ptr_a->value;
            ptr_a=ptr_a+1;
            ptr_c=ptr_c+1;
            a_count-=1;

        }
        /*b is smaller than a*/
        else if(ptr_b->row<ptr_a->row||(ptr_a->row==ptr_b->row&&ptr_b->col<ptr_a->col))
        {
            ptr_c->row=ptr_b->row;
            ptr_c->col=ptr_b->col;
            ptr_c->value=ptr_b->value;
            ptr_b=ptr_b+1;
            ptr_c=ptr_c+1;
            b_count-=1;

        }
        c_count+=1;

    }
    Matrix *ptr=NULL;
    int count=0;
    if(a_count)//a still have something
    {
        ptr=ptr_a;
        count=a_count;
    }
    else
    {
        ptr=ptr_b;
        count=b_count;
    }
    while(count)
    {
        ptr_c->row=ptr->row;
        ptr_c->col=ptr->col;
        ptr_c->value=ptr->value;
        ptr_c=ptr_c+1;
        ptr=ptr+1;
        c_count+=1;
        count-=1;
    }
    if(c_count>MAX_SMTX_SIZE)
    {
        return SMTX_ERROR;
    }
    else
    {
        c->Non_zero=c_count;
        c->Max_row=a->Max_row;
        c->Max_col=a->Max_col;
    }
    return 1;



}

int SMTX_subtract(const SMatrixType *a,const SMatrixType *b,SMatrixType *c)
{
    /*check if A's and B's dimension are the same*/
    if(a->Max_row!=b->Max_row||a->Max_col!=b->Max_col)
    {
        return SMTX_ERROR;
    }


    /*point to each matrix's head*/
    Matrix *ptr_a=&(a->R[0]);
    Matrix *ptr_b=&(b->R[0]);
    Matrix *ptr_c=&(c->R[0]);

    /* A-B->C */
    int a_count=a->Non_zero;
    int b_count=b->Non_zero;
    int c_count=0;
    while(a_count&&b_count)
    {

        /*row and col of a ,b are equal*/
        if(ptr_a->row==ptr_b->row&&ptr_a->col==ptr_b->col)
        {
            ptr_c->value=ptr_a->value-ptr_b->value;
            ptr_c->row=ptr_a->row;
            ptr_c->col=ptr_a->col;
            ptr_a=ptr_a+1;
            ptr_b=ptr_b+1;
            ptr_c=ptr_c+1;
            a_count-=1;
            b_count-=1;
        }
        /*a smaller than b*/
        else if (ptr_a->row<ptr_b->row||(ptr_a->row==ptr_b->row&&ptr_a->col<ptr_b->col))
        {
            ptr_c->row=ptr_a->row;
            ptr_c->col=ptr_a->col;
            ptr_c->value=ptr_a->value;
            ptr_a=ptr_a+1;
            ptr_c=ptr_c+1;
            a_count-=1;

        }
        /*b is smaller than a*/
        else if(ptr_b->row<ptr_a->row||(ptr_a->row==ptr_b->row&&ptr_b->col<ptr_a->col))
        {
            ptr_c->row=ptr_b->row;
            ptr_c->col=ptr_b->col;
            ptr_c->value=(ptr_b->value)*-1;
            ptr_b=ptr_b+1;
            ptr_c=ptr_c+1;
            b_count-=1;

        }
        c_count+=1;

    }
    Matrix *ptr=NULL;
    int count=0;
    int one=1;
    if(a_count)//a still have something
    {
        ptr=ptr_a;
        count=a_count;
    }
    else
    {
        ptr=ptr_b;
        count=b_count;
        one=-1;
    }
    while(count)
    {
        ptr_c->row=ptr->row;
        ptr_c->col=ptr->col;
        ptr_c->value=ptr->value*one;
        ptr_c=ptr_c+1;
        ptr=ptr+1;
        c_count+=1;
        count-=1;
    }
    if(c_count>MAX_SMTX_SIZE)
    {
        return SMTX_ERROR;
    }
    else
    {
        c->Non_zero=c_count;
        c->Max_row=a->Max_row;
        c->Max_col=a->Max_col;
    }
    return 1;

}

int SMTX_transpose(const SMatrixType *a,SMatrixType *b)
{
    int row_terms[a->Max_col],starting_pos[a->Max_col];
    b->Max_row=a->Max_col;
    b->Max_col=a->Max_row;
    b->Non_zero=a->Non_zero;

    int i=0;
    if(a->Non_zero>0)
    {
        /*set to zero*/
        for(i=0; i<a->Max_col; i++)
        {
            row_terms[i]=0;
        }
        /*calculate the time of 0~max_col appearance*/
        for(i=0; i<a->Non_zero; i++)
        {
            row_terms[a->R[i].col]+=1;
        }
        /*record starting position of each col*/
        starting_pos[0]=0;
        for(i=1; i<a->Max_col; i++)
        {
            starting_pos[i]=starting_pos[i-1]+row_terms[i-1];
        }
        int j=0;
        for(i=0; i<a->Non_zero; i++)
        {
            j=starting_pos[a->R[i].col]++;
            b->R[j].row=a->R[i].col;
            b->R[j].col=a->R[i].row;
            b->R[j].value=a->R[i].value;
        }

    }
    return 1;
}


void storesum(SMatrixType *c, int *totalc, int row, int column, int *sum)
{
    if (*sum)
    {
        if (*totalc < MAX_SMTX_SIZE)
        {
            c->R[*totalc].row = row;
            c->R[*totalc].col = column;
            c->R[(*totalc)++].value = *sum;
            *sum = 0;
        }
    }

}
int COMPARE(int a, int b)
{
    if(a>b)return -1;
    if(a==b)return 0;
    if(a<b)return 1;
}
int SMTX_multiply(SMatrixType *a,const SMatrixType *b,SMatrixType *c)
{
    int i, j, column, totalc = 0;
    int row_begin = 0, row = a->R[0].row, sum = 0;
    SMatrixType temp;

    /*col of a not equal to row of b*/
    if(a->Max_col!=b->Max_row)
    {
        return SMTX_ERROR;
    }

    /*transpose of b store in temp*/
    SMTX_transpose(b,&temp);

    /*set the boundary*/
    a->R[a->Non_zero].row = a->Max_row;
    temp.R[b->Non_zero].row = b->Max_col;
    temp.R[b->Non_zero].col = 0;

    for (i = 0; i < a->Non_zero; )
    {
        sum = 0;
        column = temp.R[0].row;
        for (j = 0; j <b->Non_zero+1;)
        {
            if (a->R[i].row != row)
            {
                storesum(c, &totalc, row, column, &sum);
                i = row_begin;
                for (; temp.R[j].row == column; j++);
                column = temp.R[j].row;
            }
            else if (temp.R[j].row != column)
            {
                storesum(c, &totalc, row, column, &sum);
                i = row_begin;
                column = temp.R[j].row;
            }
            else
            {
                switch (COMPARE(a->R[i].col,temp.R[j].col))
                {
                case 1:/* a->R[i].col < temp.R[j].col*/
                    i++;
                    break;
                case -1:/* a->R[i].col > temp.R[j].col*/
                    j++;
                    break;
                case 0:/* a->R[i].col = temp.R[j].col*/
                    sum += (a->R[i++].value * temp.R[j++].value);
                }
            }
        }
        for (; a->R[i].row == row; i++);
        row_begin = i;
        row = a->R[i].row;
    }
    c->Max_row= a->Max_row;
    c->Max_col= b->Max_col;
    c->Non_zero= totalc;
    if(c->Non_zero>MAX_SMTX_SIZE)
    {
        return SMTX_ERROR;
    }
    return 1;
}





