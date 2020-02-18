#include "TktkDirectX11Wrapper/Graphics/Camera/Asset/CameraData.h"

namespace tktk
{
	CameraData::CameraData(const Matrix4 & viewMatrix, const Matrix4 & projectionMatrix)
		: m_viewMatrix(viewMatrix)
		, m_projectionMatrix(projectionMatrix)
	{
	}

	CameraData::~CameraData()
	{
	}

	Matrix4 * CameraData::getViewMatrixPtr()
	{
		return &m_viewMatrix;
	}

	Matrix4 * CameraData::getProjectionMatrixPtr()
	{
		return &m_projectionMatrix;
	}
}