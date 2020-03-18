#ifndef DIRECTX_11_POLICY_H_
#define DIRECTX_11_POLICY_H_

#include <string>
#include <TktkMath/Vector2.h>
#include "TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	class DirectX11Policy
	{
	public:

		DirectX11Policy(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string & windowName,
			const Vector2& gameScreenSize,						// �Q�[���E�B���h�E�̑傫��
			bool fullScreenFlag,								// �t���X�N���[���ɂ��邩
			const std::string& tktkLibResFolderPath = ""		// ���C�u�����Ŏg�p���郊�\�[�X�̃t�H���_�̃p�X
		);

	public:

		bool isDestroy() const;

	private:

		void setUpdatePriority();
	};
}
#endif // !DIRECTX_11_POLICY_H_