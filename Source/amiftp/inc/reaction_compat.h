/* reaction_compat.h -- Restore varargs gadget macros suppressed by NO_INLINE_STDARG.
 *
 * NO_INLINE_STDARG is required to keep NewObject() as a plain function call so the
 * ReAction layout macro cascade (LayoutObject, ... LayoutEnd) works with GCC.
 * Unfortunately it also disables varargs macros for AllocListBrowserNode etc.
 * This header re-provides them using _sfdc_vararg, which is defined in each inline
 * header for APTR (with __attribute__((iptr))) or ULONG.
 *
 * Include AFTER all proto/gadget includes so the A-variants are already defined.
 */

#ifndef REACTION_COMPAT_H
#define REACTION_COMPAT_H

#ifdef __GNUC__

/* listbrowser.gadget */
#ifndef AllocListBrowserNode
#define AllocListBrowserNode(___columns, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; AllocListBrowserNodeA((___columns), (struct TagItem *) _tags); })
#endif
#ifndef SetListBrowserNodeAttrs
#define SetListBrowserNodeAttrs(___node, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; SetListBrowserNodeAttrsA((___node), (struct TagItem *) _tags); })
#endif
#ifndef GetListBrowserNodeAttrs
#define GetListBrowserNodeAttrs(___node, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; GetListBrowserNodeAttrsA((___node), (struct TagItem *) _tags); })
#endif

/* chooser.gadget */
#ifndef AllocChooserNode
#define AllocChooserNode(___firstTag, ...) \
    ({_sfdc_vararg _tags[] = { ___firstTag, __VA_ARGS__ }; AllocChooserNodeA((struct TagItem *) _tags); })
#endif
#ifndef GetChooserNodeAttrs
#define GetChooserNodeAttrs(___node, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; GetChooserNodeAttrsA((___node), (struct TagItem *) _tags); })
#endif

/* clicktab.gadget */
#ifndef AllocClickTabNode
#define AllocClickTabNode(___firstTag, ...) \
    ({_sfdc_vararg _tags[] = { ___firstTag, __VA_ARGS__ }; AllocClickTabNodeA((struct TagItem *) _tags); })
#endif

/* speedbar.gadget */
#ifndef AllocSpeedButtonNode
#define AllocSpeedButtonNode(___number, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; AllocSpeedButtonNodeA((___number), (struct TagItem *) _tags); })
#endif
#ifndef SetSpeedButtonNodeAttrs
#define SetSpeedButtonNodeAttrs(___node, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; SetSpeedButtonNodeAttrsA((___node), (struct TagItem *) _tags); })
#endif
#ifndef GetSpeedButtonNodeAttrs
#define GetSpeedButtonNodeAttrs(___node, ____tag1, ...) \
    ({_sfdc_vararg _tags[] = { ____tag1, __VA_ARGS__ }; GetSpeedButtonNodeAttrsA((___node), (struct TagItem *) _tags); })
#endif

#endif /* __GNUC__ */

#endif /* REACTION_COMPAT_H */
