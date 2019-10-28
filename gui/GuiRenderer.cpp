#include "GuiRenderer.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      GuiRenderer::GuiRenderer(Shader* guiShader, Shader* textShader, GuiMeshData* mesh, PanelTexture* panelTexture)
      {
        this->guiShader = guiShader;
        this->textShader = textShader;
        this->mesh = mesh;
        this->panelTexture = panelTexture;
      }

      GuiRenderer::GuiRenderer(const GuiRenderer& renderer)
      {
        guiShader = renderer.guiShader;
        textShader = renderer.textShader;
        mesh = renderer.mesh;
        panelTexture = renderer.panelTexture;
      }

      GuiRenderer& GuiRenderer::operator=(const GuiRenderer& renderer)
      {
        guiShader = renderer.guiShader;
        textShader = renderer.textShader;
        mesh = renderer.mesh;
        panelTexture = renderer.panelTexture;
        return *this;
      }

      void GuiRenderer::drawQuad(const Mesh* quadMesh, const Texture* texture, float x, float y, float sizex, float sizey) const
      {
        guiShader->loadVariable(0, x, y);
        guiShader->loadVariable(1, sizex*SCREEN_RATIO, sizey);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glBindVertexArray(quadMesh->getVao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, quadMesh->getIndicesAmount(), GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
      }

      void GuiRenderer::renderIcon(Mesh* mesh, Texture* texture, float x, float y, float sizex, float sizey, const Vector3& color) const
      {
        guiShader->bind();
        guiShader->loadVariable(2, color);
        drawQuad(mesh, texture, x*SCREEN_RATIO, y, sizex, sizey);
      }

      void GuiRenderer::renderQuad(Texture* texture, float x, float y, float sizex, float sizey, const Vector3& color) const
      {
        guiShader->bind();
        guiShader->loadVariable(2, color);
        drawQuad(&mesh->getCorner00(), texture, x*SCREEN_RATIO, y, sizex, sizey);
      }

      void GuiRenderer::renderText(float x, float y, const Text& text) const
      {
        textShader->bind();
        textShader->loadVariable(0, x*SCREEN_RATIO, y);
        textShader->loadVariable(1, text.getSize()*SCREEN_RATIO, text.getSize());
        textShader->loadVariable(2, text.color);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, text.getFont()->getAtlas()->getId());
        glBindVertexArray(text.getMesh().getVao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, text.getMesh().getIndicesAmount(), GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
      }

      void GuiRenderer::renderText(float x, float y, const DynamicText& dynamicText) const
      {
        Text* text = dynamicText.getText();
        if(text != NULL)
        {
          renderText(x, y, *text);
        }
      }

      void GuiRenderer::renderPanel(float frameBorderWidth, float x, float y, float sizex, float sizey, const Vector3& color) const
      {
        sizex = sizex - 2.0*frameBorderWidth;
        sizey = sizey - 2.0*frameBorderWidth;
        if(sizex < 0.0)
        {
          sizex = 0.0;
        }
        if(sizey < 0.0)
        {
          sizey = 0.0;
        }
        guiShader->bind();
        guiShader->loadVariable(2,color);
        drawQuad(&mesh->getCorner00(), panelTexture->getCorner(), x*SCREEN_RATIO, y, frameBorderWidth, frameBorderWidth);
        drawQuad(&mesh->getCorner01(), panelTexture->getCorner(), x*SCREEN_RATIO, y + frameBorderWidth + sizey, frameBorderWidth, frameBorderWidth);
        drawQuad(&mesh->getCorner11(), panelTexture->getCorner(), (x + frameBorderWidth + sizex)*SCREEN_RATIO, y + frameBorderWidth + sizey, frameBorderWidth, frameBorderWidth);
        drawQuad(&mesh->getCorner10(), panelTexture->getCorner(), (x + frameBorderWidth + sizex)*SCREEN_RATIO, y, frameBorderWidth, frameBorderWidth);

        drawQuad(&mesh->getCorner00(), panelTexture->getBackground(), (x + frameBorderWidth)*SCREEN_RATIO, y + frameBorderWidth, sizex, sizey);

        drawQuad(&mesh->getCorner00(), panelTexture->getBorder(), (x + frameBorderWidth)*SCREEN_RATIO, y, sizex, frameBorderWidth);
        drawQuad(&mesh->getCorner01(), panelTexture->getBorder(), x*SCREEN_RATIO, y + frameBorderWidth, frameBorderWidth, sizey);
        drawQuad(&mesh->getCorner11(), panelTexture->getBorder(), (x + frameBorderWidth)*SCREEN_RATIO, y + frameBorderWidth + sizey, sizex, frameBorderWidth);
        drawQuad(&mesh->getCorner10(), panelTexture->getBorder(), (x + frameBorderWidth + sizex)*SCREEN_RATIO, y + frameBorderWidth, frameBorderWidth, sizey);
      }
    }
  }
}
