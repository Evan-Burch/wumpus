// Agent.cc

#include <ctime>
#include <iostream>
#include <list>

#include "Agent.h"
#include "Location.h"
#include "Action.h"
#include "Orientation.h"
#include "WorldState.h"
#include "WumpusWorld.h"

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	worldState.agentHasArrow = true;
	worldState.agentOrientation = RIGHT;
	worldState.agentHasGold = false;
	worldState.agentLocation = Location(1,1);
	previousAction = CLIMB;
	actionList.clear();
}

Action Agent::Process (Percept& percept)
{
	if (percept.Glitter == true) {
		actionList.push_back(GRAB);
	} else if ((worldState.agentLocation.X == 1) && (worldState.agentLocation.Y == 1) && worldState.agentHasGold) {
		actionList.push_back(CLIMB);
	} else if ((worldState.agentHasArrow) && (worldState.agentLocation.X == 4) && (worldState.agentOrientation == UP)) {
		actionList.push_back(SHOOT);
	} else if ((worldState.agentHasArrow) && (worldState.agentLocation.Y == 4) && (worldState.agentOrientation == RIGHT)) {
		actionList.push_back(SHOOT);
	} else {
		int idx = rand() % 3;
		Action randAction = Action(idx);
		actionList.push_back(randAction);
	}
	previousAction = actionList.front();
	actionList.pop_back();
	return previousAction;
}

void Agent::Move () {
	if(worldState.agentOrientation == UP){
		worldState.agentLocation.Y += 1;
	}
	if(worldState.agentOrientation == DOWN){
		worldState.agentLocation.Y -= 1;
	}
	if(worldState.agentOrientation == RIGHT){
		worldState.agentLocation.X += 1;
	}
	if(worldState.agentOrientation == LEFT){
		worldState.agentLocation.X -= 1;
	}
}

void Agent::Update (Percept& percept) {
	if(previousAction == SHOOT){
		worldState.agentHasArrow = false;
	}
	if(previousAction == GOFORWARD){
		if(!percept.Bump){
			Move();
		}
	}
	if(previousAction == TURNLEFT){
		if (worldState.agentOrientation == RIGHT)
			worldState.agentOrientation = UP;
		else if (worldState.agentOrientation == UP)
			worldState.agentOrientation = LEFT;
		else if (worldState.agentOrientation == LEFT)
			worldState.agentOrientation = DOWN;
		else if (worldState.agentOrientation == DOWN)
			worldState.agentOrientation = RIGHT;
	}
	if(previousAction == TURNRIGHT){
		if (worldState.agentOrientation == RIGHT)
			worldState.agentOrientation = DOWN;
		else if (worldState.agentOrientation == UP)
			worldState.agentOrientation = RIGHT;
		else if (worldState.agentOrientation == LEFT)
			worldState.agentOrientation = UP;
		else if (worldState.agentOrientation == DOWN)
			worldState.agentOrientation = LEFT;
	}
	// If we just tried to grab the gold and the glitter is gone, we must have the gold
	if(previousAction == GRAB){
		if (percept.Glitter == false)
			worldState.agentHasGold = true;
	}
}

void Agent::GameOver (int score)
{

}

