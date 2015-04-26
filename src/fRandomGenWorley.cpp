#include "fRandomGenWorley.h"

fRandomGenWorley::fRandomGenWorley()
{
    //ctor
}

fRandomGenWorley::~fRandomGenWorley()
{
    //dtor
}


//Worley function
void fRandomGenWorley::worleyInitWorleyLayer()
{
    core::vector2df next_point;
    u32 highest=0;

    for(u32 n=0;n<3;n++)
    {
        next_point.X = rand() % 32;
        next_point.Y = rand() % 128;
        worley_point.push_back(next_point);
    }

    for(u32 n=0;n<3;n++)
    {
        next_point.X = 96+(rand() % 32);
        next_point.Y = rand() % 128;
        worley_point.push_back(next_point);
    }

    for(u32 n=0;n<2;n++)
    {
        next_point.X = 32+(rand() % 64);
        next_point.Y = rand() % 128;
        worley_point.push_back(next_point);
    }

    for(u32 j=0;j<_IMG_WORLEY_SIZE_;j++)
    {
        for(u32 i=0;i<_IMG_WORLEY_SIZE_;i++)
        {
            img_worley[i][j]=worleyGetDistance(i,j);
            if(img_worley[i][j]>highest)
                highest=img_worley[i][j];
        }
    }

    for(u32 j=0;j<_IMG_WORLEY_SIZE_;j++)
    {
        for(u32 i=0;i<_IMG_WORLEY_SIZE_;i++)
        {
            img_worley[i][j]=img_worley[i][j]/highest;
        }
    }

}

f32  fRandomGenWorley::worleyGetDistance(f32 x,f32 y)
{
    vector2df a;
    vector2df point(x,y);
    f32 distance=1284;
    for(u32 i=0;i<worley_point.size();i++)
    {
        a.X=point.X-worley_point[i].X;
        a.Y=point.Y-worley_point[i].Y;
        if(a.getLength()<distance)
        {
            distance=a.getLength();
        }
    }
    return distance;
}

f32 fRandomGenWorley::worleyGetValue(u32 x,u32 y)
{
    x=x%_IMG_WORLEY_SIZE_;
    y=y%_IMG_WORLEY_SIZE_;
    return img_worley[x][y];
}
