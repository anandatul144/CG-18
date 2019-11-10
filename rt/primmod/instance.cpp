#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <rt/ray.h>
#include <rt/intersection.h>


namespace rt {

    Instance::Instance(Primitive* content)
	{
		this->Content = content;
		T = Matrix::identity();
	}   
	Primitive* Instance::content()
	{
		return this->Content;
	}
	void Instance::reset()
	{
		T = Matrix::identity();
	}
	void Instance::translate(const Vector& t)
	{
		T[0][3] += t.x;
		T[1][3] += t.y;
		T[2][3] += t.z;
	}
	void Instance::rotate(const Vector& axis, float angle)
	{
		Vector u = axis.normalize();
		Matrix R = Matrix(
			Float4(cos(angle) + u.x * u.x * (1 - cos(angle)), u.x * u.y * (1 - cos(angle)) - u.z * sin(angle), u.x * u.z * (1 - cos(angle)) + u.y * sin(angle), 0),
			//Float4(-cos(angle) - u.x * u.x * (1 - cos(angle)), -u.x * u.y * (1 - cos(angle)) + u.z * sin(angle), -u.x * u.z * (1 - cos(angle)) - u.y * sin(angle), 0),
			Float4(u.y * u.x * (1 - cos(angle)) + u.z * sin(angle), cos(angle) + u.y * u.y * (1 - cos(angle)), u.y * u.z * (1 - cos(angle)) - u.x * sin(angle), 0),
			Float4(u.z * u.x * (1 - cos(angle)) - u.y * sin(angle), u.z * u.y * (1 - cos(angle)) + u.x * sin(angle), cos(angle) + u.z * u.z * (1 - cos(angle)), 0),
			//Float4(-u.z * u.x * (1 - cos(angle)) + u.y * sin(angle), -u.z * u.y * (1 - cos(angle)) - u.x * sin(angle), -cos(angle) - u.z * u.z * (1 - cos(angle)), 0),
			Float4(0, 0, 0, 1));

		T = product(R,T);
		
	}

	void Instance::scale(float scale)
	{
		for(int i = 0; i < 3; ++i)
		{
			T[i][i] *= scale;
		}
	}
	void Instance::scale(const Vector& scale)
	{
		T[0][0] *= scale.x;
		T[1][1] *= scale.y;
		T[1][2] *= scale.z;
	}

	

	Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const
	{
		Ray tempRay;
		tempRay.o = ray.o;
		tempRay.d = ray.d;
		float previousdist=previousBestDistance;
		Matrix inverseTransform = T.invert();
		tempRay.o = inverseTransform * ray.o;
		tempRay.d = (inverseTransform  * ray.d).normalize();

		float tempPreviousBestDistance = (inverseTransform * ray.getPoint(previousdist) - tempRay.o).length();

		Intersection intersection;
		intersection = Content->intersect(tempRay, tempPreviousBestDistance);
		if (intersection)
		{
			Point intersectedPoint = T * intersection.hitPoint();
			float distance = (intersectedPoint - ray.o).length();
			Vector normalVector = (inverseTransform.transpose() * intersection.normal()).normalize();
			//if (dot(normalVector, ray.d.normalize()) > 0)
			//	normalVector = -1.0f * normalVector;

			Intersection backTransformedIntersection;
			backTransformedIntersection = Intersection(distance, ray, intersection.solid, normalVector,intersectedPoint);// Relpoint(intersectedPoint,Content->getBounds.centroidOfBBox()));
			return backTransformedIntersection;
		}
		return Intersection::failure();
	}

	BBox Instance::getBounds() const
	{
		BBox originalBox = Content->getBounds();

		Point P1 = originalBox.min;
		Point P2 = originalBox.max;

		float x1 = P1.x;
		float y1 = P1.y;
		float z1 = P1.z;

		float x2 = P2.x;
		float y2 = P2.y;
		float z2 = P2.z;

		Point P3 = Point(x1, y1, z2);
		Point P4 = Point(x1, y2, z1);
		Point P5 = Point(x1, y2, z2);
		Point P6 = Point(x2, y1, z1);
		Point P7 = Point(x2, y1, z2);
		Point P8 = Point(x2, y2, z1);
		
		Point p1 = T * P1;
		Point p2 = T * P3;
		Point p3 = T * P4;
		Point p4 = T * P5;

		Point p5 = T * P6;
		Point p6 = T * P7;
		Point p7 = T * P8;
		Point p8 = T * P2;

		Point minTransformed = min(p1, min(p2, min(p3, min(p4, min(p5, min(p6, min(p7, p8)))))));
		Point maxTransformed = max(p1, max(p2, max(p3, max(p4, max(p5, max(p6, max(p7, p8)))))));

		return BBox(minTransformed, maxTransformed);
	}
 

}
