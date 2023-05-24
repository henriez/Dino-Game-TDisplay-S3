#pragma once

#include "Entity.h"

// Macros for different possible spawn positions
#define HEIGHT1 10
#define HEIGHT2 35
#define HEIGHT3 60

class Bird : public Entity {
public:
  // Constructor
  Bird(int y = HEIGHT1);

  // Destructor
  ~Bird();

  // Update position based on traveled distance received
  void update(double dx);

  // Render calling graphics manager
  void render();

  // Renew based on new height and position
  void renew(int info, int px) override;
};