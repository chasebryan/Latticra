#ifndef LATTICRA_L_UI_STATIC_REPORT_H
#define LATTICRA_L_UI_STATIC_REPORT_H

#include "latticra/nucleus_preview.h"
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_L_UI_REPORT_MAX 1024u

typedef enum {
    LATTICRA_L_UI_REPORT_NUCLEUS_PREVIEW = 0,
    LATTICRA_L_UI_REPORT_UNKNOWN = 1
} latticra_l_ui_report_kind_t;

const char *latticra_l_ui_report_kind_label(latticra_l_ui_report_kind_t kind);

latticra_status_t latticra_l_ui_nucleus_preview_card(
    const latticra_state_lattice_t *state,
    const latticra_nucleus_preview_t *preview,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
