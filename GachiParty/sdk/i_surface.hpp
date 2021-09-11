#pragma once
#include "Vector2D.hpp"
#include "i_app_system.hpp"
using VPANEL = unsigned int;
using HFont = unsigned int;
struct Vertex_t
{
    Vertex_t() {}
    Vertex_t(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
    {
        m_Position = pos;
        m_TexCoord = coord;
    }
    void Init(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
    {
        m_Position = pos;
        m_TexCoord = coord;
    }

    Vector2D m_Position;
    Vector2D m_TexCoord;
};
struct IntRect
{
    int x0;
    int y0;
    int x1;
    int y1;
};
class i_surface : public IAppSystem
{
public:
    virtual void          run_frame() = 0;
    virtual VPANEL  get_embedded_panel() = 0;
    virtual void          set_embedded_panel(VPANEL pPanel) = 0;
    virtual void          push_make_current(VPANEL panel, bool useInsets) = 0;
    virtual void          pop_make_current(VPANEL panel) = 0;
    virtual void          draw_set_color(int r, int g, int b, int a) = 0;
    virtual void          draw_set_color(void* col) = 0;
    virtual void          draw_filled_rect(int x0, int y0, int x1, int y1) = 0;
    virtual void          draw_filled_rect_array(IntRect* pRects, int numRects) = 0;
    virtual void          draw_outlined_rect(int x0, int y0, int x1, int y1) = 0;
    virtual void          draw_line(int x0, int y0, int x1, int y1) = 0;
    virtual void          draw_poly_line(int* px, int* py, int numPoints) = 0;
    virtual void          draw_set_apparent_depth(float f) = 0;
    virtual void          draw_clear_apparent_depth(void) = 0;
    virtual void          draw_set_text_font(unsigned int font) = 0;
    virtual void          draw_set_text_color(int r, int g, int b, int a) = 0;
    virtual void          draw_set_text_color(void* col) = 0;
    virtual void          draw_set_text_pos(int x, int y) = 0;
    virtual void          draw_get_text_pos(int& x, int& y) = 0;
    virtual void skip00() = 0;
    virtual void skip01() = 0;
   // virtual void          DrawPrintText(const wchar_t* text, int textLen, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT) = 0;
   // virtual void          DrawUnicodeChar(wchar_t wch, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT) = 0;
    virtual void          draw_flush_text() = 0;
    virtual void* create_html_window(void* events, VPANEL context) = 0;
    virtual void          paint_html_window(void* htmlwin) = 0;
    virtual void          delete_html_window(void* htmlwin) = 0;
    virtual int           draw_get_texture_id(char const* filename) = 0;
    virtual bool          draw_get_texture_file(int id, char* filename, int maxlen) = 0;
    virtual void          draw_set_texture_file(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
    virtual void          draw_set_texture_rgba(int id, const unsigned char* rgba, int wide, int tall) = 0;
    virtual void          draw_set_texture(int id) = 0;
    virtual void          delete_texture_by_id(int id) = 0;
    virtual void          draw_get_texture_size(int id, int& wide, int& tall) = 0;
    virtual void          draw_textured_rect(int x0, int y0, int x1, int y1) = 0;
    virtual bool          is_texture_id_valid(int id) = 0;
    virtual int           create_new_texture_id(bool procedural = false) = 0;
    virtual void          get_screen_size(int& wide, int& tall) = 0;
    virtual void          set_as_top_most(VPANEL panel, bool state) = 0;
    virtual void          bring_to_font(VPANEL panel) = 0;
    virtual void          set_foreground_window(VPANEL panel) = 0;
    virtual void          set_panel_visible(VPANEL panel, bool state) = 0;
    virtual void          set_minimized(VPANEL panel, bool state) = 0;
    virtual bool          is_minimized(VPANEL panel) = 0;
    virtual void          flash_window(VPANEL panel, bool state) = 0;
    virtual void          set_title(VPANEL panel, const wchar_t* title) = 0;
    virtual void          set_as_tool_bar(VPANEL panel, bool state) = 0;
    virtual void          create_popup(VPANEL panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
    virtual void          swap_buffers(VPANEL panel) = 0;
    virtual void          invalidate(VPANEL panel) = 0;
    virtual void          set_cursor(unsigned long cursor) = 0;
    virtual bool          is_cursor_visible() = 0;
    virtual void          apply_changes() = 0;
    virtual bool          is_within(int x, int y) = 0;
    virtual bool          has_focus() = 0;
    virtual bool          support_feature(int ) = 0;
    virtual void          RestrictPaintToSinglePanel(VPANEL panel, bool bForceAllowNonModalSurface = false) = 0;
    virtual void          set_modal_panel(VPANEL) = 0;
    virtual VPANEL  get_modal_panel() = 0;
    virtual void          unlock_cursor() = 0;
    virtual void          lock_cursor() = 0;
    virtual void          set_translate_extended_keys(bool state) = 0;
    virtual VPANEL  get_tompost_popup() = 0;
    virtual void          SetTopLevelFocus(VPANEL panel) = 0;
    virtual HFont   create_font() = 0;
    virtual bool          set_font_glyph_set(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) = 0;
    virtual bool          add_custom_font_file(const char* fontFileName) = 0;
    virtual int           get_font_tall(HFont font) = 0;
    virtual int           get_font_acsent(HFont font, wchar_t wch) = 0;
    virtual bool          is_font_additive(HFont font) = 0;
    virtual void          GetCharABCwide(HFont font, int ch, int& a, int& b, int& c) = 0;
    virtual int           GetCharacterWidth(HFont font, int ch) = 0;
    virtual void          get_text_size(HFont font, const wchar_t* text, int& wide, int& tall) = 0;
    virtual VPANEL  GetNotifyPanel() = 0;
    virtual void          SetNotifyIcon(VPANEL context, unsigned long icon, VPANEL panelToReceiveMessages, const char* text) = 0;
    virtual void          PlaySound_(const char* fileName) = 0;
    virtual int           GetPopupCount() = 0;
    virtual VPANEL  GetPopup(int index) = 0;
    virtual bool          ShouldPaintChildPanel(VPANEL childPanel) = 0;
    virtual bool          RecreateContext(VPANEL panel) = 0;
    virtual void          AddPanel(VPANEL panel) = 0;
    virtual void          ReleasePanel(VPANEL panel) = 0;
    virtual void          MovePopupToFront(VPANEL panel) = 0;
    virtual void          MovePopupToBack(VPANEL panel) = 0;
    virtual void          SolveTraverse(VPANEL panel, bool forceApplySchemeSettings = false) = 0;
    virtual void          paint_traverse(VPANEL panel) = 0;
    virtual void          EnableMouseCapture(VPANEL panel, bool state) = 0;
    virtual void          GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;
    virtual void          GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;
    virtual void          GetProportionalBase(int& width, int& height) = 0;
    virtual void          CalculateMouseVisible() = 0;
    virtual bool          NeedKBInput() = 0;
    virtual bool          HasCursorPosFunctions() = 0;
    virtual void          SurfaceGetCursorPos(int& x, int& y) = 0;
    virtual void          SurfaceSetCursorPos(int x, int y) = 0;
    virtual void          draw_textured_line(const Vertex_t& a, const Vertex_t& b) = 0;
    virtual void          draw_outlined_circle(int x, int y, int radius, int segments) = 0;
    virtual void          draw_textured_polyline(const Vertex_t* p, int n) = 0;
    virtual void          DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
    virtual void          draw_textured_polygone(int n, Vertex_t* pVertice, bool bClipVertices = true) = 0;
};