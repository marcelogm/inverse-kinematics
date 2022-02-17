#include "kinematic.hpp"

void HierarchicalKinematic::addToJointPosition(vec3 rotationA, vec3 rotationB, vec3 rotationC) {
	jointRotation.at(0) += rotationA;
	jointRotation.at(1) += rotationB;
	jointRotation.at(2) += rotationC;

	setRotation(jointRotation.at(0), 0);
	setRotation(jointRotation.at(1), 1);
	setRotation(jointRotation.at(2), 2);
}

void HierarchicalKinematic::setRotation(vec3 axis, int at) {
	glm::mat4 rotX = glm::rotate(mat4(1.f), axis.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(mat4(1.f), axis.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(mat4(1.f), axis.z, glm::vec3(0, 0, 1));

	this->rotation.at(at) = origin.at(at) * rotZ * rotY * rotX * glm::inverse(origin.at(at)) * mat4(1.f);
}

void HierarchicalKinematic::setTranslation(mat4 translationA, mat4 translationB, mat4 translationC) {
	this->translation = {
		translationA,
		translationB,
		translationC
	};
}

void HierarchicalKinematic::update() {
	vector<mat4> transformations = {};
	model = { mat4(1.f), mat4(1.f), mat4(1.f) };
	for (int i = 0; i < 3; i++) {
		transformations.push_back(this->rotation.at(i));
		transformations.push_back(this->translation.at(i));

		for (mat4& transformation: transformations) {
			model.at(i) *= transformation;
		}

		this->joints.at(i)->setKinematicTransformation(model.at(i) * glm::inverse(origin.at(i)));
		this->joints.at(i)->update();
		this->entities.at(i)->setKinematicTransformation(model.at(i));
		this->entities.at(i)->update();
	}

	this->endEffector->setKinematicTransformation(model.back() * origin.back());
	this->endEffector->update();
}

vec3 HierarchicalKinematic::getEndEffectorPosition() {
	mat4 m = *this->endEffector->getModel();
	return glm::vec3(m[3]);
}

vector<Entity*> HierarchicalKinematic::getJoints() {
	return this->joints;
}

HierarchicalKinematic::HierarchicalKinematic(vector<Entity*> entities, vector<Entity*> joints, Entity* endEffector, vector<mat4> origins) {
	this->entities = entities;
	this->joints = joints;
	this->origin = origins;
	this->endEffector = endEffector;
	this->jointRotation = { vec3(0), vec3(0), vec3(0) };
	this->rotation = {
		mat4(1.f), mat4(1.f), mat4(1.f),
	};
}