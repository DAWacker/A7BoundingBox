#include "BoundingBoxClass.h"

BoundingBoxClass::BoundingBoxClass(String a_sInstanceName)
{
	m_pMeshOBB = nullptr;
	m_v3CentroidOBB = vector3(0.0f, 0.0f, 0.0f);
	m_v3ColorOBB = MEWHITE;
	m_m4ModelToWorldOBB = matrix4(1.0f);
	m_bVisibleOBB = false;

	m_pMeshAABB = nullptr;
	m_v3CentroidAABB = vector3(0.0f, 0.0f, 0.0f);
	m_v3ColorAABB = MEWHITE;
	m_m4ModelToWorldAABB = matrix4(1.0f);
	m_bVisibleAABB = false;

	m_pModelMngr = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;

	int nInstance = m_pModelMngr->IdentifyInstance(m_sInstance);
	if (nInstance == -1)
		return;

	CalculateOBB(m_sInstance);
	CalculateAABB(m_sInstance);

	m_pMeshOBB = new PrimitiveWireClass();
}