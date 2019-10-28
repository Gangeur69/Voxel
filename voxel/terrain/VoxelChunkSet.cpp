#include "VoxelChunkSet.h"

#include "VoxelBlock.h"
#include "VoxelMaterial.h"
#include "../VoxelManager.h"
#include "../VoxelRaycaster.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {


        Vector3 cubeShapePoints[] = {Vector3(0,0,0), Vector3(1,0,0), Vector3(1,0,1), Vector3(0,0,1), Vector3(0,1,0), Vector3(1,1,0), Vector3(1,1,1), Vector3(0,1,1)};
        ConvexShape cubeShape(8, cubeShapePoints);

        VoxelChunkSet::VoxelChunkSet(int width, int height, Vector3i& position) : position(0,0,0)
        {
          this->position = Vector3i(position.getX()/CHUNK_SIZE, position.getY()/CHUNK_SIZE, position.getZ()/CHUNK_SIZE);

          this->width = width;
          this->height = height;
          int arraySize = (2*width + 1)*(2*width + 1)*(2*height + 1);
          chunks = new VoxelChunk*[arraySize];
          for(int i=0;i<arraySize;i++)
          {
            *(chunks + i) = NULL;
          }
        }

        VoxelChunkSet::~VoxelChunkSet()
        {
          int arraySize = (2*width + 1)*(2*width + 1)*(2*height + 1);
          for(int i=0;i<arraySize;i++)
          {
            if(*(chunks + i) != NULL)
            {
              delete *(chunks + i);
            }
          }
          delete [] chunks;
        }

        VoxelChunkSet::VoxelChunkSet(const VoxelChunkSet& chunkSet) : position(chunkSet.position)
        {
          width = chunkSet.width;
          height = chunkSet.height;
          int arraySize = (2*width + 1)*(2*width + 1)*(2*height + 1);
          chunks = new VoxelChunk*[arraySize];
          for(int i=0;i<arraySize;i++)
          {
            *(chunks + i) = new VoxelChunk(**(chunkSet.chunks + i));
          }
        }

        VoxelChunkSet& VoxelChunkSet::operator=(const VoxelChunkSet& chunkSet)
        {
          int arraySize = (2*width + 1)*(2*width + 1)*(2*height + 1);
          for(int i=0;i<arraySize;i++)
          {
            if(*(chunks + i) != NULL)
            {
              delete *(chunks + i);
            }
          }
          delete [] chunks;

          width = chunkSet.width;
          height = chunkSet.height;
          arraySize = (2*width + 1)*(2*width + 1)*(2*height + 1);
          chunks = new VoxelChunk*[arraySize];
          for(int i=0;i<arraySize;i++)
          {
            *(chunks + i) = new VoxelChunk(**(chunkSet.chunks + i));
          }
          return *this;
        }

        int VoxelChunkSet::getIndex(int x, int y, int z) const
        {
          return x + y*(2*width + 1) + (2*height + 1)*(2*width + 1)*z;
        }

        VoxelChunk*& VoxelChunkSet::chunkAt(int x, int y, int z) const
        {
          return *(chunks + getIndex(x, y, z));
        }

        VoxelChunk* VoxelChunkSet::uchunkAt(int x, int y, int z) const
        {
          if(x >= 0 && x <= 2*width)
          {
            if(y >= 0 && y <= 2*height)
            {
              if(z >= 0 && z <= 2*width)
              {
                return chunkAt(x, y, z);
              }
            }
          }
          return NULL;
        }

        Vector3i VoxelChunkSet::getChunkPosition(Vector3i& pos, int x, int y, int z)
        {
          int cx = pos.getX() - width + x;
          int cy = pos.getY() - height + y;
          int cz = pos.getZ() - width + z;
          return Vector3i(cx, cy, cz);
        }

        Vector3i VoxelChunkSet::getSetPosition(Vector3i& pos, int cx, int cy, int cz)
        {
          int x = cx - pos.getX() + width;
          int y = cy - pos.getY() + height;
          int z = cz - pos.getZ() + width;
          return Vector3i(x, y, z);
        }

        int VoxelChunkSet::getWidth() const
        {
          return width;
        }

        int VoxelChunkSet::getHeight() const
        {
          return height;
        }

        bool VoxelChunkSet::isInSet(Vector3i& pos, int cx, int cy, int cz)
        {
          Vector3i sp = getSetPosition(pos, cx, cy, cz);
          if(sp.getX()>=0 && sp.getX()<=2*width)
          {
            if(sp.getY()>=0 && sp.getY()<=2*height)
            {
              if(sp.getZ()>=0 && sp.getZ()<=2*width)
              {
                return true;
              }
            }
          }
          return false;
        }

        VoxelChunk* VoxelChunkSet::getChunk(int cx, int cy, int cz)
        {
          if(!isInSet(position, cx, cy, cz))
          {
            throw("ERROR index out of bounds!");
          }

          Vector3i sp = getSetPosition(position, cx, cy, cz);
          return chunkAt(sp.getX(), sp.getY(), sp.getZ());
        }

        bool VoxelChunkSet::loadNextInColumn(ChunkGenerator& generator, int x, int z)
        {
          for(int y=0;y<=2*height;y++)
          {
            if(chunkAt(x, y, z) == NULL)
            {
              VoxelChunk* chunk = new VoxelChunk();
              Vector3i cp = getChunkPosition(position, x, y, z);
              generator.generate(cp.getX(), cp.getY(), cp.getZ(), *chunk);
              chunkAt(x, y, z) = chunk;
              return true;
            }
          }
          return false;
        }

        void VoxelChunkSet::loadNext(ChunkGenerator& generator)
        {
          int startx = width;
          int endx = width;
          int startz = width;
          int endz = width;

          while(startx >= 0 && endx <= 2*width && startz >=0 && endz <= 2*width)
          {
            //left->right
            for(int i=startx;i<=endx;i++)
            {
              if(loadNextInColumn(generator, i, startz))
              {
                return;
              }
            }
            endx++;

            if(endx <= 2*width)
            {
              //up->down
              for(int i=startz;i<=endz;i++)
              {
                if(loadNextInColumn(generator, endx, i))
                {
                  return;
                }
              }
              endz++;

              if(endz <= 2*width)
              {
                //right -> left
                for(int i=endx;i>=startx;i--)
                {
                  if(loadNextInColumn(generator, i, endz))
                  {
                    return;
                  }
                }
                startx--;

                if(startx >= 0)
                {
                  //down -> up
                  for(int i=endz;i>=startz;i--)
                  {
                    if(loadNextInColumn(generator, startx, i))
                    {
                      return;
                    }
                  }
                  startz--;
                }
              }
            }
          }
        }

        bool VoxelChunkSet::surroundingsLoaded(int x, int y, int z)
        {
          if(y + 1<=2*height)
          {
            if(chunkAt(x, y+1, z) == NULL)
            {
              return false;
            }
          }
          if(y - 1 >= 0)
          {
            if(chunkAt(x, y-1, z) == NULL)
            {
              return false;
            }
          }

          if(x + 1 <= 2*width)
          {
            if(chunkAt(x + 1, y, z) == NULL)
            {
              return false;
            }
          }
          if(x - 1 >= 0)
          {
            if(chunkAt(x - 1, y, z) == NULL)
            {
              return false;
            }
          }

          if(z + 1 <= 2*width)
          {
            if(chunkAt(x, y, z + 1) == NULL)
            {
              return false;
            }
          }
          if(z - 1 >= 0)
          {
            if(chunkAt(x, y, z - 1) == NULL)
            {
              return false;
            }
          }
          return true;
        }

        bool VoxelChunkSet::buildNextMeshInColumn(const VoxelTerrainTexture& terrainTexture, int x, int z)
        {
          for(int y=0;y<=2*height;y++)
          {
            if(chunkAt(x,y,z) != NULL)
            {
              if((!chunkAt(x, y, z)->hasMeshBuilt()) && surroundingsLoaded(x, y, z))
              {
                Vector3i cp = getChunkPosition(position, x, y, z);
                chunkAt(x, y, z)->updateMesh(terrainTexture, cp.getX(), cp.getY(), cp.getZ(), uchunkAt(x, y+1, z), uchunkAt(x, y-1, z), uchunkAt(x, y, z-1), uchunkAt(x-1, y, z), uchunkAt(x+1, y, z), uchunkAt(x, y, z+1));
                return true;
              }
            }
          }
          return false;
        }

        bool VoxelChunkSet::loadNextMeshInColumnToGpu(int x, int z)
        {
          for(int y=0;y<=2*height;y++)
          {
            VoxelChunk* chunk = chunkAt(x, y, z);
            if(chunk != NULL)
            {
              if(chunk->hasMeshBuilt() && !chunk->hasMeshLoaded())
              {
                chunk->loadToGPU();
                return true;
              }
            }
          }
          return false;
        }

        void VoxelChunkSet::buildNextMesh(const VoxelTerrainTexture& terrainTexture)
        {
          int startx = width;
          int endx = width;
          int startz = width;
          int endz = width;
          while(startx >= 0 && endx <= 2*width && startz >=0 && endz <= 2*width)
          {
            //left->right
            for(int i=startx;i<=endx;i++)
            {
              if(buildNextMeshInColumn(terrainTexture, i, startz))
              {
                return;
              }
            }
            endx++;

            if(endx <= 2*width)
            {
              //up->down
              for(int i=startz;i<=endz;i++)
              {
                if(buildNextMeshInColumn(terrainTexture, endx, i))
                {
                  return;
                }
              }
              endz++;

              if(endz <= 2*width)
              {
                //right -> left
                for(int i=endx;i>=startx;i--)
                {
                  if(buildNextMeshInColumn(terrainTexture, i, endz))
                  {
                    return;
                  }
                }
                startx--;

                if(startx >= 0)
                {
                  //down -> up
                  for(int i=endz;i>=startz;i--)
                  {
                    if(buildNextMeshInColumn(terrainTexture, startx, i))
                    {
                      return;
                    }
                  }
                  startz--;
                }
              }
            }
          }
        }

        void VoxelChunkSet::loadNextMeshToGpu()
        {
          int startx = width;
          int endx = width;
          int startz = width;
          int endz = width;
          while(startx >= 0 && endx <= 2*width && startz >=0 && endz <= 2*width)
          {
            //left->right
            for(int i=startx;i<=endx;i++)
            {
              if(loadNextMeshInColumnToGpu(i, startz))
              {
                return;
              }
            }
            endx++;

            if(endx <= 2*width)
            {
              //up->down
              for(int i=startz;i<=endz;i++)
              {
                if(loadNextMeshInColumnToGpu(endx, i))
                {
                  return;
                }
              }
              endz++;

              if(endz <= 2*width)
              {
                //right -> left
                for(int i=endx;i>=startx;i--)
                {
                  if(loadNextMeshInColumnToGpu(i, endz))
                  {
                    return;
                  }
                }
                startx--;

                if(startx >= 0)
                {
                  //down -> up
                  for(int i=endz;i>=startz;i--)
                  {
                    if(loadNextMeshInColumnToGpu(startx, i))
                    {
                      return;
                    }
                  }
                  startz--;
                }
              }
            }
          }
        }

        void VoxelChunkSet::render()
        {
          for(int x=0;x<=2*width;x++)
          {
            for(int y=0;y<=2*height;y++)
            {
              for(int z=0;z<=2*width;z++)
              {
                if(chunkAt(x, y, z) != NULL)
                {
                  VoxelChunk* chunk = chunkAt(x, y, z);
                  chunk->render();
                }
              }
            }
          }
        }

        void VoxelChunkSet::updateChunkPosition(Vector3i& newPosition)
        {
          int arraySize = (2*width + 1)*(2*width + 1)*(2*height + 1);
          VoxelChunk** newChunks = new VoxelChunk*[arraySize];
          for(int x=0;x<=2*width;x++)
          {
            for(int y=0;y<=2*height;y++)
            {
              for(int z=0;z<=2*width;z++)
              {
                Vector3i cp = getChunkPosition(newPosition, x, y, z);
                if(isInSet(position, cp.getX(), cp.getY(), cp.getZ()))
                {
                  Vector3i sp = getSetPosition(position, cp.getX(), cp.getY(), cp.getZ());
                  *(newChunks + getIndex(x, y, z)) = chunkAt(sp.getX(), sp.getY(), sp.getZ());
                  chunkAt(sp.getX(), sp.getY(), sp.getZ()) = NULL;
                }
                else
                {
                  *(newChunks + getIndex(x, y, z)) = NULL;
                }
              }
            }
          }

          for(int i=0;i<arraySize;i++)
          {
            if(*(chunks + i) != NULL)
            {
              delete *(chunks + i);
            }
          }
          delete [] chunks;

          position = newPosition;
          chunks = newChunks;
        }

        void VoxelChunkSet::updatePosition(const Vector3& v)
        {
          int x;
          int y;
          int z;
          floatCoordsToChunkCoords(v.getX(), v.getY(), v.getZ(), &x, &y, &z);
          Vector3i cp(x, y, z);
          updateChunkPosition(cp);
        }

        void VoxelChunkSet::getBlockAndChunk(int x, int y, int z, VoxelBlock** block, VoxelChunk** chunk)
        {
          int cx;
          int cy;
          int cz;
          intCoordsToChunkCoords(x, y, z, &cx, &cy, &cz);

          int lcx;
          int lcy;
          int lcz;
          intCoordsToLocalChunkCoords(x, y, z, &lcx, &lcy, &lcz);

          if(isInSet(position, cx, cy, cz))
          {
            *chunk = getChunk(cx, cy, cz);
            if(*chunk != NULL)
            {
              *block = &(*chunk)->getBlock(lcx, lcy, lcz);
              return;
            }
          }
          *chunk = NULL;
          *block = NULL;
        }

        VoxelBlock* VoxelChunkSet::getBlock(int x, int y, int z)
        {
          VoxelBlock* block;
          VoxelChunk* chunk;
          getBlockAndChunk(x, y, z, &block, &chunk);
          return block;
        }

        VoxelBlock* VoxelChunkSet::getBlock(int max, const Vector3& start, const Vector3& direction)
        {
          VoxelRaycaster raycaster(max, start, direction);
          while(raycaster.isValid())
          {
            VoxelBlock* block = getBlock(raycaster.getX(), raycaster.getY(), raycaster.getZ());
            if(block != NULL)
            {
              if(block->getMaterial().isVisible())
              {
                return block;
              }
            }
            raycaster.next();
          }
          return NULL;
        }

        VoxelBlock* VoxelChunkSet::getBlockBefore(int max, const Vector3& start, const Vector3& direction)
        {
          VoxelRaycaster raycaster(max, start, direction);
          VoxelBlock* block = getBlock(raycaster.getX(), raycaster.getY(), raycaster.getZ());
          while(raycaster.isValid())
          {
            VoxelBlock* nextBlock = getBlock(raycaster.getX(), raycaster.getY(), raycaster.getZ());
            if(nextBlock != NULL)
            {
              if(nextBlock->getMaterial().isVisible())
              {
                return block;
              }
            }
            block = nextBlock;
            raycaster.next();
          }
          return block;
        }

        void VoxelChunkSet::placeBlock(int max, const Vector3& start, const Vector3& direction, VoxelMaterial* material)
        {
          VoxelRaycaster raycaster(max, start, direction);

          VoxelChunk* chunk;
          VoxelBlock* block;
          int x = raycaster.getX();
          int y = raycaster.getY();
          int z = raycaster.getZ();
          getBlockAndChunk(x, y, z, &block, &chunk);
          while(raycaster.isValid())
          {
            VoxelBlock* nextBlock;
            VoxelChunk* nextChunk;
            int nextX = raycaster.getX();
            int nextY = raycaster.getY();
            int nextZ = raycaster.getZ();
            getBlockAndChunk(nextX, nextY, nextZ, &nextBlock, &nextChunk);
            if(nextBlock != NULL)
            {
              if(nextBlock->getMaterial().isVisible())
              {
                if(block != NULL)
                {
                  block->setMaterial(material);
                  reloadChunkAfterModification(x, y, z, chunk);
                  return;
                }
              }
            }
            block = nextBlock;
            chunk = nextChunk;
            x = nextX;
            y = nextY;
            z = nextZ;
            raycaster.next();
          }
        }

        void VoxelChunkSet::breakBlock(int max, const Vector3& start, const Vector3& direction)
        {
          VoxelRaycaster raycaster(max, start, direction);
          while(raycaster.isValid())
          {
            VoxelChunk* chunk;
            VoxelBlock* block;
            int x = raycaster.getX();
            int y = raycaster.getY();
            int z = raycaster.getZ();
            getBlockAndChunk(x, y, z, &block, &chunk);
            if(block != NULL)
            {
              if(block->getMaterial().isVisible())
              {
                block->setMaterial(&MATERIAL_AIR);
                reloadChunkAfterModification(x, y, z, chunk);
                return;
              }
            }
            raycaster.next();
          }
        }

        void VoxelChunkSet::reloadChunkAfterModification(int x, int y, int z, VoxelChunk* chunk)
        {
          chunk->reload();
          int cx;
          int cy;
          int cz;
          intCoordsToChunkCoords(x, y, z, &cx, &cy, &cz);

          int lcx;
          int lcy;
          int lcz;
          intCoordsToLocalChunkCoords(x, y, z, &lcx, &lcy, &lcz);

          if(lcx == 0)
          {
            if(isInSet(position, cx-1, cy, cz))
            {
              getChunk(cx-1, cy, cz)->reload();
            }
          }
          else if(lcx == CHUNK_SIZE-1)
          {
            if(isInSet(position, cx+1, cy, cz))
            {
              getChunk(cx+1, cy, cz)->reload();
            }
          }

          if(lcy == 0)
          {
            if(isInSet(position, cx, cy-1, cz))
            {
              getChunk(cx, cy-1, cz)->reload();
            }
          }
          else if(lcy == CHUNK_SIZE-1)
          {
            if(isInSet(position, cx, cy+1, cz))
            {
              getChunk(cx, cy+1, cz)->reload();
            }
          }

          if(lcz == 0)
          {
            if(isInSet(position, cx, cy, cz-1))
            {
              getChunk(cx, cy, cz-1)->reload();
            }
          }
          else if(lcz == CHUNK_SIZE-1)
          {
            if(isInSet(position, cx, cy, cz+1))
            {
              getChunk(cx, cy, cz+1)->reload();
            }
          }

        }

        void VoxelChunkSet::checkCollisions(float timePassed, Object& object)
        {
          object.getRotation() = Quaternion(object.getRotationSpeedAngle()*timePassed, object.getRotationDirection())*object.getRotation();

          float hp;
          Vector3 normal;
          getCollisionData(object.getSpeed(), timePassed, object, &hp, &normal);

          object.setOnGround(false);

          //std::cout << "Terrain hp: " << hp << std::endl;
          //normal.print();

          if(hp >= timePassed)
          {
            object.getPosition() = object.getPosition() + timePassed*object.getSpeed();
          }
          else
          {
            object.getPosition() = object.getPosition() + hp*object.getSpeed() - 0.002*normal;
            object.getSpeed() = object.getSpeed() - object.getSpeed().dot(normal)*normal;

            if(normal.dot(Vector3(0,-1,0)) >= 0.1)
            {
              object.setOnGround(true);
            }

          }

        }

        void VoxelChunkSet::getCollisionData(const Vector3& direction, float timePassed, Object& object, float* hp, Vector3* normal)
        {
          Matrix4x4 transformation = object.getTransformation();
          Matrix4x4 inverseRotation = object.getInverseRotation();
          float rotationSpeedAngle = object.getRotationSpeedAngle();

          int ox;
          int oy;
          int oz;
          floatCoordsToInt(object.getPosition().getX(), object.getPosition().getY(), object.getPosition().getZ(), &ox, &oy, &oz);

          int radius = (int)(object.getSpeed().getLength()*timePassed + object.getHitbox().getRadius()) + 1;

          *hp = timePassed;
          *normal = Vector3(0,0,0);
          for(int ix=-radius;ix<=radius;ix++)
          {
            for(int iy=-radius;iy<=radius;iy++)
            {
              for(int iz=-radius;iz<=radius;iz++)
              {
                int x = ox + ix;
                int y = oy + iy;
                int z = oz + iz;

                float newHp;
                Vector3 newNormal;
                getCollisionDataAt(direction, timePassed, object, x, y, z, transformation, inverseRotation, rotationSpeedAngle, &newHp, &newNormal);

                if(newHp < *hp)
                {
                  *hp = newHp;
                  *normal = newNormal;
                }
              }
            }
          }
        }

        void VoxelChunkSet::getCollisionDataAt(const Vector3& direction, float timePassed, Object& object, int x, int y, int z, const Matrix4x4& transformation, const Matrix4x4& inverseRotation, float rotationSpeedAngle, float* hp, Vector3* normal)
        {
          int cx;
          int cy;
          int cz;
          intCoordsToChunkCoords(x, y, z, &cx, &cy, &cz);

          int lcx;
          int lcy;
          int lcz;
          intCoordsToLocalChunkCoords(x, y, z, &lcx, &lcy, &lcz);

          *hp = timePassed;

          if(isInSet(position, cx, cy, cz))
          {
            VoxelChunk* chunk = getChunk(cx, cy, cz);
            if(chunk != NULL)
            {
              VoxelBlock& block = chunk->getBlock(lcx, lcy, lcz);
              if(block.getMaterial().isVisible())
              {
                Matrix4x4 ct;
                ct.get(0,3) = x;
                ct.get(1,3) = y;
                ct.get(2,3) = z;

                bool hasCollision;
                float hp2;
                Vector3 normal2;
                object.getHitbox().getHitParameters(-direction, timePassed, object.getTransformation(), object.getInverseRotation(), 60.0, cubeShape, ct, Matrix4x4(), 0.0, &hasCollision, &hp2, &normal2);

                if(hasCollision)
                {
                  *hp = hp2;
                  *normal = normal2;
                }
              }
            }
            else
            {
              *hp = 0.0;
            }
          }
        }


      }
    }
  }
}
