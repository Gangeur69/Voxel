#ifndef GUIMESHDATA_H
#define GUIMESHDATA_H

#include "../graphics/Mesh.h"

using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class GuiMeshData
      {
      private:
        Mesh corner00; //quad
        Mesh corner01;
        Mesh corner11;
        Mesh corner10;

        void buildMesh();

      public:
        GuiMeshData();
        GuiMeshData(const GuiMeshData&);
        GuiMeshData& operator=(const GuiMeshData&);

        const Mesh& getCorner00() const;
        const Mesh& getCorner01() const;
        const Mesh& getCorner11() const;
        const Mesh& getCorner10() const;
      };
    }
  }
}

#endif
