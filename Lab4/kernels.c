/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "ling",              /* Team name */

    "SA12226150",     /* First member full name */
    "sa612150@mail.ustc.edu.cn",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
	int i, j;
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{ 
	int i,j,k;
	int stride = 32;
	int count = dim >> 5;
	src += dim - 1;	
	for(i=0;i<count;i++){
		for(j=0;j<dim;j++){
			for(k =0;k<stride;k++){  //32路循环展开 
				*dst++ = *src;
      	src += dim;
			}
  		src -= dim * stride + 1;
      dst += dim - stride;
		}
		src += dim * (stride + 1);
		dst -= dim * dim - stride;
	}    
}


/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
			for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    	accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
	int i,j;
	pixel *pixelA,*pixelB,*pixelC;
	int size = dim-1;	

	/********************** line 1 begin *****************************/
	//从pixel 1开始	
	pixelB = src;
	pixelC = pixelB + dim;
	dst->red = (pixelB->red + (pixelB+1)->red + pixelC->red + (pixelC+1)->red)>>2;
	dst->green = (pixelB->green + (pixelB+1)->green + pixelC->green + (pixelC+1)->green)>>2;
	dst->blue = (pixelB->blue + (pixelB+1)->blue + pixelC->blue + (pixelC+1)->blue)>>2;
	pixelB++;
	pixelC++;
	dst++;

	//pixel 2 到 pixel dim-1  
	for(i = 1; i < size; i++)
	{
		dst->red = (pixelB->red + (pixelB-1)->red + (pixelB+1)->red + pixelC->red + (pixelC-1)->red + (pixelC+1)->red)/6;
		dst->green = (pixelB->green + (pixelB-1)->green + (pixelB+1)->green + pixelC->green + (pixelC-1)->green + (pixelC+1)->green)/6;
		dst->blue = (pixelB->blue + (pixelB-1)->blue + (pixelB+1)->blue + pixelC->blue + (pixelC-1)->blue + (pixelC+1)->blue)/6;
		pixelB++;
		pixelC++;
		dst++;
	}

	//行1的最后一个pixel 
	dst->red = (pixelC->red + (pixelC-1)->red + pixelB->red + (pixelB-1)->red)>>2;
	dst->green = (pixelC->green + (pixelC-1)->green + pixelB->green + (pixelB-1)->green)>>2;
	dst->blue = (pixelC->blue + (pixelC-1)->blue + pixelB->blue + (pixelB-1)->blue)>>2;
	dst++;

	/********************** 行1结束*****************************/

	/********************** 开始处理行2到行dim-1********************/

	pixelA = src;
	pixelB = pixelA + dim;
	pixelC = pixelB + dim;
	for(i = 1; i < size; i++)
	{
		//从pixel 1开始		
		dst->red = (pixelA->red + (pixelA+1)->red + pixelB->red + (pixelB+1)->red + pixelC->red + (pixelC+1)->red)/6;
		dst->green = (pixelA->green + (pixelA+1)->green + pixelB->green + (pixelB+1)->green + pixelC->green + (pixelC+1)->green)/6;
		dst->blue = (pixelA->blue + (pixelA+1)->blue + pixelB->blue + (pixelB+1)->blue + pixelC->blue+ (pixelC+1)->blue)/6;
		dst++;
		pixelA++;
		pixelB++;
		pixelC++;
		//pixel 2 到 pixel dim-1
		for(j = 1; j < dim-1; j++)
		{
			dst->red = (pixelA->red + (pixelA-1)->red + (pixelA+1)->red + pixelB->red + (pixelB-1)->red + (pixelB+1)->red + pixelC->red + (pixelC-1)->red + (pixelC+1)->red)/9;
			dst->green = (pixelA->green + (pixelA-1)->green + (pixelA+1)->green + pixelB->green + (pixelB-1)->green + (pixelB+1)->green + pixelC->green + (pixelC-1)->green + (pixelC+1)->green)/9;
			dst->blue = (pixelA->blue + (pixelA-1)->blue + (pixelA+1)->blue + pixelB->blue + (pixelB-1)->blue + (pixelB+1)->blue + pixelC->blue + (pixelC-1)->blue + (pixelC+1)->blue)/9;
			pixelA++;
			pixelB++;
			pixelC++;
			dst++;
		}
		//行i的最后一个pixel
		dst->red = (pixelA->red + (pixelA-1)->red + pixelB->red + (pixelB-1)->red + pixelC->red + (pixelC-1)->red)/6;
		dst->green = (pixelA->green + (pixelA-1)->green + pixelB->green + (pixelB-1)->green + pixelC->green + (pixelC-1)->green)/6;
		dst->blue = (pixelA->blue + (pixelA-1)->blue + pixelB->blue + (pixelB-1)->blue + pixelC->blue+ (pixelC-1)->blue)/6;
		pixelA++;
		pixelB++;
		pixelC++;
		dst++;
	}

	/********************** 行2到行dim-1结束 ***************************/

	/**********************开始处理行dim*****************************/

	//第一个pixel	
	dst->red = (pixelA->red + (pixelA+1)->red + pixelB->red + (pixelB+1)->red)>>2;
	dst->green = (pixelA->green + (pixelA+1)->green + pixelB->green + (pixelB+1)->green)>>2;
	dst->blue = (pixelA->blue + (pixelA+1)->blue + pixelB->blue + (pixelB+1)->blue)>>2;
	dst++;
	pixelA++;
	pixelB++;
	
	//pixel 2到pixel dim-1 
	for(i = 1; i < size; i++)
	{
		dst->red = (pixelA->red + (pixelA-1)->red + (pixelA+1)->red + pixelB->red + (pixelB-1)->red + (pixelB+1)->red)/6;
		dst->green = (pixelA->green + (pixelA-1)->green + (pixelA+1)->green + pixelB->green + (pixelB-1)->green + (pixelB+1)->green)/6;
		dst->blue = (pixelA->blue + (pixelA-1)->blue + (pixelA+1)->blue + pixelB->blue + (pixelB-1)->blue + (pixelB+1)->blue)/6;
		pixelA++;
		pixelB++;
		dst++;
	}

	//行dim的最后一个pixel 
	dst->red = (pixelA->red + (pixelA-1)->red + pixelB->red + (pixelB-1)->red)>>2;
	dst->green = (pixelA->green + (pixelA-1)->green + pixelB->green + (pixelB-1)->green)>>2;
	dst->blue = (pixelA->blue + (pixelA-1)->blue + pixelB->blue + (pixelB-1)->blue)>>2;

	/********************** 行dim结束 *****************************/
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&naive_smooth, naive_smooth_descr);
	add_smooth_function(&smooth, smooth_descr);
    /* ... Register additional test functions here */
}


