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

void Scene::render() {
	this->renderer->clear();
	this->renderer->prepare();

	KinematicConfiguration* kinematic = Configuration::getInstance()->getKinematic();

	auto t1 = glm::translate(mat4(1.f), vec3(0.f, 1.0f, 0.f));
	hierarchicalEntities.at(0)->setTranslation(t1);

	auto r1 = glm::rotate(mat4(1.f), glm::radians((float)r), vec3(1.f, 0.f, 0.f));
	hierarchicalEntities.at(0)->setRotation(r1);

	auto t2 = glm::translate(mat4(1.f), vec3(0.f, 2.0f, 0.f));
	hierarchicalEntities.at(0)->getChilds().at(0)->setTranslation(t2);

	auto r2 = glm::rotate(mat4(1.f), glm::radians((float)r), vec3(0.f, 0.f, 1.f));
	hierarchicalEntities.at(0)->getChilds().at(0)->setRotation(t1 * r2 * glm::inverse(t1));

	auto t3 = glm::translate(mat4(1.f), vec3(0.f, 2.0f, 0.f));
	hierarchicalEntities.at(0)->getChilds().at(0)->getChilds().at(0)->setTranslation(t3);

	auto r3 = glm::rotate(mat4(1.f), glm::radians((float)r), vec3(1.f, 0.f, 0.f));
	hierarchicalEntities.at(0)->getChilds().at(0)->getChilds().at(0)->setRotation(t1 * r3 * glm::inverse(t1));

	hierarchicalEntities.at(0)->update({});

	for (Entity* entity : this->entities) {
		this->updateAndRender(entity, camera);
	}

	r++;
	if (r > 360) {
		r = 0;
	}
}

void Scene::updateAndRender(Entity* entity, Camera* camera) {
	entity->update();
	renderer->render(entity, camera, Configuration::getInstance()->getLight());
}

Camera* Scene::getCamera() {
	return camera;
}
