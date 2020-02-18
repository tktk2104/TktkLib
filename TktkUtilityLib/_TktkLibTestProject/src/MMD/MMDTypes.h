#ifndef MMD_TYPES_H_
#define MMD_TYPES_H_

#include <vector>

// MMD�֘A�t�@�C���f�[�^�^
namespace mmd {

//�@��{�f�[�^�^
typedef	unsigned char		byte;
typedef	unsigned short		ushort;
typedef	unsigned int		uint;

// �p�f�B���O�𖳌��ɂ���
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

// �p�f�B���O�𖳌��ɂ���
#pragma pack(1)

// �w�b�_
struct Header {
	char	pmd[3];				// "Pmd"
	float	version;			// 1.0
	char	name[20];			// ���f����
	char	comment[256];		// �R�����g
};

// ���_�f�[�^
struct Vertex {
	float3	pos;				// ���_���W
	float3	normal;				// �@���x�N�g��
	float2	uv;					// �e�N�X�`�����W
	ushort	bone[2];			// �{�[���C���f�b�N�X
	byte	weight;				// ���_�E�F�C�g [0,100]. bone1: weight, bone2: (100-weight);
	byte	edge;				// �G�b�W�t���O 0: on, 1: off
};

// �}�e���A���f�[�^
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

// �{�[���f�[�^
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

// �{�[���\���g��
struct BoneDispName {
	char	disp_name[50];
};

// �{�[���\���g
struct BoneDisp {
	ushort	bone_index;				// �g�p�{�[���ԍ�
	byte	bone_disp_frame_index;	// �\���g�ԍ� // �Z���^�[:00 ���̕\���g:01�` // �Z���^�[�g�ɃZ���^�[(index 0)�ȊO�̃{�[�����w�肵�Ă��\������܂���B
};

// IK�f�[�^
struct IK {
	// 11 + 2 * chain_length bytes
	ushort	bone_index;
	ushort	target_bone_index;
	byte	chain_length;
	ushort	iterations;
	float	weight;
	// unsigned short  child_bone_indices[]; // len=chain_length
};

// ���_���[�t�f�[�^
struct MorphVertex {
	uint	vertex_index;
	float3	pos;
};

// ���[�t�f�[�^
struct Morph {
	char	name[20];
	uint	vertex_count;
	byte	type;
	// PMDMorphVertex  vertices[];   // len = vertex_count;
};

#pragma pack()

// �{�[���\���g�����X�g
typedef std::vector<BoneDispName>	BoneNameList;

// �{�[���\���g���X�g
typedef std::vector<BoneDisp>		BoneFrameList;

// �{�[���g�\���f�[�^
struct BoneFrame {
	BoneNameList	names;
	BoneFrameList	list;
};

// ���_�z��
typedef std::vector<Vertex>		Vertices;

// ���_�C���f�b�N�X�z��
typedef std::vector<ushort>		Indices;

// �}�e���A���z��
typedef std::vector<Material>	Materials;

// ���b�V���f�[�^
struct Mesh {
	Vertices	vertices;
	Indices		indices;
	Materials	materials;
};

// �{�[���z��
typedef std::vector<Bone>		Bones;

// �X�P���g���f�[�^
struct Skeleton {
	Bones		bones;
};

// PMD�t�@�C��
struct PMDFile {
	Header		header;
	Mesh		mesh;
	Skeleton	skeleton;
	BoneFrame	bone_frame;
};

} // namespace pmd


// VMD�t�@�C���f�[�^
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
	char ik_bone_name[20];		// IK�{�[����
	unsigned char ik_enabled;	// IK�L�� // 0:off 1:on
};

#pragma pack()

// IK�f�[�^���X�g
typedef std::vector<IK>			IKList;

// �\���EIK�f�[�^
struct VisibleIK {
	int				frame_no;	// �t���[���ԍ�
	unsigned char	visible;	// �\�� // 0:off 1:on
	IKList			ik_list;	// IK�f�[�^���X�g
};

// ���[�V�����f�[�^�z��
typedef	std::vector<Motion>		Motions;

// ���[�t�f�[�^�z��
typedef std::vector<Morph>		Morphs;

// �J�����f�[�^�z��
typedef std::vector<Camera>		Cameras;

// ���C�g�f�[�^�z��
typedef std::vector<Light>		Lights;

// �Z���t�V���h�E�f�[�^�z��
typedef std::vector<SelfShadow>	SelfShadows;

// �\���EIK�f�[�^�z��
typedef std::vector<VisibleIK>	VisibleIKs;

// VMD�t�@�C��
struct VMDFile {
	Header		header;
	Motions		motions;
	Morphs		morphs;
	Cameras		cameras;
	Lights		lights;
	SelfShadows	self_shadows;
	VisibleIKs	visible_ik;
};

// VMD�t�@�C���z��
typedef std::vector<mmd::vmd::VMDFile> VMDFiles;

} // namespace vmd

// PMX�t�@�C���f�[�^
namespace pmx {

// �e�L�X�g�o�b�t�@
typedef std::vector<byte>	TextBuf;

// �t�@�C���w�b�_
struct Header {
	byte	pmx[4] = { 'P', 'M', 'X', ' ' };	// "PMX "
	float	version = 2.0f;						// �o�[�W����
	byte	encode = 0;							// �G���R�[�h�`��(0:UTF16 1 : UTF8)
	byte	uv_ex_count = 0;					// �ǉ�UV��
	byte	vertex_index_size = 4;				// ���_Index�T�C�Y
	byte	texture_index_size = 4;				// �e�N�X�`��Index�T�C�Y
	byte	material_index_size = 4;			// �ގ�Index�T�C�Y
	byte	bone_index_size = 4;				// �{�[��Index�T�C�Y
	byte	morph_index_size = 4;				// ���[�tIndex�T�C�Y
	byte	rigid_body_index_size = 4;			// ����Index�T�C�Y
};

// ���f�����
struct ModelInfo {
	TextBuf	model_name;			// ���f����
	TextBuf	model_name_eng;		// ���f�����p
	TextBuf	comment;			// �R�����g
	TextBuf	comment_eng;		// �R�����g�p
};

// ���_�E�F�C�g
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
	// �t�H�[�}�b�g���
	static const byte BDEF1 = 0;
	static const byte BDEF2 = 1;
	static const byte BDEF4 = 2;
	static const byte SDEF  = 3;
	static const byte QDEF  = 4;
};

// ���_
struct Vertex {
	float3		point;			// �ʒu(x,y,z)
	float3		normal;			// �@��(x,y,z)
	float2		uv;				// UV(u,v)
	float4		uv_ex[4];		// �ǉ�uv(�ő�4)
	BlendWeight	weight;			// �E�F�C�g
	float		edge = 1.0f;	// �G�b�W�{��
};

// �e�N�X�`��
typedef std::vector<TextBuf>	Textures;

// �ގ�
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

// IK�����N���
struct IKlink {
	int			bone_index = -1;
	byte		angle_consraint = 0;
	float3		angle_min;
	float3		angle_max;
};

// IK�����N�z��
typedef std::vector<IKlink> IKlinks;

// IK
struct IK {
	int			bone = -1;
	int			loop_count = 0;
	float		angle = 0.0;
	IKlinks		links;
};

// �{�[��
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
	// �{�[���t���O
	static const ushort CONECTED_BONE_FLAG   = 0x0001; // �ڑ���(PMD�q�{�[���w��)�\�����@ -> 0 : ���W�I�t�Z�b�g�Ŏw�� 1 : �{�[���Ŏw��
	static const ushort ROTATE_FLAG          = 0x0002; // ��]�\
	static const ushort TRANSLATE_FLAG       = 0x0004; // �ړ��\
	static const ushort VISBLE_FLAG          = 0x0008; // �\��
	static const ushort CONTROL_FLAG         = 0x0010; // �����
	static const ushort IK_FLAG              = 0x0020; // IK
	static const ushort ADD_LOCAL_FLAG       = 0x0080; // ���[�J���t�^ | �t�^�Ώ� 0 : ���[�U�[�ό`�l�^IK�����N�^���d�t�^ 1 : �e�̃��[�J���ό`��
	static const ushort ADD_ROTATE_FLAG      = 0x0100; // ��]�t�^
	static const ushort ADD_TRANSLATE_FLAG   = 0x0200; // �ړ��t�^
	static const ushort FIXED_AXIS_FLAG      = 0x0400; // ���Œ�
	static const ushort LOCAL_AXIS_FLAG      = 0x0800; // ���[�J����
	static const ushort PYSICS_MORPH_FLAG    = 0x1000; // ������ό`
	static const ushort EXTERNAL_PARENT_FLAG = 0x2000; // �O���e�ό`
};

// ���_���[�t
struct MorphVertex {
	int		index;
	float3	position_offset;
};

// UV���[�t
struct MorphUV {
	int		index;
	float4	uv_offset;
};

// �{�[�����[�t
struct MorphBone {
	int		index;
	float3	translation;
	float4	rotation;
};

// �ގ����[�t
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

// �O���[�v���[�t
struct MorphGroup {
	int		index;
	float	weight;
};

// �t���b�v���[�t
struct MorphFlip {
	int		index;
	float	value;
};

// �C���p���X���[�t
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

// ���[�t
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

// �\���g�v�f
struct FrameElement {
	byte	type = 0;	// �{�[�� or ���[�t
	int		index = 0;	// �C���f�b�N�X
};

typedef std::vector<FrameElement> FrameElements;

// �\���g
struct Frame {
	TextBuf			name;
	TextBuf			name_eng;
	byte			flag = 0;
	FrameElements	elements;
};

// ���_�f�[�^�z��
typedef std::vector<Vertex> Vertices;

// ���_�C���f�b�N�X�f�[�^�z��
typedef std::vector<int> Indices;

// �}�e���A���z��
typedef std::vector<Material> Materials;

// �{�[���z��
typedef std::vector<Bone> Skeleton;

// �\���g�z��
typedef std::vector<Frame> Frames;

// ���b�V���f�[�^
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
