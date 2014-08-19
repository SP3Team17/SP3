#include "Camera.h"
#include <iostream>

Camera* Camera::instance = 0;

Camera::Camera(void)
{
	SetCameraType(LAND_CAM);
	Reset();
}

Camera::Camera(CAM_TYPE ct)
{
	SetCameraType(ct);
	Reset();
}

Camera::~Camera(void)
{
}

Camera* Camera::getInstance()
{
	if (instance == 0)
	{
		instance = new Camera(Camera::LAND_CAM);
	}

	return instance;
}

void Camera::SetCameraType(CAM_TYPE ct) {
	CameraType = ct;
}

void Camera::Reset(void)
{
	Position = Vector3D(0.0, 0.0, 0.0);
	Along = Vector3D(1.0, 0.0, 0.0);
	Up = Vector3D(0.0, 1.0, 0.0);
	Forward = Vector3D(0.0, 0.0, -1.0);
//	Update();
}

void Camera::Update() {
	gluLookAt(	Position.x, Position.y, Position.z, 
				Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z, 
				0.0f,1.0f,0.0f);
}

Vector3D Camera::GetPosition() {
	return Position;
}

void Camera::SetPosition( GLfloat x, GLfloat y, GLfloat z )
{
	this->Position.Set( x, y, z );
}

void Camera::SetDirection( GLfloat x, GLfloat y, GLfloat z )
{
	this->Forward.Set( x, y, z );
}

void Camera::Pitch(GLfloat theta)
{
	Forward.y -= theta;
	if (Forward.y > 3.142f)
		Forward.y = 3.142f;
	else if (Forward.y < -3.142f)
		Forward.y = -3.142f;
}
void Camera::Yaw(GLfloat theta)
{
	Forward.x = sin(-theta);
	Forward.z = -cos(-theta);
}
void Camera::Roll(GLfloat theta)
{
}
void Camera::Walk(GLfloat delta)
{
	Position.Set( Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta );
}
void Camera::Strafe(GLfloat delta)
{
	Along = Forward.crossVector3D( Up );
	Along.normalizeVector3D();
	Position.Set( Position.x + Along.x * delta, Position.y + Along.y * delta, Position.z + Along.z * delta );
}
void Camera::Fly(GLfloat delta)
{
}

//Toggle HUD mode
void Camera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, -1, 1);      
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping
	}
	else
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}
}

//Get the direction of the camera
Vector3D Camera::GetDirection(void)
{
	return Forward;
}
