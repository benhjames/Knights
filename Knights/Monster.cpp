#include "Monster.h"
#include <stdio.h>
#include <stdlib.h>
#include "Items.h"

void Monster::moveRandomly(GameState* game)
{
    if(m_isMoving == false)
    {
        if((rand() % 200)==1)
        {
            m_isMoving = true;
            m_currentDirection = Direction(2 * (rand() % 4) + 1);
        }
    }
    else
    {
        if (!isCollision(m_currentDirection, game->currentLevel->levelMap))
        {
            if(m_currentDirection == North) { m_y--; }
            if(m_currentDirection == South) { m_y++; }
            if(m_currentDirection == East)  { m_x++; }
            if(m_currentDirection == West)  { m_x--; }
            
            if((rand() % 70)==1)
            {
                m_isMoving = false;
            }
        }
        else
        {
            m_isMoving = false;
        }
    }
}

void Monster::moveTowardsPlayer(GameState* game)
{
    if(game->mainCharacter->getX() - 30 > m_x && !isCollision(East, game->currentLevel->levelMap))
    {
        m_x++;
        m_currentDirection = East;
    }
    if(game->mainCharacter->getX() + 20 < m_x && !isCollision(West, game->currentLevel->levelMap))
    {
        m_x--;
        m_currentDirection = West;
    }
    if(game->mainCharacter->getY() - 30 > m_y && !isCollision(South, game->currentLevel->levelMap))
    {
        m_y++;
        m_currentDirection = South;
    }
    if(game->mainCharacter->getY() + 20 < m_y && !isCollision(North, game->currentLevel->levelMap))
    {
        m_y--;
        m_currentDirection = North;
    }
}

void Monster::handleMovement(GameState* game)
{
	if(m_spawned)
	{
        m_lastDirection = m_currentDirection;
        if(!m_inCombat)
		{
            moveRandomly(game);
		}
		else
		{
            moveTowardsPlayer(game);
		}
	}
}

void Monster::handleCombat(GameState* game)
{
    if(m_inCombat)
    {
        m_timeSinceLastAttack += GameEngine::getDeltaTime();
        if(m_timeSinceLastAttack >= 0.5)
        {
            if(abs(game->mainCharacter->getX() - m_x) + abs(game->mainCharacter->getY() - m_y) < 50)
            {
                game->mainCharacter->reduceHealth(m_offencePotential);
            }
            m_timeSinceLastAttack = 0.0;
        }
    }
}

void Monster::killed(GameState* game) //When killed drop a random item
{
    if(game->mainCharacter->selected_weapon == -1) { //Checks if the player already has a weapon equipped
        switch(rand() % 3)
        {
            case 0:
                game->currentLevel->levelMapItems[(m_x+25)/50][(m_y+25)/50] = Items::fishItem;
                break;
            case 1:
                game->currentLevel->levelMapItems[(m_x+25)/50][(m_y+25)/50] = Items::potionItem;
                break;
            case 2:
                game->currentLevel->levelMapItems[(m_x+25)/50][(m_y+25)/50] = Items::swordItem;
                break;
        }
	}
    else
    {
        switch(rand() % 2)
        {
            case 0:
                game->currentLevel->levelMapItems[(m_x+25)/50][(m_y+25)/50] = Items::fishItem;
                break;
            case 1:
                game->currentLevel->levelMapItems[(m_x+25)/50][(m_y+25)/50] = Items::potionItem;
                break;
        }
	}


	m_health = 0;
	m_x = 0;
	m_y = 0;
	m_spawned = false;
	m_inCombat = false;

	game->mainCharacter->addExperience(1);

	game->currentLevel->monsterCount--;

}

void Monster::reduceHealth(int maxReduction, GameState* game)
{
	m_health -= rand() % maxReduction;
	if(m_health <= 0)
	{
		killed(game);
	}
}

void Monster::spawn(int ID)
{
    m_width = 49;
    m_height = 49;
    
	if(ID == 1)
	{
        m_spawned = true;
		m_health = 100;
		m_maxHealth = 100;
		m_offencePotential = 10;
	}
	if(ID == 2)
	{
		m_spawned = true;
		m_health = 150;
		m_maxHealth = 150;
		m_offencePotential = 20;
	}
    
    loadImages(ID);
}
