// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include <list>

#include "Action.h"
#include "Percept.h"
#include "WorldState.h"

class Agent
{
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void Move ();
	void Update (Percept& percept);
	void GameOver (int score);
private:
	WorldState worldState;
	Action previousAction;
	list<Action> actionList;
};

#endif // AGENT_H
