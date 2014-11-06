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
	vector3 m_v3MinOBB;					// Min vertex of the OBB
	vector3 m_v3MaxOBB;					// Max vertex of the OBB
	PrimitiveWireClass* m_pMeshOBB;		// Mesh for OBB

	bool m_bVisibleAABB;				// Flag for rendering the AABB or not
	vector3 m_v3CentroidAABB;			// Centroid of the AABB
	vector3 m_v3ColorAABB;				// Color of the AABB
	matrix4 m_m4ModelToWorldAABB;		// Model matrix of the AABB
	vector3 m_v3MinAABB;				// Min vertex of the AABB
	vector3 m_v3MaxAABB;				// Max vertex of the AABB
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

	/* Helper methods for the OBB */
	bool GetVisibleOBB(void);
	void SetVisibleOBB(bool a_bVisible);
	__declspec(property(get = GetVisibleOBB, put = SetVisibleOBB)) bool VisibleOBB;

	vector3 GetCentroidOBB(void);
	__declspec(property(get = GetCentroidOBB)) vector3 CentroidOBB;

	matrix4 GetModelMatrixOBB(void);
	void SetModelMatrixOBB(matrix4 a_ModelMatrix);
	__declspec(property(get = GetModelMatrixOBB, put = SetModelMatrixOBB)) matrix4 ModelMatrixOBB;

	vector3 GetColorOBB(void);
	void SetColorOBB(vector3 a_v3Color);
	__declspec(property(get = GetColorOBB, put = SetColorOBB)) vector3 ColorOBB;

	vector3 GetMaxOBB(void);
	void SetMaxOBB(vector3 a_v3Max);
	__declspec(property(get = GetMaxOBB, put = SetMaxOBB)) vector3 MaxOBB;

	vector3 GetMinOBB(void);
	void SetMinOBB(vector3 a_v3Min);
	__declspec(property(get = GetMinOBB, put = SetMinOBB)) vector3 MinOBB;

	void RenderOBB(vector3 a_v3Color = MEDEFAULT);

	/* Helper methods for the AABB */
	bool GetVisibleAABB(void);
	bool SetVisibleAABB(bool a_bVisible);
	__declspec(property(get = GetVisibleAABB, put = SetVisibleAABB)) bool VisibleAABB;

	vector3 GetCentroidAABB(void);
	__declspec(property(get = GetCentroidAABB)) vector3 CentroidAABB;

	matrix4 GetModelMatrixAABB(void);
	void SetModelMatrixAABB(matrix4 a_ModelMatrix);
	__declspec(property(get = GetModelMatrixAABB, put = SetModelMatrixAABB)) matrix4 ModelMatrixAABB;

	vector3 GetColorAABB(void);
	void SetColorAABB(vector3 a_v3Color);
	__declspec(property(get = GetColorAABB, put = SetColorAABB)) vector3 ColorAABB;

	vector3 GetMaxAABB(void);
	void SetMaxAABB(vector3 a_v3Max);
	__declspec(property(get = GetMaxAABB, put = SetMaxAABB)) vector3 MaxAABB;

	vector3 GetMinAABB(void);
	void SetMinAABB(vector3 a_v3Min);
	__declspec(property(get = GetMinAABB, put = SetMinAABB)) vector3 MinAABB;

	void RenderAABB(vector3 a_v3Color = MEDEFAULT);

private:
	void Release(void);

	void CalculateOBB(String a_sInstance);
	void CalculateAABB(String a_sInstance);
};