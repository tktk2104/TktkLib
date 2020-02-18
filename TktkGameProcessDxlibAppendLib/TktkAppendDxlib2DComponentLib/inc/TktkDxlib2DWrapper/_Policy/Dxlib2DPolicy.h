#ifndef DXLIB_2D_POLICY_H_
#define DXLIB_2D_POLICY_H_

#include <TktkMath/Vector2.h>

namespace tktk
{
	// Dxlib���g����2D�̃v���O�����𓮂������߂̃|���V�[
	class Dxlib2DPolicy
	{
	public:

		Dxlib2DPolicy(
			const Vector2& gameScreenSize,	// �Q�[���E�B���h�E�̑傫��
			bool fullScreenFlag				// �t���X�N���[���ɂ��邩
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
	};
}

#endif // !DXLIB_2D_POLICY_H_

