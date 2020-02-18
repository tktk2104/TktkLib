#ifndef PMX_FILE_READER_H_
#define PMX_FILE_READER_H_

#include "MMDTypes.h"
#include <fstream>
#include "string_convertor.h"

namespace mmd { namespace pmx {

// PMXファイルリーダー
class PMXFileReader {
public:
	// コンストラクタ
	PMXFileReader(PMXFile& pmx) : pmx_(&pmx) {
	}
	// PMXファイルの読み込み
	void read(const std::string& fileName) {
		std::ifstream in(fileName, std::ios::binary);
		read(in, *pmx_);
	}

private:
	// 読み込み
	template <typename T>
	void read(std::istream& in, T& result) {
		in.read((char*)&result, sizeof(T));
	}
	// ベクタに読み込み
	template <typename T>
	void read(std::istream& in, std::vector<T>& result) {
		uint size = 0;
		read(in, size);
		result.resize(size);
		for (auto& element : result) {
			read(in, element);
		}
	}
	// 頂点データの読み込み
	void read(std::istream& in, Vertex& result) {
		read(in, result.point);
		read(in, result.normal);
		read(in, result.uv);
		for (int i = 0; i < pmx_->header.uv_ex_count; ++i) {
			read(in, result.uv_ex[i]);
		}
		read(in, result.weight);
		read(in, result.edge);
	}
	// 頂点ウェイトの読み込み
	void read(std::istream& in, BlendWeight& result) {
		read(in, result.format);
		if (result.format == BlendWeight::BDEF1) {
			read(in, result.bdef1);
		} else if (result.format == BlendWeight::BDEF2) {
			read(in, result.bdef2);
		} else if (result.format == BlendWeight::BDEF4) {
			read(in, result.bdef4);
		} else if (result.format == BlendWeight::SDEF) {
			read(in, result.sdef);
		} else if (result.format == BlendWeight::QDEF) {
			read(in, result.qdef);
		}
	}
	// BDEF1の読み込み
	void read(std::istream& in, BDEF1& result) {
		read_bone_index(in, result.bone);
	}
	// BDEF2の読み込み
	void read(std::istream& in, BDEF2& result) {
		read_bone_index(in, result.bone[0]);
		read_bone_index(in, result.bone[1]);
		read(in, result.weight);
	}
	// BDEF4の読み込み
	void read(std::istream& in, BDEF4& result) {
		read_bone_index(in, result.bone[0]);
		read_bone_index(in, result.bone[1]);
		read_bone_index(in, result.bone[2]);
		read_bone_index(in, result.bone[3]);
		read(in, result.weight[0]);
		read(in, result.weight[1]);
		read(in, result.weight[2]);
		read(in, result.weight[3]);
	}
	// SDEFの読み込み
	void read(std::istream& in, SDEF& result) {
		read(in, result.bdef2);
		read(in, result.c);
		read(in, result.r0);
		read(in, result.r1);
	}
	// QDEFの読み込み
	void read(std::istream& in, QDEF& result) {
		read_bone_index(in, result.bone[0]);
		read_bone_index(in, result.bone[1]);
		read_bone_index(in, result.bone[2]);
		read_bone_index(in, result.bone[3]);
		read(in, result.weight[0]);
		read(in, result.weight[1]);
		read(in, result.weight[2]);
		read(in, result.weight[3]);
	}
	// マテリアルデータの読み込み
	void read(std::istream& in, Material& result) {
		read(in, result.name);
		read(in, result.name_eng);
		read(in, result.diffuse);
		read(in, result.specular);
		read(in, result.specularity);
		read(in, result.ambient);
		read(in, result.flag);
		read(in, result.edge_color);
		read(in, result.edge_size);
		read_texture_index(in, result.texture_index);
		read_texture_index(in, result.sphere_texture_index);
		read(in, result.sphere_mode);
		read(in, result.toon_flag);
		if (result.toon_flag == 1) {
			char toon_texture_index = 0;
			read(in, toon_texture_index);
			result.toon_texture_index = toon_texture_index;
		} else {
			read_texture_index(in, result.toon_texture_index);
		}
		read(in, result.memo);
		read(in, result.vertex_count);
	}
	// ボーンデータの読み込み
	void read(std::istream& in, Bone& result) {
		read(in, result.name);
		read(in, result.name_eng);
		read(in, result.position);
		read_bone_index(in, result.parent_index);
		read(in, result.morph_layer);
		read(in, result.flag);
		if ((result.flag & Bone::CONECTED_BONE_FLAG) == 0) {
			read(in, result.offset);
		} else {
			read_bone_index(in, result.connected_bone_index);
		}
		if ((result.flag & (Bone::ADD_ROTATE_FLAG | Bone::ADD_TRANSLATE_FLAG)) != 0) {
			read_bone_index(in, result.grant_parent_index);
			read(in, result.grant_weight);
		}
		if ((result.flag & Bone::FIXED_AXIS_FLAG) != 0) {
			read(in, result.axis);
		}
		if ((result.flag & Bone::LOCAL_AXIS_FLAG) != 0) {
			read(in, result.axis_x);
			read(in, result.axis_z);
		}
		if ((result.flag & Bone::EXTERNAL_PARENT_FLAG) != 0) {
			read(in, result.key);
		}
		if ((result.flag & Bone::IK_FLAG) != 0) {
			read(in, result.ik);
		}
	}
	// IKデータの読み込み
	void read(std::istream& in, IK& result) {
		read_bone_index(in, result.bone);
		read(in, result.loop_count);
		read(in, result.angle);
		read(in, result.links);
	}
	// IKリンクデータの読み込み
	void read(std::istream& in, IKlink& result) {
		read_bone_index(in, result.bone_index);
		read(in, result.angle_consraint);
		if (result.angle_consraint == 1) {
			read(in, result.angle_min);
			read(in, result.angle_max);
		}
	}
	// ヘッダデータの読み込み
	void read(std::istream& in, Header& result) {
		in.read((char*)&result.pmx[0], sizeof(result.pmx));
		read(in, result.version);
		byte info_size = 0;
		read(in, info_size);
		std::vector<byte> info(info_size);
		in.read((char*)&info[0], info.size());
		result.encode                = info[0];
		result.uv_ex_count           = info[1];			
		result.vertex_index_size     = info[2];		
		result.texture_index_size    = info[3];	
		result.material_index_size   = info[4];	
		result.bone_index_size       = info[5];		
		result.morph_index_size      = info[6];		
		result.rigid_body_index_size = info[7];
	}
	// モデル情報の読み込み
	void read(std::istream& in, ModelInfo& result) {
		read(in, result.model_name);
		read(in, result.model_name_eng);
		read(in, result.comment);
		read(in, result.comment_eng);
	}
	// メッシュの読み込み
	void read(std::istream& in, Mesh& result) {
		read(in, result.vertices);
		read_indices(in, result.indices);
		read(in, result.texture);
		read(in, result.materials);
	}
	// 頂点インデックスデータの読み込み
	void read_indices(std::istream& in, Indices& result) {
		uint size = 0;
		read(in, size);
		result.resize(size);
		for (auto& element: result) {
			read_vertex_index(in, element);
		}
	}
	// 頂点モーフの読み込み
	void read(std::istream& in, MorphVertex& result) {
		read_vertex_index(in, result.index);
		read(in, result.position_offset);
	}
	// UVモーフの読み込み
	void read(std::istream& in, MorphUV& result) {
		read_vertex_index(in, result.index);
		read(in, result.uv_offset);
	}
	// ボーンモーフの読み込み
	void read(std::istream& in, MorphBone& result) {
		read_bone_index(in, result.index);
		read(in, result.translation);
		read(in, result.rotation);
	}
	// 材質モーフの読み込み
	void read(std::istream& in, MorphMaterial& result) {
		read_material_index(in, result.index);
		read(in, result.operation);
		read(in, result.diffuse);
		read(in, result.specular);
		read(in, result.specularity);
		read(in, result.ambient);
		read(in, result.edge_color);
		read(in, result.edge_size);
		read(in, result.texture);
		read(in, result.sphere_texture);
		read(in, result.toon_texture);
	}
	// グループモーフの読み込み
	void read(std::istream& in, MorphGroup& result) {
		read_morph_index(in, result.index);
		read(in, result.weight);
	}
	// フリップモーフの読み込み
	void read(std::istream& in, MorphFlip& result) {
		read_morph_index(in, result.index);
		read(in, result.value);
	}
	// インパルスモーフの読み込み
	void read(std::istream& in, MorphImplus& result) {
		read_rigid_body_index(in, result.index);
		read(in, result.is_local);
		read(in, result.velocity);
		read(in, result.angular_torque);
	}
	// モーフの読み込み
	void read(std::istream& in, Morph& result) {
		read(in, result.name);
		read(in, result.name_eng);
		read(in, result.category);
		read(in, result.type);
		switch (result.type) {
		case Morph::TYPE_GROUP:    read(in, result.group);    break;
		case Morph::TYPE_VERTEX:   read(in, result.vertex);   break;
		case Morph::TYPE_BONE:     read(in, result.bone);     break;
		case Morph::TYPE_MATERIAL: read(in, result.material); break;
		case Morph::TYPE_UV:       read(in, result.uv);       break;
		case Morph::TYPE_EX_UV1:   read(in, result.uv);       break;
		case Morph::TYPE_EX_UV2:   read(in, result.uv);       break;
		case Morph::TYPE_EX_UV3:   read(in, result.uv);       break;
		case Morph::TYPE_EX_UV4:   read(in, result.uv);       break;
		case Morph::TYPE_FLIP:	   read(in, result.flip);     break;
		case Morph::TYPE_IMPULS:   read(in, result.implus);   break;
		}
	}
	// 表示枠の要素の読み込み
	void read(std::istream& in, FrameElement& result) {
		read(in, result.type);
		if (result.type == 0) {
			read_bone_index(in, result.index);
		} else {
			read_morph_index(in, result.index);
		}
	}
	// 表示枠の読み込み
	void read(std::istream& in, Frame& result) {
		read(in, result.name);
		read(in, result.name_eng);
		read(in, result.flag);
		read(in, result.elements);
	}
	// PMXファイルの読み込み
	void read(std::istream& in, PMXFile& result) {
		read(in, result.header);
		read(in, result.model_info);
		read(in, result.mesh);
		read(in, result.skeleton);
		read(in, result.morphs);
		read(in, result.frames);
		// 剛体 (未対応)
		// ジョイント (未対応)
	}
	// インデックスデータの読み込み
	void read_index(std::istream& in, int& result, std::size_t size_byte) {
		if (size_byte == 1) {
			char index = 0;
			read(in, index);
			result = index;
		}
		else if (size_byte == 2) {
			short index = 0;
			read(in, index);
			result = index;
		}
		else if (size_byte == 4) {
			int index = 0;
			read(in, index);
			result = index;
		}
	}
	// 頂点インデックスデータの読み込み
	void read_vertex_index(std::istream& in, int& result) {
		if (pmx_->header.vertex_index_size == 1) {
			unsigned char index = 0;
			read(in, index);
			result = index;
		}
		else if (pmx_->header.vertex_index_size == 2) {
			unsigned short index = 0;
			read(in, index);
			result = index;
		}
		else if (pmx_->header.vertex_index_size == 4) {
			int index = 0;
			read(in, index);
			result = index;
		}
	}
	// テクスチャインデックスデータの読み込み
	void read_texture_index(std::istream& in, int& result) {
		read_index(in, result, pmx_->header.texture_index_size);
	}
	// 材質インデックスデータの読み込み
	void read_material_index(std::istream& in, int& result) {
		read_index(in, result, pmx_->header.material_index_size);
	}
	// ボーンインデックスデータの読み込み
	void read_bone_index(std::istream& in, int& result) {
		read_index(in, result, pmx_->header.bone_index_size);
	}
	// モーフインデックスデータの読み込み
	void read_morph_index(std::istream& in, int& result) {
		read_index(in, result, pmx_->header.morph_index_size);
	}
	// 剛体インデックスデータの読み込み
	void read_rigid_body_index(std::istream& in, int& result) {
		read_index(in, result, pmx_->header.rigid_body_index_size);
	}

private:
	// PMXファイル
	PMXFile* pmx_;
};

} } // namespace mmd::pmx

#endif

// end of file
