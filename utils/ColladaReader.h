#ifndef COLLADAREADER_H
#define COLLADAREADER_H

#include "String.h"
#include "XMLReader.h"
#include "XMLNode.h"
#include "LinkedList.h"

#include "../graphics/Mesh.h"
#include "../graphics/animation/Joint.h"
#include "../graphics/animation/Armature.h"
#include "../graphics/animation/JointAnimation.h"
#include "../graphics/animation/Animation.h"

#include "../math/Matrix4x4.h"
#include "../math/geometry/ConvexShape.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::graphics::animation;
using namespace gt::doubovik::math;
using namespace gt::doubovik::math::geometry;

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class ColladaReader
      {
      private:
        XMLReader reader;

        int vertexAmount;
        int* positionsIds = NULL;
        int* normalsIds = NULL;
        int* uvsIds = NULL;

        int rawPositionsSize;
        float* rawPositions = NULL;

        float* positions = NULL;
        float* uvs = NULL;
        float* normals = NULL;

        int* jointIds = NULL;
        float* weights = NULL;

        int jointNamesSize;
        String* jointNames = NULL;
        String* jointIdNames = NULL;

        //mesh
        void readTriangles(const XMLNode&);
        void readIndexLists(int, int, int, int, const LinkedList<int>&);
        LinkedList<int> toIntList(const String&);
        LinkedList<float> toFloatList(const String&);
        LinkedList<float> readRawList(const XMLNode&, const String&);
        void readGeometry(const XMLNode&, const String&, const String&, const String&);
        void organizeGeometry(float*, float*, float*);

        //skin
        void readWeightsIndices(const XMLNode&, int*, int**, int**);
        void readRawWeights(const XMLNode&, const String&, float**);
        void organizeSkin(int, int, int, int, int*, int*, float*);
        void getNextJws(int*, int, int, int, int, int*, float*, int*, float*, int);
        void getNextJw(int*, int, int, int, int*, float*, int*, float*);
        void addByOrder(int, int*, float*, int, float);
        void loadJointsList(const XMLNode&, const String&);

        //Armature
        Joint readJoint(const XMLNode&);
        int getJointId(const String&);
        Matrix4x4 toMatrix(const String&);

        //Animation
        JointAnimation readJointAnimation(const XMLNode&, int*);
        Matrix4x4 toMatrix(LinkedListIterator<String>*);
        LinkedList<Matrix4x4> toMatrixList(const String&);
        int getAnimationId(const String&);
      public:
        ColladaReader(const char*);
        ~ColladaReader();

        void readMesh();
        void loadMesh(Mesh*);
        void loadAnimatedMesh(Mesh*);

        void readSkin();
        void setJointNames(int, String*, String*);

        Armature readArmature();

        Animation readAnimation();

        void readLink();

        ConvexShape loadConvexShape();

        int getJointAmount() const;
        String* getJointNames() const;
        String* getJointIdNames() const;
      };
    }
  }
}

#endif
