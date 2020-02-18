#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include <string>
#include "Asset/PixelShaderData.h"
#include "Asset/SystemPixelShaderId.h"

namespace tktk
{
	// �uPixelShaderManager�v�̎����̈ꕔ���B�����߂̃N���X
	class PixelShader
	{
	public:

		// �V���ȃs�N�Z���V�F�[�_�[�����[�h����
		// �����̊֐��ŃV�F�[�_�[�����[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void load(int id, int useConstantBufferId, const std::string& fileName);

		// �w�肵���s�N�Z���V�F�[�_�[���폜����
		// �����̊֐��ŃV�F�[�_�[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���s�N�Z���V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const PixelShaderData& getData(int id);
	};
}
#endif // !PIXEL_SHADER_H_
