#ifndef FMATHGENERATOR_H
#define FMATHGENERATOR_H

#include <irrlicht.h>
#include <math.h>

#define POISSON_CELL_SIZE   8
#define __NO_POISSON_DISK_SAMPLING__

using namespace irr;
using namespace irr::core;
class fMathGenerator
{
    public:
        fMathGenerator();
        virtual ~fMathGenerator();
        position2df gradien(s32 x,s32 y);
        f32 PerlinNoise(f32 x,f32 y,f32 scale);

    //DLA function
        bool hasNeighbour(vector2df test_point);
        void createDLA(vector2df center,f32 radius);
    //gaussian process
        void gauss_process(u8 radius);
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

        //DLA
        array<vector2df> diffuse_point;
        //gaussian process
        u8 gauss_srcs_vector[256][256];
        u8 gauss_proc_vector[256][256];
//    #ifndef __NO_POISSON_DISK_SAMPLING__
        array<vector2df> process_poisson;
        array<vector2df> grid_handler[128][128];
//    #endif // __NO_POISSON_DISK_SAMPLING__

};

#endif // FMATHGENERATOR_H
