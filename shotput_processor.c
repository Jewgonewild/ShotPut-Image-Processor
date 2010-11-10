#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <magick/api.h>

short size_arr[2];

char pikchur_spec(double width,double height, char *type)
{
	double scale;
	double new_width = width;
	double new_height = height;
	//size_arr= (int *) malloc(16);
	if (width > 48)
	{
		if(strcmp("t",type)==0)
		{
			new_width = 50;
			new_height = 50;
		}
		else if(strcmp("s",type)==0)
		{
			if (width > 170)
			{
				scale = width/170;
				new_width = 170;
				new_height = height / scale;
			}
			
		}
		else if(strcmp("m",type)==0)
		{
			if (width > 320)
			{
				scale = width/320;
				new_width = 320;
				new_height = height / scale;
			}
		}
		else if(strcmp("l",type)==0)
		{
			if (width > 640)
			{
				scale = width/640;
				new_width = 640;
				new_height = height / scale;
			}
		}
	}
	
	size_arr[0] = new_width;
	size_arr[1] = new_height;
	return *type;
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
	int  in_height = 0;
	
	char *output_file = NULL;
	char type;
	const char *result = NULL;
	
	long unsigned int
	 width,
	 height;
	
	/*
    	Initialize the image info structure and read the 
    	provided image file from the args.
  	*/
	InitializeMagick(*argv);
	GetExceptionInfo(&exception);
	//in_width = atoi(argv[2]);
	//in_height = atoi(argv[3]);
	output_file = argv[2];
	image_info=CloneImageInfo((ImageInfo *) NULL);
	(void) strcpy(image_info->filename,argv[1]);
	//printf("Reading %s ...",argv[argc-1]);
	image=ReadImage(image_info,&exception);
	width = image->magick_columns; //Will need orig image length and size for scaling later.
	height = image->magick_rows;  
	//printf(" %lu frames\n", GetImageListLength(image));
      	if (exception.severity != UndefinedException)
        	CatchException(&exception);
	
	/*Resize the image.. for now defaulting to constrained width and height.. needs work*/
	//printf("Reading %s ...",argv[5]);
	type = pikchur_spec(width,height,argv[3]);
	printf("Reading %s ...",&type);
	resize_image=SampleImage(image,size_arr[0],size_arr[1],&exception);
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
		//Ghetto way .. need to get around this soon with a loop.
		strcpy(thumbnail->filename,(const char *) argv[argc-2]);
		WriteImage(image_info,thumbnail);
	}
	
	/*Clean up objects*/
	DestroyImageInfo(image_info);
  	DestroyExceptionInfo(&exception);
  	DestroyMagick();
	return (0);

}

