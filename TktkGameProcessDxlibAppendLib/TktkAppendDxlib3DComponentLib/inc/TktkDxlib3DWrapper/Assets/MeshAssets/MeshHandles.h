#ifndef MESH_HANDLES_H_
#define MESH_HANDLES_H_

#include <vector>

namespace tktk
{
	// ���b�V���ƑΉ�����A�j���[�V�����𓯎��Ɋi�[����\����
	struct MeshHandles
	{
	public:

		// ���b�V���ƑΉ�����A�j���[�V�������A�����[�h����
		void unLoadMesh() const;

	public:

		// ���b�V���{�̂̃n���h��
		int meshHandle{ -1 };

		// ���b�V���ɑΉ�����A�j���[�V�����̃n���h��
		std::vector<int> animHandles;
	};
}
#endif // !MESH_HANDLES_H_