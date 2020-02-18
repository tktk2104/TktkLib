#ifndef MMD_TYPES_H_
#define MMD_TYPES_H_

#include <vector>

// MMD関連ファイルデータ型
namespace mmd {

//　基本データ型
typedef	unsigned char		byte;
typedef	unsigned short		ushort;
typedef	unsigned int		uint;

// パディングを無効にする
#pragma pack(1)

struct float2 {
	float x = 0.0f;
	float y = 0.0f;
};

struct float3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

struct float4 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;
};

#pragma pack()

namespace pmd {

// パディングを無効にする
#pragma pack(1)

// ヘッダ
struct Header {
	char	pmd[3];				// "Pmd"
	float	version;			// 1.0
	char	name[20];			// モデル名
	char	comment[256];		// コメント
};

// 頂点データ
struct Vertex {
	float3	pos;				// 頂点座標
	float3	normal;				// 法線ベクトル
	float2	uv;					// テクスチャ座標
	ushort	bone[2];			// ボーンインデックス
	byte	weight;				// 頂点ウェイト [0,100]. bone1: weight, bone2: (100-weight);
	byte	edge;				// エッジフラグ 0: on, 1: off
};

// マテリアルデータ
struct Material {
	float4	diffuse;
	float	specularity;
	float3	specular;
	float3	ambient;
	byte	toon_index;
	byte	edge_flag;
	uint	vertex_count;
	char	texture_filename[20];
};

// ボーンデータ
struct Bone {
	char	bone_name[20];
	ushort	parent_bone_index;		// root=0xFFFF
	ushort	tail_bone_index;		// tail=0xFFFF
	byte	bone_type;				// 0:rot, 1:rot+trans, 2:IK, 3:?, 4:AffectedbyIK,
									// 5:AfftectedByRot, 6:IKTarget, 7:Invisible
									// ver4.0~ 8:twist, 9:rot
	ushort	ik_parent_bone_index;	// NoIK=0
	float3	bone_pos;
};

// ボーン表示枠名
struct BoneDispName {
	char	disp_name[50];
};

// ボーン表示枠
struct BoneDisp {
	ushort	bone_index;				// 枠用ボーン番号
	byte	bone_disp_frame_index;	// 表示枠番号 // センター:00 他の表示枠:01～ // センター枠にセンター(index 0)以外のボーンを指定しても表示されません。
};

// IKデータ
struct IK {
	// 11 + 2 * chain_length bytes
	ushort	bone_index;
	ushort	target_bone_index;
	byte	chain_length;
	ushort	iterations;
	float	weight;
	// unsigned short  child_bone_indices[]; // len=chain_length
};

// 頂点モーフデータ
struct MorphVertex {
	uint	vertex_index;
	float3	pos;
};

// モーフデータ
struct Morph {
	char	name[20];
	uint	vertex_count;
	byte	type;
	// PMDMorphVertex  vertices[];   // len = vertex_count;
};

#pragma pack()

// ボーン表示枠名リスト
typedef std::vector<BoneDispName>	BoneNameList;

// ボーン表示枠リスト
typedef std::vector<BoneDisp>		BoneFrameList;

// ボーン枠表示データ
struct BoneFrame {
	BoneNameList	names;
	BoneFrameList	list;
};

// 頂点配列
typedef std::vector<Vertex>		Vertices;

// 頂点インデックス配列
typedef std::vector<ushort>		Indices;

// マテリアル配列
typedef std::vector<Material>	Materials;

// メッシュデータ
struct Mesh {
	Vertices	vertices;
	Indices		indices;
	Materials	materials;
};

// ボーン配列
typedef std::vector<Bone>		Bones;

// スケルトンデータ
struct Skeleton {
	Bones		bones;
};

// PMDファイル
struct PMDFile {
	Header		header;
	Mesh		mesh;
	Skeleton	skeleton;
	BoneFrame	bone_frame;
};

} // namespace pmd


// VMDファイルデータ
namespace vmd {

#pragma pack(1)

struct Header {
	char	version[30];
	char	name[20];
};

struct Motion {
	char	bone_name[15];
	uint	frame_no;
	float3	location;
	float4	rotation;               // quaternion
	byte	interpolation[4][4][4];
};

struct Morph {
	char	morph_name[15];
	uint	frame_no;
	float	weight;
};

struct Camera {
	uint	frame_no;
	float	length;
	float3	location;
	float3	rotation;
	byte	interpolation[4][4][4];
	uint	viewing_angle;
	byte	perspective;
};

struct Light {
	uint	frame_no;
	float3	rgb;
	float3	location;
};

struct SelfShadow {
	uint	frame_no;
	byte	mode; // 00-02
	float	distance;     // 0.1 - (dist * 0.000001)
};

struct IK {
	char ik_bone_name[20];		// IKボーン名
	unsigned char ik_enabled;	// IK有効 // 0:off 1:on
};

#pragma pack()

// IKデータリスト
typedef std::vector<IK>			IKList;

// 表示・IKデータ
struct VisibleIK {
	int				frame_no;	// フレーム番号
	unsigned char	visible;	// 表示 // 0:off 1:on
	IKList			ik_list;	// IKデータリスト
};

// モーションデータ配列
typedef	std::vector<Motion>		Motions;

// モーフデータ配列
typedef std::vector<Morph>		Morphs;

// カメラデータ配列
typedef std::vector<Camera>		Cameras;

// ライトデータ配列
typedef std::vector<Light>		Lights;

// セルフシャドウデータ配列
typedef std::vector<SelfShadow>	SelfShadows;

// 表示・IKデータ配列
typedef std::vector<VisibleIK>	VisibleIKs;

// VMDファイル
struct VMDFile {
	Header		header;
	Motions		motions;
	Morphs		morphs;
	Cameras		cameras;
	Lights		lights;
	SelfShadows	self_shadows;
	VisibleIKs	visible_ik;
};

// VMDファイル配列
typedef std::vector<mmd::vmd::VMDFile> VMDFiles;

} // namespace vmd

// PMXファイルデータ
namespace pmx {

// テキストバッファ
typedef std::vector<byte>	TextBuf;

// ファイルヘッダ
struct Header {
	byte	pmx[4] = { 'P', 'M', 'X', ' ' };	// "PMX "
	float	version = 2.0f;						// バージョン
	byte	encode = 0;							// エンコード形式(0:UTF16 1 : UTF8)
	byte	uv_ex_count = 0;					// 追加UV数
	byte	vertex_index_size = 4;				// 頂点Indexサイズ
	byte	texture_index_size = 4;				// テクスチャIndexサイズ
	byte	material_index_size = 4;			// 材質Indexサイズ
	byte	bone_index_size = 4;				// ボーンIndexサイズ
	byte	morph_index_size = 4;				// モーフIndexサイズ
	byte	rigid_body_index_size = 4;			// 剛体Indexサイズ
};

// モデル情報
struct ModelInfo {
	TextBuf	model_name;			// モデル名
	TextBuf	model_name_eng;		// モデル名英
	TextBuf	comment;			// コメント
	TextBuf	comment_eng;		// コメント英
};

// 頂点ウェイト
struct BDEF1 {
	int			bone = -1;
};

struct BDEF2  {
	int			bone[2] = { -1, -1 };
	float		weight = 0.0f;
};

struct BDEF4 {
	int			bone[4] = { -1, -1, -1, -1 };
	float		weight[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
};

struct SDEF {
	BDEF2		bdef2;
	float3		c;
	float3		r0;
	float3		r1;
};

struct QDEF {
	int			bone[4] = { -1, -1, -1, -1 };
	float		weight[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
};

struct BlendWeight {
	byte		format = 0;
	BDEF1		bdef1;
	BDEF2		bdef2;
	BDEF4		bdef4;
	SDEF		sdef;
	QDEF		qdef;
	// フォーマット情報
	static const byte BDEF1 = 0;
	static const byte BDEF2 = 1;
	static const byte BDEF4 = 2;
	static const byte SDEF  = 3;
	static const byte QDEF  = 4;
};

// 頂点
struct Vertex {
	float3		point;			// 位置(x,y,z)
	float3		normal;			// 法線(x,y,z)
	float2		uv;				// UV(u,v)
	float4		uv_ex[4];		// 追加uv(最大4)
	BlendWeight	weight;			// ウェイト
	float		edge = 1.0f;	// エッジ倍率
};

// テクスチャ
typedef std::vector<TextBuf>	Textures;

// 材質
struct Material {
	TextBuf		name;
	TextBuf		name_eng;
	float4		diffuse;
	float3		specular;
	float		specularity = 0.0;
	float3		ambient;
	byte		flag = 0;
	float4		edge_color;
	float		edge_size = 0.0f;
	int			texture_index = -1;
	int			sphere_texture_index = -1;
	byte		sphere_mode = 0;
	byte		toon_flag = 0;
	int			toon_texture_index = -1;
	TextBuf		memo;
	int			vertex_count = 0;
};

// IKリンク情報
struct IKlink {
	int			bone_index = -1;
	byte		angle_consraint = 0;
	float3		angle_min;
	float3		angle_max;
};

// IKリンク配列
typedef std::vector<IKlink> IKlinks;

// IK
struct IK {
	int			bone = -1;
	int			loop_count = 0;
	float		angle = 0.0;
	IKlinks		links;
};

// ボーン
struct Bone {
	TextBuf		name;
	TextBuf		name_eng;
	float3		position;
	int			parent_index = -1;
	int			morph_layer = 0;
	ushort		flag = 0;
	float3		offset;
	int			connected_bone_index = -1;
	int			grant_parent_index = -1;
	float		grant_weight = 0.0f;
	float3		axis;
	float3		axis_x;
	float3		axis_z;
	int			key = 0;
	IK			ik;
	// ボーンフラグ
	static const ushort CONECTED_BONE_FLAG   = 0x0001; // 接続先(PMD子ボーン指定)表示方法 -> 0 : 座標オフセットで指定 1 : ボーンで指定
	static const ushort ROTATE_FLAG          = 0x0002; // 回転可能
	static const ushort TRANSLATE_FLAG       = 0x0004; // 移動可能
	static const ushort VISBLE_FLAG          = 0x0008; // 表示
	static const ushort CONTROL_FLAG         = 0x0010; // 操作可
	static const ushort IK_FLAG              = 0x0020; // IK
	static const ushort ADD_LOCAL_FLAG       = 0x0080; // ローカル付与 | 付与対象 0 : ユーザー変形値／IKリンク／多重付与 1 : 親のローカル変形量
	static const ushort ADD_ROTATE_FLAG      = 0x0100; // 回転付与
	static const ushort ADD_TRANSLATE_FLAG   = 0x0200; // 移動付与
	static const ushort FIXED_AXIS_FLAG      = 0x0400; // 軸固定
	static const ushort LOCAL_AXIS_FLAG      = 0x0800; // ローカル軸
	static const ushort PYSICS_MORPH_FLAG    = 0x1000; // 物理後変形
	static const ushort EXTERNAL_PARENT_FLAG = 0x2000; // 外部親変形
};

// 頂点モーフ
struct MorphVertex {
	int		index;
	float3	position_offset;
};

// UVモーフ
struct MorphUV {
	int		index;
	float4	uv_offset;
};

// ボーンモーフ
struct MorphBone {
	int		index;
	float3	translation;
	float4	rotation;
};

// 材質モーフ
struct MorphMaterial {
	int		index;
	byte	operation;
	float4	diffuse;
	float3	specular;
	float	specularity;
	float3	ambient;
	float4	edge_color;
	float	edge_size;
	float4	texture;
	float4	sphere_texture;
	float4	toon_texture;
};

// グループモーフ
struct MorphGroup {
	int		index;
	float	weight;
};

// フリップモーフ
struct MorphFlip {
	int		index;
	float	value;
};

// インパルスモーフ
struct MorphImplus {
	int		index;
	byte	is_local;
	float3	velocity;
	float3	angular_torque;
};

typedef std::vector<MorphVertex>	MorphVertices;
typedef std::vector<MorphUV>		MorphUVs;
typedef std::vector<MorphBone>		MorphBones;
typedef std::vector<MorphMaterial>	MorphMaterials;
typedef std::vector<MorphGroup>		MorphGroups;
typedef std::vector<MorphFlip>		MorphFlips;
typedef std::vector<MorphImplus>	MorphImpluses;

// モーフ
struct Morph {
	TextBuf			name;
	TextBuf			name_eng;
	byte			category;
	byte			type;
	MorphVertices	vertex;
	MorphUVs		uv;
	MorphBones		bone;
	MorphMaterials	material;
	MorphGroups		group;
	MorphFlips		flip;
	MorphImpluses	implus;
	static const byte TYPE_GROUP     = 0;
	static const byte TYPE_VERTEX    = 1;
	static const byte TYPE_BONE      = 2;
	static const byte TYPE_UV        = 3;
	static const byte TYPE_EX_UV1    = 4;
	static const byte TYPE_EX_UV2    = 5;
	static const byte TYPE_EX_UV3    = 6;
	static const byte TYPE_EX_UV4    = 7;
	static const byte TYPE_MATERIAL  = 8;
	static const byte TYPE_FLIP      = 9;
	static const byte TYPE_IMPULS    = 10;
};

typedef std::vector<Morph>	Morphs;

// 表示枠要素
struct FrameElement {
	byte	type = 0;	// ボーン or モーフ
	int		index = 0;	// インデックス
};

typedef std::vector<FrameElement> FrameElements;

// 表示枠
struct Frame {
	TextBuf			name;
	TextBuf			name_eng;
	byte			flag = 0;
	FrameElements	elements;
};

// 頂点データ配列
typedef std::vector<Vertex> Vertices;

// 頂点インデックスデータ配列
typedef std::vector<int> Indices;

// マテリアル配列
typedef std::vector<Material> Materials;

// ボーン配列
typedef std::vector<Bone> Skeleton;

// 表示枠配列
typedef std::vector<Frame> Frames;

// メッシュデータ
struct Mesh
{
	Vertices	vertices;
	Indices		indices;
	Textures	texture;
	Materials	materials;
};

// PMX File
struct PMXFile {
	Header		header;
	ModelInfo	model_info;
	Mesh		mesh;
	Skeleton	skeleton;
	Morphs		morphs;
	Frames		frames;
};

} // namespace pmx

} // namespace mmd

// end of file

#endif
