#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h"

namespace tktk
{
	SphereMeshDrawerMaker SphereMeshDrawerMaker::m_self;

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SphereMeshDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID�̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SphereMeshDrawer> SphereMeshDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<SphereMeshDrawer>(
			m_drawPriority,
			m_radius,
			m_albedoColor,
			m_cameraId,
			m_shadowMapCameraId,
			m_lightId,
			m_useRtvDescriptorHeapId
			);
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_albedoColor = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraId = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_shadowMapCameraId = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lightId = value;
		return *this;
	}
}