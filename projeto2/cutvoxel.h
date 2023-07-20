#ifndef CUTVOXEL_H
#define CUTVOXEL_H
#include "figurageometrica.h"

class cutVoxel : public FiguraGeometrica
{
public:
    cutVoxel(int x, int y, int z);
    void draw(Sculptor &s);
};

#endif // CUTVOXEL_H