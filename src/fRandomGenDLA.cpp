#include "fRandomGenDLA.h"

fRandomGenDLA::fRandomGenDLA()
{
    for(u32 j=0;j<_IMAGE_DLA_SIZE_;j++)
    {
        for(u32 i=0;i<_IMAGE_DLA_SIZE_;i++)
        {
            img_dla[i][j]=0;
        }
    }
}

fRandomGenDLA::~fRandomGenDLA()
{
    //dtor
}


//DLA
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fRandomGenDLA::dlaCreateDLA(u32 x,u32 y,f32 radius)
{
    dlaResetDLA();
    vector2df center(x,y);
    vector2df x_mark;

    diffuse_point.push_back(center);

    for(u32 i=0;i<32;i++)
    {
        u16 r2 = rand() % 8;
        f32 angle = 0.0175*r2*45;// 0.0055= 1/180 derajat
        x_mark.X = center.X+round(50*cos(angle));
        x_mark.Y = center.Y+round(50*sin(angle));

        while(!dlaHasNeighbour(x_mark))
        {
            r2 = rand() % 16;
            angle = 0.0175*r2*22.5;
            x_mark.X = x_mark.X+round(5*cos(angle));
            x_mark.Y = x_mark.Y+round(5*sin(angle));

            while(dlaIsOutOfPosition(x_mark,center,100))
            {
                r2 = rand() % 8;
                angle = 0.0175*r2*45;// 0.0055= 1/180 derajat
                x_mark.X = center.X+round(50*cos(angle));
                x_mark.Y = center.Y+round(50*sin(angle));
            }
        }
//        plotLine(x_mark,the_neighbour);
        diffuse_point.push_back(x_mark);
    }

//    for(u32 i=0;i<32;i++)
//    {
//        u32 n=diffuse_point[i].X;
//        u32 m=diffuse_point[i].Y;
//        TextureLayer[LAYER_DLA][n][m]=0xff;
//    }

}

void fRandomGenDLA::dlaResetDLA()
{
    diffuse_point.clear();
}

bool fRandomGenDLA::dlaIsOutOfPosition(vector2df test_point,vector2df center,f32 radius)
{
    if(test_point.X<0||test_point.X>_IMAGE_DLA_SIZE_)
    {
        return true;
    }

    if(test_point.Y<0||test_point.Y>_IMAGE_DLA_SIZE_)
    {
        return true;
    }

    vector2df a;
    a.X=test_point.X-center.X;
    a.Y=test_point.Y-center.Y;

    if(a.getLength()<radius)
    {
        return false;
    }else
    {
        return true;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool fRandomGenDLA::dlaHasNeighbour(vector2df test_point)
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

void fRandomGenDLA::setPixel(s32 x, s32 y)
{
    img_dla[x][y]=1.0;
}

void fRandomGenDLA::plotLine(int x0, int y0, int x1, int y1)
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

f32 fRandomGenDLA::getImage(u32 x,u32 y)
{
    x=x%_IMAGE_DLA_SIZE_;
    y=y%_IMAGE_DLA_SIZE_;
    return img_dla[x][y];
}
