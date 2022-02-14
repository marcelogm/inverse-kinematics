#include "scene.hpp"
#include "scene.hpp"
#include <glm/gtx/norm.hpp>

Scene::Scene(vector<Entity*> fixed, vector<HierarchicalEntity*> hierarchicalEntities, Camera* camera) {
	this->entities = fixed;
	this->hierarchicalEntities = hierarchicalEntities;
	this->camera = camera;
	this->renderer = new Renderer();
	this->r = 0;
}

typedef struct {
	float angle;
	vec3 position;
} Transfomation;

void Scene::render() {
	this->renderer->clear();
	this->renderer->prepare();

	KinematicConfiguration* kinematic = Configuration::getInstance()->getKinematic();

	vector<Transfomation> transformations = { 
		{ 60.f, vec3(0.f, 1.0f, 0.f) }, 
		{ 60.f, vec3(0.f, 2.0f, 0.f) },
		{ 60.f, vec3(0.f, 2.0f, 0.f) }
	};

	HierarchicalEntity* root = hierarchicalEntities.at(0);
	
	for(Transfomation t : transformations) {
		auto position = glm::translate(mat4(1.f), t.position);
		auto rotation = glm::rotate(mat4(1.f), glm::radians((float) t.angle), vec3(1.f, 0.f, 0.f));
		root->setTranslation(position);
		root->setRotation(rotation);
		root = next(root);
	}

	hierarchicalEntities.at(0)->update({});

	for (Entity* entity : this->entities) {
		this->updateAndRender(entity, camera);
	}

	r++;
	if (r > 360) {
		r = 0;
	}
}

HierarchicalEntity* Scene::next(HierarchicalEntity* root) {
	if (root->getChilds().size() > 0) {
		return root->getChilds().at(0);
	}
	return nullptr;
}

void Scene::updateAndRender(Entity* entity, Camera* camera) {
	entity->update();
	renderer->render(entity, camera, Configuration::getInstance()->getLight());
}

Camera* Scene::getCamera() {
	return camera;
}
