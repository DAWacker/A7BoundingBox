#include "BoundingBoxClass.h"

BoundingBoxClass::BoundingBoxClass(String a_sInstanceName)
{
	m_pMeshOBB = nullptr;
	m_v3CentroidOBB = vector3(0.0f, 0.0f, 0.0f);
	m_v3ColorOBB = MEBLUE;
	m_m4ModelToWorldOBB = matrix4(1.0f);
	m_bVisibleOBB = false;

	m_pMeshAABB = nullptr;
	m_v3CentroidAABB = vector3(0.0f,0.0f,0.0f);
	m_v3ColorAABB = MEWHITE;
	m_m4ModelToWorldAABB = matrix4(1.0f);
	m_bVisibleAABB = false;

	m_pModelMngr = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;

	int nInstance = m_pModelMngr->IdentifyInstance(m_sInstance);
	if (nInstance == -1)
		return;

	CalculateOBB(m_sInstance);
	m_m4ModelToWorldOBB = m_pModelMngr->GetModelMatrix(m_sInstance);

	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEBLUE);
	SetModelMatrixOBB(m_m4ModelToWorldOBB);

	CalculateAABB(m_sInstance);
	m_m4ModelToWorldAABB = m_pModelMngr->GetModelMatrix(m_sInstance);

	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
	SetModelMatrixAABB(m_m4ModelToWorldAABB);
}

BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	m_sInstance = other.m_sInstance;
	m_pModelMngr = other.m_pModelMngr;

	m_bVisibleOBB = other.m_bVisibleOBB;
	m_v3CentroidOBB = other.m_v3CentroidOBB;
	m_m4ModelToWorldOBB = other.m_m4ModelToWorldOBB;

	m_bVisibleAABB = other.m_bVisibleAABB;
	m_v3CentroidAABB = other.m_v3CentroidAABB;
	m_m4ModelToWorldAABB = other.m_m4ModelToWorldAABB;

	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEBLUE);
	m_pMeshOBB->SetModelMatrix(glm::translate(m_m4ModelToWorldOBB, m_v3CentroidOBB));

	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
	m_pMeshAABB->SetModelMatrix(glm::translate(m_m4ModelToWorldAABB, m_v3CentroidAABB));
}

BoundingBoxClass& BoundingBoxClass::operator=(BoundingBoxClass const& other)
{
	if (this != &other)
	{
		m_sInstance = other.m_sInstance;
		m_pModelMngr = other.m_pModelMngr;

		m_bVisibleOBB = other.m_bVisibleOBB;
		m_v3CentroidOBB = other.m_v3CentroidOBB;
		m_m4ModelToWorldOBB = other.m_m4ModelToWorldOBB;

		m_bVisibleAABB = other.m_bVisibleAABB;
		m_v3CentroidAABB = other.m_v3CentroidAABB;
		m_m4ModelToWorldAABB = other.m_m4ModelToWorldAABB;

		m_pMeshOBB = new PrimitiveWireClass();
		m_pMeshOBB->GenerateCube(1.0f, MEBLUE);
		m_pMeshOBB->SetModelMatrix(glm::translate(m_m4ModelToWorldOBB, m_v3CentroidOBB));

		m_pMeshAABB = new PrimitiveWireClass();
		m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
		m_pMeshAABB->SetModelMatrix(glm::translate(m_m4ModelToWorldAABB, m_v3CentroidAABB));
	}
	return *this;
}

BoundingBoxClass::~BoundingBoxClass()
{
	// Destory the object and release all of the allocated memory first
	Release();
}

void BoundingBoxClass::Release(void)
{
	// If the OBB mesh exists, release it
	if (m_pMeshOBB != nullptr)
	{
		delete m_pMeshOBB;
		m_pMeshOBB = nullptr;
	}

	// If the AABB mesh exists, release it
	if (m_pMeshAABB != nullptr)
	{
		delete m_pMeshAABB;
		m_pMeshAABB = nullptr;
	}

	// No longer point to the model manager singleton
	m_pModelMngr = nullptr;
}

// Accessors
String BoundingBoxClass::GetInstanceName(void){ return m_sInstance; }

bool BoundingBoxClass::GetVisibleOBB(void) { return m_bVisibleOBB; }
void BoundingBoxClass::SetVisibleOBB(bool a_bVisible) { m_bVisibleOBB = a_bVisible; }

bool BoundingBoxClass::GetVisibleAABB(void) { return m_bVisibleAABB; }
void BoundingBoxClass::SetVisibleAABB(bool a_bVisible) { m_bVisibleAABB = a_bVisible; }

vector3 BoundingBoxClass::GetColorOBB(void) { return m_v3ColorOBB; }
void BoundingBoxClass::SetColorOBB(vector3 a_v3Color){ m_v3ColorOBB = a_v3Color == m_v3ColorAABB ? m_v3ColorOBB : a_v3Color; }

vector3 BoundingBoxClass::GetColorAABB(void) { return m_v3ColorAABB; }
//void BoundingBoxClass::SetColorAABB(vector3 a_v3Color) { m_v3ColorAABB = a_v3Color == m_v3ColorOBB ? m_v3ColorAABB : a_v3Color; }
void BoundingBoxClass::SetColorAABB(vector3 a_v3Color) { m_v3ColorAABB = a_v3Color; }

matrix4 BoundingBoxClass::GetModelMatrixOBB(void) { return m_m4ModelToWorldOBB; }
void BoundingBoxClass::SetModelMatrixOBB(matrix4 a_m4Matrix)
{ 
	m_m4ModelToWorldOBB = a_m4Matrix;

	CalculateOBB(m_sInstance);

	matrix4 translate = glm::translate(a_m4Matrix, m_v3CentroidOBB);
	
	vector3 v3Min = GetMinOBB();
	vector3 v3Max = GetMaxOBB();
	matrix4 scale = glm::scale(v3Max - v3Min);

	matrix4 m4MatrixOBB = translate * scale;

	m_pMeshOBB->SetModelMatrix(m4MatrixOBB);
}

matrix4 BoundingBoxClass::GetModelMatrixAABB(void) { return m_m4ModelToWorldAABB; }
void BoundingBoxClass::SetModelMatrixAABB(matrix4 a_m4Matrix)
{ 
	m_m4ModelToWorldAABB = a_m4Matrix;

	CalculateAABB(m_sInstance);

	matrix4 translate = glm::translate(m_v3CentroidAABB);

	vector3 v3Min = GetMinAABB();
	vector3 v3Max = GetMaxAABB();
	matrix4 scale = glm::scale(v3Max - v3Min);

	matrix4 m4MatrixAABB = translate * scale;

	m_pMeshAABB->SetModelMatrix(m4MatrixAABB);
}

vector3 BoundingBoxClass::GetMaxOBB(void)
{
	//Go one by one on each component and realize which one is the largest one
	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(m_sInstance);
	int nVertices = static_cast<int>(vVertices.size());

	vector3 v3Maximum;
	if (nVertices > 0)
	{
		//We assume the first vertex is the largest one
		v3Maximum = vVertices[0];
		//And iterate one by one
		for (int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if (vVertices[nVertex].x > v3Maximum.x)
				v3Maximum.x = vVertices[nVertex].x;

			if (vVertices[nVertex].y > v3Maximum.y)
				v3Maximum.y = vVertices[nVertex].y;

			if (vVertices[nVertex].z > v3Maximum.z)
				v3Maximum.z = vVertices[nVertex].z;
		}
	}

	return v3Maximum;
}

vector3 BoundingBoxClass::GetMinOBB(void)
{
	//Go one by one on each component and realize which one is the smallest one
	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(m_sInstance);
	int nVertices = static_cast<int>(vVertices.size());

	vector3 v3Minimum;
	if (nVertices > 0)
	{
		//We assume the first vertex is the smallest one
		v3Minimum = vVertices[0];
		//And iterate one by one
		for (int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if (vVertices[nVertex].x < v3Minimum.x)
				v3Minimum.x = vVertices[nVertex].x;

			if (vVertices[nVertex].y < v3Minimum.y)
				v3Minimum.y = vVertices[nVertex].y;

			if (vVertices[nVertex].z < v3Minimum.z)
				v3Minimum.z = vVertices[nVertex].z;
		}
	}

	return v3Minimum;
}

void BoundingBoxClass::CalculateOBB(String a_sInstance)
{
	vector3 v3Minimum = GetMinOBB();
	vector3 v3Maximum = GetMaxOBB();

	m_v3CentroidOBB = v3Minimum + v3Maximum;
	m_v3CentroidOBB /= 2.0f;

	return;
}

void BoundingBoxClass::CalculateAABB(String a_sIstance)
{
	vector3 v3Minimum = GetMinAABB();
	vector3 v3Maximum = GetMaxAABB();

	m_v3CentroidAABB = v3Minimum + v3Maximum;
	m_v3CentroidAABB /= 2.0f;

	return;
}

//Helper function for making local coordinates global
vector3 LocalToWorld(vector3 vec3, matrix4 mat4World){
	vector4 vec4(vec3.x, vec3.y, vec3.z, 1);
	vector4 vec4Translated = mat4World * vec4;
	vector3 translated(vec4Translated.x, vec4Translated.y, vec4Translated.z);
	return translated;
}

vector3 BoundingBoxClass::GetMaxAABB(void)
{
	vector3 v3Maximum;

	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(m_sInstance);
	int nVertices = static_cast<int>(vVertices.size());
	if (nVertices > 0)
	{
		v3Maximum = LocalToWorld(vVertices[0], m_pModelMngr->GetModelMatrix(m_sInstance));
		for (int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			vector3 checking = LocalToWorld(vVertices[nVertex],  m_pModelMngr->GetModelMatrix(m_sInstance));
			
			if (checking.x > v3Maximum.x)
				v3Maximum.x = checking.x;

			if (checking.y > v3Maximum.y)
				v3Maximum.y = checking.y;

			if (checking.z > v3Maximum.z)
				v3Maximum.z = checking.z;
		}
	}

	return v3Maximum;
}

vector3 BoundingBoxClass::GetMinAABB(void)
{
	vector3 v3Minimum;

	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(m_sInstance);
	int nVertices = static_cast<int>(vVertices.size());
	if (nVertices > 0)
	{
		v3Minimum = LocalToWorld(vVertices[0], m_pModelMngr->GetModelMatrix(m_sInstance));
		for (int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			vector3 checking = LocalToWorld(vVertices[nVertex],  m_pModelMngr->GetModelMatrix(m_sInstance));
			
			if (checking.x < v3Minimum.x)
				v3Minimum.x = checking.x;

			if (checking.y < v3Minimum.y)
				v3Minimum.y = checking.y;

			if (checking.z < v3Minimum.z)
				v3Minimum.z = checking.z;
		}
	}
	return v3Minimum;
}

vector3 BoundingBoxClass::GetCentroidOBB(void)
{
	vector3 v3Minimum = GetMinOBB();
	vector3 v3Maximum = GetMaxOBB();

	vector3 v3Centroid = v3Minimum + v3Maximum;
	v3Centroid /= 2.0f;

	m_v3CentroidOBB = v3Centroid;
	return m_v3CentroidOBB;
}

vector3 BoundingBoxClass::GetCentroidAABB(void)
{
	vector3 v3Minimum = GetMinAABB();
	vector3 v3Maximum = GetMaxAABB();

	vector3 v3Centroid = v3Minimum + v3Maximum;
	v3Centroid /= 2.0f;

	m_v3CentroidAABB = v3Centroid;
	return m_v3CentroidAABB;
}

void BoundingBoxClass::RenderOBB(vector3 a_v3Color)
{
	if (!m_bVisibleOBB)
		return;

	vector3 v3Color = a_v3Color == MEDEFAULT ? m_v3ColorOBB : a_v3Color;

	m_pMeshOBB->Render(matrix4(1.0f), v3Color);
}

void BoundingBoxClass::RenderAABB(vector3 a_v3Color)
{
	if (!m_bVisibleAABB)
		return;

	vector3 v3Color = a_v3Color == MEDEFAULT ? m_v3ColorAABB : a_v3Color;

	// Not completed, need box manager to test if things are rendering properly

	m_pMeshAABB->Render(matrix4(1.0f), v3Color);
}