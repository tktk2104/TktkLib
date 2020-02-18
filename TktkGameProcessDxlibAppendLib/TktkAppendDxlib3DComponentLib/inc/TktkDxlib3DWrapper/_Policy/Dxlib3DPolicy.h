#ifndef DXLIB_3D_POLICY_H_
#define DXLIB_3D_POLICY_H_

#include <TktkMath/Vector2.h>

namespace tktk
{
	// Dxlib���g����3D�̃v���O�����𓮂������߂̃|���V�[
	class Dxlib3DPolicy
	{
	public:

		Dxlib3DPolicy(
			const Vector2& gameScreenSize,	// �Q�[���E�B���h�E�̑傫��
			bool fullScreenFlag,			// �t���X�N���[���ɂ��邩
			float oneMeterDistance,			// �R�������W�n�ł̂P���[�g���̋���
			bool useXAudio					// XAudio���g�p���邩�H
		);

	public:

		void awake();

		bool isDestroy() const;

	private:

		void setUpdatePriority();

	private:

		// �Q�[����ʂ̑傫��
		Vector2 m_gameScreenSize;

		// �t���X�N���[���t���O
		bool m_fullScreenFlag;

		// �R�������W�n�ł̂P���[�g���̋���
		float m_oneMeterDistance;

		// XAudio���g�p���邩�H
		bool m_useXAudio;
	};
}
#endif // !DXLIB_3D_POLICY_H_