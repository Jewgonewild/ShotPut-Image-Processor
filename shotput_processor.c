#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>

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
	in_width = atoi(argv[2]);
	in_height = atoi(argv[3]);
	output_file = argv[4];
	image_info=CloneImageInfo((ImageInfo *) NULL);
	(void) strcpy(image_info->filename,argv[1]);
	printf("Reading %s ...",argv[argc-1]);
	image=ReadImage(image_info,&exception);
	width = image->magick_columns; //Will need orig image length and size for scaling later.
	height = image->magick_rows;  
	printf(" %lu frames\n", GetImageListLength(image));
      	if (exception.severity != UndefinedException)
        	CatchException(&exception);
	
	/*Resize the image.. for now defaulting to constrained width and height.. needs work*/
	resize_image=SampleImage(image,in_width,in_height,&exception);
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
	}

	/*Clean up objects*/
	DestroyImageInfo(image_info);
  	DestroyExceptionInfo(&exception);
  	DestroyMagick();
	return (0);

}
