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
//
//    for (u32 j=0;j<128;j++)
//    {
//        for (u32 i=0;i<128;i++)
//        {
//            img_gradframe[i][j]=1.0;
//            if(i<16)    img_gradframe[i][j]=img_gradframe[i][j]*((f32)i)/16;
//            if(i>112)   img_gradframe[i][j]=img_gradframe[i][j]*((f32)128-i)/16;
//            if(j<16)    img_gradframe[i][j]=img_gradframe[i][j]*(f32)j/16;
//            if(j>112)   img_gradframe[i][j]=img_gradframe[i][j]*((f32)128-j)/16;
////            img_gradframe[i][j]=1-cos((f32)j/32);
////            if(i<16)    img_gradframe[i][j]=img_gradframe[i][j]*((f32)i)/16;
////            if(i>112)   img_gradframe[i][j]=img_gradframe[i][j]*((f32)128-i)/16;
//
//        }
//    }

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

f32 fMathGenerator::GradientFrame(u32 x,u32 y)
{
    x=x%128;
    y=y%128;

    f32 g=1.0;

    if(x<16)    g=g*((f32)x)/16;
    if(x>112)   g=g*((f32)128-x)/16;
    if(y<16)    g=g*(f32)y/16;
    if(y>112)   g=g*((f32)128-y)/16;

    return g;
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

    f32 u0=v_img [ix] [iy];
    f32 u1=v_img[ix2] [iy];
    f32 u2=v_img [ix][iy2];
    f32 u3=v_img[ix2][iy2];

    f32 Sx   = 3*(frac_x*frac_x) - 2*(frac_x*frac_x*frac_x);
    f32 u0_1 = u0 + Sx*(u1-u0);
    f32 u2_3 = u2 + Sx*(u3-u2);

    f32 Sy     = 3*(frac_y*frac_y) - 2*(frac_y*frac_y*frac_y);
    f32 u01_23 = u0_1 + Sy*(u2_3-u0_1);

    return u01_23;
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

