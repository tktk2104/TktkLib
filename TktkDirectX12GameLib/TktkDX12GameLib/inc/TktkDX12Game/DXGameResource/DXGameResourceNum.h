#ifndef DX_GAME_RESOURCE_NUM_H_
#define DX_GAME_RESOURCE_NUM_H_

namespace tktk
{
	// �Q�[���Ŏg�p����\�ʓI�ȃ��\�[�X�̐�
	struct DXGameResourceNum
	{
		// �V�[����
		unsigned int sceneNum				{};

		// �T�E���h��
		unsigned int soundNum				{};

		// �X�v���C�g�}�e���A����
		unsigned int spriteNum				{};

		// �ʏ탁�b�V����
		unsigned int basicMeshNum			{};

		// �ʏ탁�b�V���}�e���A����
		unsigned int basicMeshMaterialNum	{};

		// �X�P���g���f�[�^��
		unsigned int skeletonNum			{};

		// ���[�V�����f�[�^��
		unsigned int motionNum				{};

		// �|�X�g�G�t�F�N�g�}�e���A����
		unsigned int postEffectMaterialNum	{};

		// �J������
		unsigned int cameraNum				{};

		// ���C�g��
		unsigned int lightNum				{};
	};
}
#endif // !DX_GAME_RESOURCE_NUM_H_