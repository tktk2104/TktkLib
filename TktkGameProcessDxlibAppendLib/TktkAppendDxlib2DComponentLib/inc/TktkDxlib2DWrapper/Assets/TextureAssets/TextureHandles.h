#ifndef TEXTURE_HANDLES_H_
#define TEXTURE_HANDLES_H_

#include <vector>

namespace tktk
{
	// �����H�摜�ƕ����摜�̃n���h�����i�[����\����
	struct TextureHandles
	{
	public:

		// �����H�摜�ƕ����摜�̃n���h�����A�����[�h����
		void unLoadTexture() const;

	public:

		// �����H�摜�̃n���h��
		int textureHandle{ -1 };

		// ���������摜�̃n���h���̃��X�g
		std::vector<int> splitTextureHandles;
	};
}
#endif // !TEXTURE_HANDLES_H_