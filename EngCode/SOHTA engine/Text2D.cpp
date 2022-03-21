#include "Text2D.h"
#include <comdef.h>


void Text2D::Create(const wchar_t* ID)
{
    bstr_t b(ID);
    const char* c = b;
    cout << "Creating textbox: " << c << endl;
    
    TextBox TB;
    TB.ID = ID;
    auto& TBref = TB;

    StdFontStyle(TBref);

    TextsData.insert(pair <const wchar_t*, TextBox> (ID, TB));
    RenderOrder.insert(RenderOrder.begin(), ID);

    cout << "textbox: " << c <<" Created"<<endl;

    return;
}

void Text2D::Update(const wchar_t* ID, const wchar_t* text, float TextSize, int posX, int posY, D2D1::ColorF color, float Transparency)
{
    if (posX > H_res)
    {
        posX = H_res;
    }
    if (posY > V_res)
    {
        posY = V_res;
    }

    TextsData[ID].ActualText = text;
    TextsData[ID].transparency = Transparency;

    HRESULT hr;

    if (TextSize != TextsData[ID].size)
    {
        hr = DWriteFactory->CreateTextFormat(
            L"Unispace",
            NULL,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            TextSize,
            L"en-us",
            &TextsData[ID].TextFormat
        );

        TextsData[ID].size = TextSize;

        hr = TextsData[ID].TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        hr = TextsData[ID].TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }
    
   
    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &TextsData[ID].Brush);

    TextsData[ID].rect = D2D1::RectF(posX, posY, H_res, V_res);

}

void Text2D::Update(const wchar_t* ID, const wchar_t* text, float TextSize, int left, int top, int right, int bottom, D2D1::ColorF color, float Transparency)
{
    if (left > H_res)
    {
        left = H_res;
    }
    if (top > V_res)
    {
        top = V_res;
    }

    TextsData[ID].ActualText = text;
    TextsData[ID].transparency = Transparency;

    HRESULT hr;

    if (TextSize != TextsData[ID].size)
    {
        hr = DWriteFactory->CreateTextFormat(
            L"Unispace",
            NULL,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            TextSize,
            L"en-us",
            &TextsData[ID].TextFormat
        );

        TextsData[ID].size = TextSize;

        hr = TextsData[ID].TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        hr = TextsData[ID].TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }


    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &TextsData[ID].Brush);

    TextsData[ID].rect = D2D1::RectF(left, top, right, bottom);
}

void Text2D::Update(const wchar_t* ID, const wchar_t* text, int fps, float TextSize, int posX, int posY, D2D1::ColorF color, float Transparency)
{
    if (posX > H_res)
    {
        posX = H_res;
    }
    if (posY > V_res)
    {
        posY = V_res;
    }

    TextsData[ID].ActualText = text;
    TextsData[ID].fps = fps;
    TextsData[ID].transparency = Transparency;

    HRESULT hr;

    if (TextSize != TextsData[ID].size)
    {
        hr = DWriteFactory->CreateTextFormat(
            L"Unispace",
            NULL,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            TextSize,
            L"en-us",
            &TextsData[ID].TextFormat
        );

        TextsData[ID].size = TextSize;

        hr = TextsData[ID].TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        hr = TextsData[ID].TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }


    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &TextsData[ID].Brush);

    TextsData[ID].rect = D2D1::RectF(posX, posY, H_res, V_res);
}

void Text2D::Update(const wchar_t* ID, const wchar_t* text, int fps, float TextSize, int left, int top, int right, int bottom, D2D1::ColorF color, float Transparency)
{
    if (left > H_res)
    {
        left = H_res;
    }
    if (top > V_res)
    {
        top = V_res;
    }

    TextsData[ID].ActualText = text;
    TextsData[ID].fps = fps;
    TextsData[ID].transparency = Transparency;

    HRESULT hr;

    if (TextSize != TextsData[ID].size)
    {
        hr = DWriteFactory->CreateTextFormat(
            L"Unispace",
            NULL,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            TextSize,
            L"en-us",
            &TextsData[ID].TextFormat
        );

        TextsData[ID].size = TextSize;

        hr = TextsData[ID].TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        hr = TextsData[ID].TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }


    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &TextsData[ID].Brush);

    TextsData[ID].rect = D2D1::RectF(left, top, right, bottom);
}

void Text2D::Render(const wchar_t* ID, bool state)
{
    TextsData[ID].render = state;
}

void Text2D::Release()
{
    TextsData.clear();
}

void Text2D::StdFontStyle(TextBox& FT)
{
    HRESULT hr = DWriteFactory->CreateTextFormat(
        L"Arial",
        NULL,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        20.0f,
        L"en-us",
        &FT.TextFormat
    );

    hr = FT.TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    hr = FT.TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &FT.Brush);

    FT.rect = D2D1::RectF(0, 0, H_res, V_res);
}

