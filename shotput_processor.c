#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <magick/api.h>

//Set some globals.
short size_arr[2];
RectangleInfo geometry;

/*
	Scale image based on width or height.
	@params origin_width,origin_height: width of image object, height of image object.
	@params desired_width, desired_height: desired width and height of scaled image.
	*/
void scale(double orig_width,double orig_height, double desired_width, double desired_height)
{
	double scale;
	double new_width = 0;
	double new_height = 0;
	
	if(desired_width!=0){
		scale = orig_width/desired_width;
		new_width = desired_width;
		new_height = orig_height / scale;
	}
	
	if(desired_width==0 && desired_height!=0){
		scale = orig_height/desired_height;
		new_height = desired_height;
		new_width = orig_width / scale;
	}
	//Set global resize arr for re-sampling.
	size_arr[0] = new_width;
	size_arr[1] = new_height;
}
/*
	Crop image, and center it to a fixed crop frame.
	@params origin_width,origin_height: width of image object, height of image object.
	@params desired_width, desired_height: desired width and height of crop frame.
	*/
void crop(int orig_width, int orig_height, unsigned int desired_width, unsigned int desired_height)
{
	double ratio_x, ratio_y;
	long crop_x = 0, crop_y = 0, new_width, new_height;
	
	ratio_x = (double)desired_width / (double)orig_width; 
	ratio_y = (double)desired_height / (double)orig_height;
	
	//Scale image either based on width or height.
	if(ratio_x > ratio_y){ 
		new_width  = desired_width; 
		new_height = ratio_x * (double)orig_height;
	}else{
		new_height = desired_height; 
		new_width  = ratio_y * (double)orig_width;
	}
	
	//Set global resize arr for re-sampling.
	size_arr[0] = new_width;
	size_arr[1] = new_height;
	
	//Set center cropping.
	crop_x = (new_width - desired_width) / 2;
	crop_y = (new_height - desired_height) / 2;
	
	//Prepare geometry struct for cropping.
	geometry.width = desired_width;
	geometry.height = desired_height;
	geometry.x = crop_x;
	geometry.y = crop_y;
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
	
	clock_t t1, t2;
	
	int  rendered = 0;
	int  in_width = 0;
	int  input_width = 0;
	int input_height =0;
	
	char *output_file = NULL;
	char type;
	char *source_image, *strategy;
	const char *result = NULL;
	
	long unsigned int
	 width,
	 height;
	
	t1 = clock();
	InitializeMagick(*argv);
	GetExceptionInfo(&exception);
	
	/*Start argument collection.. iterate on this..*/
	source_image = argv[2];
	
	if(strcmp(argv[3],"-w")==0){
		input_width = atoi(argv[4]);
	}
	else if(strcmp(argv[3],"-h")==0){
		input_height = atoi(argv[4]);
	}
	if(strcmp(argv[5],"-w")==0){
		input_width = atoi(argv[6]);
	}
	else if(strcmp(argv[5],"-h")==0){
		input_height = atoi(argv[6]);
	}
	if(strcmp(argv[7],"-st")==0){
		strategy = argv[8];
	}
	else{
		strategy = "fit";
	}
	
	image_info=CloneImageInfo((ImageInfo *) NULL);
	(void) strcpy(image_info->filename,source_image);
	image=ReadImage(image_info,&exception);
	width = image->magick_columns;
	height = image->magick_rows;
	if (exception.severity != UndefinedException)
		CatchException(&exception);
	
	//printf("\n\n\nimage width %lu image height %lu in width %d in height %d\n\n\n",width,height,input_width,input_height);
   
	if(strcmp(strategy,"fit")==0){
		scale(width,height,input_width,input_height);
		resize_image=ScaleImage(image,size_arr[0],size_arr[1],&exception);
	}
	else if(strcmp(strategy,"crop")==0){
		crop(width,height,input_width,input_height);//cro(image,&geometry, &exception);
		resize_image = ScaleImage(image,size_arr[0],size_arr[1],&exception); //Resize, than crop this image to specified region
		resize_image = CropImage(resize_image,&geometry, &exception); //Crop to specified region.
	}
	else if(strcmp(strategy,"stretch")==0){
		resize_image=ScaleImage(image,input_width,input_height,&exception);
	}
	DestroyImage(image);
	
	if (resize_image == (Image *) NULL){
		 CatchException(&exception);
	}
	else{
		rendered = 1;
	}
	
	if(rendered){	
		strcpy(thumbnail->filename,(const char *) argv[argc-1]);
		WriteImage(image_info,thumbnail);
		printf("\n\n ----Done.----\n\n");
	}
	t2 = clock();
	float diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	
	/*Clean up objects*/
	DestroyImageInfo(image_info);
	DestroyImage(resize_image);
  	DestroyExceptionInfo(&exception);
  	DestroyMagick();
	return (0);

}