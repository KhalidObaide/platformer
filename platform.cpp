#include <unordered_map>
#include <string>
#include "lib.h"

Platform::Platform(
  Coordinate new_position, Coordinate new_size, bool new_is_draggable
) : GameObject(
  new_position, new_size, {0, 200, 0, 255}
) { 
  is_draggable = new_is_draggable;
}

void Platform::update(std::unordered_map<std::string, int> *events) {
  if (!is_draggable) return;
  if ((*events)["HOLD_MOUSE_BUTTON"]) {
    int mouse_x = (*events)["POS_MOUSE_X"]; 
    int mouse_y = (*events)["POS_MOUSE_Y"];
    if (mouse_x >= position.x && mouse_x <= (position.x + size.x)
      && mouse_y >= position.y && mouse_y <= (position.y + size.y)
    ) {
      position.x = mouse_x - (size.x/2);
      position.y = mouse_y - (size.y/2);
    }
  }
}

