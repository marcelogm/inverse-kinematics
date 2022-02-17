#pragma once
#include "../entity/entity.hpp"

class HierarchicalKinematic {
private:
	vector<Entity*> entities;
	vector<Entity*> joints;
	Entity* endEffector;
	vector<mat4> origin;
	vector<mat4> translation;
	vector<mat4> rotation;
	vector<mat4> model;
	vector<vec3> jointRotation;
public:
	void addToJointPosition(vec3 rotationA, vec3 rotationB, vec3 rotationC);
	void setRotation(vec3 axis, int at);
	void setTranslation(mat4 translaitonA, mat4 translationB, mat4 translationC);
	void update();
	vec3 getEndEffectorPosition();
	vector<Entity*> getJoints();
	HierarchicalKinematic(vector<Entity*> entities, vector<Entity*> joints, Entity* endEffector, vector<mat4> origins);
};