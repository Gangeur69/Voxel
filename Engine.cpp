#include <iostream>
#include <GL/glew.h>
#include <chrono>
#include <thread>
#include <mutex>

#include <math.h>

#include "graphics/Mesh.h"
#include "graphics/Display.h"
#include "graphics/GeometryLoader.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "graphics/animation/AnimatedModel.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/Joint.h"
#include "graphics/animation/Armature.h"
#include "graphics/Texture.h"

#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/Matrix3x3.h"

#include "voxel/VoxelRenderer.h"

#include "utils/ArrayList.h"

#include "physics/Object.h"


#include "gui/Panel.h"
#include "gui/GuiMeshData.h"

#include "gui/text/FontReader.h"
#include "gui/text/Font.h"
#include "gui/text/CharData.h"
#include "gui/text/TextBuilder.h"
#include "gui/text/Text.h"
#include "gui/PanelTexture.h"
#include "gui/GuiRenderer.h"
#include "gui/Gui.h"
#include "gui/InventoryPanel.h"
#include "gui/ItemSelectionWheel.h"

#include "gui/components/GuiTextButton.h"
#include "gui/components/GuiIconButton.h"
#include "gui/components/GuiItemSlot.h"
#include "gui/components/GuiItemHolder.h"

#include "items/Item.h"
#include "items/ItemStack.h"
#include "items/Inventory.h"

#include "utils/ColladaReader.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::graphics::animation;
using namespace gt::doubovik::math;
using namespace gt::doubovik::math::geometry;
using namespace gt::doubovik::utils;
using namespace gt::doubovik::voxel;
using namespace gt::doubovik::voxel::terrain;
using namespace gt::doubovik::physics;
using namespace gt::doubovik::gui;
using namespace gt::doubovik::gui::text;
using namespace gt::doubovik::gui::components;
using namespace gt::doubovik::items;

std::mutex m;

void generateChunks(VoxelRenderer& renderer)
{
  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  float GENERATE_TIME = 10000000.0;
  while(!DISPLAY_WINDOW_CLOSED)
  {
    start = std::chrono::system_clock::now();

    renderer.loadNext(m);

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int timePassedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    int toWait = GENERATE_TIME - timePassedNs;
    std::this_thread::sleep_for(std::chrono::nanoseconds(toWait));
  }
}

void runEngine()
{
  std::cout << "Engine started" << std::endl;

  ColladaReader reader("resources/fpsArms.dae");
  reader.readMesh();
  reader.readSkin();
  Armature armature = reader.readArmature();
  Animation animation = reader.readAnimation();

  ColladaReader miningAnimationReader("resources/mineing.dae");
  miningAnimationReader.setJointNames(reader.getJointAmount(), reader.getJointNames(), reader.getJointIdNames());
  Animation miningAnimation = miningAnimationReader.readAnimation();
  miningAnimation.setToBeReplayed(false);

  ColladaReader holdBlockAnimationReader("resources/animation_hold_block.dae");
  holdBlockAnimationReader.setJointNames(reader.getJointAmount(), reader.getJointNames(), reader.getJointIdNames());
  Animation holdBlockAnimation = holdBlockAnimationReader.readAnimation();

  ColladaReader placeBlockAnimationReader("resources/animation_place_block.dae");
  placeBlockAnimationReader.setJointNames(reader.getJointAmount(), reader.getJointNames(), reader.getJointIdNames());
  Animation placeBlockAnimation = placeBlockAnimationReader.readAnimation();

  ColladaReader gunHoldAnimationReader("resources/animation_gun_hold.dae");
  gunHoldAnimationReader.setJointNames(reader.getJointAmount(), reader.getJointNames(), reader.getJointIdNames());
  Animation gunHoldAnimation = gunHoldAnimationReader.readAnimation();

  ColladaReader gunShootAnimationReader("resources/animation_gun_shoot.dae");
  gunShootAnimationReader.setJointNames(reader.getJointAmount(), reader.getJointNames(), reader.getJointIdNames());
  Animation gunShootAnimation = gunShootAnimationReader.readAnimation();

  ColladaReader pickaxeReader("resources/pick_stone2.dae");
  pickaxeReader.readMesh();

  ColladaReader blockReader("resources/block.dae");
  blockReader.readMesh();

  ColladaReader pistolReader("resources/1911.dae");
  pistolReader.readMesh();
  pistolReader.readSkin();
  Armature pistolArmature = pistolReader.readArmature();
  Animation defaultPistolAnimation = pistolReader.readAnimation();

  ColladaReader pistolShootAnimationReader("resources/1911_shoot_animation.dae");
  pistolShootAnimationReader.setJointNames(pistolReader.getJointAmount(), pistolReader.getJointNames(), pistolReader.getJointIdNames());
  Animation pistolShootAnimation = pistolShootAnimationReader.readAnimation();
  pistolShootAnimation.setToBeReplayed(false);

  ColladaReader playerHitboxReader("resources/player_hitbox2.dae");
  playerHitboxReader.readMesh();
  ConvexShape playerHitbox = playerHitboxReader.loadConvexShape();

  initDisplay("Mine Fabrik by Ivan D. & Max S.", 1280, 720);
  //1280 720

  Shader shader("shaders/AnimationShader");
  shader.registerVariable("projection");
  shader.registerVariable("camera");
  shader.registerVariable("transformation");
  shader.registerVariable("sunDirection");
  shader.registerVariable("sunColor");
  shader.registerArray("joints", 100);

  Shader objectShader("shaders/BasicShader");
  objectShader.registerVariable("projection");
  objectShader.registerVariable("camera");
  objectShader.registerVariable("transformation");
  objectShader.registerVariable("sunDirection");
  objectShader.registerVariable("sunColor");


  Matrix4x4 projection(1280, 720, 90, 90, 0.2, 5000);
  projection.print();
  shader.bind();
  shader.loadVariable(0, projection);
  objectShader.bind();
  objectShader.loadVariable(0, projection);
  /*int posAmount = 12;
  float positions[] = {-1,-1,0, 1,-1,0, 1,1,0, -1,1,0};
  float texutres[] = {-1,-1, 1,-1, 1,1, -1,1};
  int indAmount = 6;loadToGPU(positions, posAmount, texutres, 8, indices, indAmount);
  unsigned int indices[] = {0,1,2, 0,2,3};
  */

  //= loadToGPU(reader.getMeshPositions(), reader.getMeshDataAmount()*3, reader.getMeshTexCoords(), reader.getMeshDataAmount()*2, reader.getMeshIndices(), reader.getMeshSize());


  //TESTS START


  //Vector3 cubePoints[] = {Vector3(-1,-1,-1), Vector3(1,-1,-1), Vector3(1,-1,1), Vector3(-1,-1,1), Vector3(-1,1,-1), Vector3(1,1,-1),Vector3(1,1,1),Vector3(-1,1,1)};
  //ConvexShape cubeShape(8, cubePoints);
  /*
  MeshData pmeshData = playerHitboxReader.readMesh();
  Mesh pmesh;
  pmesh.addVbo(0, 3, pmeshData.getPositions(), pmeshData.getVertexAmount()*3);
  pmesh.addVbo(1, 2, pmeshData.getTextureCoords(), pmeshData.getVertexAmount()*2);
  pmesh.addVbo(2, 3, pmeshData.getNormals(), pmeshData.getVertexAmount()*3);
  pmesh.addIndices(pmeshData.getIndices(), pmeshData.getIndicesAmount());
  */

  float angle = 0;

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  float FPS_TIME = 2500000.0;

  Camera camera(Vector3(0,63,15));
  float speed = 6.0;
  float rotSpeed = 60.0;

  //test
  std::cout << "debug 1" << std::endl;
  VoxelRenderer voxelRenderer(projection);
  std::cout << "debug 2" << std::endl;

  std::thread generation(generateChunks, std::ref(voxelRenderer));

  Shader guiShader("shaders/GuiShader");
  guiShader.registerVariable("location");
  guiShader.registerVariable("size");
  guiShader.registerVariable("color");
  guiShader.loadVariable(2, Vector3(1.0,1.0,1.0));

  Shader textShader("shaders/TextShader");
  textShader.registerVariable("location");
  textShader.registerVariable("size");
  textShader.registerVariable("color");

  Texture guiCoreTexture(loadTexture("resources/gui/core.png"));
  Texture guiBorderTexture(loadTexture("resources/gui/border.png"));
  Texture guiCornerTexture(loadTexture("resources/gui/corner.png"));

  GuiMeshData guiMeshData;
  PanelTexture panelTexture(&guiCoreTexture, &guiBorderTexture, &guiCornerTexture);
  GuiRenderer guiRenderer(&guiShader, &textShader, &guiMeshData, &panelTexture);

  FontReader fontReader("resources/gui/fonts/calibri.fnt");
  Texture textAtlas(loadFontAtlas("resources/gui/fonts/calibri.png"));
  Font calibri(fontReader.getLineHeight(), fontReader.getAmount(), fontReader.getCharDatas(), &textAtlas);
  Text text("Joli text XDDD lol.txt \nIvan D.\n est un BG. \n2+2 = 2*2 = 4", &calibri, 1.7, 1.0, true);
  text.color = Vector3(0.0, 0.0, 0.0);
  Text text2("sample text pi\nHAHAha HA XD", &calibri, 1.7, 0.3, true);
  text2.color = Vector3(1.0, 0.0, 0.0);

  GLuint tttexture = loadTexture("resources/terrain.png");
  VoxelTerrainTexture terrainTexture(3, 3, tttexture);

  float itemPos[] = {0.0,-1.0, 1.0,-1.0, 1.0,0.0, 0.0,0.0};
  LinkedList<float> itemLUvs;
  terrainTexture.getTextureCoords(1, itemLUvs);
  float itemUvs[8];
  itemLUvs.toArray(itemUvs);
  unsigned int itemIndices[] = {0,1,2,2,3,0};
  Mesh itemMesh;
  itemMesh.addVbo(0,2,itemPos,8);
  itemMesh.addVbo(1,2,itemUvs,8);
  itemMesh.addIndices(itemIndices,6);
  Texture itemTexture(loadTexture("resources/terrain.png"));
  Item grass(&itemMesh, &itemTexture, String("Grass"));
  ItemStack itemStack;
  itemStack.amount = 235;
  itemStack.item = &grass;

  float quadPos[] = {0.0,-1.0, 1.0,-1.0, 1.0,0.0, 0.0,0.0};
  float quadUvs[] = {0.0,1.0, 1.0,1.0, 1.0,0.0, 0.0,0.0};
  unsigned int quadIndices[] = {0,1,2,2,3,0};
  Mesh quadMesh;
  quadMesh.addVbo(0, 2, quadPos, 8);
  quadMesh.addVbo(1, 2, quadUvs, 8);
  quadMesh.addIndices(quadIndices, 6);
  Texture iconPickStone(loadTexture("resources/icon_pick_stone.png"));
  Item itemStonePick(&quadMesh, &iconPickStone, String("Stone Pickaxe"));
  ItemStack pickStoneStack;
  pickStoneStack.amount = 1;
  pickStoneStack.item = &itemStonePick;

  Texture iconPistol(loadTexture("resources/1911icon.png"));
  Item itemPistol(&quadMesh, &iconPistol, String("1911"));
  ItemStack pistolStack;
  pistolStack.amount = 1;
  pistolStack.item = &itemPistol;

  ItemStack holderStack;
  GuiItemHolder itemHolder(&holderStack, &calibri);
  Gui gui;
  Panel panel;
  panel.x = -1.7;
  panel.y = -0.9;
  panel.width = 0.2 + 2.0*0.06;
  panel.height = 1.6 + 2.0*0.06;

  GuiTextButton button1("boutton", &calibri, 0.3, true, 0.16 + 2.0*0.06, 2.0*0.06);
  button1.x = 0.02;
  button1.y = 0.02;
  panel.addComponent(&button1);

  Texture inventoryIcon(loadTexture("resources/gui/inventory_icon.png"));


  Text invName("Inventory", &calibri, 1.7, 0.6, true);

  Inventory inventory(9,3);
  inventory.setItemStack(0, itemStack);
  inventory.setItemStack(10, pickStoneStack);
  inventory.setItemStack(14, itemStack);
  inventory.setItemStack(16, pistolStack);
  InventoryPanel inventoryPanel(&itemHolder, &inventory, &calibri);

  GuiIconButton inventoryButton(&inventoryIcon, &inventoryPanel.isVisible, 0.28, 0.28);
  inventoryButton.x = 0.02;
  inventoryButton.y = panel.height - inventoryButton.height - 0.02;
  panel.addComponent(&inventoryButton);

  Texture itemWheelTexture(loadTexture("resources/gui/item_wheel.png"));
  ItemSelectionWheel itemWheel(9, &itemWheelTexture, &inventory, &calibri);

  gui.addComponent(&itemWheel);
  gui.addComponent(&panel);
  gui.addComponent(&inventoryPanel);
  gui.addComponent(&itemHolder);

  Texture animationTexture(loadTexture("resources/texture_arms.png"));
  Mesh animatedMesh;
  reader.loadAnimatedMesh(&animatedMesh);

  Texture pistolTexture(loadTexture("resources/pistol.png"));
  AnimatedModel animatedModel(&animatedMesh, &animationTexture, armature, &animation);
  Joint* hand = animatedModel.getArmature().getJoint(26);

  Mesh pistolMesh;
  pistolReader.loadAnimatedMesh(&pistolMesh);
  AnimatedModel pistol(&pistolMesh, &animationTexture, pistolArmature, &defaultPistolAnimation);

  Mesh dab;
  pickaxeReader.loadMesh(&dab);
  Texture texturePickStone(loadTexture("resources/texture_pick_stone.png"));

  Mesh block;
  blockReader.loadMesh(&block);

  Object player(&playerHitbox, Vector3(0 ,63, 20));


  Vector3 gravity(0,-9.81,0);

  float fpsSecondCount = 0;
  int fps = 0;

  bool hasMined = false;
  float mineStamp = 0.8333333;

  Vector3 sunDirection(2.0,-3.0,1.0);
  sunDirection.normalize();


  while(!DISPLAY_WINDOW_CLOSED)
  {
    //cubeShape.getDistance(cube1.getTransformation(), cubeShape, cube2.getTransformation());
    //cubeShape.getHitParameters(Vector3(-1,0,0), 4, cube2.getTransformation(), cubeShape, cube1.getTransformation());

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int timePassedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    float timePassed = ((float)timePassedNs)/(1000000000.0);
    start = now;

    fps++;
    fpsSecondCount+=timePassed;
    if(fpsSecondCount >= 1.0)
    {
      std::cout << "FPS: " << fps << std::endl;
      fps = 0;
      fpsSecondCount = 0.0;
    }
    /*
    cube1.getRotation().getX()+=10*timePassed;
    cube1.getRotation().getY()+=60*timePassed;
    cube2.getRotation().getY()+=35*timePassed;
    cube2.getRotation().getZ()+=73*timePassed;
    */

    float mx = 2.0*(float)(MOUSE_X - 1280/2)/720.0;
    float my = 2.0*(float)(MOUSE_Y - 720/2)/720.0;
    gui.updateMouseData(isToggledMouseButton(SDL_BUTTON_LEFT), mx, my);

    angle+=10*timePassed;
    Quaternion cameraRotation(camera.getRotation().getY(), Vector3(0,1,0));

    Vector3 playerSpeed;
    if(isPressed(SDLK_z))
    {
      playerSpeed.getZ() = -1;
    }
    if(isPressed(SDLK_s))
    {
      playerSpeed.getZ() = 1;
    }
    if(isPressed(SDLK_SPACE) && player.isOnGround())
    {
      player.getSpeed().getY() += 6.0;
    }


    playerSpeed = cameraRotation.rotate(playerSpeed);
    playerSpeed.setLength(speed);
    player.getSpeed().getX() = playerSpeed.getX();
    player.getSpeed().getZ() = playerSpeed.getZ();


    /*
    if(isToggledKey(SDLK_e))
    {

      if(&animatedModel.getAnimator().getAnimation() != &miningAnimation)
      {
        animatedModel.setAnimation(&miningAnimation);
        hasMined = false;
      }
    }
    */

    if(isToggledKey(SDLK_v))
    {
      grabMouse();
    }
    if(MOUSE_WHEEL_Y > 0)
    {
      itemWheel.previous();
    }
    else if(MOUSE_WHEEL_Y < 0)
    {
      itemWheel.next();
    }

    /*
    if(&animatedModel.getAnimator().getAnimation() == &miningAnimation)
    {
      if(animatedModel.getAnimator().getCurrentTime() >= mineStamp && !hasMined)
      {
        m.lock();
        //VoxelBlock* block = voxelRenderer.getBlock(30, camera.getPosition(), camera.getDirection());
        voxelRenderer.breakBlock(10, camera.getPosition(), camera.getDirection());
        m.unlock();
        hasMined = true;
      }
    }
    */

    //start animations test
    //******************************************************************************************//
    if(itemWheel.getSelectedItem()->getItem() == &grass)
    {
      if(isToggledKey(SDLK_e))
      {
        if(&animatedModel.getAnimator().getAnimation() != &placeBlockAnimation)
        {
          animatedModel.setAnimation(&placeBlockAnimation);
          m.lock();
          voxelRenderer.placeBlock(10, camera.getPosition(), camera.getDirection(), &MATERIAL_GRASS);
          m.unlock();
        }
      }
      if(&animatedModel.getAnimator().getAnimation() != &holdBlockAnimation)
      {
        if(&animatedModel.getAnimator().getAnimation() == &placeBlockAnimation)
        {
          if(animatedModel.getAnimator().animationHasLooped())
          {
            animatedModel.setAnimation(&holdBlockAnimation);
          }
        }
        else
        {
          animatedModel.setAnimation(&holdBlockAnimation);
        }
      }
    }
    else if(itemWheel.getSelectedItem()->getItem() == &itemStonePick)
    {
      if(isToggledKey(SDLK_e))
      {
        if(&animatedModel.getAnimator().getAnimation() != &miningAnimation)
        {
          animatedModel.setAnimation(&miningAnimation);
          hasMined = false;
        }
      }
      if(&animatedModel.getAnimator().getAnimation() != &animation)
      {
        if(&animatedModel.getAnimator().getAnimation() == &miningAnimation)
        {
          if(animatedModel.getAnimator().animationHasLooped())
          {
            animatedModel.setAnimation(&animation);
          }
        }
        else
        {
          animatedModel.setAnimation(&animation);
        }
      }
    }
    else if(itemWheel.getSelectedItem()->getItem() == &itemPistol)
    {
      if(isToggledKey(SDLK_e))
      {
        if(&animatedModel.getAnimator().getAnimation() != &gunShootAnimation)
        {
          animatedModel.setAnimation(&gunShootAnimation);
          pistol.setAnimation(&pistolShootAnimation);
        }
      }
      if(&animatedModel.getAnimator().getAnimation() != &gunHoldAnimation)
      {
        if(&animatedModel.getAnimator().getAnimation() == &gunShootAnimation)
        {
          if(animatedModel.getAnimator().animationHasLooped())
          {
            animatedModel.setAnimation(&gunHoldAnimation);
          }
        }
        else
        {
          animatedModel.setAnimation(&gunHoldAnimation);
        }
      }
    }

    if(&animatedModel.getAnimator().getAnimation() == &miningAnimation)
    {
      if(animatedModel.getAnimator().getCurrentTime() >= mineStamp && !hasMined)
      {
        m.lock();
        //VoxelBlock* block = voxelRenderer.getBlock(30, camera.getPosition(), camera.getDirection());
        voxelRenderer.breakBlock(10, camera.getPosition(), camera.getDirection());
        m.unlock();
        hasMined = true;
      }
    }

    if(pistol.getAnimator().animationHasLooped())
    {
      if(!pistol.getAnimator().getAnimation().toBeReplayed())
      {
        pistol.setAnimation(&defaultPistolAnimation);
      }
    }
    //******************************************************************************************//

    player.getRotationSpeed() = Vector3(0,-MOUSE_MOVE_X*rotSpeed,0);
    camera.getRotation().getX()+= -MOUSE_MOVE_Y*rotSpeed*timePassed;

    //player.getRotation() = Quaternion(player.getRotationSpeedAngle()*timePassed, player.getRotationDirection())*player.getRotation();
    //player.getPosition() = player.getPosition() + player.getSpeed()*timePassed;

    voxelRenderer.checkCollisions(timePassed, player);
    if(!player.isOnGround())
    {
      player.getSpeed() = player.getSpeed() + timePassed*gravity;
    }

    player.getRotation() = Quaternion(player.getRotationSpeedAngle()*timePassed, player.getRotationDirection())*player.getRotation();

    //cubeShape.getDistance(player.getTransformation(), player.getInverseRotation(), cubeShape, cube1.getTransformation(), cube1.getInverseRotation());
    //cube2.getRotation() = Quaternion(cube2.getRotationSpeedAngle()*lambda, cube2.getRotationDirection())*cube2.getRotation();

    //cubeShape.getDistance(cube1.getTransformation(), cube1.getInverseRotation(), cubeShape, cube2.getTransformation(), cube2.getInverseRotation());


    Vector3 front = player.getDirection(Vector3(0,0,-1));
    float angleY = acos(-front.getZ())*(180.0/M_PI);
    if(front.getX() > 0)
    {
      angleY=-angleY;
    }

    camera.getPosition() = player.getPosition() + Vector3(0,1.81,0);
    camera.getRotation().getY() = angleY;


    animatedModel.update(timePassed);
    pistol.update(timePassed);


    clearDisplay(0,0.8,0.9,0);



    voxelRenderer.render(camera, m);


    //0,63,15


    Matrix4x4 playerTransformation = player.getTransformation();
    Matrix4x4 cameraR = Quaternion(camera.getRotation().getX(), Vector3(1.0,0.0,0.0)).toMatrix4x4();
    shader.bind();
    shader.loadVariable(1, camera.getTransformation());
    shader.loadVariable(2, playerTransformation);
    shader.loadVariable(3, sunDirection);
    shader.loadVariable(4, Vector3(1.0, 1.0, 1.0));

    Matrix4x4 jointsM[100];
    animatedModel.getMatrixArray(jointsM);
    shader.loadArray(5, jointsM, 100);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, animationTexture.getId());
    glBindVertexArray(animatedMesh.getVao());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glDrawArrays(GL_TRIANGLES, 0, animatedMesh.getVertexAmount());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glBindVertexArray(0);

    Matrix4x4 transformation;
    transformation.get(0,3) = 0.0;
    transformation.get(1,3) = 63.0;
    transformation.get(2,3) = 5.0;

    Quaternion rot(0, Vector3(1,0,0));
    //        0 0 0 1
    Matrix4x4 tempt;
    tempt.get(0,0) = 0.9997856;
    tempt.get(0,1) = 0.01990014;
    tempt.get(0,2) = -0.005379135;
    tempt.get(0,3) = 0.01254673;

    tempt.get(1,0) = -0.01984426;
    tempt.get(1,1) = 0.9997537;
    tempt.get(1,2) = 0.009981459;
    tempt.get(1,3) = -0.02532283;

    tempt.get(2,0) = 0.005578736;
    tempt.get(2,1) = -0.00987116;
    tempt.get(2,2) = 0.9999374;
    tempt.get(2,3) = 0.003811532;

    tempt.get(3,0) = 0.0;
    tempt.get(3,1) = 0.0;
    tempt.get(3,2) = 0.0;
    tempt.get(3,3) = 1.0;

    objectShader.bind();
    objectShader.loadVariable(3, sunDirection);
    objectShader.loadVariable(4, Vector3(1.0, 1.0, 1.0));

    //DrawItem TESTS
    //*******************************************************
    if(itemWheel.getSelectedItem()->getItem() == &itemStonePick)
    {
      objectShader.loadVariable(1, camera.getTransformation());
      objectShader.loadVariable(2, playerTransformation*hand->getTransformation());

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texturePickStone.getId());
      glBindVertexArray(dab.getVao());
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);

      glDrawArrays(GL_TRIANGLES, 0, dab.getVertexAmount());

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
      glBindVertexArray(0);
    }
    else if(itemWheel.getSelectedItem()->getItem() == &grass)
    {
      Matrix4x4 mot;
      mot.get(0,0) = 0.067;
      mot.get(0,3) = 0.03515671;

      mot.get(1,1) = 0.067;
      mot.get(1,3) = 0.1260156;

      mot.get(2,2) = 0.067;
      mot.get(2,3) = 0.1259697;
      mot.get(3,3) = 1.0;

      objectShader.loadVariable(1, camera.getTransformation());
      objectShader.loadVariable(2, playerTransformation*hand->getTransformation()*hand->getDefaultTransformation()*mot);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, tttexture);
      glBindVertexArray(block.getVao());
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);

      glDrawArrays(GL_TRIANGLES, 0, block.getVertexAmount());

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
      glBindVertexArray(0);
    }
    else if(itemWheel.getSelectedItem()->getItem() == &itemPistol)
    {
      Matrix4x4 pmot;
      pmot.setDiag(1.0);
      pmot.get(0,3) = -0.0130522;
      pmot.get(1,3) = 0.2183124;
      pmot.get(2,3) = 0.03267321;

      pmot = pmot*Quaternion(0.010549, -0.692375, -0.009098, -0.721403).toMatrix4x4();

      shader.bind();
      shader.loadVariable(1, camera.getTransformation());
      shader.loadVariable(2, playerTransformation*hand->getTransformation()*hand->getDefaultTransformation()*pmot);
      shader.loadVariable(3, sunDirection);
      shader.loadVariable(4, Vector3(1.0, 1.0, 1.0));

      Matrix4x4 pistolJointsM[100];
      pistol.getMatrixArray(pistolJointsM);
      shader.loadArray(5, pistolJointsM, 100);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, pistolTexture.getId());
      glBindVertexArray(pistolMesh.getVao());
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glEnableVertexAttribArray(3);
      glEnableVertexAttribArray(4);

      glDrawArrays(GL_TRIANGLES, 0, pistolMesh.getVertexAmount());

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
      glDisableVertexAttribArray(3);
      glDisableVertexAttribArray(4);
      glBindVertexArray(0);
    }
    //*******************************************************
    gui.update(timePassed);
    gui.render(&guiRenderer);

    updateDisplay();
    //0,0.8,0.9,0

    now = std::chrono::system_clock::now();
    timePassedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    int toWait = FPS_TIME - timePassedNs;
    std::this_thread::sleep_for(std::chrono::nanoseconds(toWait));
  }
  generation.join();
  cleanDisplay();

  std::cout << "Engine ended" << std::endl;
}

void barycenterTest(const Vector3& OA, const Vector3& OB, const Vector3& OC, const Vector3& OD, float* u, float* v, float* w, float* k)
{
  Vector3 AB = OB - OA;
  Vector3 AC = OC - OA;
  Vector3 AD = OD - OA;
  Vector3 AO = -OA;

  float ABAB = AB.dot(AB);
  float ACAC = AC.dot(AC);
  float ADAD = AD.dot(AD);

  float ABAC = AB.dot(AC);
  float ABAD = AB.dot(AD);

  float ACAD = AC.dot(AD);

  float AOAB = AO.dot(AB);
  float AOAC = AO.dot(AC);
  float AOAD = AO.dot(AD);

  float detA  = - ABAB*(ACAC*ADAD - ACAD*ACAD)
                + ABAC*(ABAC*ADAD - ACAD*ABAD)
                - ABAD*(ABAC*ACAD - ACAC*ABAD);

  float detAv = - AOAB*(ACAC*ADAD - ACAD*ACAD)
                + AOAC*(ABAC*ADAD - ACAD*ABAD)
                - AOAD*(ABAC*ACAD - ACAC*ABAD);

  float detAw = - ABAB*(AOAC*ADAD - AOAD*ACAD)
                + ABAC*(AOAB*ADAD - AOAD*ABAD)
                - ABAD*(AOAB*ACAD - AOAC*ABAD);

  float detAk = - ABAB*(ACAC*AOAD - ACAD*AOAC)
                + ABAC*(ABAC*AOAD - ACAD*AOAB)
                - ABAD*(ABAC*AOAC - ACAC*AOAB);

  float denom = 1.0/detA;

  *v = detAv*denom;
  *w = detAw*denom;
  *k = detAk*denom;
  *u = 1.0 - *v - *w - *k;
}

int main()
{
  runEngine();

  Vector3 OA(-1,-3,-1);
  Vector3 OB(1,-1,-1);
  Vector3 OC(0,-6,1);
  Vector3 OD(0.5,45,0);
  float u;
  float v;
  float w;
  float k;
  barycenterTest(OA, OB, OC, OD, &u, &v, &w, &k);
  std::cout << "u : v : w : k " << u << " : " << v << " : " << w << " : " << k << std::endl;
  std::cout << "sum: " << u + v + w + k << std::endl;
  (u*OA + v*OB + w*OC + k*OD).print();

  return 0;
}
