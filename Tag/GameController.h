#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
class Mesh;
class Shader;
class Camera;

class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();
	void HandleKeys();

	void RunGame();

private:
	void Initialize();
	Mesh* mesh;
	Shader* shader;
	vector<Camera*> cameras;
	int curentCamera;
	bool held;
	bool held2;
};

#endif GAME_CONTROLLER_H