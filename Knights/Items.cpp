#include "Items.h"

void Items::setItems(void) {
    fishItem = std::make_unique<Item>("fish.bmp", "Fish", "Heals some health", ItemType::Food, 0, 0, 150);
    swordItem = std::make_unique<Item>("sword.bmp", "Sword", "A deadly weapon", ItemType::Weapon, 30, 0, 0);
    potionItem = std::make_unique<Item>("healingPotion.bmp", "Potion", "Heals some health", ItemType::Food, 0, 0, 300);
}

ItemPtr Items::fishItem = NULL;
ItemPtr Items::potionItem = NULL;
ItemPtr Items::swordItem = NULL;