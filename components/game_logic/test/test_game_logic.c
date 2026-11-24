#include "unity.h"
#include "game_logic.h"

TEST_CASE("feed_pet adds 30 hunger", "[game_logic]")
{
  chimera_pet_t pet = {.hunger = 50}; // start value
  feed_pet(&pet);
  TEST_ASSERT_EQUAL_INT(80, pet.hunger); // expected value
}

TEST_CASE("feed_pet caps hunger at 100", "[game_logic]")
{
  chimera_pet_t pet = {.hunger = 90}; // start value
  feed_pet(&pet);
  TEST_ASSERT_EQUAL_INT(100, pet.hunger); // expected value
}

TEST_CASE("feed_pet ignores NULL", "[game_logic]")
{
  chimera_pet_t pet = {.hunger = 90}; // start value
  feed_pet(NULL);
  TEST_ASSERT_EQUAL_INT(90, pet.hunger); // expected value
}