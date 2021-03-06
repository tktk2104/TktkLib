#ifndef BASIC_MESH_LOAD_PMD_RETURN_VALUE_H_
#define BASIC_MESH_LOAD_PMD_RETURN_VALUE_H_

namespace tktk
{
	// pmdファイルを読み込んだ結果の値
	struct BasicMeshLoadPmdReturnValue
	{
		// 一番最後に作成した通常メッシュのディスクリプタヒープのID
		unsigned int createDescriptorHeapIdEndNum;

		// 一番最後に作成した通常メッシュマテリアルのID
		unsigned int createBasicMeshMaterialIdEndNum;

		// 一番最後に作成したテクスチャのID
		unsigned int createTextureIdEndNum;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_RETURN_VALUE_H_
