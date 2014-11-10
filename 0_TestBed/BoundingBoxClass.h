#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"
using namespace MyEngine;

class BoundingBoxClass
{
	String m_sInstance;					// The name of the instance related to the OBB and AABB
	ModelManagerClass* m_pModelMngr;	// ModelManager instance

	bool m_bVisibleOBB;					// Flag for rendering the OBB or not
	vector3 m_v3CentroidOBB;			// Centroid of the OBB
	vector3 m_v3ColorOBB;				// Color of the OBB
	matrix4 m_m4ModelToWorldOBB;		// Model matrix of the OBB
	PrimitiveWireClass* m_pMeshOBB;		// Mesh for OBB

	bool m_bVisibleAABB;				// Flag for rendering the AABB or not
	vector3 m_v3CentroidAABB;			// Centroid of the AABB
	vector3 m_v3ColorAABB;				// Color of the AABB
	matrix4 m_m4ModelToWorldAABB;		// Model matrix of the AABB
	PrimitiveWireClass* m_pMeshAABB;	// Mesh for AABB

public:
	// Constructor
	BoundingBoxClass(String a_sInstanceName);
	// Copy Constructor
	BoundingBoxClass(BoundingBoxClass const& other);
	// Copy Assignment Operator
	BoundingBoxClass& operator=(BoundingBoxClass const& other);
	// Deconstructor
	~BoundingBoxClass(void);

	/* Gets the visibility of the object bounding box (whether or not it is going to be drawn in render) */
	bool GetVisibleOBB(void);
	/* Sets the visibility of the object bounding box (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw */
	void SetVisibleOBB(bool a_bVisible);
	/* Property:
	GetVisibleOBB() or SetVisibleOBB() */
	__declspec(property(get = GetVisibleOBB, put = SetVisibleOBB)) bool VisibleOBB;

	/* Gets the centroid the object bounding box */
	vector3 GetCentroidOBB(void);
	/* Property:
	GetCentroidOBB() */
	__declspec(property(get = GetCentroidOBB)) vector3 CentroidOBB;

	/* Gets the "ModelToWorld" matrix associated with the object bounding box */
	matrix4 GetModelMatrixOBB(void);
	/* Sets the "ModelToWorld" matrix associated with the object bounding box 
	Args:
		matrix4 a_ModelMatrix -> the "ModelToWorld" matrix */
	void SetModelMatrixOBB(matrix4 a_ModelMatrix);
	/* "ModelToWorld"
	GetModelMatrixOBB() or SetModelMatrixOBB() */
	__declspec(property(get = GetModelMatrixOBB, put = SetModelMatrixOBB)) matrix4 ModelMatrixOBB;

	/* Gets the color vector of this object bounding box (the default color in which is going to be rendered) */
	vector3 GetColorOBB(void);
	/* Sets the color vector of this object bounding box (the default color in which is going to be rendered)
	Args:
		vector3 a_v3Color -> the color of the object bounding box */
	void SetColorOBB(vector3 a_v3Color);
	/* Property:
	GetColorOBB() or SetColorOBB() */
	__declspec(property(get = GetColorOBB, put = SetColorOBB)) vector3 ColorOBB;

	/* Gets the maximum vector of this object bounding box */
	vector3 GetMaxOBB(void);
	/* Property:
	GetMaxOBB() */
	__declspec(property(get = GetMaxOBB)) vector3 MaxOBB;

	/* Gets the minimum vector of this object bounding box */
	vector3 GetMinOBB(void);
	/* Property:
	GetMinOBB() */
	__declspec(property(get = GetMinOBB)) vector3 MinOBB;

	/* Renders the object bounding box
	Args:
		a_vColor -> determinate the color of the box to be rendered, if MEDEFAULT
		it will render the shape in the constructed color (white) */
	void RenderOBB(vector3 a_v3Color = MEDEFAULT);
	
	/* Gets the name of the model associated with this bounding sphere from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;

	/* Gets the visibility of the axis aligned bounding box (whether or not it is going to be drawn in render) */
	bool GetVisibleAABB(void);
	/* Sets the visibility of the axis aligned bounding box (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw */
	void SetVisibleAABB(bool a_bVisible);
	/* Property:
	GetVisibleAABB() or SetVisibleAABB() */
	__declspec(property(get = GetVisibleAABB, put = SetVisibleAABB)) bool VisibleAABB;

	/* Gets the centroid the axis aligned bounding box */
	vector3 GetCentroidAABB(void);
	/* Property:
	GetCentriodAABB() */
	__declspec(property(get = GetCentroidAABB)) vector3 CentroidAABB;

	/* Gets the "ModelToWorld" matrix associated with the axis aligned bounding box */
	matrix4 GetModelMatrixAABB(void);
	/* Sets the "ModelToWorld" matrix associated with the axis aligned bounding box 
	Args:
		matrix4 a_ModelMatrix -> the "ModelToWorld" matrix */
	void SetModelMatrixAABB(matrix4 a_ModelMatrix);
	/* Property:
	GetModelMatrixAABB() or SetModelMatrixAABB() */
	__declspec(property(get = GetModelMatrixAABB, put = SetModelMatrixAABB)) matrix4 ModelMatrixAABB;

	/* Gets the color vector of this axis aligned bounding box (the default color in which is going to be rendered) */
	vector3 GetColorAABB(void);
	/* Sets the color vector of this axis aligned bounding box (the default color in which is going to be rendered)
	Args:
		vector3 a_v3Color -> the color of the axis aligned bounding box */
	void SetColorAABB(vector3 a_v3Color);
	/*  Property:
	GetColorAABB() or SetColorAABB() */
	__declspec(property(get = GetColorAABB, put = SetColorAABB)) vector3 ColorAABB;

	/* Gets the maximum vector of this axis aligned bounding box */
	vector3 GetMaxAABB(void);
	/* Property:
	GetMaxAABB() */
	__declspec(property(get = GetMaxAABB)) vector3 MaxAABB;

	/* Gets the minimum vector of this axis aligned bounding box */
	vector3 GetMinAABB(void);
	/* Property:
	GetMinAABB(); */
	__declspec(property(get = GetMinAABB)) vector3 MinAABB;

	/* Renders the axis aligned bounding box
	Args:
		a_vColor -> determinate the color of the box to be rendered, if MEDEFAULT
		it will render the shape in the constructed color (white) */
	void RenderAABB(vector3 a_v3Color = MEDEFAULT);

private:
	/* Released Memory and objects allocated. */
	void Release(void);

	/* Calculates the object bounding box from the instance
	Args:
		a_sInstance: The name of the instance for which the object bounding box is going to be calculated */
	void CalculateOBB(String a_sInstance);

	/* Calculates the axis aligned bounding box from the instance
	Args:
		a_sInstance: The name of the instance for which the axis aligned bounding box is going to be calculated */
	void CalculateAABB(String a_sInstance);
};