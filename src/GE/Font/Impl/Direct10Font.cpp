#include "GE/Utils/PreprocessorDef.h"

#if _FONT == FONT_DIRECT_X_10

// 参考：https://www.braynzarsoft.net/viewtutorial/q16390-04-simple-font

#include "../Font.h"
#include <d3dx10.h>
#include <stdexcept>
#include "GE/DataType/Rect.h"
#include "GE/DataType/Color.h"
#include "GE/Debug/Log.h"

namespace GE::Render
{
    extern ID3D10Device* GetDirectXDevice();
    extern void TempEnd2DRender();
    extern void Resume2DRender();
}

namespace GE::Font
{
    namespace
    {
        RECT ConvertRect(const RectPixel& rect)
        {
            return RECT(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
        }

        D3DXCOLOR ConvertColor(const Color& color)
        {
            return D3DXCOLOR(color.r, color.g, color.b, color.a);
        }

        UINT ConvertAlignment(UI::TextVerticalAlignment verticalAlignment, UI::TextHorizontalAlignment horizontalAlignment)
        {
            UINT result = 0;
            switch (verticalAlignment) {
                case UI::TextVerticalAlignment::Top:        result |= DT_TOP;       break;
                case UI::TextVerticalAlignment::Middle:     result |= DT_VCENTER;   break;
                case UI::TextVerticalAlignment::Bottom:     result |= DT_BOTTOM;    break;
            }

            switch (horizontalAlignment) {
                case UI::TextHorizontalAlignment::Left:     result |= DT_LEFT;      break;
                case UI::TextHorizontalAlignment::Center:   result |= DT_CENTER;    break;
                case UI::TextHorizontalAlignment::Right:    result |= DT_RIGHT;     break;
            }

            return result;
        }
    }

    struct DirectX10FontImpl : public Font::FontImpl
    {
        ID3DX10Font* directXFont;

        DirectX10FontImpl() : directXFont(nullptr)
        {
        }

        ~DirectX10FontImpl()
        {
            if (directXFont != nullptr) {
                directXFont->Release();
                directXFont = nullptr;
            }
        }

        void ShowText(
            const std::string & text,
            const RectPixel& rect, 
            const Color& color,
            UI::TextVerticalAlignment verticalAlignment,
            UI::TextHorizontalAlignment horizontalAlignment) const override
        {
            GE::Render::TempEnd2DRender();

            RECT rectangle = ConvertRect(rect);
            directXFont->DrawText(
                nullptr, 
                text.c_str(), 
                -1, 
                &rectangle,
                ConvertAlignment(verticalAlignment, horizontalAlignment),
                ConvertColor(color));

            GE::Render::Resume2DRender();
        }
    };

    Font::Font(const FontInfo& fontInfo) : pImpl(std::make_unique<DirectX10FontImpl>())
    {
        D3DX10_FONT_DESC desc;
        desc.Height = fontInfo.fontSize;
        desc.Width = fontInfo.fontSize / 2;
        desc.Weight = FW_NORMAL;
        desc.MipLevels = 1;
        desc.Italic = false;
        desc.CharSet = DEFAULT_CHARSET;
        desc.OutputPrecision = OUT_DEFAULT_PRECIS;
        desc.Quality = ANTIALIASED_QUALITY;
        desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

        strcpy_s(desc.FaceName, 32, fontInfo.fontName.c_str());

        DirectX10FontImpl* directX10FontImpl = static_cast<DirectX10FontImpl*>(pImpl.get());

        ID3D10Device* device = Render::GetDirectXDevice();
        if (!device) {
            throw std::runtime_error("Font：" + fontInfo.ToString() + "の作成は失敗した。DirectXDeviceが見つけられない。");
        }

        HRESULT result = D3DX10CreateFontIndirect(&(*device), &desc, &(directX10FontImpl->directXFont));
        if (FAILED(result)) {
            throw std::runtime_error("Font：" + fontInfo.ToString() + "の作成は失敗した。DirectXFontが作成できない。");
        }
	}
}

#endif