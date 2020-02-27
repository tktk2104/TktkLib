#ifndef CONSTANT_BUFFER_ASSETS_H_
#define CONSTANT_BUFFER_ASSETS_H_

#include <unordered_map>
#include "ConstantBufferData.h"

namespace tktk
{
	// �uConstantBufferData�v���Ǘ�����N���X
	class ConstantBufferAssets
	{
	public:

		ConstantBufferAssets() = default;
		~ConstantBufferAssets();

		ConstantBufferAssets(const ConstantBufferAssets& other) = delete;
		ConstantBufferAssets& operator = (const ConstantBufferAssets& other) = delete;

	public:

		// �V���Ȓ萔�o�b�t�@���쐬����
		template<class BufferDataType>
		void create(int id, BufferDataType* data);

		// �w�肵���萔�o�b�t�@���폜����
		void erase(int id);

		// �S�Ă̒萔�o�b�t�@���폜����
		void clear();

		// �w�肵���萔�o�b�t�@���Ǘ�����N���X�̃|�C���^���擾����
		ConstantBufferData* getDataPtr(int id);

		// �w�肵���萔�o�b�t�@�ɓ����\��̃f�[�^�̓���̒l�ɃA�N�Z�X���邽�߂̐ݒ���s��
		void addParamLocation(int id, int locationType, unsigned int locationFromBufferTop);

	private:

		// �萔�o�b�t�@���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, ConstantBufferData> m_assets;
	};

	// �V���Ȓ萔�o�b�t�@���쐬����i�e���v���[�g�g�p�Łj
	template<class BufferDataType>
	inline void ConstantBufferAssets::create(int id, BufferDataType* data)
	{
		erase(id);

		m_assets.emplace(id, data);
	}
}
#endif // !CONSTANT_BUFFER_ASSETS_H_