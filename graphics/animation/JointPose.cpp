#include "JointPose.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        JointPose::JointPose()
        {

        }

        JointPose::JointPose(const Vector3& position, const Vector3& scale, const Quaternion& rotation)
        {
          this->position = position;
          this->scale = scale;
          this->rotation = rotation;
        }

        JointPose::JointPose(const Matrix4x4& matrix)
        {
          Matrix4x4 m = matrix;
          position = Vector3(m.get(0,3), m.get(1,3), m.get(2,3));
          scale = m.getScale();
          m.unScale();
          rotation = Quaternion(m);
        }

        JointPose::JointPose(const JointPose& pose)
        {
          position = pose.position;
          scale = pose.scale;
          rotation = pose.rotation;
        }

        JointPose& JointPose::operator=(const JointPose& pose)
        {
          position = pose.position;
          scale = pose.scale;
          rotation = pose.rotation;
          return *this;
        }

        Matrix4x4 JointPose::getTransformation() const
        {
          Matrix4x4 scalem;
          scalem.get(0,0) = scale.getX();
          scalem.get(1,1) = scale.getY();
          scalem.get(2,2) = scale.getZ();
          Matrix4x4 transformation = rotation.toMatrix4x4()*scalem;
          transformation.get(0,3) = position.getX();
          transformation.get(1,3) = position.getY();
          transformation.get(2,3) = position.getZ();
          return transformation;
        }

        JointPose JointPose::interpolate(float t, const JointPose& pose) const
        {
          Vector3 tposition = position + t*(pose.position - position);
          Vector3 tscale = scale + t*(pose.scale - scale);
          Quaternion troation = rotation.slerp(t, pose.rotation);
          return JointPose(tposition, tscale, troation);
        }
      }
    }
  }
}
