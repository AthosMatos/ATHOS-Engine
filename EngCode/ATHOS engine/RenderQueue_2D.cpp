#include "RenderQueue_2D.h"

map <const wchar_t*, TextBox> RenderQueue_2D::TextsData;
map <const wchar_t*, Images> RenderQueue_2D::ImagesData;
vector <const wchar_t*> RenderQueue_2D::RenderOrder;

void RenderQueue_2D::Render()
{  
    Start2Din3D();     
    D2DRenderTarget->BeginDraw();
    D2DRenderTarget->Clear();

    for (int i = 0; i < RenderOrder.size(); i++)
    {
        try 
        {
            TextsData.at(RenderOrder[i]); // vector::at throws an out-of-range  
            TextRender(i);
        }
        catch (const std::out_of_range&) {
            try
            {
                ImagesData.at(RenderOrder[i]); 
                ImageRender(i);
               
            }
            catch (const std::out_of_range&)
            {
                return;
            }
        }
    }   
  
    D2DRenderTarget->EndDraw();
    End2Din3D();
}

void RenderQueue_2D::Release()
{
    TextsData.clear();
    ImagesData.clear();
    RenderOrder.clear();
}

void RenderQueue_2D::ImageRender(int i)
{
    if (ImagesData[RenderOrder[i]].render)
    {
        D2DRenderTarget->DrawBitmap(
            ImagesData[RenderOrder[i]].bmp,
            ImagesData[RenderOrder[i]].rect,
            1.0f,
            D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
            D2D1::RectF(0.0f, 0.0f, ImagesData[RenderOrder[i]].bmp->GetSize().width, ImagesData[RenderOrder[i]].bmp->GetSize().height)
        );

        CheckTransparency(i, RenderOrder.size(), ImagesData[RenderOrder[i]].transparency);
    }
}

void RenderQueue_2D::TextRender(int i)
{
    if (TextsData[RenderOrder[i]].render)
    {
        if (TextsData[RenderOrder[i]].fps != 0)
        {
            std::wostringstream TempvariableFPS;
            TempvariableFPS << "FPS: " << TextsData[RenderOrder[i]].fps;
            D2DRenderTarget->DrawText(TempvariableFPS.str().c_str(), (UINT32)wcslen(TempvariableFPS.str().c_str()), TextsData[RenderOrder[i]].TextFormat, TextsData[RenderOrder[i]].rect, TextsData[RenderOrder[i]].Brush);
        }
        else
        {
            D2DRenderTarget->DrawText(TextsData[RenderOrder[i]].ActualText, (UINT32)wcslen(TextsData[RenderOrder[i]].ActualText), TextsData[RenderOrder[i]].TextFormat, TextsData[RenderOrder[i]].rect, TextsData[RenderOrder[i]].Brush);
        }
        CheckTransparency(i, RenderOrder.size(), TextsData[RenderOrder[i]].transparency);
    }
}

void RenderQueue_2D::CheckTransparency(int index, int limit, float transparency)
{
    limit -= 1;

    if (transparency != 0.0f)
    {
        D2DRenderTarget->EndDraw();
        End2Din3D(transparency);

        if (index != limit)
        {
            Start2Din3D();
            D2DRenderTarget->BeginDraw();
            D2DRenderTarget->Clear();
        }

    }
}
