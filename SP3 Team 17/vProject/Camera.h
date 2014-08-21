#ifndef CAMERA_H
#define CAMERA_H

#include "definitions.h"
#include "vector3D.h"
#include <GL/glut.h>

class Camera
{
public:
	static Camera* getInstance();
	enum CAM_TYPE { LAND_CAM, AIR_CAM };

private:
	static Camera* instance;
	CAM_TYPE CameraType;
	Vector3D Position;
	Vector3D Along;
	Vector3D Up;
	Vector3D Forward;

public:
	Camera(void);
	Camera(CAM_TYPE ct);
	~Camera(void);

	void SetCameraType(CAM_TYPE ct);
	void Reset(void);
	void Update();
	Vector3D GetPosition();
	// Get the direction of the camera
	Vector3D GetDirection(void);
	void SetPosition( GLfloat x, GLfloat y, GLfloat z );
	void SetDirection( GLfloat x, GLfloat y, GLfloat z );

	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	void Walk(GLfloat delta);//, bool Wall[4]);
	void Strafe(GLfloat delta);//, bool Wall[4]);
	void Fly(GLfloat delta);
	// Toggle HUD mode
	void SetHUD(bool m_bHUDmode);
};

#endif