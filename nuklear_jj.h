#ifndef __NUKLEAR_JJ_H__
#define __NUKLEAR_JJ_H__

enum nk_theme {
        THEME_DEFAULT,
        THEME_BLACK,
        THEME_WHITE,
        THEME_RED,
        THEME_BLUE,
        THEME_GREEN,
        THEME_PURPLE,
        THEME_BROWN,
        THEME_DRACULA,
        THEME_DARK,
        THEME_GRUVBOX,
        NUM_NK_THEMES,
};

static inline void nk_set_style(struct nk_context *ctx, enum nk_theme theme)
{
        struct nk_color table[NK_COLOR_COUNT];

        switch (theme) {
        case THEME_BLACK:
        case THEME_DEFAULT:
                nk_style_default(ctx);
                return;

        case THEME_WHITE:
                table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(175, 175, 175, 255);
                table[NK_COLOR_HEADER] = nk_rgba(175, 175, 175, 255);
                table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(185, 185, 185, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(170, 170, 170, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(150, 150, 150, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(120, 120, 120, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(175, 175, 175, 255);
                table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(175, 175, 175, 255);
                table[NK_COLOR_EDIT] = nk_rgba(150, 150, 150, 255);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
                table[NK_COLOR_COMBO] = nk_rgba(175, 175, 175, 255);
                table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(180, 180, 180, 255);
                break;

        case THEME_RED:
                table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
                table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
                table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
                table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
                table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
                break;

        case THEME_BLUE:
                table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
                table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
                table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(137, 182, 224, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
                table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
                table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
                break;

        case THEME_GREEN:
                table[NK_COLOR_TEXT] = nk_rgba(244, 244, 244, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(57, 71, 58, 215);
                table[NK_COLOR_HEADER] = nk_rgba(52, 57, 52, 220);
                table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(48, 112, 54, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(71, 161, 80, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(89, 201, 100, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(50, 61, 50, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(73, 84, 72, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 112, 54, 255);
                table[NK_COLOR_SELECT] = nk_rgba(58, 67, 57, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 112, 54, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(50, 61, 50, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 112, 54, 245);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(59, 115, 53, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(71, 161, 80, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(50, 61, 50, 255);
                table[NK_COLOR_EDIT] = nk_rgba(50, 61, 50, 225);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_COMBO] = nk_rgba(50, 61, 50, 255);
                table[NK_COLOR_CHART] = nk_rgba(50, 61, 50, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 112, 54, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 61, 50, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 112, 54, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(59, 115, 53, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(71, 161, 80, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 112, 54, 255);
                break;

        case THEME_BROWN:
                table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(71, 67, 57, 215);
                table[NK_COLOR_HEADER] = nk_rgba(56, 51, 51, 220);
                table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(111, 83, 48, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(121, 93, 58, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(126, 98, 63, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(61, 58, 50, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(56, 53, 45, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(111, 83, 48, 255);
                table[NK_COLOR_SELECT] = nk_rgba(61, 67, 57, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(111, 83, 48, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(61, 58, 50, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(111, 83, 48, 245);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(116, 88, 53, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(121, 93, 58, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(61, 58, 50, 255);
                table[NK_COLOR_EDIT] = nk_rgba(61, 58, 50, 225);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_COMBO] = nk_rgba(61, 58, 50, 255);
                table[NK_COLOR_CHART] = nk_rgba(61, 58, 50, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(111, 83, 48, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(0, 0, 255, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(61, 58, 50, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(111, 83, 48, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(116, 88, 53, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(121, 93, 58, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(111, 83, 48, 255);
                break;

        case THEME_PURPLE:
                table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(67, 57, 71, 215);
                table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
                table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(83, 48, 111, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(93, 58, 121, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(98, 63, 126, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(58, 50, 61, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(53, 45, 56, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(83, 48, 111, 255);
                table[NK_COLOR_SELECT] = nk_rgba(67, 57, 61, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(83, 48, 111, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(58, 50, 61, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(83, 48, 111, 245);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(88, 53, 116, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(93, 58, 121, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(58, 50, 61, 255);
                table[NK_COLOR_EDIT] = nk_rgba(58, 50, 61, 225);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_COMBO] = nk_rgba(58, 50, 61, 255);
                table[NK_COLOR_CHART] = nk_rgba(58, 50, 61, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(83, 48, 111, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(0, 255, 0, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(58, 50, 61, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(83, 48, 111, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(88, 53, 116, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(93, 58, 121, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(83, 48, 111, 255);
                break;

        case THEME_DARK:
                table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
                table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
                table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
                table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
                table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
                table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
                table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
                break;

        case THEME_DRACULA:
                table[NK_COLOR_TEXT] = nk_rgba(248, 248, 242, 255);
                table[NK_COLOR_WINDOW] = nk_rgba(68, 71, 90, 255);
                table[NK_COLOR_HEADER] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
                table[NK_COLOR_BUTTON] = nk_rgba(98, 114, 164, 255);
                table[NK_COLOR_BUTTON_HOVER] = nk_rgba(255, 121, 198, 255);
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(255, 85, 85, 255);
                table[NK_COLOR_TOGGLE] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(255, 121, 198, 255);
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(255, 85, 85, 255);
                table[NK_COLOR_SELECT] = nk_rgba(98, 114, 164, 255);
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(255, 85, 85, 255);
                table[NK_COLOR_SLIDER] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(98, 114, 164, 255);
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(255, 121, 198, 255);
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(255, 85, 85, 255);
                table[NK_COLOR_PROPERTY] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_EDIT] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_EDIT_CURSOR] = nk_rgba(255, 184, 108, 255);
                table[NK_COLOR_COMBO] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_CHART] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_CHART_COLOR] = nk_rgba(68, 71, 90, 255);
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 184, 108, 255);
                table[NK_COLOR_SCROLLBAR] = nk_rgba(40, 42, 54, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(98, 114, 164, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(255, 121, 198, 255);
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(255, 85, 85, 255);
                table[NK_COLOR_TAB_HEADER] = nk_rgba(255, 85, 85, 255);
                break;

        case THEME_GRUVBOX:
                table[NK_COLOR_TEXT] = nk_rgb_hex("#ebdbb2");                   /* fg */
                table[NK_COLOR_WINDOW] = nk_rgb_hex("#32302f");                 /* bg0_s */
                table[NK_COLOR_HEADER] = nk_rgb_hex("#076678");                 /* blue-b */
                table[NK_COLOR_BORDER] = nk_rgb_hex("#928374");                 /* gray-f */
                table[NK_COLOR_BUTTON] = nk_rgb_hex("#104b5b");
                table[NK_COLOR_BUTTON_HOVER] = nk_rgb_hex("#076678");           /* blue-f in light mode */
                table[NK_COLOR_BUTTON_ACTIVE] = nk_rgb_hex("#076678");          /* blue-f in light mode */
                table[NK_COLOR_TOGGLE] = nk_rgb_hex("#1d2021");                 /* bg0_h */
                table[NK_COLOR_TOGGLE_HOVER] = nk_rgb_hex("#928374");           /* gray-f */
                table[NK_COLOR_TOGGLE_CURSOR] = nk_rgb_hex("#458588");          /* blue-b */
                table[NK_COLOR_SELECT] = nk_rgb_hex("#1d2021");                 /* bg0_h */
                table[NK_COLOR_SELECT_ACTIVE] = nk_rgb_hex("#fabd2f");          /* yellow-f */
                table[NK_COLOR_SLIDER] = nk_rgb_hex("#1d2021");                 /* bg0_h */
                table[NK_COLOR_SLIDER_CURSOR] = nk_rgb_hex("#d79921");          /* yellow-b */
                table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgb_hex("#fabd2f");    /* yellow-f */
                table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgb_hex("#fabd2f");   /* yellow-f */
                table[NK_COLOR_PROPERTY] = nk_rgb_hex("#1d2021");               /* bg0_h */
                table[NK_COLOR_EDIT] = nk_rgb_hex("#1d2021");                   /* bg0_h */
                table[NK_COLOR_EDIT_CURSOR] = nk_rgb_hex("#fbf1c7");            /* fg0 (bg0 in light mode) */
                table[NK_COLOR_COMBO] = nk_rgb_hex("#1d2021");                  /* bg0_h */
                table[NK_COLOR_CHART] = nk_rgb_hex("#1d2021");                  /* bg0_h */
                table[NK_COLOR_CHART_COLOR] = nk_rgb_hex("#cc241d");            /* red-b */
                table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgb_hex("#fb4934");  /* red-f */
                table[NK_COLOR_SCROLLBAR] = nk_rgb_hex("#1d2021");              /* bg0_h */
                table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgb_hex("#928374");       /* gray-f */
                table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgb_hex("#a899a4"); /* gray-b */
                table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgb_hex("#a899a4");/* gray-b */
                table[NK_COLOR_TAB_HEADER] = nk_rgb_hex("#104b5b");
                break;

        default:
                return;
        }

        nk_style_from_table(ctx, table);
}

NK_API void nk_widget_tooltip(struct nk_context *ctx, const char *tooltip)
{
        struct nk_rect bounds = nk_widget_bounds(ctx);
        if (nk_input_is_mouse_hovering_rect(&ctx->input, bounds)) {
                nk_tooltip(ctx, tooltip);
        }
}

NK_API nk_bool nk_button_label_disabled(struct nk_context *ctx, const char *title, int disabled)
{
        struct nk_style_button t = ctx->style.button;
        nk_bool ret;

        if (disabled) {
                ctx->style.button.normal = nk_style_item_color(nk_rgb(40,40,40));
                ctx->style.button.hover = nk_style_item_color(nk_rgb(40,40,40));
                ctx->style.button.active = nk_style_item_color(nk_rgb(40,40,40));
                ctx->style.button.border_color = nk_rgb(60,60,60);
                ctx->style.button.text_background = nk_rgb(60,60,60);
                ctx->style.button.text_normal = nk_rgb(60,60,60);
                ctx->style.button.text_hover = nk_rgb(60,60,60);
                ctx->style.button.text_active = nk_rgb(60,60,60);;
        }

        ret = nk_button_label(ctx, title);

        if (disabled) {
                ctx->style.button = t;
        }

        return ret;
}

#endif // __NUKLEAR_JJ_H__