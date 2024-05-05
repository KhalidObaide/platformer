#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "lib.h"

Player::Player(
  Coordinate new_position, std::vector<GameObject*> new_platforms
) : GameObject(
  new_position, {20, 50}, {0, 0, 255, 255}
), ground_detector({0, 0}, {0, 0}, {0, 0, 0, 0}){
  gravity = 10; 
  speed = 5;
  velocity = {0, 0};
  platforms = new_platforms;

  is_jumping = false;
  jump_time = 10;
  jump_counter = 0;
  jump_delay = 300;
  last_jump = current_epoch();

  ground_detector = GameObject(
    {0, 0}, {size.x, 2}, {0, 0, 0, 0}
  );

}

void Player::update(std::unordered_map<std::string, int>* events) {
  int current = current_epoch();

  bool on_platform = false;
  if (!is_jumping) {
    for (int i=0; i<static_cast<int>(platforms.size()); i++) {
      on_platform = ground_detector.is_colliding(platforms[i]);
      if(on_platform) {
        position.y = platforms[i]->position.y - size.y;
        break;
      }
    }
    velocity.y = on_platform ? 0 : gravity;
  } else {
    jump_counter++;
    if (jump_counter >= jump_time) {
      jump_counter = 0;
      is_jumping = false;
      last_jump = current;
    }
    velocity.y = -10;
  }

  if (
    (*events)["HOLD_KEY_UP"] 
    && !is_jumping 
    && on_platform
    && current - last_jump > jump_delay
  ) {
    is_jumping = true;
  }

  velocity.x = 0;
  velocity.x = (*events)["HOLD_KEY_RIGHT"] ? speed : velocity.x;
  velocity.x = (*events)["HOLD_KEY_LEFT"] ? -speed : velocity.x;

  position.x += velocity.x;
  position.y += velocity.y;
  ground_detector.position.x = position.x;
  ground_detector.position.y = position.y+size.y;
}
