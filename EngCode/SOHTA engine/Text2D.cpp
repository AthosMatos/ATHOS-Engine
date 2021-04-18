#include "Text2D.h"
#include <comdef.h>

Text2D::Text2D() {}

Text2D::Text2D(nullptr_t)
{
    SelectedTextBox = NULL;
    TB = NULL;
}

void Text2D::Create(const wchar_t* ID)
{
    bstr_t b(ID);
    const char* c = b;
    cout << "Creating textbox: " << c << endl;

    if (TB == NULL)
    {
        TB = (TextBox*)malloc(sizeof(TextBox));      
        TB->ID = ID;
        TB->next = NULL;
        TB->prev = NULL;

        StdFontStyle(TB);
    }
    else
    {
        TextBox* NTB;
        NTB = (TextBox*)malloc(sizeof(TextBox));
        NTB->ID = ID;
        NTB->next = NULL;
        StdFontStyle(NTB);

        if (TB->next == NULL)
        {
            TB->next = NTB;
            NTB->prev = TB;
        }
        else
        {
            while (TB->next != NULL) { TB = TB->next; }

            TB->next = NTB;
            NTB->prev = TB;

            while (TB->prev != NULL) { TB = TB->prev; }
        }
    }

    cout << "textbox: " << c <<" Created"<<endl;

    return;
}

void Text2D::Select(const wchar_t* ID)
{  
    SelectedTextBox = ID;   
}

void Text2D::Update(const wchar_t* ID, float TextSize, int posX, int posY, D2D1::ColorF color)
{
    if (posX > H_res)
    {
        posX = H_res;
    }
    if (posY > V_res)
    {
        posY = V_res;
    }

    TextBox* FT = TB;

    while (true)
    {
        if (FT->ID != ID)
        {
            if (FT->next != NULL)FT = FT->next;
            else { cout << "TEXTBOX UPDATE:NOT FOUND"; return; }
        }
        else break;
    }

    HRESULT hr = DWriteFactory->CreateTextFormat(
        L"Unispace",
        NULL,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        TextSize,
        L"en-us",
        &FT->TextFormat
    );

    FT->size = TextSize;

    hr = FT->TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    hr = FT->TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &FT->Brush);

    FT->rect = D2D1::RectF(posX, posY, H_res, V_res);

}

void Text2D::Update(float TextSize, int posX, int posY, D2D1::ColorF color)
{
    if (SelectedTextBox == NULL)
    {
        return;
    }

    if (posX > H_res)
    {
        posX = H_res;
    }
    if (posY > V_res)
    {
        posY = V_res;
    }

    TextBox* FT = TB;

    while (true)
    {
        if (FT->ID != SelectedTextBox)
        {
            if (FT->next != NULL)FT = FT->next;
            else { cout << "TEXTBOX UPDATE:NOT FOUND"; return; }
        }
        else break;
    }

    HRESULT hr = DWriteFactory->CreateTextFormat(
        L"Unispace",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        TextSize,
        L"en-us",
        &FT->TextFormat
    );

    FT->size = TextSize;

    hr = FT->TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    hr = FT->TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &FT->Brush);

    FT->rect = D2D1::RectF(posX, posY, H_res, V_res);
}

void Text2D::Render(const wchar_t* ID, const wchar_t* text)
{
    TextBox* FT = TB;

    while (true)
    {
        if (FT->ID != ID)
        {
            if (FT->next != NULL)FT = FT->next;
            else { cout << "TEXTBOX RENDER:NOT FOUND"; return; }
        }
        else break;
    }

    Start2Din3D();

    //Draw D2D content        
    D2DRenderTarget->BeginDraw();
   
    D2DRenderTarget->DrawText(text, (UINT32)wcslen(text), FT->TextFormat, FT->rect, FT->Brush);

    FT->ActualText = text;
    D2DRenderTarget->EndDraw();

    End2Din3D();
}

void Text2D::Render(const wchar_t* text)
{
    if (SelectedTextBox == NULL)
    {
        return;
    }

    TextBox* FT = TB;

    while (true)
    {
        if (FT->ID != SelectedTextBox)
        {
            if (FT->next != NULL)FT = FT->next;
            else { cout << "TEXTBOX RENDER:NOT FOUND"; return; }
        }
        else break;
    }

    Start2Din3D();

    //Draw D2D content        
    D2DRenderTarget->BeginDraw();

    D2DRenderTarget->DrawText(text, (UINT32)wcslen(text), FT->TextFormat, FT->rect, FT->Brush);

    FT->ActualText = text;
    D2DRenderTarget->EndDraw();

    End2Din3D();
}

void Text2D::Release()
{
    TextBox* Temp_TB = TB;
    while (true)
    {
        if (Temp_TB != NULL)
        {
            TextBox* TTemp = Temp_TB->next;
            free(Temp_TB);
            Temp_TB = TTemp;
        }
        else break;
    }
}

void Text2D::StdFontStyle(TextBox* FT)
{
    HRESULT hr = DWriteFactory->CreateTextFormat(
        L"Arial",
        NULL,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        20.0f,
        L"en-us",
        &FT->TextFormat
    );

    hr = FT->TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    hr = FT->TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &FT->Brush);

    FT->rect = D2D1::RectF(0, 0, H_res, V_res);
}

