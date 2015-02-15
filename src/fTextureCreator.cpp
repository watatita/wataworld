#include "fTextureCreator.h"

#include <irrlicht.h>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;


/** @ HSV to RGB
  *
  * modified from: http://www.cs.rit.edu/~ncs/color/t_convert.html
  *
  * h:  color degree, 0 to 360 degree
  * s:  color saturation, 0.0 to 1.0
  * v:  color value, 0 to 255
  */
SColor HSVtoRGB( float h, float s, float v )
{
	u32 i;
	f32 f, p, q, t;
	u32  r,g,b;
	SColor rgbColor;

	if( s == 0 ) {
		// achromatic (grey) *r = *g = *b = v;
		rgbColor.setBlue(v);
		rgbColor.setGreen(v);
		rgbColor.setRed(v);
		return rgbColor;
	}

	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			r = (u32) v;
			g = (u32) t;
			b = (u32) p;
			break;
		case 1:
			r = (u32) q;
			g = (u32) v;
			b = (u32) p;
			break;
		case 2:
			r = (u32) p;
			g = (u32) v;
			b = (u32) t;
			break;
		case 3:
			r = (u32) p;
			g = (u32) q;
			b = (u32) v;
			break;
		case 4:
			r = (u32) t;
			g = (u32) p;
			b = (u32) v;
			break;
		default:		// case 5:
			r = (u32) v;
			g = (u32) p;
			b = (u32) q;
			break;
	}

	rgbColor.setBlue(b);
    rgbColor.setGreen(g);
    rgbColor.setRed(r);
    return rgbColor;

}

fTextureCreator::fTextureCreator(fMathGenerator* t_mathgenerator)
{
    //ctor
    mgen=t_mathgenerator;
}

fTextureCreator::~fTextureCreator()
{
    //dtor
}

void fTextureCreator::createSkyTexture(IImage* skyimage)
{
    s32 t_width=skyimage->getDimension().Width;
    s32 t_height=skyimage->getDimension().Height;

    for(u32 j=0;j<t_height;j++)
    {
        for(u32 i=0;i<t_width;i++)
        {
            f32 framecosine=1-cos((f32)j*8/t_height);
//            framecosine=framecosine*(1-cos((f32)i/32));
            if(i<16)             framecosine=framecosine*((f32)i)/16;
            if(i>(t_width-16))   framecosine=framecosine*((f32)t_width-i)/16;

            f32 c=(framecosine* (mgen->PerlinNoise(i,j,16)+mgen->PerlinNoise(i,j,8)/2+mgen->PerlinNoise(i,j,4)/4+0.75)/2 );
            if(c<0)c=0;
            if(c>1.0) c=1;

            skyimage->setPixel(i,j,HSVtoRGB(210,1-c,255));
        }
    }
}

void fTextureCreator::createWaterTexture(IImage* waterimage)
{
    for(u32 j=0;j<waterimage->getDimension().Height;j++)
    {
        for(u32 i=0;i<waterimage->getDimension().Width;i++)
        {
            f32 z=mgen->PerlinNoise(i,j,16)*2;
            if(z<0) z=-z;
            s32 c=0xff*z*2;
            waterimage->setPixel(i,j,HSVtoRGB(210-z*15,0.8,0xa8));
        }
    }
}

void fTextureCreator::createSun(IImage* sunimage)
{
    resetGauss();
    for(s32 j=-16;j<16;j++)
    {
        for(s32 i=-16;i<16;i++)
        {
            gauss_srcs_vector[128+i][128+j]=1000;
        }
    }

    gauss_process(30);

    for (u32 j=0;j<256;j++)
    {
        for (u32 i=0;i<256;i++)
        {
            gauss_srcs_vector[i][j]=gauss_proc_vector[i][j];
        }
    }
    gauss_process(16);

    for(u32 j=0;j<128;j++)
    {
        for(u32 i=0;i<128;i++)
        {
            s32 c=gauss_proc_vector[i+64][j+64];
            if(c>0xff)c=0xff;
//            sunimage->setPixel(i,j,SColor(0xff,c,c,c));
            sunimage->setPixel(i,j,HSVtoRGB(30,0.2,c));
        }
    }

}


/** @brief (one liner)
  *
  * (documentation goes here)
  * --gauss table explanation--
  *   [-3 -2 -1  0  1  2  3]
  *-------------------------
  * 3 | 6  5  4  3  4  5  6}
  * 2 | 5  4  3  2  3  4  5}
  * 1 | 4  3  2  1  2  3  4}
  * 0 | 3  2  1  0  1  2  3}
  *-1 | 4  3  2  1  2  3  4}
  *-2 | 5  4  3  2  3  4  5}
  *-3 | 6  5  4  3  4  5  6}
  *
  * G[-1][2]=G[1][2]
  * G[3][-2]=G[3][2]
  * G[a][b]=G[abs(a)][abs(b)]

  */
f32 fTextureCreator::getGaussTable(s32 x, s32 y)
{
    u32 ux=abs(x);
    u32 uy=abs(y);
    return gaussTable[ux][uy];
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fTextureCreator::initGaussTable(s32 radius)
{
    if(radius>=32)
    {
        printf("out of radius\n");
        return;
    }

    if(radius!=gaussRadius)
    {
        gaussRadius=radius;
        s32 r=radius;
        for(u32 j=0;j<=radius;j++)
        {
            for(u32 i=0;i<=radius;i++)
            {
                f32 dsq=i*i+j*j;
                f32 wgt=exp(-dsq/(2*radius*radius));
                wgt=wgt/(2*3.14*radius*radius);
                gaussTable[i][j]=wgt;
            }
        }

        gaussSum=0;
        for(s32 jn=-r;jn<=r;jn++)
        {
            for(s32 in=-r;in<=r;in++)
            {
                gaussSum=gaussSum+getGaussTable(in,jn);
            }
        }
    }
}

//gaussian process
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fTextureCreator::gauss_process(s32 radius)
{
    if(radius<0) radius=-radius;

    initGaussTable(radius);

    for (u32 j=0;j<256;j++)
    {
        for (u32 i=0;i<256;i++)
        {
            gauss_proc_vector[i][j]=0;
        }
    }

    for(u32 j=64; j<(128+64); j++)
    {
        for(u32 i=64; i<(128+64); i++)
        {
            f32 val=0;
            for(s32 jn = -radius;jn <= radius; jn++)
            {
                for(s32 in = -radius;in <= radius; in++)
                {
//                    if((gauss_srcs_vector[i+in][j+jn] * getGaussTable(in,jn))>0)
//                        printf("%f\n",(gauss_srcs_vector[i+in][j+jn] * getGaussTable(in,jn)));
                    val += (gauss_srcs_vector[i+in][j+jn] * getGaussTable(in,jn));
//                    printf("%f %f\n",in,jn);
                }
            }


            gauss_proc_vector[i][j]=(val/gaussSum);
        }
    }
}

void fTextureCreator::resetGauss()
{
    for (u32 j=0;j<256;j++)
    {
        for (u32 i=0;i<256;i++)
        {
            gauss_srcs_vector[i][j]=0;
        }
    }
}

