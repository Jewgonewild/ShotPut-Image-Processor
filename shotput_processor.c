#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <magick/api.h>

short size_arr[2];

void scale(double width,double height, double input_width, double input_height)
{
	double scale;
	double new_width = 0;
	double new_height = 0;
	
	if(input_width!=0)
	{
		scale = width/input_width;
		new_width = input_width;
		new_height = height / scale;
	}
	
	if(input_width==0 && input_height!=0)
	{
		scale = height/input_height;
		new_height = input_height;
		new_width = width / scale;
	}
	size_arr[0] = new_width;
	size_arr[1] = new_height;
}

int main(int argc,char **argv)
{
	ExceptionInfo exception;
	
	Image
	 *image,
	 *resize_image,
	 *thumbnail;
	
	ImageInfo
	 *image_info;
	
	int  rendered = 0;
	int  in_width = 0;
	int  input_width = 0;
	int input_height =0;
	
	char *output_file = NULL;
	char type;
	char *source_image;
	const char *result = NULL;
	
	long unsigned int
	 width,
	 height;
	
	InitializeMagick(*argv);
	GetExceptionInfo(&exception);
	
	/*Start argument collection.. iterate on this..*/
	source_image = argv[2];
	
	if(strcmp(argv[3],"-w")==0)
	{
		input_width = atoi(argv[4]);
	}
	else if(strcmp(argv[3],"-h")==0)
	{
		input_height = atoi(argv[4]);
	}
	if(strcmp(argv[5],"-w")==0)
	{
		input_width = atoi(argv[6]);
	}
	else if(strcmp(argv[5],"-h")==0)
	{
		input_height = atoi(argv[6]);
	}
	
	image_info=CloneImageInfo((ImageInfo *) NULL);
	(void) strcpy(image_info->filename,source_image);
	image=ReadImage(image_info,&exception);
	width = image->magick_columns;
	height = image->magick_rows;
	if (exception.severity != UndefinedException)
		CatchException(&exception);
	scale(width,height,input_width,input_height);
	resize_image=SampleImage(image,round(size_arr[0]),round(size_arr[1]),&exception);
	DestroyImage(image);
	
	if (resize_image == (Image *) NULL)
	{
		 CatchException(&exception);
	}
	else
	{
		rendered = 1;
	}
	
	if(rendered)
	{	
		strcpy(thumbnail->filename,(const char *) argv[argc-1]);
		WriteImage(image_info,thumbnail);
		printf("\n\n ----Done.----\n\n");
	}
	
	/*Clean up objects*/
	DestroyImageInfo(image_info);
  	DestroyExceptionInfo(&exception);
  	DestroyMagick();
	return (0);

}