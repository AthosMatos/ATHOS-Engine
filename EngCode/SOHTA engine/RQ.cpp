#include "RQ.h"

RenderQueue* RQ::Q;

void RQ::Queue(const wchar_t* name, bool ActivateTransparenry, XMMATRIX GeometryWorld)
{
    if (Q == NULL)
    {
        Q = (RenderQueue*)malloc(sizeof(RenderQueue));

        Q->ActivateTransparenry = ActivateTransparenry;
        Q->queued = false;
        Q->name = name;
        Q->GeometryWorld = GeometryWorld;

        Q->next = NULL;
        Q->prev = NULL;

        return;
    }
    else
    {
        RenderQueue* NewQ;
        NewQ = (RenderQueue*)malloc(sizeof(RenderQueue));

        NewQ->queued = false;
        NewQ->name = name;
        NewQ->ActivateTransparenry = ActivateTransparenry;
        NewQ->GeometryWorld = GeometryWorld;

        NewQ->next = NULL;


        if (Q->next == NULL)
        {
            Q->next = NewQ;
            NewQ->prev = Q;

            return;
        }
        else
        {
            while (Q->next != NULL) { Q = Q->next; }
            Q->next = NewQ;
            NewQ->prev = Q;
            while (Q->prev != NULL) { Q = Q->prev; }

            return;
        }
    }
}

void RQ::Organize()
{
    RenderQueue* fQ = Q;

    while (true)
    {
        if (fQ->ActivateTransparenry && !fQ->queued)
        {
            RenderQueue* NQ = fQ;
            if (fQ->prev != NULL)fQ->prev->next = fQ->next;
            if (fQ->next != NULL)fQ->next->prev = fQ->prev;
            while (NQ->next != NULL)NQ = NQ->next;

            NQ->next = fQ;
            fQ->prev = NQ;
            fQ->next = NULL;
            fQ->queued = true;

            while (fQ->prev != NULL)fQ = fQ->prev;
        }
        else
        {
            if (fQ->next != NULL)fQ = fQ->next;
            else
            {
                while (fQ->prev != NULL)fQ = fQ->prev;
                Q = fQ;
                break;
            }
        }
    }
    TransparencyOrganize();
}

void RQ::Render()
{
}

void RQ::TransparencyOrganize()
{
    RenderQueue* fQ = Q;


    while (!fQ->ActivateTransparenry)
    {
        if (fQ->next != NULL)
        {
            fQ = fQ->next;
        }
        else return;
    }

    RenderQueue* NQ;
    if (fQ->next != NULL)NQ = fQ;
    else return;

    while (true)
    {
        if (NQ->next != NULL)NQ = NQ->next;
        else
        {
            if (fQ->next != NULL)
            {
                fQ = fQ->next;
                if (fQ->next != NULL)NQ = fQ->next;
                else
                {
                    while (fQ->prev != NULL)fQ = fQ->prev;
                    Q = fQ;
                    break;
                };
            }
            else
            {
                while (fQ->prev != NULL)fQ = fQ->prev;
                Q = fQ;
                break;
            }
        }

        if (fQ->GetDistFromCam() < NQ->GetDistFromCam())
        {
            if (fQ->next == NQ)
            {
                fQ->next = NQ->next;
                NQ->next = fQ;
                NQ->prev = fQ->prev;
                NQ->prev->next = NQ;
                fQ->prev = NQ;
                if (fQ->next != NULL)fQ->next->prev = fQ;

                RenderQueue* Temp = fQ;
                fQ = NQ;
                NQ = Temp;
            }
            else
            {
                RenderQueue* FCN = fQ->next;
                RenderQueue* FCP = fQ->prev;

                fQ->next = NQ->next;
                fQ->prev = NQ->prev;
                if (fQ->next != NULL)fQ->next->prev = fQ;
                fQ->prev->next = fQ;
                NQ->next = FCN;
                NQ->prev = FCP;
                NQ->next->prev = NQ;
                NQ->prev->next = NQ;

                FCN = fQ;
                fQ = NQ;
                NQ = FCN;
            }
        }
    }
}
