#include "game_element.h"
#include <vector>
#include "cpputils/graphics/image.h"

bool GameElement::IsOutOfBounds(const graphics::Image& screen) {
  return GetX() < 0 || GetY() < 0 || GetX() + GetWidth() > screen.GetWidth() ||
         GetY() + GetHeight() > screen.GetHeight();
}

bool GameElement::IntersectsWith(GameElement* other) {
  return !(GetX() > (*other).GetX() + (*other).GetWidth() ||
           (*other).GetX() > GetX() + GetWidth() ||
           GetY() > (*other).GetY() + (*other).GetHeight() ||
           (*other).GetY() > GetY() + GetHeight());
}
