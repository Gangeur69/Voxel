#include "ColladaReader.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      ColladaReader::ColladaReader(const char* fileName) : reader(fileName)
      {

      }

      ColladaReader::~ColladaReader()
      {
        delete[] positionsIds;
        delete[] uvsIds;
        delete[] normalsIds;

        delete[] rawPositions;

        delete[] positions;
        delete[] uvs;
        delete[] normals;

        delete[] jointIds;
        delete[] weights;

        delete[] jointNames;
        delete[] jointIdNames;
      }

      void ColladaReader::readMesh()
      {
        const XMLNode& meshNode = reader["COLLADA"]["library_geometries"]["geometry"]["mesh"];
        readTriangles(meshNode);
      }

      void ColladaReader::readTriangles(const XMLNode& meshNode)
      {
        const XMLNode& triangles = meshNode["triangles"];
        int stride = triangles.getNodeAmount("input");

        const XMLNode normalsInput = triangles.getByAttribute("input", "semantic", "NORMAL");
        String normalsSource = normalsInput.getAttribute("source");
        normalsSource.replace("#", "");
        int normalsOffset = normalsInput.getAttribute("offset");

        const XMLNode uvsInput = triangles.getByAttribute("input", "semantic", "TEXCOORD");
        String uvsSource = uvsInput.getAttribute("source");
        uvsSource.replace("#", "");
        int uvsOffset = uvsInput.getAttribute("offset");

        const XMLNode positionsInput = triangles.getByAttribute("input", "semantic", "VERTEX");
        int positionsOffset = positionsInput.getAttribute("offset");
        String positionsSource = meshNode["vertices"]["input"].getAttribute("source");
        positionsSource.replace("#", "");

        LinkedList<int> trianglesIds = toIntList(triangles["p"].getData());
        readIndexLists(stride, positionsOffset, uvsOffset, normalsOffset, trianglesIds);

        readGeometry(meshNode, positionsSource, uvsSource, normalsSource);
      }

      LinkedList<int> ColladaReader::toIntList(const String& string)
      {
        LinkedList<String> data = string.split(" ");
        LinkedList<int> res;
        for(LinkedListIterator<String> itt=data.getIterator();itt.isValid();itt.next())
        {
          int i = itt.getElement();
          res.add(i);
        }
        return res;
      }

      LinkedList<float> ColladaReader::toFloatList(const String& string)
      {
        LinkedList<String> data = string.split(" ");
        LinkedList<float> res;
        for(LinkedListIterator<String> itt=data.getIterator();itt.isValid();itt.next())
        {
          float i = itt.getElement();
          res.add(i);
        }
        return res;
      }

      void ColladaReader::readIndexLists(int stride, int positionsOffset, int uvsOffset, int normalsOffset, const LinkedList<int>& trianglesIds)
      {
        vertexAmount = trianglesIds.size()/stride;
        positionsIds = new int[vertexAmount];
        uvsIds = new int[vertexAmount];
        normalsIds = new int[vertexAmount];

        int i = 0;
        LinkedListIterator<int> itt = trianglesIds.getIterator();
        while(itt.isValid())
        {
          for(int offset = 0;offset<stride;offset++)
          {
            if(positionsOffset == offset)
            {
              *(positionsIds + i) = itt.getElement();
            }
            if(uvsOffset == offset)
            {
              *(uvsIds + i) = itt.getElement();
            }
            if(normalsOffset == offset)
            {
              *(normalsIds + i) = itt.getElement();
            }
            itt.next();
          }
          i++;
        }
      }

      LinkedList<float> ColladaReader::readRawList(const XMLNode& meshNode, const String& source)
      {
        return toFloatList(meshNode.getByAttribute("source", "id", source)["float_array"].getData());
      }

      void ColladaReader::readGeometry(const XMLNode& meshNode, const String& positionsSource, const String& uvsSource, const String& normalsSource)
      {
        LinkedList<float> tempPositions = readRawList(meshNode, positionsSource);
        rawPositionsSize = tempPositions.size();
        rawPositions = new float[rawPositionsSize];
        tempPositions.toArray(rawPositions);

        LinkedList<float> tempUvs = readRawList(meshNode, uvsSource);
        int rawUvsSize = tempUvs.size();
        float* rawUvs = new float[rawUvsSize];
        tempUvs.toArray(rawUvs);

        LinkedList<float> tempNormals = readRawList(meshNode, normalsSource);
        int rawNormalsSize = tempNormals.size();
        float* rawNormals = new float[rawNormalsSize];
        tempNormals.toArray(rawNormals);

        organizeGeometry(rawPositions, rawUvs, rawNormals);

        delete[] rawUvs;
        delete[] rawNormals;
      }

      void ColladaReader::organizeGeometry(float* rawPositions, float* rawUvs, float* rawNormals)
      {
        positions = new float[vertexAmount*3];
        uvs = new float[vertexAmount*2];
        normals = new float[vertexAmount*3];

        for(int i=0;i<vertexAmount;i++)
        {
          int pi = *(positionsIds + i);
          *(positions + 3*i) = *(rawPositions + 3*pi);
          *(positions + 3*i + 1) = *(rawPositions + 3*pi + 1);
          *(positions + 3*i + 2) = *(rawPositions + 3*pi + 2);

          int ui = *(uvsIds + i);
          *(uvs + 2*i) = *(rawUvs + 2*ui);
          *(uvs + 2*i + 1) = 1.0 - *(rawUvs + 2*ui + 1);

          int ni = *(normalsIds + i);
          *(normals + 3*i) = *(rawNormals + 3*ni);
          *(normals + 3*i + 1) = *(rawNormals + 3*ni + 1);
          *(normals + 3*i + 2) = *(rawNormals + 3*ni + 2);
        }
      }

      void ColladaReader::readSkin()
      {
        std::cout << "reading skin1" << std::endl;
        const XMLNode& skinNode = reader["COLLADA"]["library_controllers"]["controller"]["skin"];

        const XMLNode& weightsNode = skinNode["vertex_weights"];
        int stride = weightsNode.getNodeAmount("input");

        const XMLNode& jointNode = weightsNode.getByAttribute("input", "semantic", "JOINT");
        String jointsSource = jointNode.getAttribute("source");
        jointsSource.replace("#","");
        int jointsOffset = jointNode.getAttribute("offset");

        const XMLNode& weightNode = weightsNode.getByAttribute("input", "semantic", "WEIGHT");
        String weightsSource = weightNode.getAttribute("source");
        weightsSource.replace("#","");
        int weightsOffset = weightNode.getAttribute("offset");

        int jwAmountSize;
        int* jwAmount;
        int* jwIndices;
        std::cout << "reading skin2" << std::endl;
        readWeightsIndices(weightsNode, &jwAmountSize, &jwAmount, &jwIndices);
        std::cout << "reading skin3" << std::endl;
        float* rawWeights;
        readRawWeights(skinNode, weightsSource, &rawWeights);
        std::cout << "reading skin4" << std::endl;
        organizeSkin(stride, weightsOffset, jointsOffset, jwAmountSize, jwAmount, jwIndices, rawWeights);
        std::cout << "reading skin5" << std::endl;
        loadJointsList(skinNode, jointsSource);

        delete[] jwAmount;
        delete[] jwIndices;
        delete[] rawWeights;
      }

      void ColladaReader::readWeightsIndices(const XMLNode& weightsNode, int* jwAmountSize, int** jwAmount, int** jwIndices)
      {
        LinkedList<int> tempJwAmount = toIntList(weightsNode["vcount"].getData());
        LinkedList<int> tempJwIndices = toIntList(weightsNode["v"].getData());

        *jwAmountSize = tempJwAmount.size();
        *jwAmount = new int[*jwAmountSize];
        tempJwAmount.toArray(*jwAmount);

        int jwIndicesSize = tempJwIndices.size();
        *jwIndices = new int[jwIndicesSize];
        tempJwIndices.toArray(*jwIndices);
      }

      void ColladaReader::readRawWeights(const XMLNode& skinNode, const String& weightsSource, float** rawWeights)
      {
        LinkedList<float> tempRawWeights = toFloatList(skinNode.getByAttribute("source", "id", weightsSource)["float_array"].getData());
        int rawWeightsSize = tempRawWeights.size();
        *rawWeights = new float[rawWeightsSize];
        tempRawWeights.toArray(*rawWeights);
      }

      void ColladaReader::organizeSkin(int stride, int weightsOffset, int jointsOffset, int jwAmountSize, int* jwAmount, int* jwIndices, float* rawWeights)
      {
        std::cout << "organizeing skin1: " << rawPositionsSize << std::endl;
        int* tempJointIds = new int[rawPositionsSize];
        float* tempWeights = new float[rawPositionsSize];
        std::cout << "organizeing skin2" << std::endl;

        std::cout << "jwAmountSize: " << 3*jwAmountSize << " / " << rawPositionsSize << std::endl;

        int index = 0;
        for(int i=0;i<jwAmountSize;i++)
        {
          int jw = *(jwAmount + i);

          getNextJws(&index, stride, weightsOffset, jointsOffset, jw, jwIndices, rawWeights, tempJointIds, tempWeights, i);
        }
        std::cout << "organizeing skin3: " << vertexAmount << std::endl;


        jointIds = new int[vertexAmount*3];
        std::cout << "organizeing skin3.1" << std::endl;
        weights = new float[vertexAmount*3];
        std::cout << "organizeing skin3.2" << std::endl;
        for(int i=0;i<vertexAmount;i++)
        {
          int positionId = *(positionsIds + i);

          //std::cout << "3*p: " << 3*positionId << " : " << rawPositionsSize << std::endl;
          //std::cout << "3*i: " << 3*i << " : " << vertexAmount*3 << std::endl;

          *(jointIds + 3*i) = *(tempJointIds + 3*positionId);
          *(jointIds + 3*i + 1) = *(tempJointIds + 3*positionId + 1);
          *(jointIds + 3*i + 2) = *(tempJointIds + 3*positionId + 2);

          *(weights + 3*i) = *(tempWeights + 3*positionId);
          *(weights + 3*i + 1) = *(tempWeights + 3*positionId + 1);
          *(weights + 3*i + 2) = *(tempWeights + 3*positionId + 2);
        }

        std::cout << "organizeing skin4" << std::endl;

        delete[] tempJointIds;
        delete[] tempWeights;
        std::cout << "organizeing skin5" << std::endl;
      }

      void ColladaReader::addByOrder(int size, int* jointId, float* weight, int jointIdToAdd, float weightToAdd)
      {
        for(int i=0;i<size;i++)
        {
          if(*(weight + i) < weightToAdd)
          {
            for(int j=size-1;j>i;j--)
            {
              *(jointId + j) = *(jointId + j - 1);
              *(weight + j) = *(weight + j - 1);
            }
            *(jointId + i) = jointIdToAdd;
            *(weight + i) = weightToAdd;
            i = size;
          }
        }
      }

      void ColladaReader::getNextJws(int* index, int stride, int weightsOffset, int jointsOffset, int jw, int* jwIndices, float* rawWeights, int* tempJointIds, float* tempWeights, int vertexIndex)
      {
        int jointId[] = {0,0,0};
        float weight[] = {0.0, 0.0, 0.0};

        for(int i=0;i<jw;i++)
        {
          int jointIdToAdd;
          float weightToAdd;
          getNextJw(index, stride, weightsOffset, jointsOffset, jwIndices, rawWeights, &jointIdToAdd, &weightToAdd);
          addByOrder(3, jointId, weight, jointIdToAdd, weightToAdd);
        }

        float k = 0.0;
        for(int i=0;i<3;i++)
        {
          k+= *(weight + i);
        }

        float p = 1.0/k;
        for(int i=0;i<3;i++)
        {
          //std::cout << "ti: " << 3*vertexIndex + i << " : " << rawPositionsSize << std::endl;
          *(tempJointIds + 3*vertexIndex + i) = *(jointId + i);
          *(tempWeights + 3*vertexIndex + i) = (*(weight + i))*p;
        }
      }

      void ColladaReader::getNextJw(int* index, int stride, int weightsOffset, int jointsOffset, int* jwIndices, float* rawWeights, int* jointId, float* weight)
      {
        for(int i=0;i<stride;i++)
        {
          if(i == jointsOffset)
          {
            *jointId = *(jwIndices + *index);
          }
          if(i == weightsOffset)
          {
            int weightId = *(jwIndices + *index);
            *weight = *(rawWeights + weightId);
          }
          (*index)++;
        }
      }

      void ColladaReader::loadJointsList(const XMLNode& skinNode, const String& jointsSource)
      {
        LinkedList<String> tempJointNames = skinNode.getByAttribute("source", "id", jointsSource)["Name_array"].getData().split(" ");
        jointNamesSize = tempJointNames.size();
        jointNames = new String[jointNamesSize];
        tempJointNames.toArray(jointNames);
      }

      Armature ColladaReader::readArmature()
      {
        jointIdNames = new String[jointNamesSize];
        const XMLNode& rootJointNode = reader["COLLADA"]["library_visual_scenes"]["visual_scene"]["node"]["node"];
        return Armature(jointNamesSize, readJoint(rootJointNode));
      }

      Joint ColladaReader::readJoint(const XMLNode& jointNode)
      {
        String name = jointNode.getAttribute("sid");
        String idName = jointNode.getAttribute("id");
        int id = getJointId(name);
        *(jointIdNames + id) = idName;
        Matrix4x4 m = toMatrix(jointNode["matrix"].getData());
        std::cout << "loading joint: " << id << std::endl;
        name.print();
        std::cout << "{" << std::endl;
        Joint joint(id, name, m);
        LinkedList<const XMLNode*> children = jointNode.getChildren("node");
        for(LinkedListIterator<const XMLNode*> itt=children.getIterator();itt.isValid();itt.next())
        {
          joint.getChildren().add(readJoint(*itt.getElement()));
        }
        std::cout << "}" << std::endl;
        name.print();
        return joint;
      }

      int ColladaReader::getJointId(const String& jointName)
      {
        for(int i=0;i<jointNamesSize;i++)
        {
          if(*(jointNames + i) == jointName)
          {
            return i;
          }
        }
        throw("Error joint name not found!");
        return 0;
      }

      Matrix4x4 ColladaReader::toMatrix(const String& string)
      {
        Matrix4x4 m;
        LinkedList<String> data = string.split(" ");
        LinkedListIterator<String> itt = data.getIterator();
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            m.get(i,j) = itt.getElement();
            itt.next();
          }
        }
        return m;
      }

      Animation ColladaReader::readAnimation()
      {
        const XMLNode& animationNode = reader["COLLADA"]["library_animations"];
        LinkedList<const XMLNode*> jointAnimationNodes = animationNode.getChildren("animation");

        LinkedList<int> ids;
        LinkedList<JointAnimation> jointAnimations;
        for(LinkedListIterator<const XMLNode*> itt=jointAnimationNodes.getIterator();itt.isValid();itt.next())
        {
          int id;
          JointAnimation jointAnimation = readJointAnimation(*itt.getElement(), &id);
          ids.add(id);
          jointAnimations.add(jointAnimation);
        }

        return Animation(ids, jointAnimations);
      }

      JointAnimation ColladaReader::readJointAnimation(const XMLNode& jointAnimationNode, int* id)
      {
        const XMLNode& samplerNode = jointAnimationNode["sampler"];
        String timeStampsSource = samplerNode.getByAttribute("input", "semantic", "INPUT").getAttribute("source");
        timeStampsSource.replace("#","");

        String posesSource = samplerNode.getByAttribute("input", "semantic", "OUTPUT").getAttribute("source");
        posesSource.replace("#","");

        LinkedList<float> timeStamps = toFloatList(jointAnimationNode.getByAttribute("source", "id", timeStampsSource)["float_array"].getData());
        LinkedList<Matrix4x4> poses = toMatrixList(jointAnimationNode.getByAttribute("source", "id", posesSource)["float_array"].getData());

        String name = jointAnimationNode["channel"].getAttribute("target").split("/").get(0);
        name.print();
        *id = getAnimationId(name);
        std::cout << "id: " << *id << std::endl;
        return JointAnimation(timeStamps, poses);
      }

      LinkedList<Matrix4x4> ColladaReader::toMatrixList(const String& string)
      {
        LinkedList<String> data = string.split(" ");
        LinkedListIterator<String> itt = data.getIterator();

        LinkedList<Matrix4x4> matrixList;
        while(itt.isValid())
        {
          matrixList.add(toMatrix(&itt));
        }
        return matrixList;
      }

      Matrix4x4 ColladaReader::toMatrix(LinkedListIterator<String>* itt)
      {
        Matrix4x4 m;
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            m.get(i,j) = itt->getElement();
            itt->next();
          }
        }
        return m;
      }

      int ColladaReader::getAnimationId(const String& name)
      {
        for(int i=0;i<jointNamesSize;i++)
        {
          if(*(jointIdNames + i) == name)
          {
            return i;
          }
        }
        throw("ERROR name not found!");
        return 0;
      }

      void ColladaReader::setJointNames(int jointNamesSize, String* jointNames, String* jointIdNames)
      {
        delete[] this->jointNames;
        delete[] this->jointIdNames;

        this->jointNamesSize = jointNamesSize;
        this->jointNames = new String[jointNamesSize];
        this->jointIdNames = new String[jointNamesSize];

        for(int i=0;i<jointNamesSize;i++)
        {
          *(this->jointNames + i) = *(jointNames + i);
          *(this->jointIdNames + i) = *(jointIdNames + i);
        }
      }

      void ColladaReader::readLink()
      {

      }

      void ColladaReader::loadMesh(Mesh* mesh)
      {
        mesh->addVbo(0, 3, positions, vertexAmount*3);
        mesh->addVbo(1, 2, uvs, vertexAmount*2);
        mesh->addVbo(2, 3, normals, vertexAmount*3);
        mesh->setVertexAmount(vertexAmount);
      }

      void ColladaReader::loadAnimatedMesh(Mesh* mesh)
      {
        loadMesh(mesh);
        mesh->addIVbo(3, 3, jointIds, vertexAmount*3);
        mesh->addVbo(4, 3, weights, vertexAmount*3);
      }

      int ColladaReader::getJointAmount() const
      {
        return jointNamesSize;
      }

      String* ColladaReader::getJointNames() const
      {
        return jointNames;
      }

      String* ColladaReader::getJointIdNames() const
      {
        return jointIdNames;
      }

      ConvexShape ColladaReader::loadConvexShape()
      {
        int convexShapeSize = rawPositionsSize/3;
        Vector3* v3positions = new Vector3[convexShapeSize];
        for(int i=0;i<convexShapeSize;i++)
        {
          float x = *(rawPositions + 3*i);
          float y = *(rawPositions + 3*i + 1);
          float z = *(rawPositions + 3*i + 2);
          *(v3positions + i) = Vector3(x, y, z);
        }
        ConvexShape shape(convexShapeSize, v3positions);
        delete[] v3positions;
        return shape;
      }
    }
  }
}
