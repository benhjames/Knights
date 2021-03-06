#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <allegro5/allegro_font.h>
#include "Player.h"
#include "GameState.h"

class Player;
class GameState;

class Inventory
{
public:
	Inventory();
	~Inventory(void);
    
    int getSelectedSlot();
    Item* getSelectedItem(void);
    Item* getItemAt(int slot);
    void deleteFromSelectedSlot(void);
    void deleteFromSlot(int slot);
	bool addToInventory(Item* itemToAdd);
    void useSelectedItem(Player* player);
    void dropSelectedItem(GameState* game);
    
    void populateInventory(void);
    
    void moveSelectorRight(void);
    void moveSelectorLeft(void);
    
    void drawInventory(int equippedItem);
    ALLEGRO_BITMAP* getDrawnInventory(void) { return cachedInventoryDraw; };
    
private:
    std::vector<Item*> items;
    int capacity = 10;
    int selectedSlot = 0;
    ALLEGRO_BITMAP *cachedInventoryDraw;
    bool needsRedraw = true;
};

#endif