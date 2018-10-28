#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;
namespace Engenie
{

enum CameraType
{
  FPV = 0,
  TPV = 1,
  BV = 2
};

enum CameraDirection
{
  FORWARD = 0,
  BACKWARD = 1,
  RIGHT = 2,
  LEFT = 3,
  UP = 4,
  DOWN = 5
};

class Camera
{
public:
  Camera(){};
  Camera(Json config){

  };

  void setType(CameraType t);
  CameraType getType();
  void setLinearVelocity(float v);
  float getLinearVelocity();
  void setAngularVelocity(float v);
  float getAngularVelocity();
  void setPosition(glm::vec3 posVec);
  glm::vec3 getPosition();
  void setDirection(glm::vec3 directionVec);
  glm::vec3 getDirection();
  void setUpVector(glm::vec3 upVec);
  glm::vec3 getUpVector();
  void calculateLinearDisplacement(float dt);
  void calculateAngularDisplacement();
  void recalculateCameraVectors();
  glm::mat4 generateViewMatrix();

private:
  CameraType type;
  bool initialized;
  bool moveDirections[6];
  GLfloat pitch, yaw, linearVelocity, angularVelocity;
  glm::vec3 position, direction, up, worldUp, right;
};
}; // namespace Engenie
#endif