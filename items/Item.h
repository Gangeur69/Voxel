#ifndef ITEM_H
#define ITEM_H

#include "../graphics/Mesh.h"
#include "../graphics/Texture.h"
#include "../utils/String.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::utils;

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class Item
      {
      private:
        Mesh* mesh;
        Texture* texture;
        String name;

      public:
        Item(Mesh*, Texture*, const String&);
        Item(const Item&);
        Item& operator=(const Item&);

        Mesh* getMesh() const;
        Texture* getTexture() const;
        const String& getName() const;
      };
    }
  }
}

#endif
