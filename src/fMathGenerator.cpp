#include "fMathGenerator.h"
using namespace irr::core;
fMathGenerator::fMathGenerator()
{
    //ctor
    for (u32 j=0;j<128;j++)
    {
        for (u32 i=0;i<128;i++)
        {
            static_grad[i][j].X=(f32)((rand()%512)-256)/256;
            static_grad[i][j].Y=(f32)((rand()%512)-256)/256;
            f32 r=sqrt(static_grad[i][j].X*static_grad[i][j].X + static_grad[i][j].Y*static_grad[i][j].Y);
            static_grad[i][j].X=static_grad[i][j].X/r;
            static_grad[i][j].Y=static_grad[i][j].Y/r;
            if(j==127)
            {
                static_grad[i][j].X=static_grad[i][0].X;
                static_grad[i][j].Y=static_grad[i][0].Y;
            }
        }
        static_grad[127][j].X=static_grad[0][j].X;
        static_grad[127][j].Y=static_grad[0][j].Y;
    }

    for (u32 j=0;j<168;j++)
    {
        for (u32 i=0;i<168;i++)
        {
            gauss_srcs_vector[i][j]=0;
            gauss_proc_vector[i][j]=0;
        }
    }

}

fMathGenerator::~fMathGenerator()
{
    //dtor
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
position2df fMathGenerator::gradien(s32 x, s32 y)
{
    s32 xn=x;
    s32 yn=y;
    xn=xn%128;
    yn=yn%128;
    return static_grad[xn][yn];
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
f32 fMathGenerator::PerlinNoise(f32 x, f32 y,f32 scale)
{
    f32 cx=x/scale;
    f32 cy=y/scale;
    cx=cx+128;
    cy=cy+128;
    s32 ix=(s32)cx;
    s32 iy=(s32)cy;
    s32 ix2=ix+1;
    s32 iy2=iy+1;
    f32 frac_x=cx-ix;
    f32 frac_y=cy-iy;

    core::position2df g00 = gradien(ix,iy);
    core::position2df g10 = gradien(ix2,iy);
    core::position2df g01 = gradien(ix,iy2);
    core::position2df g11 = gradien(ix2,iy2);

    f32 u0=g00.X*(cx-ix)  + g00.Y*(cy-iy);
    f32 u1=g10.X*(cx-ix2) + g10.Y*(cy-iy);
    f32 u2=g01.X*(cx-ix)  + g01.Y*(cy-iy2);
    f32 u3=g11.X*(cx-ix2) + g11.Y*(cy-iy2);

    f32 Sx   = 3*(frac_x*frac_x) - 2*(frac_x*frac_x*frac_x);
    f32 u0_1 = u0 + Sx*(u1-u0);
    f32 u2_3 = u2 + Sx*(u3-u2);

    f32 Sy     = 3*(frac_y*frac_y) - 2*(frac_y*frac_y*frac_y);
    f32 u01_23 = u0_1 + Sy*(u2_3-u0_1);

    return u01_23;
}

//DLA
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fMathGenerator::createDLA(vector2df center,f32 radius)
{

    vector2df x_mark;
    vector2df start_mark;
    start_mark = new_random_point(center,radius-10);

    diffuse_point.push_back(center);

    for(u32 i=0;i<200;i++)
    {
        if((i%100)==0)
        {
            start_mark = new_random_point(center,radius-10);
        }
        x_mark = start_mark;

        while(!hasNeighbour(x_mark))
        {
            x_mark=new_random_point(x_mark,4);
            if(check_distance(x_mark,center)>radius)    //out of bound
            {
                x_mark = start_mark;
            }
        }
//        plotLine(x_mark,the_neighbour);
        diffuse_point.push_back(x_mark);
    }
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool fMathGenerator::hasNeighbour(vector2df test_point)
{
    if(diffuse_point.size()>0)
    {

        for(u32 i=0;i<diffuse_point.size();i++)
        {
            vector2df a;
            a.X=test_point.X-diffuse_point[i].X;
            a.Y=test_point.Y-diffuse_point[i].Y;
            if(a.getLength()<5)
            {
                plotLine(diffuse_point[i].X,diffuse_point[i].Y,
                         test_point.X,test_point.Y);
                return true;
            }
        }
    }
    return false;
}

void fMathGenerator::setPixel(int x, int y)
{
    TextureLayer[LAYER_DLA_1][x][y]=255;
}

void fMathGenerator::plotLine(int x0, int y0, int x1, int y1)
{
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
   int err = dx+dy, e2; /* error value e_xy */
   sx*=1;
   sy*=1;

   for(;;){  /* loop */
      setPixel(x0,y0);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

//gaussian process
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fMathGenerator::gauss_process(u32 radius)
{

    initGaussTable(radius);

    for (u32 j=0;j<168;j++)
    {
        for (u32 i=0;i<168;i++)
        {
            gauss_proc_vector[i][j]=0;
        }
    }

    for(u32 j=20; j<148; j++)
    {
        for(u32 i=20; i<148; i++)
        {
            f32 val=0;
            for(s32 jn = -radius;jn <= radius; jn++)
            {
                for(s32 in = -radius;in <= radius; in++)
                {
                    val += (gauss_srcs_vector[i+in][j+jn] * getGaussTable(in,jn));
                }
            }

            gauss_proc_vector[i][j]=(u8)(val/gaussSum);
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
f32 fMathGenerator::getGaussTable(s32 x, s32 y)
{
    u32 ux=abs(x);
    u32 uy=abs(y);
    return gaussTable[ux][uy];
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fMathGenerator::initGaussTable(u32 radius)
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

void fMathGenerator::resetGauss()
{
    for (u32 j=0;j<256;j++)
    {
        for (u32 i=0;i<256;i++)
        {
            gauss_srcs_vector[i][j]=0;
        }
    }
}

f32 fMathGenerator::scaleImage(f32 x, f32 y,f32 scale)
{

    f32 cx=x/scale;
    f32 cy=y/scale;

    s32 ix=(s32)cx;
    s32 iy=(s32)cy;
    s32 ix2=ix+1;
    s32 iy2=iy+1;
    f32 frac_x=cx-ix;
    f32 frac_y=cy-iy;

    f32 u0=TextureLayer[0] [ix] [iy];
    f32 u1=TextureLayer[0][ix2] [iy];
    f32 u2=TextureLayer[0] [ix][iy2];
    f32 u3=TextureLayer[0][ix2][iy2];

    f32 Sx   = 3*(frac_x*frac_x) - 2*(frac_x*frac_x*frac_x);
    f32 u0_1 = u0 + Sx*(u1-u0);
    f32 u2_3 = u2 + Sx*(u3-u2);

    f32 Sy     = 3*(frac_y*frac_y) - 2*(frac_y*frac_y*frac_y);
    f32 u01_23 = u0_1 + Sy*(u2_3-u0_1);

    return u01_23;
}

/** @ HSV to RGB
  *
  * modified from: http://www.cs.rit.edu/~ncs/color/t_convert.html
  *
  * h:  color degree, 0 to 360 degree
  * s:  color saturation, 0.0 to 1.0
  * v:  color value, 0 to 255
  */
SColor fMathGenerator::HSVtoRGB( float h, float s, float v )
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

#ifndef __NO_POISSON_DISK_SAMPLING__
/** @brief (one liner)
  *
  * (documentation goes here)
  */
f32 fMathGenerator::check_distance(core::vector2df a, core::vector2df b)
{
    core::vector2df result;
    result.X=a.X-b.X;
    result.Y=a.Y-b.Y;
    return result.getLength();
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool fMathGenerator::check_empty_neighbour(core::vector2df a, f32 min_radius)
{
    u16 grid_x=(u16) a.X/POISSON_CELL_SIZE;
    u16 grid_y=(u16) a.Y/POISSON_CELL_SIZE;

    for(s16 j=-min_radius/POISSON_CELL_SIZE;j<=min_radius/POISSON_CELL_SIZE;j++)
    {
        for(s16 i=-min_radius/POISSON_CELL_SIZE;i<=min_radius/POISSON_CELL_SIZE;i++)
        {
            u32 xn=grid_x+i;
            u32 yn=grid_y+j;
            if(grid_x+i<0)      xn=0;
            if(grid_x+i>127)    xn=127;
            if(grid_y+j<0)      yn=0;
            if(grid_y+j>127)    yn=127;

            for(u32 n=0;n<grid_handler[xn][yn].size();n++)
            {
                if(check_distance(a,grid_handler[xn][yn][n])<min_radius)
                {
                        return false;
                }
            }

        }
    }
    return true;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
vector2df fMathGenerator::new_random_point(core::vector2df previous_point, f32 min_radius)
{
    core::vector2df next_point;
    u16 r1 = rand()%10;
    u16 r2 = rand()%360;
    f32 radius = min_radius * (1+r1/10);
    f32 angle = r2*0.0174;// 0.0174= 1/180 derajat
    next_point.X = round(previous_point.X + radius*cos(angle));
    next_point.Y = round(previous_point.Y + radius*sin(angle));
    return next_point;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fMathGenerator::createPoisson(u32 width, u32 height, u32 new_points_count)
{
    process_poisson.push_back(core::vector2d<f32>(15,10));
    sample_poisson.push_back(core::vector2d<f32>(15,10));

    grid_handler[0][0].push_back(core::vector2d<f32>(15,10));

    while(process_poisson.size()>0)
    {
        vector2df point=process_poisson.getLast();
        process_poisson.erase(process_poisson.size()-1);
        for (u32 i=0;i<new_points_count;i++)
        {
            f32 radius = round(-PerlinNoise(point.Y, point.X,50)*10)+5;
            radius*=4;
            if(radius<8) radius=8;
//            radius+=10;
//            radius*=2;
//            printf("radius:%f\n",radius);
//            f32 radius=10;
            vector2df new_point=new_random_point(point,radius);
            if(check_empty_neighbour(new_point,radius)
               && (new_point.X<width)  && (new_point.X>0)
               && (new_point.Y<height) && (new_point.Y>0))
            {
                u32 grid_handler_x=(u32) new_point.X/POISSON_CELL_SIZE;
                u32 grid_handler_y=(u32) new_point.Y/POISSON_CELL_SIZE;

                grid_handler[grid_handler_x][grid_handler_y].push_back(new_point);

                process_poisson.push_back(new_point);
                sample_poisson.push_back(new_point);
            }
        }
    }
}
#endif // __NO_POISSON_DISK_SAMPLING__

