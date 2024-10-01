#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{
public:
	Camera(Resolution _resolution);
	Camera(Resolution _resolution, glm::vec3 _camLocation);
	virtual ~Camera() {}

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }

	void ChangeFov();
	void ChangePosition(const glm::vec3 _locaton);

	void CreateView(glm::vec3 _position, glm::vec3 _target, glm::vec3 _up);
	void CreateProjection(Resolution _res, float _nearP, float _farP);


private:
	glm::mat4 projection = {};
	glm::mat4 view = {};
	Resolution curentRes;
};

#endif

