#include <stddef.h>
#include "game_logic.h"

void feed_pet(chimera_pet_t *pet)
{
  if (pet == NULL)
    return;

  pet->hunger += 30;
  if (pet->hunger > 100)
    pet->hunger = 100;
}