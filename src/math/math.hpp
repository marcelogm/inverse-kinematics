#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include "../kinematic/kinematic.hpp"

using glm::mat3;
using glm::vec3;
using std::vector;

class Jacobian {
public:
	vec3 getJacobianAtAxis(Entity* joint, vec3 target, vec3 axis);
	float IK(HierarchicalKinematic* hierarchical, vec3 target);
};