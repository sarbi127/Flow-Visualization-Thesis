
#ifndef IVW_SPHERE_H
#define IVW_SPHERE_H

//#include <modules/vectorfieldvisualization/vectorfieldvisualizationmoduledefine.h>
#include <bitset>
#include <flow\flowmoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/datastructures/geometry/geometrytype.h>

#include <inviwo/core/ports/meshport.h>
#include <inviwo/core/ports/volumeport.h>
#include <inviwo/core/properties/optionproperty.h>
#include <inviwo/core/properties/ordinalproperty.h>
#include <modules/base/algorithm/volume/volumeramsubset.h>
#include <inviwo\core\datastructures\buffer\bufferramprecision.h>
#include <inviwo/core/properties/minmaxproperty.h>
#include <inviwo/core/datastructures/geometry/basicmesh.h>
#include <inviwo/core/properties/buttonproperty.h>
#include <flow/datastructures/Face.h>


namespace inviwo {
	
class IVW_MODULE_FLOW_API Sphere : public Processor { 
public:

    Sphere();
    virtual ~Sphere();

    InviwoProcessorInfo();

    virtual void process();
	
    protected:

	ButtonProperty subdivide_btn_;
	ButtonProperty subdividebackward_btn_;
	BasicMesh *mesh_;

	MeshOutport outportmesh_;
	DataOutport<std::vector<vec3>> outportpoint_;
	DataOutport<std::vector<Face>> outportface_;
	//DataOutport<BasicMesh> outportmesh_;
	

	FloatProperty radius_;

	/*struct face{

		size_t p1;
		size_t p2;
		size_t p3;

		face() {}

		face(size_t o, size_t t, size_t f ,bool is_parent, bool is_core, bool is_child) {

			p1 = o;
			p2 = t;
			p3 = f;
			is_parent_ = is_parent;
			is_core_ = is_core;
			is_child_ = is_child;

		}

		bool is_parent_;
		bool is_core_;
		bool is_child_;
	};*/


	vec3 getNormal(Face &f) {

		vec3 p1 = vertices_->at(f.p1);
		vec3 p2 = vertices_->at(f.p2);
		vec3 p3 = vertices_->at(f.p3);

		vec3 u = p2 - p1;
		vec3 v = p3 - p1;

		return glm::normalize(glm::cross(u, v));

	};

	void subdivide(Face &f, size_t);
	void subdividebackward(Face &f, std::vector<Face> faces);
	void CreateAndSetOutportData();
	void onButtonPress();
	void onButtonPressback();
	bool findMatch(size_t, Face &);

	glm::mat4 model_matrix_;
	std::vector<vec3> *vertices_;
	std::vector<Face> *faces_;
	std::vector<Face> candidatesParent_;
	std::vector<Face> candidatesChild_;
	
};

} // namespace

#endif // IVW_SPHERE_H

