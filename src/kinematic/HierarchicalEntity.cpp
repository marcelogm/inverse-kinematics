#include "kinematic.hpp"

void HierarchicalEntity::setRotation(mat4 rotation) {
	this->rotation = rotation;
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

HierarchicalEntity::HierarchicalEntity(Entity* entity, Entity* joint, vec3 origin, vector<HierarchicalEntity*> childs) {
	this->entity = entity;
	this->joint = joint;
	this->origin = glm::translate(mat4(1.f), origin);
	this->childs = childs;
	this->rotation = mat4(1.f);
	this->translation = mat4(1.f);
}

vector<HierarchicalEntity*> HierarchicalEntity::getChilds() {
	return childs;
}
