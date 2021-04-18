#include "Camera.h"

Camera::Camera(){}

Camera::Camera(nullptr_t)
{
    CamHead = NULL;
    ActiveCam_name = NULL;

    CamChange = false;

    StdCamPos();
}

void Camera::Create(const wchar_t* name)
{
    if (CamHead == NULL)
    {
        CamHead = (Cam*)malloc(sizeof(Cam));

        CamHead->D_FR();
        CamHead->name = name;

        CamHead->camPosition = XMVectorSet(5.0f, 1.0f, -10.0f, 0.0f);//fist person or camera movement
        CamHead->camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);//basicamente 1 zoom tipo scope duma sniper ou binoculos
        CamHead->camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);///inclina a camera tipo strafe do R6 + inclina pra esquerda e - pra direita

        //Set the View matrix
        CamHead->camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

        //Set the Projection matrix
        CamHead->camProjection = XMMatrixPerspectiveFovLH((stdFOV / 250) * XM_PI, (float)H_res / V_res, 1.0f, 1000.0f); ///fov da camera  

        CamHead->next = NULL;
        CamHead->prev = NULL;

     

        return;
    }
    else
    {
        Cam* Ncam = (Cam*)malloc(sizeof(Cam));
        Ncam->D_FR();
        Ncam->name = name;

        Ncam->camPosition = XMVectorSet(5.0f, 1.0f, -10.0f, 0.0f);//fist person or camera movement
        Ncam->camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);//basicamente 1 zoom tipo scope duma sniper ou binoculos
        Ncam->camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);///inclina a camera tipo strafe do R6 + inclina pra esquerda e - pra direita

        //Set the View matrix
        Ncam->camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

        //Set the Projection matrix
        Ncam->camProjection = XMMatrixPerspectiveFovLH((stdFOV / 250) * XM_PI, (float)H_res / V_res, 1.0f, 1000.0f); ///fov da camera  
      
        Ncam->next = NULL;

        if (CamHead->next == NULL)
        {
            Ncam->prev = CamHead;
            CamHead->next = Ncam;

            return;
        }
        else
        {
            while (CamHead->next != NULL) { CamHead = CamHead->next; }
            Ncam->prev = CamHead;
            CamHead->next = Ncam;
            while (CamHead->prev != NULL) { CamHead = CamHead->prev; }

            return;
        }
    }
}

void Camera::UseCam(const wchar_t* cam)
{
    if (ActiveCam_name != NULL)
    {
        CamChange = true;
    }
    ActiveCam_name = cam;
}

void Camera::SetFistPerson()
{
    Cam* Tcam = CamHead;
    while (true)
    {
        if (Tcam->name == ActiveCam_name)break;
        else
        {
            if (Tcam->next != NULL)
            {
                Tcam = Tcam->next;
            }
            else return;
        }
    }
    Tcam->FirstPerson = true;
    Tcam->NoClip = false;       
}

void Camera::SetNoClip()
{
    Cam* Tcam = CamHead;
    while (true)
    {
        if (Tcam->name == ActiveCam_name)break;
        else
        {
            if (Tcam->next != NULL)
            {
                Tcam = Tcam->next;
            }
            else return;
        }
    }
    Tcam->FirstPerson = false;
    Tcam->NoClip = true;
}

void Camera::Set_FOV(float FOV)
{
    Cam* Tcam = CamHead;
    while (true)
    {
        if (Tcam->name == ActiveCam_name)break;
        else
        {
            if (Tcam->next != NULL)
            {
                Tcam = Tcam->next;
            }
            else return;
        }
    }
    Tcam->camProjection = XMMatrixPerspectiveFovLH((FOV / 250) * XM_PI, (float)H_res / V_res, 1.0f, 1000.0f); ///fov da camera
}

void Camera::UpdateActiveCam()
{
    Cam* Activecam = CamHead;

    if (ActiveCam_name == NULL)
    {
        if (Activecam != NULL)ActiveCam_name = Activecam->name;
        else return;
    }
    else
    {
        while (true)
        {
            if (Activecam->name == ActiveCam_name)break;
            else
            {
                if (Activecam->next != NULL)
                {
                    Activecam = Activecam->next;
                }
                else return;
            }
        }
    } 

    camView = Activecam->camView;
    camProjection = Activecam->camProjection;
    camPosition = Activecam->camPosition;
    camTarget = Activecam->camTarget;
    camUp = Activecam->camUp;
}

void Camera::StdCamPos()
{
    camPosition = XMVectorSet(5.0f, 1.0f, -10.0f, 0.0f);//fist person or camera movement
    camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);//basicamente 1 zoom tipo scope duma sniper ou binoculos
    camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);///inclina a camera tipo strafe do R6 + inclina pra esquerda e - pra direita

    //Set the View matrix
    camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

    //Set the Projection matrix
    camProjection = XMMatrixPerspectiveFovLH((stdFOV / 250) * XM_PI, (float)H_res / V_res, 1.0f, 1000.0f); ///fov da camera  
}

void Camera::UpdatePY(Cam* cam)
{
    cam->camPitch = input.camPitch;
    cam->camYaw = input.camYaw; 
}

void Camera::Update(const wchar_t* cam)
{
    Cam* Tcam = CamHead;

        while (true)
        {
            if (Tcam->name == cam)break;
            else
            {
                if (Tcam->next != NULL)
                {
                    Tcam = Tcam->next;
                }
                else return;
            }
        }
        if (CamChange)
        {
            input.camPitch = Tcam->camPitch;
            input.camPitch2 = input.camPitch;
            input.camYaw = Tcam->camYaw;
            CamChange = false;
        }
        UpdatePY(Tcam);

        if (Tcam->FirstPerson)
        {
            UpdateFP(Tcam);
        }
        else if (Tcam->NoClip)
        {
            UpdateNC(Tcam);
        }
  
        UpdateActiveCam();
}

void Camera::Remove(const wchar_t* cam)
{
    Cam* Fcam;
    Fcam = CamHead;
    while (Fcam->name != cam) { Fcam = Fcam->next; }

    if (Fcam->prev == NULL)
    {
        CamHead = Fcam->next;
        Fcam->next->prev = Fcam->prev;

        free(Fcam);

        return;
    }
    if (Fcam->next == NULL)
    {
        Fcam->prev->next = Fcam->next;

        free(Fcam);

        return;
    }

    Fcam->prev->next = Fcam->next;
    Fcam->next->prev = Fcam->prev;
    free(Fcam);
}

void Camera::Release()
{
    Cam* Temp;
    Cam* TTemp;
    Temp = CamHead;

    while (true)
    {
        if (Temp != NULL)
        {
            TTemp = Temp->next;
            free(Temp);
            Temp = TTemp;
        }
        else break;
    }
}

void Camera::UpdateFP(Cam* Tcam)
{
    Tcam->camRotationMatrix = XMMatrixRotationRollPitchYaw(Tcam->camPitch, Tcam->camYaw, 0);
    Tcam->camTarget = XMVector3TransformCoord(Tcam->DefaultForward, Tcam->camRotationMatrix);
    Tcam->camTarget = XMVector3Normalize(Tcam->camTarget);

    ///fist person
    XMMATRIX RotateYTempMatrix;
    RotateYTempMatrix = XMMatrixRotationY(input.camYaw);

    Tcam->camRight = XMVector3TransformCoord(Tcam->DefaultRight, RotateYTempMatrix);
    Tcam->camUp = XMVector3TransformCoord(Tcam->camUp, RotateYTempMatrix);
    Tcam->camForward = XMVector3TransformCoord(Tcam->DefaultForward, RotateYTempMatrix);

    Tcam->camPosition += input.moveLeftRight * Tcam->camRight;
    Tcam->camPosition += input.moveBackForward * Tcam->camForward;

    ///USE THIS IN ORDDER TO CREATE A ACCELERATION  
    input.moveLeftRight = 0.0f;
    input.moveBackForward = 0.0f;

    Tcam->camTarget = Tcam->camPosition + Tcam->camTarget;

    Tcam->camView = XMMatrixLookAtLH(Tcam->camPosition, Tcam->camTarget, Tcam->camUp);
}

void Camera::UpdateNC(Cam* Tcam)
{
    Tcam->camRotationMatrix = XMMatrixRotationRollPitchYaw(Tcam->camPitch, Tcam->camYaw, 0);
    Tcam->camTarget = XMVector3TransformCoord(Tcam->DefaultForward, Tcam->camRotationMatrix);
    Tcam->camTarget = XMVector3Normalize(Tcam->camTarget);

    // Free-Look Camera
    Tcam->camRight = XMVector3TransformCoord(Tcam->DefaultRight, Tcam->camRotationMatrix);
    Tcam->camForward = XMVector3TransformCoord(Tcam->DefaultForward, Tcam->camRotationMatrix);
    Tcam->camUp = XMVector3Cross(Tcam->camForward, Tcam->camRight);

    Tcam->camPosition += input.moveLeftRight * Tcam->camRight;
    Tcam->camPosition += input.moveBackForward * Tcam->camForward;

    ///USE THIS IN ORDDER TO CREATE A ACCELERATION  
    input.moveLeftRight = 0.0f;
    input.moveBackForward = 0.0f;

    Tcam->camTarget = Tcam->camPosition + Tcam->camTarget;

    Tcam->camView = XMMatrixLookAtLH(Tcam->camPosition, Tcam->camTarget, Tcam->camUp);
}
