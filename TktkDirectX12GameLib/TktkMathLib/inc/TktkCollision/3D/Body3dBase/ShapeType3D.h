#ifndef SHAPE_TYPE_3D_H_
#define SHAPE_TYPE_3D_H_

// 図形の種類
enum class ShapeType3D
{
	None,		// 初期値
	Sphere,		// 球体
	AABB,		// Axis Aligned Bounding Box

	Count		// 図形の数
};

#endif // !SHAPE_TYPE_3D_H_