#ifndef NK_GDI_WINDOW
#define NK_GDI_WINDOW

#define NK_GDI_WINDOW_CLS               L"WNDCLS_NkGdi"

#include <windows.h>
#include <winuser.h>

#define WM_NKGDI_WND_UPDATE             (WM_USER + 60)
#define WM_NKGDI_WND_MAGIC              (0xc0cacac0)

struct nkgdi_window;

/* Functin pointer types for window callbacks */
typedef int(*nkgdi_window_func_close)(struct nkgdi_window *);

typedef int(*nkgdi_window_func_draw)(struct nkgdi_window *, struct nk_context *);

/* Window container / context */
struct nkgdi_window {
        /* The window can be sized */
        int allow_sizing;
        /* The window can be maximized by double clicking the titlebar */
        int allow_maximize;
        /* The window is allowed to be moved by the user */
        int allow_move;
        /* The window will render it's title bar */
        int has_titlebar;

        int always_on_top;

        int close_on_focus_lose;

        int update_on_foreground_only;
        int fps_max;

        char *font_name;
        int font_size;
        int font_weight; // FW_NORMAL/FW_BOLD/etc

        /* Callbacks */
        nkgdi_window_func_close cb_on_close;
        /* Called when the user or os requests a window close (return 1 to accept the reqest)*/
        /* Called each time the window content should be drawn. Here you will do your nuklear drawing code
         * but WITHOUT nk_begin and nk_end. Return 1 to keep the window open.
         */
        nkgdi_window_func_draw cb_on_draw;

        /* Internal Data */
        struct {
                void *userdata;

                /* Window handle */
                HWND window_handle;
                HICON icon;

                /* Nuklear & GDI context */
                nk_gdi_ctx nk_gdi_ctx;
                struct nk_context *nk_ctx;

                /* GDI required objects */
                GdiFont *gdi_font;
                HDC window_dc;

                /* Internally used state variables */
                int is_open;
                int is_draggin;
                int is_on_focus;
                int ws_override;
                int is_maximized;
                POINT drag_offset;
                int width;
                int height;
        } _internal;
};

/* API */
/* This function will init all resources used by the implementation */
void nkgdi_window_init(void);

/* This function will free all globally used resources */
void nkgdi_window_shutdown(void);

/* Creates a new window (for the wnd context) */
int nkgdi_window_create(struct nkgdi_window *wnd, unsigned int width, unsigned int height, const char *name, int posX,
                        int posY);

/* Updates the window (Windows message loop, nuklear loop and drawing). Returns one as long as the window is valid and open */
int nkgdi_window_update(struct nkgdi_window *wnd);

/* Destroys the window context wnd */
void nkgdi_window_destroy(struct nkgdi_window *wnd);

#ifdef NKGDI_IMPLEMENT_WINDOW

/* Predeclare the windows window message procs */
/* This proc will setup the pointer to the window context */
LRESULT CALLBACK nkgdi_window_proc_setup(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

/* This proc will take the window context pointer and performs operations on it*/
LRESULT CALLBACK nkgdi_window_proc_run(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

void nkgdi_window_init(void)
{
        /* Describe the window class */
        WNDCLASSEXW cls;
        cls.cbSize = sizeof(WNDCLASSEXW);
        cls.style = CS_OWNDC | CS_DBLCLKS;
        cls.lpfnWndProc = &nkgdi_window_proc_setup;
        cls.cbClsExtra = 0;
        cls.cbWndExtra = 0;
        cls.hInstance = GetModuleHandle(NULL);
        cls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        cls.hCursor = LoadCursor(NULL, IDC_ARROW);
        cls.hbrBackground = NULL;
        cls.lpszMenuName = NULL;
        cls.lpszClassName = NK_GDI_WINDOW_CLS;
        cls.hIconSm = NULL;

        /* Register the window class */
        RegisterClassExW(&cls);
}

void nkgdi_window_shutdown(void)
{
        /* Windows class no longer required, unregister it */
        UnregisterClassW(NK_GDI_WINDOW_CLS, GetModuleHandle(NULL));
}

static inline struct nk_context *nkgdi_window_nkctx_get(struct nkgdi_window *wnd)
{
        return wnd->_internal.nk_ctx;
}

static inline HWND nkgdi_window_hwnd_get(struct nkgdi_window *wnd)
{
        return wnd->_internal.window_handle;
}

static inline void nkgdi_window_userdata_set(struct nkgdi_window *wnd, void *userdata)
{
        wnd->_internal.userdata = userdata;
}

static inline void *nkgdi_window_userdata_get(struct nkgdi_window *wnd)
{
        return wnd->_internal.userdata;
}

int nkgdi_window_create(struct nkgdi_window *wnd, unsigned int width, unsigned int height, const char *name, int posX,
                        int posY)
{
        DWORD styleEx = WS_EX_WINDOWEDGE;
        DWORD style = WS_POPUP;

        /* Adjust window size to fit selected window styles */
        RECT cr;
        cr.left = 0;
        cr.top = 0;
        cr.right = width;
        cr.bottom = height;
        AdjustWindowRectEx(&cr, style, FALSE, styleEx);

        /* Create the new window */
        wnd->_internal.window_handle = CreateWindowExW(
                styleEx,
                NK_GDI_WINDOW_CLS,
                L"NkGdi",
                style | WS_VISIBLE,
                posX, posY,
                cr.right - cr.left, cr.bottom - cr.top,
                NULL, NULL,
                GetModuleHandleW(NULL),
                wnd
                );

        /* Give the window the ascii char name */
        SetWindowTextA(wnd->_internal.window_handle, name);

        SetWindowPos(wnd->_internal.window_handle,
                     wnd->always_on_top ? HWND_TOPMOST : NULL,
                     0, 0, cr.right - cr.left, cr.bottom - cr.top,
                     SWP_NOMOVE | SWP_NOOWNERZORDER);

        /* Extract the window dc for gdi drawing */
        wnd->_internal.window_dc = GetWindowDC(wnd->_internal.window_handle);

        /* Create the gdi font required to draw text */
        wnd->_internal.gdi_font = nk_gdifont_create(wnd->font_name ? wnd->font_name : "Arial",
                                                    wnd->font_size > 0 ? wnd->font_size : 16,
                                                    wnd->font_weight >= 0 ? wnd->font_weight : FW_NORMAL);
        if (!wnd->_internal.gdi_font)
                return -1;

        /* Init the gdi backend */
        wnd->_internal.nk_ctx = nk_gdi_init(&wnd->_internal.nk_gdi_ctx, wnd->_internal.gdi_font,
                                            wnd->_internal.window_dc, width, height);

        /* Bring all internal variables to a defined and valid initial state */
        wnd->_internal.is_open = 1;
        wnd->_internal.is_draggin = 0;
        wnd->_internal.ws_override = 0;
        wnd->_internal.is_maximized = 0;
        wnd->_internal.drag_offset.x = 0;
        wnd->_internal.drag_offset.y = 0;
        wnd->_internal.width = width;
        wnd->_internal.height = height;

        if (wnd->fps_max == 0)
                wnd->fps_max = 120;

        return 0;
}

void nkgdi_window_destroy(struct nkgdi_window *wnd)
{
        /* Destroy all objects in reverse order */
        if (wnd->_internal.nk_gdi_ctx) {
                nk_gdi_shutdown(wnd->_internal.nk_gdi_ctx);
        }

        if (wnd->_internal.gdi_font) {
                nk_gdifont_del(wnd->_internal.gdi_font);
        }

        if (wnd->_internal.window_dc) {
                ReleaseDC(wnd->_internal.window_handle, wnd->_internal.window_dc);
        }

        if (wnd->_internal.icon) {
                DestroyIcon(wnd->_internal.icon);
        }

        if (wnd->_internal.window_handle) {
                CloseWindow(wnd->_internal.window_handle);
                DestroyWindow(wnd->_internal.window_handle);
        }
}

void _nkgdi_window_update(struct nkgdi_window *wnd)
{
        /* To setup the nuklear window we need the windows title */
        char title[256];

        GetWindowTextA(wnd->_internal.window_handle, title, sizeof(title));

        /* The nk window flags are beeing create based on the context setup */
        nk_flags window_flags = NK_WINDOW_BORDER;
        if (wnd->has_titlebar)
                window_flags |= NK_WINDOW_CLOSABLE | NK_WINDOW_TITLE;
        if (!wnd->_internal.is_maximized && wnd->allow_sizing)
                window_flags |= NK_WINDOW_SCALABLE;

        /* Override the nuklear windows size when required */
        if (wnd->_internal.ws_override)
                nk_window_set_bounds(wnd->_internal.nk_ctx, title,
                                     nk_rect(0, 0, wnd->_internal.width, wnd->_internal.height));

        /* Start the nuklear window */
        if (nk_begin(wnd->_internal.nk_ctx, title, nk_rect(0, 0, wnd->_internal.width, wnd->_internal.height),
                     window_flags)) {
                /* Call user drawing callback */
                if (wnd->cb_on_draw && !wnd->cb_on_draw(wnd, wnd->_internal.nk_ctx)) {
                        wnd->_internal.is_open = 0;
                        if (wnd->cb_on_close)
                                wnd->cb_on_close(wnd);
                }

                /* Update the windows window to reflect the nuklear windows size */
                struct nk_rect bounds = nk_window_get_bounds(wnd->_internal.nk_ctx);
                if (bounds.w != wnd->_internal.width || bounds.h != wnd->_internal.height)
                        SetWindowPos(wnd->_internal.window_handle,
                                     wnd->always_on_top ? HWND_TOPMOST : NULL,
                                     0, 0, bounds.w, bounds.h,
                                     SWP_NOMOVE | SWP_NOOWNERZORDER);
        } else {
                /* Nuklear window was closed. Handle close internally */
                if (!wnd->cb_on_close || wnd->cb_on_close(wnd))
                        wnd->_internal.is_open = 0;
        }
        nk_end(wnd->_internal.nk_ctx);

        /* We no longer need the window size override flag to be set */
        wnd->_internal.ws_override = 0;

        /* Pass context to the nuklear gdi renderer */
        nk_gdi_render(wnd->_internal.nk_gdi_ctx, nk_rgb(0, 0, 0));

        if (wnd->close_on_focus_lose && !wnd->_internal.is_on_focus) {
                if (!wnd->cb_on_close || wnd->cb_on_close(wnd))
                        wnd->_internal.is_open = 0;
        }
}

// Non-blocking update, need to call in a loop outside
int nkgdi_window_peek_update(struct nkgdi_window *wnd)
{
        /* The window will only be updated when it is open / valid */
        if (wnd->_internal.is_open) {
                /* First all pending window events will be processed */
                MSG msg;
                nk_input_begin(wnd->_internal.nk_ctx);
                while (PeekMessage(&msg, wnd->_internal.window_handle, 0, 0, PM_REMOVE)) {
                        TranslateMessage(&msg);
                        DispatchMessageW(&msg);
                }
                nk_input_end(wnd->_internal.nk_ctx);

                _nkgdi_window_update(wnd);
        }

        return wnd->_internal.is_open;
}

void *nkgdi_window_periodic_updater(void *data)
{
        struct nkgdi_window *wnd = data;
        HWND hwnd = wnd->_internal.window_handle;

        while (1) {
                if (!wnd->_internal.is_open)
                        break;

                if (wnd->fps_max > 0)
                        Sleep(1000 / wnd->fps_max);

                if (wnd->update_on_foreground_only && GetForegroundWindow() != hwnd)
                        continue;

                PostMessage(hwnd, WM_NKGDI_WND_UPDATE, WM_NKGDI_WND_MAGIC, 0);
        }

        pthread_exit(NULL);
        return NULL;
}

// Blocking update
void nkgdi_window_blocking_update(struct nkgdi_window *wnd)
{
        pthread_t periodic_updater;
        MSG msg;

        if (pthread_create(&periodic_updater, NULL, nkgdi_window_periodic_updater, wnd))
                periodic_updater = 0;

        while (GetMessage(&msg, wnd->_internal.window_handle, 0, 0)) {
                nk_input_begin(wnd->_internal.nk_ctx);
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
                nk_input_end(wnd->_internal.nk_ctx);

                _nkgdi_window_update(wnd);

                if (!wnd->_internal.is_open)
                        break;
        }

        if (periodic_updater)
                pthread_join(periodic_updater, NULL);
}

inline int nkgdi_window_update(struct nkgdi_window *wnd)
{
        return nkgdi_window_peek_update(wnd);
}

LRESULT CALLBACK nkgdi_window_proc_setup(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        /* Waiting to receive the NCCREATE message with the custom window data */
        if (msg == WM_NCCREATE) {
                /* Extracting the window context from message parameters */
                CREATESTRUCT *ptrCr = (CREATESTRUCT *)lParam;
                struct nkgdi_window *nkgdi_wnd = (struct nkgdi_window *)ptrCr->lpCreateParams;

                /* Store the context in the window and redirect any further message to the run window proc*/
                SetWindowLongPtr(wnd, GWLP_USERDATA, (LONG_PTR)nkgdi_wnd);
                SetWindowLongPtr(wnd, GWLP_WNDPROC, (LONG_PTR)&nkgdi_window_proc_run);

                /* Already call the run proc so that it gets the chance to handle NCCREATE as well */
                return nkgdi_window_proc_run(wnd, msg, wParam, lParam);
        }

        /* Until we get WM_NCCREATE windows is going to handle the messages */
        return DefWindowProc(wnd, msg, wParam, lParam);
}

LRESULT CALLBACK nkgdi_window_proc_run(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        /* The window context is extracted from the window data */
        struct nkgdi_window *nkwnd = (struct nkgdi_window *)GetWindowLongPtrW(wnd, GWLP_USERDATA);

        /* Switch on the message code to handle all required messages */
        switch (msg) {
                /* Window close event */
        case WM_CLOSE:
                /* Call custom close callback */
                if (!nkwnd->cb_on_close || nkwnd->cb_on_close(nkwnd))
                        nkwnd->_internal.is_open = 0;
                return 0; /* No default behaviour. We do it our own way */

                /* Window sizing event (is currently beeing sized) */
        case WM_SIZING: {
                /* Size of the client / active are is extracted and stored */
                RECT cr;
                GetClientRect(wnd, &cr);
                nkwnd->_internal.width = cr.right - cr.left;
                nkwnd->_internal.height = cr.bottom - cr.top;
        }
                break;

                /* Window size event (done sizing, maximize, minimize, ...) */
        case WM_SIZE: {
                /* Window was maximized */
                if (wParam == SIZE_MAXIMIZED) {
                        /* Get the nearest monitor and retrive its details */
                        HMONITOR monitor = MonitorFromWindow(wnd, MONITOR_DEFAULTTOPRIMARY);
                        MONITORINFO monitorInfo;
                        monitorInfo.cbSize = sizeof(MONITORINFO);
                        if (GetMonitorInfoW(monitor, &monitorInfo)) {
                                /* Adjust the window size and position by the monitor working area (without taskbar) */
                                nkwnd->_internal.height = monitorInfo.rcWork.bottom - monitorInfo.rcWork.top;
                                nkwnd->_internal.width = monitorInfo.rcWork.right - monitorInfo.rcWork.left;
                                nkwnd->_internal.ws_override = 1; /* Sizing was done without nuklear beeing aware. So we need to override it */
                                nkwnd->_internal.is_maximized = 1;
                                SetWindowPos(wnd, nkwnd->always_on_top ? HWND_TOPMOST : NULL,
                                             0, 0, nkwnd->_internal.width, nkwnd->_internal.height,
                                             SWP_NOMOVE | SWP_NOZORDER);
                        }
                }
                        /* Window was restored (no longer maximized) */
                else if (wParam == SIZE_RESTORED) {
                        nkwnd->_internal.is_maximized = 0;
                }

                /* Always get the new bounds of the window */
                RECT cr;
                GetClientRect(wnd, &cr);
                nkwnd->_internal.width = cr.right - cr.left;
                nkwnd->_internal.height = cr.bottom - cr.top;
        }
                break;

                /* Mouse started left click */
        case WM_LBUTTONDOWN: {
                /* Handle dragging when allowed, has titlebar and mouse is in titlebar (Y <= 30) */
                if (HIWORD(lParam) <= 30 && nkwnd->allow_move && nkwnd->has_titlebar) {
                        /* Mark dragging internally and store mouse click offset */
                        nkwnd->_internal.is_draggin = 1;
                        nkwnd->_internal.drag_offset.x = LOWORD(lParam);
                        nkwnd->_internal.drag_offset.y = HIWORD(lParam);
                }
        }
                break;

                /* Mouse stoped left click */
        case WM_LBUTTONUP:
                /* No longer dragging the window */
                nkwnd->_internal.is_draggin = 0;
                break;

                /* Mouse is moving on the window */
        case WM_MOUSEMOVE: {
                /* When we are dragging and are not maximized process dragging */
                if (nkwnd->_internal.is_draggin && !nkwnd->_internal.is_maximized) {
                        /* Get the current global position of the mouse */
                        POINT cursorPos;
                        GetCursorPos(&cursorPos);
                        /* Substract the internal offset */
                        cursorPos.x -= nkwnd->_internal.drag_offset.x;
                        cursorPos.y -= nkwnd->_internal.drag_offset.y;
                        /* Update position of out window and make sure window is in a movable state (= Restored) */
                        ShowWindow(wnd, SW_RESTORE);
                        SetWindowPos(wnd, nkwnd->always_on_top ? HWND_TOPMOST : NULL,
                                     cursorPos.x, cursorPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                }
        }
                break;

                /* Mouse double clicked */
        case WM_LBUTTONDBLCLK: {
                /* Will only affect window when on the titlebar */
                if (HIWORD(lParam) <= 30 && nkwnd->allow_maximize && nkwnd->has_titlebar) {
                        /* When the window is already maximized restore it */
                        if (nkwnd->_internal.is_maximized) {
                                ShowWindow(wnd, SW_RESTORE);
                        }
                                /* Else we gonna do maximize it*/
                        else {
                                ShowWindow(wnd, SW_MAXIMIZE);
                        }
                        /* We overrideed the window size, make sure to affect the nk window as well */
                        nkwnd->_internal.ws_override = 1;
                }
        }
                break;

        case WM_SETFOCUS:
                nkwnd->_internal.is_on_focus = 1;
                break;

        case WM_KILLFOCUS:
                nkwnd->_internal.is_on_focus = 0;
                break;
        }

        /* Allow nuklear to handle the message as well */
        if (nkwnd->_internal.nk_gdi_ctx && nk_gdi_handle_event(nkwnd->_internal.nk_gdi_ctx, wnd, msg, wParam, lParam))
                return 0;

        /* In case we reach this line our code and nuklear did not respond to the message. Allow windows to handle it s*/
        return DefWindowProc(wnd, msg, wParam, lParam);
}

static inline void nkgdi_window_icon_set(struct nkgdi_window *wnd, HICON hicon)
{
        HWND hwnd = nkgdi_window_hwnd_get(wnd);

        if (wnd->_internal.icon)
                DestroyIcon(wnd->_internal.icon);

        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);

        wnd->_internal.icon = hicon;
}

static inline void nkgdi_window_set_center(struct nkgdi_window *wnd)
{
        HWND hwnd = nkgdi_window_hwnd_get(wnd);
        HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
        MONITORINFO monitorInfo;

        monitorInfo.cbSize = sizeof(MONITORINFO);
        if (GetMonitorInfoW(monitor, &monitorInfo)) {
                SetWindowPos(nkgdi_window_hwnd_get(wnd),
                             wnd->always_on_top ? HWND_TOPMOST : NULL,
                             abs(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left - wnd->_internal.width) / 2,
                             abs(monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top - wnd->_internal.height) / 2,
                             0, 0,
                             SWP_NOSIZE | SWP_NOZORDER);
        }
}

#endif
#endif
