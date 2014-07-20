#ifndef FMATHGENERATOR_H
#define FMATHGENERATOR_H

#define MAPSCALE   32
#define MAPSCALE2   8
#define C_CHUNKSIZE 64
#define POISSON_CELL_SIZE   8

#include <irrlicht.h>
using namespace irr;
using namespace core;
class fMathGenerator
{
    public:
        fMathGenerator();
        virtual ~fMathGenerator();
        position2df gradien(s32 x,s32 y);
        f32 PerlinNoise(f32 x,f32 y,f32 scale);

        f32 check_distance(core::vector2df a, core::vector2df b);
        bool check_empty_neighbour(core::vector2df a,f32 min_radius);
        core::vector2df new_random_point(core::vector2df previous_point,f32 min_radius);
        void createPoisson(u32 width, u32 height, u32 new_points_count);

        core::array<vector2df> sample_poisson;

    protected:
    private:
        position2df static_grad[128][128];
        core::array<vector2df> process_poisson;
        core::array<vector2df> grid_handler[128][128];

};

#endif // FMATHGENERATOR_H
