#include "CImg.h"
#include <iostream>

using namespace cimg_library;

int main(int argc, char const ** argv) {


	char file_name[200], base_name[200], *pt, *ptc; // = 
	char ext[32];

	if ( argc != 4) {
		std::cout << "USAGE : ./main image.hdr " << std::endl;
		return 0;
	}

	// strcpy(file_name,argv[1]) ;
	// char * extention;
	
	// std::cout << file_name << std::endl;
	// extention = strrchr(file_name,'.') ;
	// strcpy(ext,extention) ;
	// std::cout << " Extention : " << ext << std::endl;

	// extention -- ;
	// while( ((*extention)>='0') && ((*extention)<='9') && extention > file_name ) extention -- ;
	// extention ++ ;
	// std::cout << " Suffixe : " << extention << std::endl;
	
	// ptc = base_name;
	// pt = file_name;
	// while(pt<extention) (*ptc++) = (*pt++) ; (*ptc) = (char)0 ;
	// std::cout << " Nom de Base : " << base_name << std::endl;


	// bool ok = true;
	// int increment = 0;
	// FILE * file;
	float voxels_size[3];
	CImg<> img_read;
	img_read.load_analyze (argv[1], voxels_size);
	CImgDisplay img_readDisp(img_read, argv[1]);
	bool redraw = false;

	// while (ok) {
		
	// 	if (increment < 21)
	// 		sprintf(file_name, "%s%d%s", base_name, increment, ext);
	// 	std::cout << "Nom du fichier : " << file_name << std::endl;

	// 	file = fopen(file_name, "r");
	// 	ok = (file!=NULL);
	// 	if (ok) {
	// 		fclose(file);
	// 		img_read.load_analyze ( file_name, voxels_size );
	// 		img_readDisp.display(img_read);
	// 	}

	// 	if (img_readDisp.is_keySPACE()) {
	// 		increment ++;
	// 		redraw = true;
	// 	}
	// 	if (increment == 21) {
	// 		increment == 0;
	// 	}

	// 	if (redraw) {

	// 	}
			
	
	// }

	int height = img_read.height ();
	int width = img_read.width ();
	int depth = 10;
	int slice = 0;
	int threshold = atoi(argv[2]);
	int erosion = atoi(argv[3]);
	CImg<> edited_img = img_read.get_blur_median(4);
	edited_img = edited_img.get_threshold(threshold);
	edited_img = edited_img.erode(erosion, erosion, erosion);
	edited_img = edited_img.dilate(erosion, erosion, erosion);
	CImgDisplay edited_disp (edited_img, "edited_img");

	while (!img_readDisp.is_closed() && !img_readDisp.is_keyESC()) {

		if ( img_readDisp.button()&1 ) {

		    edited_img = edited_img.dilate(erosion,erosion,erosion);
            edited_disp.display(edited_img);
		} 

		if (img_readDisp.button()&2) {
			edited_img = img_read;
			edited_img = edited_img.get_threshold(50);
			edited_disp.display(edited_img);
		}

		img_readDisp.wait();
	}



	return 0;
}