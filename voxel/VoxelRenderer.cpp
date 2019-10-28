#include "VoxelRenderer.h"

#include "terrain/ChunkGenerator.h"
#include "../graphics/GeometryLoader.h"
#include "../math/Vector3i.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      VoxelRenderer::VoxelRenderer(const Matrix4x4& projection) : shader("shaders/VoxelShader")
      {
        shader.bind();
        shader.registerVariable("projection");
        shader.registerVariable("camera");
        shader.registerVariable("sunDirection");
        shader.registerVariable("sunColor");
        shader.loadVariable(0, projection);
        Vector3 sunDirection(2.0, -3.0, 1.0);
        sunDirection.normalize();
        shader.loadVariable(2, sunDirection);
        shader.loadVariable(3, Vector3(1.0,1.0,1.0));

        GLuint texture = loadTexture("resources/terrain.png");
        terrainTexture = new VoxelTerrainTexture(3, 3, texture);
        Vector3i pos(0,63,15);
        chunkSet = new VoxelChunkSet(6,3, pos);
      }

      VoxelRenderer::~VoxelRenderer()
      {
        delete terrainTexture;
        delete chunkSet;
      }

      void VoxelRenderer::checkCollisions(float timePassed, Object& object)
      {
        chunkSet->checkCollisions(timePassed, object);
      }

      void VoxelRenderer::render(Camera& camera, std::mutex& m)
      {
        m.lock();
        chunkSet->loadNextMeshToGpu();
        chunkSet->updatePosition(camera.getPosition());
        shader.bind();
        shader.loadVariable(1, camera.getTransformation());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, terrainTexture->getTexture());

        chunkSet->render();
        m.unlock();
      }

      void VoxelRenderer::loadNext(std::mutex& m)
      {
        m.lock();
        chunkSet->loadNext(generator);
        chunkSet->buildNextMesh(*terrainTexture);
        m.unlock();
      }

      VoxelBlock* VoxelRenderer::getBlock(int max, const Vector3& start, const Vector3& direction)
      {
        return chunkSet->getBlock(max, start, direction);
      }

      void VoxelRenderer::breakBlock(int max, const Vector3& start, const Vector3& direction)
      {
        chunkSet->breakBlock(max, start, direction);
      }

      void VoxelRenderer::placeBlock(int max, const Vector3& start, const Vector3& direction, VoxelMaterial* material)
      {
        chunkSet->placeBlock(max, start, direction, material);
      }
    }
  }
}
