#include "latticra/lat_pipeline_diagnostics.h"

const char *latticra_lat_pipeline_diagnostic_class_label(
    latticra_lat_pipeline_diagnostic_class_t diagnostic_class) {
    switch (diagnostic_class) {
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID: return "valid";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE: return "parse";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC: return "semantic";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING: return "lowering";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR: return "lir";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_EFFECT_CHECK: return "effect-check";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL: return "model";
    case LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL:
    default: return "internal";
    }
}
