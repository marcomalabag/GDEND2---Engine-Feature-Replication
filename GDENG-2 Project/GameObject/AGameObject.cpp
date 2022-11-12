#include "AGameObject.h"

AGameObject::AGameObject(std::string_view name) :
	Name(name)
{
	this->Name = name;
	this->Position = Vector3D::zeros();
	this->Rotation = Vector3D::zeros();
	this->Scale = Vector3D::ones();


}

void AGameObject::setPosition(float x, float y, float z)
{
	this->Position = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->Position = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->Position;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->Scale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->Scale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->Scale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->Rotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->Rotation = rot;
}

void AGameObject::setRotationX(float x)
{
	this->Rotation.x = x;
}

void AGameObject::setRotationY(float y)
{
	this->Rotation.y = y;
}

void AGameObject::setRotationz(float z)
{
	this->Rotation.z = z;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->Rotation;
}
Matrix4x4 AGameObject::getLocalMatrix()
{
	Matrix4x4 summation;
	Matrix4x4 translate;
	Matrix4x4 scale;
	Matrix4x4 rotateZ;
	Matrix4x4 rotateF;
	Matrix4x4 rotateGl;
	Matrix4x4 rotateTotal;
	
	summation.setIdentity();
	
	translate.setIdentity();
	scale.setIdentity();

	translate.setTranslation(this->getLocalPosition());
	scale.setScale(this->getLocalScale());
	const Vector3D rotation = Vector3D(this->getLocalRotation());

	rotateZ.setIdentity();
	rotateZ.setRotationZ(rotation.z);

	rotateF.setIdentity();
	rotateF.setRotationX(rotation.x);

	rotateGl.setIdentity();
	rotateGl.setRotationY(rotation.y);

	rotateTotal.setIdentity();
	rotateTotal = rotateTotal.mulMatrix(rotateF.mulMatrix(rotateGl.mulMatrix(rotateZ)));
	summation = summation.mulMatrix(scale.mulMatrix(rotateTotal));
	summation = summation.mulMatrix(translate);
	return summation;
}

String AGameObject::getName()
{
	return this->name;
}

AGameObject::~AGameObject()
{
}
