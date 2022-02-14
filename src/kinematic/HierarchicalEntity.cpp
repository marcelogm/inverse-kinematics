#include "kinematic.hpp"

void HierarchicalEntity::setRotation(mat4 rotation) {
	this->rotation = this->getOrigin() * rotation * glm::inverse(this->getOrigin());
}

void HierarchicalEntity::setTranslation(mat4 translation) {
	this->translation = translation;
}

void HierarchicalEntity::update(vector<mat4> transformations) {
	auto model = mat4(1.f);
	transformations.push_back(this->rotation);
	transformations.push_back(this->translation);

	for (int i = 0; i < transformations.size(); i++) {
		model *= transformations.at(i);
	}

	joint->setKinematicTransformation(model * glm::inverse(origin));
	joint->update();
	entity->setKinematicTransformation(model);
	entity->update();

	for (HierarchicalEntity* child : this->childs) {
		child->update(transformations);
	}
}

mat4 HierarchicalEntity::getOrigin() {
	return origin;
}

HierarchicalEntity::HierarchicalEntity(Entity* entity, Entity* joint, mat4 origin, vector<HierarchicalEntity*> childs) {
	this->entity = entity;
	this->joint = joint;
	this->origin = origin;
	this->childs = childs;
	this->rotation = mat4(1.f);
	this->translation = mat4(1.f);
}

vector<HierarchicalEntity*> HierarchicalEntity::getChilds() {
	return childs;
}
