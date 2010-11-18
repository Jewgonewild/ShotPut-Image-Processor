//gcc -o get_exif get_exif.c -O `GraphicsMagick-config --cppflags --ldflags --libs`
//./get_exif image
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <magick/api.h>

void ExtractExif(Image *image)
{
	const ImageAttribute
	    *attribute;
	char
		**values;
	char
		*first;
	int 
		x;
	
	/*printf("%s\n",first);
	first = strtok( NULL, "=" );
	printf("%s\n",strtok(first,"="));*/
	
	attribute=GetImageAttribute(image,"EXIF:*");
	values=StringToList(attribute->value);
	
	if (values != (char **) NULL)
	{
		for (x=0; values[x] != (char *) NULL; x++)
		{
			printf("%s\n",values[x]);
		}
	}
	free(values);
}

int main(int argc,char **argv)
{
	ExceptionInfo exception;
	
	Image
	 *image,
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
	
	InitializeMagick(*argv);
	GetExceptionInfo(&exception);
	
	image_info=CloneImageInfo((ImageInfo *) NULL);
	(void) strcpy(image_info->filename,argv[1]);
	image=ReadImage(image_info,&exception);
	ExtractExif(image);
	
	/*Clean up objects*/
	DestroyImageInfo(image_info);
  	DestroyExceptionInfo(&exception);
  	DestroyMagick();
	return (0);
}