#pragma once

#include "Entity.h"

// Macros for different possible models of cactus
#define CACTUS_MODEL_1 1
#define CACTUS_MODEL_2 2
#define CACTUS_MODEL_3 3
#define CACTUS_MODEL_4 4

class Cactus : public Entity {
public:
  // Constructor
  Cactus(int model = CACTUS_MODEL_1);

  // Destructor
  ~Cactus();

  // Render calling graphics manager
  void render();

  // Update position based on traveled distance received
  void update(double dx);

  // Renew based on new height and position
  void renew(int info, int px) override;

private:
  int model;
};