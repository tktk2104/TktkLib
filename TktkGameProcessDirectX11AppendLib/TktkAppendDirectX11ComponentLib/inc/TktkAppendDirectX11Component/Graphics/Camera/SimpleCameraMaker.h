#ifndef SIMPLE_CAMERA_MAKER_H_
#define SIMPLE_CAMERA_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SimpleCamera.h"

namespace tktk
{
	class SimpleCameraMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SimpleCameraMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<SimpleCamera> create();

		SimpleCameraMaker& cameraId(int value);

		SimpleCameraMaker& cameraFov(float value);

		SimpleCameraMaker& cameraNear(float value);

		SimpleCameraMaker& cameraFar(float value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static SimpleCameraMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_cameraId{ 0 };
		float m_cameraFov{ 45.0f };
		float m_cameraNear{ 0.01f };
		float m_cameraFar{ 1000.0f };
	};
}
#endif // !SIMPLE_CAMERA_MAKER_H_