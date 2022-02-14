#include "../entity/entity.hpp"

class HierarchicalEntity {
private:
	vector<HierarchicalEntity*> childs;
	mat4 translation;
	mat4 rotation;
	mat4 origin;
	Entity* joint;
	Entity* entity;
public:
	void setRotation(mat4 rotation);
	void setTranslation(mat4 translation);
	void update(vector<mat4> transformations);
	mat4 getOrigin();
	HierarchicalEntity(Entity* entity, Entity* joint, mat4 origin, vector<HierarchicalEntity*> childs);
	vector<HierarchicalEntity*> getChilds();
};