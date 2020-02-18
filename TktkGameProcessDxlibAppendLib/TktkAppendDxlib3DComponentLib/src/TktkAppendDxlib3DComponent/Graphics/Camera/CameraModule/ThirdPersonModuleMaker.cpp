#include "TktkAppendDxlib3DComponent/Graphics/Camera/CameraModule/ThirdPersonModuleMaker.h"

namespace tktk
{
	ThirdPersonModuleMaker ThirdPersonModuleMaker::m_self;

	ThirdPersonModuleMaker & ThirdPersonModuleMaker::makeStart()
	{
		m_self = ThirdPersonModuleMaker();
		return m_self;
	}

	std::shared_ptr<ThirdPersonModule> ThirdPersonModuleMaker::create()
	{
		return std::make_shared<ThirdPersonModule>(
			m_target,
			m_targetRelativeLookAtPos,
			m_relativePos
			);
	}

	ThirdPersonModuleMaker & ThirdPersonModuleMaker::target(GameObjectPtr value)
	{
		m_target = value;
		return *this;
	}

	ThirdPersonModuleMaker & ThirdPersonModuleMaker::targetRelativeLookAtPos(const Vector3 & value)
	{
		m_targetRelativeLookAtPos = value;
		return *this;
	}

	ThirdPersonModuleMaker & ThirdPersonModuleMaker::relativePos(const Vector3 & value)
	{
		m_relativePos = value;
		return *this;
	}
}