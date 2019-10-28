#include "Item.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      Item::Item(Mesh* mesh, Texture* texture, const String& name)
      {
        this->mesh = mesh;
        this->texture = texture;
        this->name = name;
      }

      Item::Item(const Item& item)
      {
        mesh = item.mesh;
        texture = item.texture;
        name = item.name;
      }

      Item& Item::operator=(const Item& item)
      {
        mesh = item.mesh;
        texture = item.texture;
        name = item.name;
        return *this;
      }

      Mesh* Item::getMesh() const
      {
        return mesh;
      }

      Texture* Item::getTexture() const
      {
        return texture;
      }

      const String& Item::getName() const
      {
        return name;
      }
    }
  }
}
