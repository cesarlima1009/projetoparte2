#ifndef PUTVOXEL_H
#define PUTVOXEL_H
#include "figurageometrica.h"

class PutVoxel : public FiguraGeometrica
{
public:
    PutVoxel(int x, int y, int z, float r, float g, float b, float a);
    void draw(Sculptor &s);
};

#endif // PUTVOXEL_H