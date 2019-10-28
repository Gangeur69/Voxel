#include "GuiMeshData.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      GuiMeshData::GuiMeshData()
      {
        buildMesh();
      }

      void GuiMeshData::buildMesh()
      {
        float positions[] = {0.0,-1.0, 1.0,-1.0, 1.0,0.0, 0.0, 0.0};

        float uvsCorner00[] = {0.0,1.0, 1.0,1.0, 1.0,0.0, 0.0,0.0};
        float uvsCorner01[] = {0.0,0.0, 0.0,1.0, 1.0,1.0, 1.0,0.0};
        float uvsCorner11[] = {1.0,0.0, 0.0,0.0, 0.0,1.0, 1.0,1.0};
        float uvsCorner10[] = {1.0,1.0, 1.0,0.0, 0.0,0.0, 0.0,1.0};


        unsigned int indices[] = {0,1,2,2,3,0};

        corner00.addVbo(0, 2, positions, 8);
        corner00.addVbo(1, 2, uvsCorner00, 8);
        corner00.addIndices(indices, 6);

        corner01.addVbo(0, 2, positions, 8);
        corner01.addVbo(1, 2, uvsCorner01, 8);
        corner01.addIndices(indices, 6);

        corner11.addVbo(0, 2, positions, 8);
        corner11.addVbo(1, 2, uvsCorner11, 8);
        corner11.addIndices(indices, 6);

        corner10.addVbo(0, 2, positions, 8);
        corner10.addVbo(1, 2, uvsCorner10, 8);
        corner10.addIndices(indices, 6);
      }

      GuiMeshData::GuiMeshData(const GuiMeshData& data)
      {
        buildMesh();
      }

      GuiMeshData& GuiMeshData::operator=(const GuiMeshData& data)
      {
        buildMesh();
        return *this;
      }

      const Mesh& GuiMeshData::getCorner00() const
      {
        return corner00;
      }

      const Mesh& GuiMeshData::getCorner01() const
      {
        return corner01;
      }

      const Mesh& GuiMeshData::getCorner11() const
      {
        return corner11;
      }

      const Mesh& GuiMeshData::getCorner10() const
      {
        return corner10;
      }
    }
  }
}
