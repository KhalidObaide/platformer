// types
#include <string>
#include <unordered_map>
#include <vector>
typedef struct {
  int x;
  int y;
} Coordinate;

typedef struct {
  int r, g, b, a;
} RGBA;

// helpers.cpp
int current_epoch();

// gameobjects.cpp
class GameObject {
public:
  Coordinate position;
  Coordinate size;
  RGBA fill;
  GameObject(Coordinate new_position, Coordinate new_size, RGBA new_fill);
  bool is_colliding(GameObject* target);
  virtual ~GameObject();
  virtual void update(std::unordered_map<std::string, int>* events);
};

class Player : public GameObject {
private:
  std::vector<GameObject*> platforms;
  int gravity;
  int speed;

  GameObject ground_detector;

  bool is_jumping;
  int jump_time;
  int jump_counter;
  int jump_delay;
  int last_jump;
public:
  Coordinate velocity;
  Player(Coordinate new_position, std::vector<GameObject*> new_platforms);
  void update(std::unordered_map<std::string, int>* events);
};

class Platform : public GameObject {
private:
  bool is_draggable;
public:
  Platform(
    Coordinate new_position, 
    Coordinate new_size, 
    bool new_is_draggable = true
  );
  void update(std::unordered_map<std::string, int>* events);
};
