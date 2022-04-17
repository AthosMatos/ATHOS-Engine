#include "RQ.h"

vector <Model> RQ::Queue;

RQ::RQ()
{

}

void RQ::addToQueue(Model data)
{
    Queue.insert(Queue.begin(), data);
}

void RQ::UpdateModel(const wchar_t* ModelName, Model data)
{
    int i = 0;
    for (; i < Queue.size(); i++)
    {
        if (Queue[i].name == ModelName) break;
    }
   
    Queue[i].modelWorld = data.modelWorld;
    Queue[i].Translation = data.Translation;
    Queue[i].Scale = data.Scale;
    Queue[i].Rotation = data.Rotation;
    Queue[i].ActivateTransparenry = data.ActivateTransparenry;
    Queue[i].ActivateWireframe = data.ActivateWireframe;
    Queue[i].opaque = data.opaque;
    Queue[i].ActivatePixelcliping = data.ActivatePixelcliping;
    Queue[i].ActivateLight = data.ActivateLight;

    if (data.ActivateTranslation == true && data.ActivateScale == true && data.rot == 0) Queue[i].modelWorld = Queue[i].Translation * Queue[i].Scale;
    else if (data.ActivateTranslation == true && data.ActivateScale == true && data.rot != 0) Queue[i].modelWorld = Queue[i].Translation * Queue[i].Rotation * Queue[i].Scale;
    else if (data.ActivateTranslation == true && data.ActivateScale == false && data.rot != 0) Queue[i].modelWorld = Queue[i].Translation * Queue[i].Rotation;
    else if (data.ActivateTranslation == true && data.ActivateScale == false && data.rot == 0) Queue[i].modelWorld = Queue[i].Translation;
    else if (data.ActivateTranslation == false && data.ActivateScale == true && data.rot != 0) Queue[i].modelWorld = Queue[i].Rotation * Queue[i].Scale;
    else if (data.ActivateTranslation == false && data.ActivateScale == true && data.rot == 0) Queue[i].modelWorld = Queue[i].Scale;
    else Queue[i].modelWorld = Queue[i].Rotation;
}

void RQ::RenderModel()
{

}

void RQ::RenderAll()
{

}
