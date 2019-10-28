#include "VoxelPlanet.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {

        VoxelPlanet::VoxelPlanet()
        {
          for(int x=-5;x<=5;x++)
          {
            for(int z=-5;z<=5;z++)
            {
              for(int y=0;y<=4;y++)
              {
                setChunk(x, y, z, VoxelChunk());
              }
            }
          }
        }

        int VoxelPlanet::getListIndex(int i)
        {
          if(i >= 0)
          {
            return 2*i;
          }
          else
          {
            return -2*i + 1;
          }
        }

        VoxelChunk& VoxelPlanet::getChunk(int x, int y, int z)
        {
          int ix = getListIndex(x);
          int iy = getListIndex(y);
          int iz = getListIndex(z);
          return chunks[ix][iy][iz];
        }

        void VoxelPlanet::setChunk(int x, int y, int z, const VoxelChunk& chunk)
        {
          int ix = getListIndex(x);
          int iy = getListIndex(y);
          int iz = getListIndex(z);

          initializeListTo(ix, iy, iz);
          chunks[ix][iy][iz] = chunk;
        }

        void VoxelPlanet::initializeListTo(int i, int j, int k)
        {
          while(chunks.size() <= i)
          {
            chunks.add(ArrayList<ArrayList<VoxelChunk>>());
          }

          while(chunks[i].size() <= j)
          {
            chunks[i].add(ArrayList<VoxelChunk>());
          }

          while(chunks[i][j].size() <= k)
          {
            chunks[i][j].add(VoxelChunk());
          }
        }
      }
    }
  }
}
