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
	WorldState worldState;
	worldState.agentHasArrow = true;
	worldState.agentOrientation = UP;
	worldState.agentHasGold = false;
	worldState.agentLocation = Location(1,1);
	Action previousAction = CLIMB;
	actionList.clear();
}

Action Agent::Process (Percept& percept)
{
	Update(percept);
		if (percept.Glitter == true) {
			actionList.push_back(GRAB);
		} else if ((worldState.agentLocation == Location(1,1)) && worldState.agentHasGold) {
			actionList.push_back(CLIMB);
		} else if ((worldState.agentHasArrow) && (worldState.agentLocation.X == 4) && (worldState.agentOrientation = Orientation(UP))) {
			actionList.push_back(SHOOT);
		} else if ((worldState.agentHasArrow) && (worldState.agentLocation.Y == 4) && (worldState.agentOrientation = Orientation(RIGHT))) {
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
		worldState.agentLocation.Y -= 1;
	}
}

void Agent::Update (Percept& percept) {
	if(previousAction == CLIMB){
		worldState.agentHasGold = true;
	}
	if(previousAction == SHOOT){
		worldState.agentHasArrow = false;
	}
	if(previousAction == GOFORWARD){
		if(!percept.Bump){
			Move();
		}
	}
	if(previousAction == TURNLEFT){
		worldState.agentOrientation = Orientation(LEFT);
	}
	if(previousAction == TURNRIGHT){
		worldState.agentOrientation = Orientation(RIGHT);
	}
	if(previousAction == GRAB){
		percept.Glitter = true;
	}
}

void Agent::GameOver (int score)
{

}

