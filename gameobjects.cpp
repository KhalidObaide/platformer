#include "lib.h"
#include <string>
#include <unordered_map>

GameObject::GameObject(
  Coordinate new_position, Coordinate new_size, RGBA new_fill
) {
  position = new_position;
  size = new_size;
  fill = new_fill;
}

void GameObject::update(std::unordered_map<std::string, bool>*) {};

bool GameObject::is_colliding(GameObject* target) {
    // Check if the current object is colliding with the target object
    // For simplicity, let's assume collision detection based on bounding boxes
    
    // Calculate the bounding boxes for both objects
    int left1 = position.x;
    int right1 = position.x + size.x;
    int top1 = position.y;
    int bottom1 = position.y + size.y;

    int left2 = target->position.x;
    int right2 = target->position.x + target->size.x;
    int top2 = target->position.y;
    int bottom2 = target->position.y + target->size.y;

    // Check for collision
    return (
      right1 >= left2 
      && left1 <= right2 
      && bottom1 >= top2 
      && top1 <= bottom2
    );
}

GameObject::~GameObject() {}


