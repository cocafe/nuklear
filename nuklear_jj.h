#ifndef __NUKLEAR_JJ_H__
#define __NUKLEAR_JJ_H__

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