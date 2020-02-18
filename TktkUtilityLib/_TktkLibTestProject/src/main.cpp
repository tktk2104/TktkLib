#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkMathLib_mt.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mt.lib" )
#else
#pragma comment( lib, "TktkMathLib_mtd.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mtd.lib" )
#endif

//#include "MMD/PMXFileReader.h"
//#include "MMD/MMDMath.h"
//#include "MMD/string_convertor.h"
//#include <TktkMath/Color.h>
//#include <TktkMath/Vector2.h>
//#include <TktkMath/Vector3.h>
//#include <TktkMath/Matrix4.h>
//#include <string>
//#include <fstream>
//
//struct Material {                                   // �}�e���A���\����
//	Color           ambient;                        // �����J���[
//	Color           diffuse;                        // �g�U���ˌ��J���[
//	Color           specular;                       // ���ʔ��ˌ��J���[
//	Color           emission;                       // ���ȏƖ��J���[
//	float           shininess;                      // ���ʔ��ˎw��
//	char            texture_file_name[128];         // �e�N�X�`���t�@�C����
//	char          normal_texture_file_name[128];  // �@���}�b�v��
//	void*           texture;                        // �J���[�}�b�v�e�N�X�`���|�C���^
//	void*           normal_texture;                 // �@���}�b�v�e�N�X�`���|�C���^
//};
//
//struct Subset {                                     // �T�u�Z�b�g�\����
//	int             material;                       // �}�e���A��
//	int             start;                          // �C���f�b�N�X�̊J�n�ʒu
//	int             count;                          // �C���f�b�N�X��
//};
//
//struct Vertex {                                     // ���_�f�[�^�\����
//	Vector3         point;                          // ���W
//	Vector3         normal;                         // �@���x�N�g��
//	Vector2         texcoord;                       // �e�N�X�`�����W
//	unsigned char   bone_indices[4];                // �{�[���C���f�b�N�X
//	float           bone_weights[4];                // �{�[���E�F�C�g
//	Vector3         tangent;                        // �ڃx�N�g��
//	Vector3         binormal;                       // �]�@���x�N�g��
//};
//
//struct Bone {                                       // �{�[���\����
//	char            name[32];                       // �{�[����
//	int             ID;                             // �{�[��ID
//	int             parentID;                       // �e�{�[��ID
//	Matrix4			transform;                      // �{�[���̕ϊ��s��
//	Matrix4			inverse;                        // �{�[���̋t�s��
//};
//
//// ���b�V���t�@�C���̏o��
//void output_simple_mesh(const std::string& simple_mesh_file_name, const mmd::pmx::PMXFile& pmx) {
//	std::ofstream file(simple_mesh_file_name, std::ios::binary);
//	// �}�e���A���̏o��
//	unsigned int material_size = pmx.mesh.materials.size();
//	file.write((const char*)&material_size, sizeof(material_size));
//	for (const auto& material : pmx.mesh.materials) {
//		Material out_material;
//		std::memset(&out_material, 0, sizeof(out_material));
//		out_material.ambient.r = material.ambient.x;
//		out_material.ambient.g = material.ambient.y;
//		out_material.ambient.b = material.ambient.z;
//		out_material.ambient.a = 1.0f;
//		out_material.diffuse.r = material.diffuse.x;
//		out_material.diffuse.g = material.diffuse.y;
//		out_material.diffuse.b = material.diffuse.z;
//		out_material.diffuse.a = 1.0f;
//		out_material.specular.r = material.specular.x;
//		out_material.specular.g = material.specular.y;
//		out_material.specular.b = material.specular.z;
//		out_material.specular.a = 1.0f;
//		out_material.emission.r = 0.0f;
//		out_material.emission.g = 0.0f;
//		out_material.emission.b = 0.0f;
//		out_material.emission.a = 1.0f;
//		out_material.shininess = material.specularity;
//		if (material.texture_index != -1) {
//			std::string texture_file_name =
//				utf16_to_sjis(pmx.mesh.texture[material.texture_index]);
//			strcpy_s(out_material.texture_file_name, texture_file_name.c_str());
//			// ���@���}�b�v�̃e�N�X�`�����̓f�B�t���[�Y�e�N�X�`���̖��O�̑O��normal_��t���� 
//			strcpy_s(out_material.normal_texture_file_name,
//				("normal_" + texture_file_name).c_str());
//		}
//		file.write((const char*)&out_material, sizeof(out_material));
//	}
//	// �T�u�Z�b�g�̏o��
//	unsigned int subset_size = pmx.mesh.materials.size();
//	file.write((const char*)&subset_size, sizeof(subset_size));
//	int start = 0;
//	for (int material = 0; material < (int)pmx.mesh.materials.size(); ++material) {
//		Subset subset;
//		subset.material = material;
//		subset.start = start;
//		subset.count = pmx.mesh.materials[material].vertex_count;
//		start += pmx.mesh.materials[material].vertex_count;
//		file.write((const char*)&subset, sizeof(subset));
//	}
//	// �C���f�b�N�X�̏o��
//	unsigned int indices_size = pmx.mesh.indices.size();
//	file.write((const char*)&indices_size, sizeof(indices_size));
//	for (int i = 0; i < (int)pmx.mesh.indices.size(); i += 3) {
//		file.write((const char*)&pmx.mesh.indices[i + 0], sizeof(unsigned int));
//		file.write((const char*)&pmx.mesh.indices[i + 1], sizeof(unsigned int));
//		file.write((const char*)&pmx.mesh.indices[i + 2], sizeof(unsigned int));
//	}
//
//	// ���_�f�[�^�̏o��
//	unsigned int vertices_size = pmx.mesh.vertices.size();
//	file.write((const char*)&vertices_size, sizeof(vertices_size));
//	for (const auto& vertex : pmx.mesh.vertices) {
//		Vertex out_vertex;
//		std::memset(&out_vertex, 0, sizeof(out_vertex));
//		out_vertex.point.x = vertex.point.x;
//		out_vertex.point.y = vertex.point.y;
//		out_vertex.point.z = vertex.point.z;
//		out_vertex.normal.x = vertex.normal.x;
//		out_vertex.normal.y = vertex.normal.y;
//		out_vertex.normal.z = vertex.normal.z;
//		out_vertex.texcoord.x = vertex.uv.x;
//		out_vertex.texcoord.y = vertex.uv.y;
//		if (vertex.weight.format == mmd::pmx::BlendWeight::BDEF1) {
//			out_vertex.bone_indices[0] =
//				(vertex.weight.bdef1.bone != -1) ? vertex.weight.bdef1.bone : 0;
//			out_vertex.bone_weights[0] = 1.0f;
//		}
//		else if (vertex.weight.format == mmd::pmx::BlendWeight::BDEF2) {
//			out_vertex.bone_indices[0] =
//				(vertex.weight.bdef2.bone[0] != -1) ? vertex.weight.bdef2.bone[0] : 0;
//			out_vertex.bone_indices[1] =
//				(vertex.weight.bdef2.bone[1] != -1) ? vertex.weight.bdef2.bone[1] : 0;
//			out_vertex.bone_weights[0] = vertex.weight.bdef2.weight;
//			out_vertex.bone_weights[1] = 1.0f - vertex.weight.bdef2.weight;
//		}
//		else if (vertex.weight.format == mmd::pmx::BlendWeight::BDEF4) {
//			out_vertex.bone_indices[0] =
//				(vertex.weight.bdef4.bone[0] != -1) ? vertex.weight.bdef4.bone[0] : 0;
//			out_vertex.bone_indices[1] =
//				(vertex.weight.bdef4.bone[1] != -1) ? vertex.weight.bdef4.bone[1] : 0;
//			out_vertex.bone_indices[2] =
//				(vertex.weight.bdef4.bone[2] != -1) ? vertex.weight.bdef4.bone[2] : 0;
//			out_vertex.bone_indices[3] =
//				(vertex.weight.bdef4.bone[3] != -1) ? vertex.weight.bdef4.bone[3] : 0;
//			out_vertex.bone_weights[0] = vertex.weight.bdef4.weight[0];
//			out_vertex.bone_weights[1] = vertex.weight.bdef4.weight[1];
//			out_vertex.bone_weights[2] = vertex.weight.bdef4.weight[2];
//			out_vertex.bone_weights[3] = vertex.weight.bdef4.weight[3];
//		}
//		else if (vertex.weight.format == mmd::pmx::BlendWeight::SDEF) {
//			out_vertex.bone_indices[0] =
//				(vertex.weight.sdef.bdef2.bone[0] != -1) ? vertex.weight.sdef.bdef2.bone[0] : 0;
//			out_vertex.bone_indices[1] =
//				(vertex.weight.sdef.bdef2.bone[1] != -1) ? vertex.weight.sdef.bdef2.bone[1] : 0;
//			out_vertex.bone_weights[0] = vertex.weight.sdef.bdef2.weight;
//			out_vertex.bone_weights[1] = 1.0f - vertex.weight.sdef.bdef2.weight;
//		}
//
//		Vector3::orthoNormalize(
//			&out_vertex.normal,
//			&out_vertex.tangent,
//			&out_vertex.binormal
//		);
//		file.write((const char*)&out_vertex, sizeof(out_vertex));
//	}
//}
//
//// �X�P���g���t�@�C���̏o��
//void output_simple_skeleton(const std::string& simple_mesh_file_name,
//	const mmd::pmx::PMXFile& pmx) {
//	std::ofstream file(simple_mesh_file_name, std::ios::binary);
//	unsigned int skeleton_size = pmx.skeleton.size();
//	file.write((const char*)&skeleton_size, sizeof(skeleton_size));
//	for (int id = 0; id < (int)pmx.skeleton.size(); ++id) {
//		const auto& bone = pmx.skeleton[id];
//		const mmd::float3 parentOffset = (bone.parent_index == -1) ?
//			bone.position : (bone.position - pmx.skeleton[bone.parent_index].position);
//		Bone out_bone;
//		strcpy_s(out_bone.name, utf16_to_sjis(bone.name).c_str());
//		out_bone.ID = id;
//		out_bone.parentID = bone.parent_index;
//		out_bone.transform = Matrix4::createTranslation(
//			Vector3(parentOffset.x, parentOffset.y, parentOffset.z));
//		out_bone.inverse = Matrix4::createTranslation(
//			Vector3(-bone.position.x, -bone.position.y, -bone.position.z));
//		file.write((const char*)&out_bone, sizeof(out_bone));
//	}
//}
//
//#include <TktkMath/Matrix4.h>
//
//// �ȈՃ��b�V���t�@�C���o��
//int main(int argc, const char *argv[]) {
//
//	Matrix4 tempMat = Matrix4::createRotationZ(90);
//
//
//
//	if (argc < 3) return 1;
//	// ���̓t�@�C���̏�����
//	const std::string pmx_file_name = argv[1];
//	// �o�̓t�@�C�����̏�����
//	const std::string simple_mesh_file_name = argv[2];
//	const std::string simple_skeleton_file_name = (argc >= 4) ? argv[3] : std::string();
//	// PMX�f�[�^�̓ǂݍ���
//	mmd::pmx::PMXFile pmx;
//	mmd::pmx::PMXFileReader(pmx).read(pmx_file_name);
//	// ���b�V���t�@�C���̏o��
//	output_simple_mesh(simple_mesh_file_name, pmx);
//	// �X�P���g���t�@�C���̏o��
//	if (!simple_skeleton_file_name.empty()) {
//		output_simple_skeleton(simple_skeleton_file_name, pmx);
//	}
//	return 0;
//}

#include <iostream>
#include <vector>
#include <forward_list>
#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix3.h>
#include <TktkMath/Matrix4.h>
#include <TktkMath/Quaternion.h>
#include <Tktk2dCollision/BoundingCircle.h>
#include <Tktk2dCollision/BoundingRect.h>
#include <Tktk2dCollision/BoundingPolygon2d.h>

#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include <ctime>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <vector>
#include <typeindex>
#include <list>

#include <type_traits>
#include <array>

//class A
//{
//public:
//	void update()
//	{
//		std::cout << "A update" << std::endl;
//	}
//};
//
//class B
//{
//public:
//	void update()
//	{
//		std::cout << "B update" << std::endl;
//	}
//};
//
//class C
//{
//};
//
//struct HasUpdateCheckImpl
//{
//	template <class T>
//	static auto check(T*) -> decltype(std::declval<T&>()->update(), std::true_type());
//
//	template <class T>
//	static auto check(...)->std::false_type;
//};
//
//template <class T>
//struct HasUpdateCheck : decltype(HasUpdateCheckImpl::check<T>(nullptr))
//{
//};
//
//struct UpdateRunner
//{
//	template <class T, typename std::enable_if<HasUpdateCheck<T>::value>::type* = nullptr>
//	static void checkAndRun(T runClass)
//	{
//		runClass->update();
//	}
//	template <class T, typename std::enable_if<!HasUpdateCheck<T>::value>::type* = nullptr>
//	static void checkAndRun(T runClass)
//	{
//	}
//};
//
//class HasUpdateClass
//{
//public:
//
//	template<class T>
//	HasUpdateClass(T* raw)
//		: m_self(raw)
//		, m_vtablePtr(&VTableInitializer<T>::m_vtable) {}
//public:
//
//	void runFunc()
//	{
//		m_vtablePtr->runFunc(m_self);
//	}
//
//private:
//
//	struct VTable
//	{
//		void(*runFunc)(void*);
//	};
//
//	template <class T>
//	struct VTableInitializer
//	{
//		static VTable m_vtable;
//
//		static void runFunc(void* self)
//		{
//			UpdateRunner::checkAndRun((T*)(self));
//
//			//checkAndRunFunc((T*)(self));
//		}
//
//		template<class U>
//		static void checkAndRunFunc(U runClass)
//		{
//			//UpdateRunner::checkAndRun(runClass);
//		}
//	};
//
//private:
//
//	void* m_self;
//
//	VTable* m_vtablePtr;
//};
//
//template<class T>
//typename HasUpdateClass::VTable HasUpdateClass::VTableInitializer<T>::m_vtable =
//{
//	&HasUpdateClass::VTableInitializer<T>::runFunc
//};

template <class T>
struct TCarrierImpl
{
	static constexpr T* value{ nullptr };
};

template<class T>
constexpr T* TCarrier = TCarrierImpl<T>::value;

class MyClass
{
public:
	template <class T, class... Args>
	MyClass(T*, Args&&... args)
	{
		auto temp = std::make_shared<T>(std::forward<Args>(args)...);

		m_self = temp;
	}

private:

	std::shared_ptr<void> m_self;
};

int main()
{
	MyClass mc = MyClass(TCarrier<int>, 10);

	/*std::shared_ptr<A> sA = std::make_shared<A>();

	std::shared_ptr<void> sVA = sA;

	A* a = new A();
	B* b = new B();
	C* c = new C();

	std::list<HasUpdateClass> manager;

	manager.push_back(HasUpdateClass(a));
	manager.push_back(HasUpdateClass(b));
	manager.push_back(HasUpdateClass(c));

	for (auto node : manager)
	{
		node.runFunc();
	}


	delete(a);
	delete(b);
	delete(c);*/
	
	/*
	while (true)
	{

	}

	sizeof(std::pair<int, double>);

	std::unordered_multimap<int, int> testMap;

	std::forward_list<int> testList;

	std::vector<int> testVector;
	testVector.resize(10000);

	for (int i = 0; i < 10000; i++)
	{
		testMap.insert(std::make_pair(1, 1));

		testList.push_front(1);

		testVector.at(i) = 1;
	}

	std::clock_t startTime = std::clock();
	
	for (int i = 0; i < 10000; i++)
	{
		std::for_each(
			std::begin(testVector),
			std::end(testVector),
			[](const auto& node) {; }
		);
	}

	std::clock_t endTime = std::clock();

	std::cout << (static_cast<float>(endTime - startTime) / 1000.0f) << std::endl;*/

	return 0;
}