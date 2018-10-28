#include "camera.hpp"

namespace Engenie
{
CameraType Camera::getType()
{
    return type;
}

void Camera::setType(CameraType cType)
{
    type = cType;
}

float Camera::getLinearVelocity()
{
    return linearVelocity;
}

void Camera::setLinearVelocity(float newVelocity)
{
    linearVelocity = newVelocity;
}

float Camera::getAngularVelocity()
{
    return angularVelocity;
}

void Camera::setAngularVelocity(float newVelocity)
{
    angularVelocity = newVelocity;
}

glm::vec3 Camera::getPosition()
{
    return position;
}

void Camera::setPosition(glm::vec3 pos)
{
    position = pos;
}

glm::vec3 Camera::getDirection()
{
    return direction;
}

void Camera::setDirection(glm::vec3 dir)
{
    direction = dir;
}

glm::vec3 Camera::getUpVector()
{
    return up;
}

void Camera::setUpVector(glm::vec3 upVec)
{
    up = upVec;
}

glm::mat4 Camera::generateViewMatrix()
{
    return glm::mat4(1.0f);
}

void Camera::calculateLinearDisplacement(float dt)
{
    if (moveDirections[CameraDirection::FORWARD])
    {
        position += (direction * linearVelocity * dt);
    }
    else if (moveDirections[CameraDirection::BACKWARD])
    {
        position -= (direction * linearVelocity * dt);
    }

    if (moveDirections[CameraDirection::LEFT])
    {
        position -= (right * linearVelocity * dt);
    }
    else if (moveDirections[CameraDirection::RIGHT])
    {
        position += (right * linearVelocity * dt);
    }
}

void Camera::calculateAngularDisplacement()
{
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

}; // namespace Engenie