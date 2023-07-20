#include "sculptor.h"
#include "voxel.h"
#include <fstream>
#include <iostream>

Sculptor::Sculptor(int nx, int ny, int nz)
{
    if (nx <= 0 || ny <= 0 || nz <= 0)
    {
        throw "Dimensoes invalidas para matriz do escultor";
    }
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
    v = new Voxel **[nx];
    v[0] = new Voxel *[nx * ny];
    v[0][0] = new Voxel[nx * ny * nz];
    for (int i = 1; i < nx; i++)
    {
        v[i] = v[i - 1] + ny;
    }
    for (int i = 1; i < nx * ny; i++)
    {
        v[0][i] = v[0][i - 1] + nz;
    }
    for (int i = 0; i < nx * ny * nz; i++)
    {
        v[0][0][i].isOn = false;
    }
}

Sculptor::~Sculptor()
{
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}


void Sculptor::putVoxel(int x, int y, int z)
{
    if ((0 <= x < nx) && (0 <= y < ny) && (0 <= z < nz))
    {
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
        v[x][y][z].isOn = true;
    }
    else
    {
        std::cout << "Erro em putVoxel\n";
    }
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    if ((0 <= x < nx) && (0 <= y < ny) && (0 <= z < nz))
    {
        v[x][y][z].isOn = false;
    }
    else
    {
         std::cout << "Erro em cutVoxel\n";
    }
}


void Sculptor::writeOFF(const char *filename)
{
    std::ofstream fout;
    int nVoxel = 0, ref = 0;
    fout.open(filename);

    if (fout.is_open())
    {
        std::cout << "Gravando arquivo...\n";
    }
    else
    {
        std::cout << "Erro na abertura do arquivo\n";
        std::cin.get();
        exit(1);
    }

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    nVoxel++;
                }
            }
        }
    }

    fout << "OFF" << std::endl;
    fout << nVoxel * 8 << " " << nVoxel * 6 << " " << 0 << std::endl;

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    fout << 4 << " " << ref + 0 << " " << ref + 3 << " " << ref + 2 << " " << ref + 1 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 4 << " " << ref + 5 << " " << ref + 6 << " " << ref + 7 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 0 << " " << ref + 1 << " " << ref + 5 << " " << ref + 4 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 0 << " " << ref + 4 << " " << ref + 7 << " " << ref + 3 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 3 << " " << ref + 7 << " " << ref + 6 << " " << ref + 2 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 1 << " " << ref + 2 << " " << ref + 6 << " " << ref + 5 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    ref += 8;
                }
            }
        }
    }

    if (fout.is_open())
    {
        std::cout << "Arquivo gerado com sucesso!\n";
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}