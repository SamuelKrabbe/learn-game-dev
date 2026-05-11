#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <raylib.h>
#include <vector>

// class Item {
// public:
//   void (*action)();
//
// private:
//   unsigned int id;
//   Texture2D texture;
// };

class Inventory {
public:
  void update();
  void draw();

private:
  std::vector<Texture2D> slots{};
  unsigned int maxStackSize{};
};

#endif
