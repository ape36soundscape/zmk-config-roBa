/*
 * The pinned PMW3610 driver always links its layer-aware paths, even when the
 * sensor has no layer properties and only forwards raw input from a split
 * peripheral. ZMK intentionally omits the keymap and behavior queue from
 * peripheral builds, so provide unreachable compatibility hooks there.
 */

#include <errno.h>

#include <zephyr/kernel.h>

#include <zmk/behavior_queue.h>
#include <zmk/keymap.h>

zmk_keymap_layer_index_t zmk_keymap_highest_layer_active(void) { return 0; }

int zmk_behavior_queue_add(const struct zmk_behavior_binding_event *event,
                           const struct zmk_behavior_binding behavior, bool press,
                           uint32_t wait) {
    ARG_UNUSED(event);
    ARG_UNUSED(behavior);
    ARG_UNUSED(press);
    ARG_UNUSED(wait);

    return -ENOTSUP;
}
