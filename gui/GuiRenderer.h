#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "GuiMeshData.h"
#include "PanelTexture.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/Mesh.h"
#include "../math/Vector3.h"
#include "text/Text.h"
#include "text/DynamicText.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::math;
using namespace gt::doubovik::gui::text;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class GuiRenderer
      {
      private:
        Shader* guiShader;
        Shader* textShader;
        GuiMeshData* mesh;
        PanelTexture* panelTexture;

        void drawQuad(const Mesh*, const Texture*, float, float, float, float) const;

      public:
        float SCREEN_RATIO = 9.0/16.0;

        GuiRenderer(Shader*, Shader*, GuiMeshData*, PanelTexture*);
        GuiRenderer(const GuiRenderer&);
        GuiRenderer& operator=(const GuiRenderer&);

        void renderIcon(Mesh*, Texture*, float, float, float, float, const Vector3&) const;
        void renderQuad(Texture*, float, float, float, float, const Vector3&) const;
        void renderText(float, float, const Text&) const;
        void renderText(float, float, const DynamicText&) const;
        void renderPanel(float, float, float, float, float, const Vector3&) const;
      };
    }
  }
}

#endif
