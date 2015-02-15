#ifndef FMATHGENERATOR_H
#define FMATHGENERATOR_H

#include <irrlicht.h>
#include <math.h>

#define POISSON_CELL_SIZE   8
//#define __NO_POISSON_DISK_SAMPLING__



#define randomWalk(_c_)   new_random_point(_c_,5);

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

class fMathGenerator
{
    public:
        fMathGenerator();
        virtual ~fMathGenerator();
        position2df gradien(s32 x,s32 y);
        f32 PerlinNoise(f32 x,f32 y,f32 scale);
        f32 GradientFrame(u32 x,u32 y);


    //image scalling
        f32 scaleImage(f32 x, f32 y,f32 scale);
    //unused Poisson disk sampling
//    #ifndef __NO_POISSON_DISK_SAMPLING__
        f32 check_distance(core::vector2df a, core::vector2df b);
        bool check_empty_neighbour(core::vector2df a,f32 min_radius);
        vector2df new_random_point(core::vector2df previous_point,f32 min_radius);
        void createPoisson(u32 width, u32 height, u32 new_points_count);

        array<vector2df> sample_poisson;
//    #endif // __NO_POISSON_DISK_SAMPLING__
    protected:
    private:
        position2df static_grad[128][128];
        u8  v_img[128][128];
        f32 img_gradframe[128][128];



//    #ifndef __NO_POISSON_DISK_SAMPLING__
        array<vector2df> process_poisson;
        array<vector2df> grid_handler[128][128];
//    #endif // __NO_POISSON_DISK_SAMPLING__

};

/*

*/
#endif // FMATHGENERATOR_H
/*
------------------------
    scaling functions
------------------------
f32 scaleImage(f32 x, f32 y,f32 scale)
{

    f32 cx=x/scale;
    f32 cy=y/scale;

    s32 ix=(s32)cx;
    s32 iy=(s32)cy;
    s32 ix2=ix+1;
    s32 iy2=iy+1;
    f32 frac_x=cx-ix;
    f32 frac_y=cy-iy;


    f32 u0=tImage [ix] [iy];
    f32 u1=tImage[ix2] [iy];
    f32 u2=tImage [ix][iy2];
    f32 u3=tImage[ix2][iy2];

    f32 Sx   = 3*(frac_x*frac_x) - 2*(frac_x*frac_x*frac_x);
    f32 u0_1 = u0 + Sx*(u1-u0);
    f32 u2_3 = u2 + Sx*(u3-u2);

    f32 Sy     = 3*(frac_y*frac_y) - 2*(frac_y*frac_y*frac_y);
    f32 u01_23 = u0_1 + Sy*(u2_3-u0_1);

    return u01_23;
}
*/

/*
------------------------
    coloring functions
------------------------

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	float min, max, delta;

	min = MIN( r, g, b );
	max = MAX( r, g, b );
	*v = max;				// v

	delta = max - min;

	if( max != 0 )
		*s = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		*s = 0;
		*h = -1;
		return;
	}

	if( r == max )
		*h = ( g - b ) / delta;		// between yellow & magenta
	else if( g == max )
		*h = 2 + ( b - r ) / delta;	// between cyan & yellow
	else
		*h = 4 + ( r - g ) / delta;	// between magenta & cyan

	*h *= 60;				// degrees
	if( *h < 0 )
		*h += 360;

}

void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;

	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}

	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}

}
*/
