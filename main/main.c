#include <stdio.h>
#include "game_logic.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
  chimera_pet_t my_pet = {.hunger = 50};

  printf("Initial hunger: %d\n", my_pet.hunger);

  while (1)
  {
    if (my_pet.hunger < 70)
    {
      feed_pet(&my_pet);
      printf("Hunger after feeding: %d\n", my_pet.hunger);
    }
    vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 second
  }
}
