#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

const char *latticra_runtime_boundary_request_kind_label(latticra_runtime_boundary_request_kind_t kind) {
    switch (kind) {
    case LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY: return "parse-only";
    case LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY: return "validate-only";
    case LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY: return "classify-only";
    case LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT: return "render-report";
    case LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT: return "nucleus-task-report";
    case LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE: return "lat-validate";
    case LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE: return "lir-validate";
    case LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK: return "authority-check";
    case LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE: return "lat-pipeline-validate";
    case LATTICRA_RUNTIME_BOUNDARY_UNKNOWN: return "unknown";
    default: return "future-gated";
    }
}

const char *latticra_runtime_boundary_effect_label(latticra_runtime_boundary_effect_t effect) {
    if (effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE) return "none";
    if (effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ) return "read";
    if (effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN) return "unknown";
    return "blocked-effect";
}

const char *latticra_runtime_boundary_mode_label(latticra_runtime_boundary_mode_t mode) {
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY) return "report-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY) return "validation-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_PREVIEW_ONLY) return "preview-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY) return "classification-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_DENY_ALL) return "deny-all";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE) return "future-gated";
    return "disabled";
}

const char *latticra_runtime_boundary_policy_label(latticra_runtime_boundary_policy_t policy) {
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT) return "allow-report";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION) return "allow-validation";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION) return "allow-classification";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_PREVIEW) return "allow-preview";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE) return "future-gated";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_BLOCKED) return "blocked";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_UNSUPPORTED) return "unsupported";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_INTERNAL_ERROR) return "internal-error";
    return "deny";
}

const char *latticra_runtime_boundary_denial_label(latticra_runtime_boundary_denial_t denial) {
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK) return "ok";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT) return "null-argument";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST) return "unknown-request";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT) return "unknown-effect";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED) return "authority-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED) return "task-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED) return "render-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED) return "parser-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_SEMANTIC_FAILED) return "semantic-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED) return "lir-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS) return "non-no-effect-flags";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED) return "runtime-disabled";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED) return "operator-confirmation-not-supported";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE) return "future-gate-required";
    return "blocked";
}

const char *latticra_runtime_boundary_gate_state_label(latticra_runtime_boundary_gate_state_t gate_state) {
    if (gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED) return "planned";
    if (gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED) return "blocked";
    return "disabled";
}

const char *latticra_runtime_boundary_operator_confirmation_label(latticra_runtime_boundary_operator_confirmation_t confirmation) {
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_PRESENT) return "present";
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REQUIRED) return "required";
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REJECTED) return "rejected";
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_SUPPORTED) return "not-supported";
    return "not-applicable";
}

const char *latticra_runtime_boundary_report_classification_label(latticra_runtime_boundary_report_classification_t classification) {
    if (classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_DECLARATIVE) return "declarative";
    if (classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING) return "boundary-seeking";
    if (classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED) return "denied";
    return "invalid";
}

const char *latticra_runtime_boundary_domain_label(latticra_runtime_boundary_domain_t domain) {
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MEMORY) return "memory";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM) return "filesystem";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK) return "network";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS) return "process";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE) return "device";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_CLOCK) return "clock";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_RANDOMNESS) return "randomness";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST) return "host";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_EXTERNAL_CALL) return "external-call";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PERSISTENCE) return "persistence";
    if (domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_SCHEDULER) return "scheduler";
    return "unknown";
}

const char *latticra_runtime_boundary_authorization_state_label(latticra_runtime_boundary_authorization_state_t state) {
    if (state == LATTICRA_RUNTIME_BOUNDARY_AUTH_NOT_REQUESTED) return "not-requested";
    if (state == LATTICRA_RUNTIME_BOUNDARY_AUTH_REQUESTED) return "requested";
    if (state == LATTICRA_RUNTIME_BOUNDARY_AUTH_DENIED) return "denied";
    if (state == LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE) return "reserved-for-future";
    return "unavailable";
}

const char *latticra_runtime_boundary_policy_matrix_cell_label(latticra_runtime_boundary_policy_matrix_cell_t cell) {
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_REPORT) return "no-effect-report";
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_VALIDATION) return "no-effect-validation";
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_CLASSIFICATION) return "no-effect-classification";
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION) return "future-gated-operation";
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT) return "blocked-effect";
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED) return "prerequisite-denied";
    if (cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID) return "invalid";
    return "unsupported";
}

static const char *runtime_lat_pipeline_error_label(latticra_lat_pipeline_error_t error) {
    if (error == LATTICRA_LAT_PIPELINE_OK) return "ok";
    if (error == LATTICRA_LAT_PIPELINE_NULL_ARGUMENT) return "null_argument";
    if (error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK) return "parse_not_ok";
    if (error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK) return "semantic_not_ok";
    if (error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID) return "semantic_not_valid";
    if (error == LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK) return "lowering_not_ok";
    if (error == LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION) return "no_effect_violation";
    if (error == LATTICRA_LAT_PIPELINE_MODEL_NOT_OK) return "model_not_ok";
    return "internal_error";
}

static const char *runtime_lat_pipeline_stage_label(latticra_lat_pipeline_stage_t stage) {
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_NONE) return "none";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_PARSE) return "parse";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC) return "semantic";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_MODEL) return "model";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_LOWERING) return "lowering";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_LIR) return "lir";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_EFFECT_CHECK) return "effect-check";
    if (stage == LATTICRA_LAT_PIPELINE_STAGE_REPORT) return "report";
    return "unknown";
}

static const char *runtime_lat_declaration_kind_label(latticra_lat_declaration_kind_t kind) {
    if (kind == LATTICRA_LAT_DECLARATION_STATE) return "state";
    if (kind == LATTICRA_LAT_DECLARATION_POLICY) return "policy";
    if (kind == LATTICRA_LAT_DECLARATION_TRANSITION) return "transition";
    if (kind == LATTICRA_LAT_DECLARATION_ASSERTION) return "assertion";
    if (kind == LATTICRA_LAT_DECLARATION_EFFECT) return "effect";
    return "unknown";
}

static const char *runtime_lat_model_clause_role_label(latticra_lat_model_clause_role_t role) {
    if (role == LATTICRA_LAT_MODEL_CLAUSE_FIELD) return "field";
    if (role == LATTICRA_LAT_MODEL_CLAUSE_REQUIRE) return "require";
    if (role == LATTICRA_LAT_MODEL_CLAUSE_ENSURE) return "ensure";
    if (role == LATTICRA_LAT_MODEL_CLAUSE_EFFECT) return "effect";
    return "unknown";
}

static const char *runtime_lat_effect_label(latticra_lat_effect_t effect) {
    if (effect == LATTICRA_LAT_EFFECT_NONE) return "none";
    if (effect == LATTICRA_LAT_EFFECT_READ) return "read";
    if (effect == LATTICRA_LAT_EFFECT_LOCAL_MUTATION) return "local_mutation";
    if (effect == LATTICRA_LAT_EFFECT_HOST_MUTATION) return "host_mutation";
    if (effect == LATTICRA_LAT_EFFECT_NETWORK) return "network";
    if (effect == LATTICRA_LAT_EFFECT_HARDWARE) return "hardware";
    if (effect == LATTICRA_LAT_EFFECT_BOOT) return "boot";
    if (effect == LATTICRA_LAT_EFFECT_RECOVERY) return "recovery";
    if (effect == LATTICRA_LAT_EFFECT_EXTERNAL) return "external";
    return "unknown";
}

static const char *runtime_lat_parse_error_label(latticra_lat_parse_error_t error) {
    if (error == LATTICRA_LAT_PARSE_OK) return "ok";
    if (error == LATTICRA_LAT_PARSE_NULL_ARGUMENT) return "null_argument";
    if (error == LATTICRA_LAT_PARSE_EMPTY_SOURCE) return "empty_source";
    if (error == LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE) return "source_too_large";
    if (error == LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM) return "unsupported_extension_claim";
    if (error == LATTICRA_LAT_PARSE_MISSING_MODULE) return "missing_module";
    if (error == LATTICRA_LAT_PARSE_INVALID_MODULE_NAME) return "invalid_module_name";
    if (error == LATTICRA_LAT_PARSE_UNBALANCED_BRACE) return "unbalanced_brace";
    if (error == LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION) return "unknown_declaration";
    if (error == LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME) return "invalid_declaration_name";
    if (error == LATTICRA_LAT_PARSE_UNTERMINATED_STRING) return "unterminated_string";
    if (error == LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE) return "invalid_string_escape";
    if (error == LATTICRA_LAT_PARSE_INVALID_HEX_ESCAPE) return "invalid_hex_escape";
    if (error == LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING) return "literal_nul_in_string";
    if (error == LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED) return "capacity_exceeded";
    if (error == LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER) return "forbidden_behavior_marker";
    if (error == LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT) return "unsupported_block_comment";
    return "internal_error";
}

static const char *runtime_lat_semantic_error_label(latticra_lat_semantic_error_t error) {
    if (error == LATTICRA_LAT_SEMANTIC_OK) return "ok";
    if (error == LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT) return "null_argument";
    if (error == LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK) return "parse_not_ok";
    if (error == LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION) return "duplicate_declaration";
    if (error == LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE) return "unknown_transition_source";
    if (error == LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD) return "invalid_state_field";
    if (error == LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT) return "invalid_require_left";
    if (error == LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET) return "invalid_effect_target";
    if (error == LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE) return "invalid_effect_value";
    if (error == LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE) return "effect_requires_gate";
    if (error == LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION) return "invalid_clause_for_declaration";
    if (error == LATTICRA_LAT_SEMANTIC_EMPTY_DECLARATION) return "empty_declaration";
    if (error == LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION) return "no_effect_violation";
    if (error == LATTICRA_LAT_SEMANTIC_CAPACITY_EXCEEDED) return "capacity_exceeded";
    return "internal_error";
}

static const char *runtime_lat_model_error_label(latticra_lat_model_error_t error) {
    if (error == LATTICRA_LAT_MODEL_OK) return "ok";
    if (error == LATTICRA_LAT_MODEL_NULL_ARGUMENT) return "null_argument";
    if (error == LATTICRA_LAT_MODEL_PARSE_NOT_OK) return "parse_not_ok";
    if (error == LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK) return "semantic_not_ok";
    if (error == LATTICRA_LAT_MODEL_SEMANTIC_NOT_VALID) return "semantic_not_valid";
    if (error == LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION) return "no_effect_violation";
    if (error == LATTICRA_LAT_MODEL_CAPACITY_EXCEEDED) return "capacity_exceeded";
    if (error == LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION) return "unsupported_declaration";
    if (error == LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE) return "unsupported_clause";
    return "internal_error";
}

static const char *runtime_lat_to_lir_error_label(latticra_lat_to_lir_error_t error) {
    if (error == LATTICRA_LAT_TO_LIR_OK) return "ok";
    if (error == LATTICRA_LAT_TO_LIR_NULL_ARGUMENT) return "null_argument";
    if (error == LATTICRA_LAT_TO_LIR_PARSE_NOT_OK) return "parse_not_ok";
    if (error == LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK) return "semantic_not_ok";
    if (error == LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID) return "semantic_not_valid";
    if (error == LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION) return "no_effect_violation";
    if (error == LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED) return "capacity_exceeded";
    if (error == LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT) return "unsupported_effect";
    if (error == LATTICRA_LAT_TO_LIR_MODEL_NOT_OK) return "model_not_ok";
    return "internal_error";
}

static const char *runtime_lir_error_label(latticra_lir_error_t error) {
    if (error == LATTICRA_LIR_OK) return "ok";
    if (error == LATTICRA_LIR_NULL_ARGUMENT) return "null_argument";
    if (error == LATTICRA_LIR_SEMANTIC_FAILED) return "semantic_failed";
    if (error == LATTICRA_LIR_CAPACITY_EXCEEDED) return "capacity_exceeded";
    if (error == LATTICRA_LIR_UNSUPPORTED_SOURCE_KIND) return "unsupported_source_kind";
    if (error == LATTICRA_LIR_UNSUPPORTED_NODE_KIND) return "unsupported_node_kind";
    if (error == LATTICRA_LIR_UNSUPPORTED_EFFECT) return "unsupported_effect";
    if (error == LATTICRA_LIR_UNSUPPORTED_BOUNDARY) return "unsupported_boundary";
    return "internal_error";
}

static const char *runtime_lir_source_kind_label(latticra_lir_source_kind_t kind) {
    if (kind == LATTICRA_LIR_SOURCE_L_UI_CARD) return "l_ui_card";
    if (kind == LATTICRA_LIR_SOURCE_LAT_MODULE) return "lat_module";
    if (kind == LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE) return "internal_fixture";
    return "unknown";
}

static const char *runtime_lir_node_kind_label(latticra_lir_node_kind_t kind) {
    if (kind == LATTICRA_LIR_NODE_MODULE) return "module";
    if (kind == LATTICRA_LIR_NODE_CARD) return "card";
    if (kind == LATTICRA_LIR_NODE_RAIL) return "rail";
    if (kind == LATTICRA_LIR_NODE_FIELD) return "field";
    if (kind == LATTICRA_LIR_NODE_TEXT) return "text";
    if (kind == LATTICRA_LIR_NODE_BINDING) return "binding";
    if (kind == LATTICRA_LIR_NODE_EFFECT) return "effect";
    if (kind == LATTICRA_LIR_NODE_BOUNDARY) return "boundary";
    if (kind == LATTICRA_LIR_NODE_LAT_STATE) return "lat_state";
    if (kind == LATTICRA_LIR_NODE_LAT_POLICY) return "lat_policy";
    if (kind == LATTICRA_LIR_NODE_LAT_TRANSITION) return "lat_transition";
    if (kind == LATTICRA_LIR_NODE_LAT_ASSERTION) return "lat_assertion";
    if (kind == LATTICRA_LIR_NODE_LAT_REQUIREMENT) return "lat_requirement";
    if (kind == LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION) return "lat_effect_declaration";
    return "unknown";
}

static int runtime_lir_node_kind_is_lat(latticra_lir_node_kind_t kind) {
    return kind == LATTICRA_LIR_NODE_LAT_STATE ||
           kind == LATTICRA_LIR_NODE_LAT_POLICY ||
           kind == LATTICRA_LIR_NODE_LAT_TRANSITION ||
           kind == LATTICRA_LIR_NODE_LAT_ASSERTION ||
           kind == LATTICRA_LIR_NODE_LAT_REQUIREMENT ||
           kind == LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION;
}

static const char *runtime_lir_edge_kind_label(latticra_lir_edge_kind_t kind) {
    if (kind == LATTICRA_LIR_EDGE_CONTAINS) return "contains";
    if (kind == LATTICRA_LIR_EDGE_BINDS) return "binds";
    if (kind == LATTICRA_LIR_EDGE_ANNOTATES) return "annotates";
    if (kind == LATTICRA_LIR_EDGE_ORDERS_BEFORE) return "orders_before";
    if (kind == LATTICRA_LIR_EDGE_TRANSITIONS_FROM) return "transitions_from";
    return "unknown";
}

static const char *runtime_lir_report_classification_label(latticra_lir_report_classification_t classification) {
    if (classification == LATTICRA_LIR_REPORT_MATERIALIZED) return "materialized";
    if (classification == LATTICRA_LIR_REPORT_REJECTED) return "rejected";
    if (classification == LATTICRA_LIR_REPORT_INVALID) return "invalid";
    return "empty";
}

static const char *runtime_lir_shape_kind_label(latticra_lir_shape_kind_t shape_kind) {
    if (shape_kind == LATTICRA_LIR_SHAPE_L_UI_CARD_GRAPH) return "l-ui-card-graph";
    if (shape_kind == LATTICRA_LIR_SHAPE_LAT_MODULE_GRAPH) return "lat-module-graph";
    if (shape_kind == LATTICRA_LIR_SHAPE_INTERNAL_FIXTURE_GRAPH) return "internal-fixture-graph";
    return "unknown";
}

static int runtime_boundary_kind_is_future_gated(latticra_runtime_boundary_request_kind_t kind) {
    return (int)kind >= (int)LATTICRA_RUNTIME_BOUNDARY_RUNTIME_EXECUTE &&
           (int)kind <= (int)LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION;
}

static int runtime_boundary_effect_is_no_effect(latticra_runtime_boundary_effect_t effect) {
    return effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE ||
           effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ;
}

static int runtime_boundary_mode_matches_request_kind(const latticra_runtime_boundary_request_t *request) {
    if (request == 0) return 0;
    if ((request->request_kind == LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY ||
         request->request_kind == LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT ||
         request->request_kind == LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT) &&
        request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY) return 1;
    if ((request->request_kind == LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY ||
         request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE ||
         request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE ||
         request->request_kind == LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK ||
         request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE) &&
        request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY) return 1;
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY &&
        request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY) return 1;
    if (runtime_boundary_kind_is_future_gated(request->request_kind) &&
        request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE) return 1;
    return 0;
}

static latticra_runtime_boundary_domain_t runtime_boundary_domain_for_request(const latticra_runtime_boundary_request_t *request) {
    if (request == 0) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN;

    switch (request->request_kind) {
    case LATTICRA_RUNTIME_BOUNDARY_FILE_READ:
    case LATTICRA_RUNTIME_BOUNDARY_FILE_WRITE:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM;
    case LATTICRA_RUNTIME_BOUNDARY_NETWORK_OPEN:
    case LATTICRA_RUNTIME_BOUNDARY_SERVER_INTERACTION:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK;
    case LATTICRA_RUNTIME_BOUNDARY_RUNTIME_EXECUTE:
    case LATTICRA_RUNTIME_BOUNDARY_COMMAND_EXECUTE:
    case LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE:
    case LATTICRA_RUNTIME_BOUNDARY_LIR_EXECUTE:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS;
    case LATTICRA_RUNTIME_BOUNDARY_HARDWARE_ACTION:
    case LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE;
    case LATTICRA_RUNTIME_BOUNDARY_SELF_UPDATE:
    case LATTICRA_RUNTIME_BOUNDARY_RECOVERY_ACTION:
    case LATTICRA_RUNTIME_BOUNDARY_ROLLBACK_ACTION:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PERSISTENCE;
    case LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_SCHEDULER;
    case LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK:
        return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST;
    default:
        break;
    }

    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MEMORY;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_LOCAL_MUTATION) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MEMORY;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_HOST_MUTATION) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_HARDWARE) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_BOOT) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_RECOVERY) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PERSISTENCE;
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_EXTERNAL) return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_EXTERNAL_CALL;
    return LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN;
}

static void finalize_policy_matrix_metadata(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result == 0) return;

    result->record.matrix_requires_authority = request != 0 ? 1 : 0;
    result->record.matrix_requires_future_gate = request != 0 && runtime_boundary_kind_is_future_gated(request->request_kind) ? 1 : 0;
    result->record.matrix_effect_allowed = request != 0 && runtime_boundary_effect_is_no_effect(request->requested_effect) ? 1 : 0;
    result->record.matrix_mode_allowed = runtime_boundary_mode_matches_request_kind(request);

    if (request == 0 ||
        result->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT ||
        result->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST ||
        result->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID;
        return;
    }
    if (result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_REPORT;
        return;
    }
    if (result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_VALIDATION;
        return;
    }
    if (result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_CLASSIFICATION;
        return;
    }
    if (result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE ||
        runtime_boundary_kind_is_future_gated(request->request_kind)) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION;
        return;
    }
    if (!result->record.matrix_effect_allowed) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT;
        return;
    }
    if (result->record.denial != LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK) {
        result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED;
        return;
    }
    result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_UNSUPPORTED;
}

static void finalize_report_refinement_metadata(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result == 0) return;

    result->record.boundary_domain = runtime_boundary_domain_for_request(request);

    if (request == 0 ||
        result->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT ||
        result->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST ||
        result->record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT) {
        result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_INVALID;
        result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_UNAVAILABLE;
        result->record.evidence_level = 0u;
        finalize_policy_matrix_metadata(request, result);
        return;
    }

    if (result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT ||
        result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION ||
        result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION ||
        result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_PREVIEW) {
        result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_DECLARATIVE;
        result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_NOT_REQUESTED;
        result->record.evidence_level = 2u;
        finalize_policy_matrix_metadata(request, result);
        return;
    }

    if (result->record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE ||
        runtime_boundary_kind_is_future_gated(request->request_kind)) {
        result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING;
        result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE;
        result->record.evidence_level = 1u;
        finalize_policy_matrix_metadata(request, result);
        return;
    }

    if (!runtime_boundary_effect_is_no_effect(request->requested_effect)) {
        result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED;
        result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_DENIED;
        result->record.evidence_level = 1u;
        finalize_policy_matrix_metadata(request, result);
        return;
    }

    if (result->record.denial != LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK) {
        result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED;
        result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_DENIED;
        result->record.evidence_level = 1u;
        finalize_policy_matrix_metadata(request, result);
        return;
    }

    result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_DECLARATIVE;
    result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_NOT_REQUESTED;
    result->record.evidence_level = 1u;
    finalize_policy_matrix_metadata(request, result);
}

static void seed_result(latticra_runtime_boundary_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    result->record_count = 1u;
    result->no_effect = 1;
    result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY;
    result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED;
    result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED;
    result->record.report_classification = LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED;
    result->record.boundary_domain = LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN;
    result->record.authorization_state = LATTICRA_RUNTIME_BOUNDARY_AUTH_DENIED;
    result->record.policy_matrix_cell = LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED;
    result->record.matrix_requires_authority = 1;
    result->record.task_policy = LATTICRA_NUCLEUS_TASK_POLICY_DENY;
    result->record.task_reason = LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT;
    result->record.lat_pipeline_span.start_line = 1u;
    result->record.lat_pipeline_span.start_column = 1u;
    result->record.lat_pipeline_span.end_line = 1u;
    result->record.lat_pipeline_span.end_column = 1u;
    result->record.lat_pipeline_first_comment_span.start_line = 1u;
    result->record.lat_pipeline_first_comment_span.start_column = 1u;
    result->record.lat_pipeline_first_comment_span.end_line = 1u;
    result->record.lat_pipeline_first_comment_span.end_column = 1u;
    result->record.lat_lir_source_kind = LATTICRA_LIR_SOURCE_UNKNOWN;
}

static void copy_runtime_id(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    size_t n;
    n = strlen(request->runtime_id);
    if (n >= sizeof(result->record.runtime_id)) n = sizeof(result->record.runtime_id) - 1u;
    memcpy(result->record.runtime_id, request->runtime_id, n);
    result->record.runtime_id[n] = '\0';
}

static void copy_source_identity(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    size_t n;
    if (request->source_identity == 0 || request->source_identity_len == 0u) return;
    n = request->source_identity_len;
    if (n >= sizeof(result->record.source_identity)) n = sizeof(result->record.source_identity) - 1u;
    memcpy(result->record.source_identity, request->source_identity, n);
    result->record.source_identity[n] = '\0';
}

static void copy_task_flags(const latticra_nucleus_task_result_t *task, latticra_runtime_boundary_result_t *result) {
    if (task == 0) return;
    result->record.task_executed = task->record.executed;
    result->record.task_mutation_allowed = task->record.mutation_allowed;
    result->record.task_server_interaction_allowed = task->record.server_interaction_allowed;
    result->record.task_network_allowed = task->record.network_allowed;
    result->record.task_recovery_allowed = task->record.recovery_allowed;
    result->record.task_hardware_allowed = task->record.hardware_allowed;
}

static void copy_lat_pipeline(const latticra_lat_pipeline_result_t *lat_pipeline, latticra_runtime_boundary_result_t *result) {
    if (lat_pipeline == 0) return;
    result->record.lat_pipeline_status = lat_pipeline->status;
    result->record.lat_pipeline_error = lat_pipeline->error;
    result->record.lat_pipeline_parse_error = lat_pipeline->parse_error;
    result->record.lat_pipeline_span = lat_pipeline->span;
    result->record.lat_pipeline_semantic_error = lat_pipeline->semantic_error;
    result->record.lat_pipeline_model_error = lat_pipeline->model_error;
    result->record.lat_pipeline_lowering_error = lat_pipeline->lowering_error;
    result->record.lat_pipeline_lir_error = lat_pipeline->lir_error;
    result->record.lat_pipeline_last_completed_stage = lat_pipeline->last_completed_stage;
    result->record.lat_pipeline_failed_stage = lat_pipeline->failed_stage;
    result->record.lat_pipeline_parse_ok = lat_pipeline->parse_ok;
    result->record.lat_pipeline_semantic_ok = lat_pipeline->semantic_ok;
    result->record.lat_pipeline_model_ok = lat_pipeline->model_ok;
    result->record.lat_pipeline_lowering_ok = lat_pipeline->lowering_ok;
    result->record.lat_pipeline_lir_ok = lat_pipeline->lir_ok;
    result->record.lat_pipeline_no_effect_chain_ok = lat_pipeline->no_effect_chain_ok;
    result->record.lat_pipeline_evidence_level = lat_pipeline->evidence_level;
    result->record.lat_pipeline_semantic_valid = lat_pipeline->semantic_valid;
    (void)snprintf(result->record.lat_pipeline_module_name, sizeof(result->record.lat_pipeline_module_name), "%s", lat_pipeline->module_name);
    result->record.lat_pipeline_source_len = lat_pipeline->source_len;
    result->record.lat_pipeline_declaration_count = lat_pipeline->declaration_count;
    result->record.lat_pipeline_clause_count = lat_pipeline->clause_count;
    result->record.lat_pipeline_model_declaration_count = lat_pipeline->model_declaration_count;
    result->record.lat_pipeline_model_clause_count = lat_pipeline->model_clause_count;
    result->record.lat_pipeline_first_declaration_node_index = lat_pipeline->first_declaration_node_index;
    result->record.lat_pipeline_first_declaration_kind = lat_pipeline->first_declaration_kind;
    (void)snprintf(result->record.lat_pipeline_first_declaration_name, sizeof(result->record.lat_pipeline_first_declaration_name), "%s", lat_pipeline->first_declaration_name);
    (void)snprintf(result->record.lat_pipeline_first_declaration_source, sizeof(result->record.lat_pipeline_first_declaration_source), "%s", lat_pipeline->first_declaration_source);
    result->record.lat_pipeline_first_declaration_parse_index = lat_pipeline->first_declaration_parse_index;
    result->record.lat_pipeline_first_declaration_first_clause_index = lat_pipeline->first_declaration_first_clause_index;
    result->record.lat_pipeline_first_declaration_clause_count = lat_pipeline->first_declaration_clause_count;
    result->record.lat_pipeline_first_declaration_source_index = lat_pipeline->first_declaration_source_index;
    result->record.lat_pipeline_first_transition_source_index = lat_pipeline->first_transition_source_index;
    result->record.lat_pipeline_first_clause_node_index = lat_pipeline->first_clause_node_index;
    result->record.lat_pipeline_first_clause_role = lat_pipeline->first_clause_role;
    result->record.lat_pipeline_first_clause_effect = lat_pipeline->first_clause_effect;
    (void)snprintf(result->record.lat_pipeline_first_clause_name, sizeof(result->record.lat_pipeline_first_clause_name), "%s", lat_pipeline->first_clause_name);
    (void)snprintf(result->record.lat_pipeline_first_clause_operator, sizeof(result->record.lat_pipeline_first_clause_operator), "%s", lat_pipeline->first_clause_operator);
    (void)snprintf(result->record.lat_pipeline_first_clause_value, sizeof(result->record.lat_pipeline_first_clause_value), "%s", lat_pipeline->first_clause_value);
    result->record.lat_pipeline_node_count = lat_pipeline->node_count;
    result->record.lat_pipeline_edge_count = lat_pipeline->edge_count;
    result->record.lat_pipeline_comment_count = lat_pipeline->comment_count;
    result->record.lat_pipeline_first_comment_span = lat_pipeline->first_comment_span;
}

static void copy_lat_lir_evidence(const latticra_lir_module_t *lir, latticra_runtime_boundary_result_t *result) {
    size_t index;
    if (lir == 0) return;
    result->record.lat_lir_source_kind = lir->source_kind;
    (void)snprintf(result->record.lat_lir_module_name, sizeof(result->record.lat_lir_module_name), "%s", lir->module_name);
    (void)snprintf(result->record.lat_lir_card_name, sizeof(result->record.lat_lir_card_name), "%s", lir->card_name);
    (void)snprintf(result->record.lat_lir_effect, sizeof(result->record.lat_lir_effect), "%s", lir->effect);
    (void)snprintf(result->record.lat_lir_boundary, sizeof(result->record.lat_lir_boundary), "%s", lir->boundary);
    result->record.lat_lir_report_classification = lir->report_classification;
    result->record.lat_lir_shape_kind = lir->shape_kind;
    result->record.lat_lir_source_span = lir->source_span;
    result->record.lat_lir_module_node_count = lir->node_count;
    result->record.lat_lir_module_edge_count = lir->edge_count;
    result->record.lat_lir_binding_count = lir->binding_count;
    result->record.lat_lir_text_count = lir->text_count;
    result->record.lat_lir_no_effect_chain_ok = lir->no_effect_chain_ok;
    result->record.lat_lir_evidence_level = lir->evidence_level;
    result->record.lat_lir_no_effect = lir->no_effect;
    result->record.lat_lir_execution_allowed = lir->execution_allowed;
    result->record.lat_lir_mutation_allowed = lir->mutation_allowed;
    result->record.lat_lir_server_allowed = lir->server_allowed;
    result->record.lat_lir_network_allowed = lir->network_allowed;
    result->record.lat_lir_recovery_allowed = lir->recovery_allowed;
    result->record.lat_lir_hardware_allowed = lir->hardware_allowed;
    for (index = 0u; index < lir->node_count && index < LATTICRA_LIR_NODE_MAX; index++) {
        if (runtime_lir_node_kind_is_lat(lir->nodes[index].kind) &&
            result->record.lat_lir_has_first_lat_node == 0) {
            result->record.lat_lir_has_first_lat_node = 1;
            result->record.lat_lir_first_lat_node_index = index;
            result->record.lat_lir_first_lat_node_kind = lir->nodes[index].kind;
            result->record.lat_lir_first_lat_node_parent_index = lir->nodes[index].parent_index;
            result->record.lat_lir_first_lat_node_first_child_index = lir->nodes[index].first_child_index;
            result->record.lat_lir_first_lat_node_child_count = lir->nodes[index].child_count;
            result->record.lat_lir_first_lat_node_span = lir->nodes[index].source_span;
            (void)snprintf(result->record.lat_lir_first_lat_node_name,
                           sizeof(result->record.lat_lir_first_lat_node_name),
                           "%s",
                           lir->nodes[index].name);
            (void)snprintf(result->record.lat_lir_first_lat_node_value,
                           sizeof(result->record.lat_lir_first_lat_node_value),
                           "%s",
                           lir->nodes[index].value);
            (void)snprintf(result->record.lat_lir_first_lat_node_operator,
                           sizeof(result->record.lat_lir_first_lat_node_operator),
                           "%s",
                           lir->nodes[index].operator_text);
            (void)snprintf(result->record.lat_lir_first_lat_node_binding,
                           sizeof(result->record.lat_lir_first_lat_node_binding),
                           "%s",
                           lir->nodes[index].binding);
        }
        if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_TRANSITION &&
            result->record.lat_lir_has_first_transition_node == 0) {
            result->record.lat_lir_has_first_transition_node = 1;
            result->record.lat_lir_first_transition_node_index = index;
            result->record.lat_lir_first_transition_node_kind = lir->nodes[index].kind;
            result->record.lat_lir_first_transition_node_parent_index = lir->nodes[index].parent_index;
            result->record.lat_lir_first_transition_node_first_child_index = lir->nodes[index].first_child_index;
            result->record.lat_lir_first_transition_node_child_count = lir->nodes[index].child_count;
            result->record.lat_lir_first_transition_node_span = lir->nodes[index].source_span;
            (void)snprintf(result->record.lat_lir_first_transition_node_name,
                           sizeof(result->record.lat_lir_first_transition_node_name),
                           "%s",
                           lir->nodes[index].name);
            (void)snprintf(result->record.lat_lir_first_transition_node_value,
                           sizeof(result->record.lat_lir_first_transition_node_value),
                           "%s",
                           lir->nodes[index].value);
            (void)snprintf(result->record.lat_lir_first_transition_node_operator,
                           sizeof(result->record.lat_lir_first_transition_node_operator),
                           "%s",
                           lir->nodes[index].operator_text);
            (void)snprintf(result->record.lat_lir_first_transition_node_binding,
                           sizeof(result->record.lat_lir_first_transition_node_binding),
                           "%s",
                           lir->nodes[index].binding);
        }
        if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_STATE) {
            result->record.lat_lir_lat_state_node_count += 1u;
            result->record.lat_lir_has_lat_state_nodes = 1;
        } else if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_POLICY) {
            result->record.lat_lir_lat_policy_node_count += 1u;
        } else if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_TRANSITION) {
            result->record.lat_lir_lat_transition_node_count += 1u;
            result->record.lat_lir_has_lat_transition_nodes = 1;
        } else if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_ASSERTION) {
            result->record.lat_lir_lat_assertion_node_count += 1u;
        } else if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_REQUIREMENT) {
            result->record.lat_lir_lat_requirement_node_count += 1u;
        } else if (lir->nodes[index].kind == LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION) {
            result->record.lat_lir_lat_effect_declaration_node_count += 1u;
        }
    }
    for (index = 0u; index < lir->edge_count && index < LATTICRA_LIR_EDGE_MAX; index++) {
        if (result->record.lat_lir_has_first_edge == 0) {
            result->record.lat_lir_has_first_edge = 1;
            result->record.lat_lir_first_edge_index = index;
            result->record.lat_lir_first_edge_from_index = lir->edges[index].from_index;
            result->record.lat_lir_first_edge_to_index = lir->edges[index].to_index;
            result->record.lat_lir_first_edge_kind = lir->edges[index].edge_kind;
            result->record.lat_lir_first_edge_span = lir->edges[index].source_span;
        }
        if (lir->edges[index].edge_kind == LATTICRA_LIR_EDGE_CONTAINS) {
            result->record.lat_lir_contains_edge_count += 1u;
        } else if (lir->edges[index].edge_kind == LATTICRA_LIR_EDGE_BINDS) {
            result->record.lat_lir_binds_edge_count += 1u;
        } else if (lir->edges[index].edge_kind == LATTICRA_LIR_EDGE_ANNOTATES) {
            result->record.lat_lir_annotates_edge_count += 1u;
        } else if (lir->edges[index].edge_kind == LATTICRA_LIR_EDGE_ORDERS_BEFORE) {
            result->record.lat_lir_orders_before_edge_count += 1u;
        } else if (lir->edges[index].edge_kind == LATTICRA_LIR_EDGE_TRANSITIONS_FROM) {
            result->record.lat_lir_transition_edge_count += 1u;
            result->record.lat_lir_has_transition_source_edges = 1;
            if (result->record.lat_lir_has_first_transition_source_edge == 0) {
                result->record.lat_lir_has_first_transition_source_edge = 1;
                result->record.lat_lir_first_transition_source_edge_index = index;
                result->record.lat_lir_first_transition_source_edge_from_index = lir->edges[index].from_index;
                result->record.lat_lir_first_transition_source_edge_to_index = lir->edges[index].to_index;
                result->record.lat_lir_first_transition_source_edge_kind = lir->edges[index].edge_kind;
                result->record.lat_lir_first_transition_source_edge_from_node_kind = LATTICRA_LIR_NODE_UNKNOWN;
                result->record.lat_lir_first_transition_source_edge_to_node_kind = LATTICRA_LIR_NODE_UNKNOWN;
                if (lir->edges[index].from_index < lir->node_count &&
                    lir->edges[index].from_index < LATTICRA_LIR_NODE_MAX) {
                    size_t from_index = lir->edges[index].from_index;
                    result->record.lat_lir_first_transition_source_edge_from_node_kind = lir->nodes[from_index].kind;
                    result->record.lat_lir_first_transition_source_edge_from_node_parent_index = lir->nodes[from_index].parent_index;
                    result->record.lat_lir_first_transition_source_edge_from_node_first_child_index = lir->nodes[from_index].first_child_index;
                    result->record.lat_lir_first_transition_source_edge_from_node_child_count = lir->nodes[from_index].child_count;
                    result->record.lat_lir_first_transition_source_edge_from_node_span = lir->nodes[from_index].source_span;
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_from_node_name,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_from_node_name),
                                   "%s",
                                   lir->nodes[from_index].name);
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_from_node_value,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_from_node_value),
                                   "%s",
                                   lir->nodes[from_index].value);
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_from_node_operator,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_from_node_operator),
                                   "%s",
                                   lir->nodes[from_index].operator_text);
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_from_node_binding,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_from_node_binding),
                                   "%s",
                                   lir->nodes[from_index].binding);
                }
                if (lir->edges[index].to_index < lir->node_count &&
                    lir->edges[index].to_index < LATTICRA_LIR_NODE_MAX) {
                    size_t to_index = lir->edges[index].to_index;
                    result->record.lat_lir_first_transition_source_edge_to_node_kind = lir->nodes[to_index].kind;
                    result->record.lat_lir_first_transition_source_edge_to_node_parent_index = lir->nodes[to_index].parent_index;
                    result->record.lat_lir_first_transition_source_edge_to_node_first_child_index = lir->nodes[to_index].first_child_index;
                    result->record.lat_lir_first_transition_source_edge_to_node_child_count = lir->nodes[to_index].child_count;
                    result->record.lat_lir_first_transition_source_edge_to_node_span = lir->nodes[to_index].source_span;
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_to_node_name,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_to_node_name),
                                   "%s",
                                   lir->nodes[to_index].name);
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_to_node_value,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_to_node_value),
                                   "%s",
                                   lir->nodes[to_index].value);
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_to_node_operator,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_to_node_operator),
                                   "%s",
                                   lir->nodes[to_index].operator_text);
                    (void)snprintf(result->record.lat_lir_first_transition_source_edge_to_node_binding,
                                   sizeof(result->record.lat_lir_first_transition_source_edge_to_node_binding),
                                   "%s",
                                   lir->nodes[to_index].binding);
                }
                result->record.lat_lir_first_transition_source_edge_span = lir->edges[index].source_span;
            }
        }
    }
}

static void copy_prerequisites(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (request->render != 0) {
        result->record.render_status = request->render->status;
        result->record.render_error = request->render->error;
    }
    if (request->lat != 0) {
        result->record.lat_status = request->lat->status;
        result->record.lat_error = request->lat->error;
    }
    if (request->lir != 0) {
        result->record.lir_status = request->lir->status;
        result->record.lir_error = request->lir->error;
        copy_lat_lir_evidence(request->lir, result);
    }
    copy_lat_pipeline(request->lat_pipeline, result);
}

static int authority_flags_ok(const latticra_runtime_boundary_authority_summary_t *authority) {
    return authority != 0 && authority->status == LATTICRA_STATUS_OK && authority->no_effect == 1 && authority->execution_allowed == 0 && authority->mutation_allowed == 0 && authority->server_allowed == 0 && authority->network_allowed == 0 && authority->recovery_allowed == 0 && authority->hardware_allowed == 0;
}

static int task_result_ok(const latticra_nucleus_task_result_t *task) {
    return task != 0 && task->status == LATTICRA_STATUS_OK && task->record_count > 0u && task->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_OK && task->record.executed == 0 && task->record.mutation_allowed == 0 && task->record.server_interaction_allowed == 0 && task->record.network_allowed == 0 && task->record.recovery_allowed == 0 && task->record.hardware_allowed == 0;
}

static int render_ok(const latticra_l_ui_render_result_t *render) {
    return render != 0 && render->status == LATTICRA_STATUS_OK && render->error == LATTICRA_L_UI_RENDER_OK;
}

static int lat_ok(const latticra_lat_parse_result_t *lat) {
    return lat != 0 && lat->status == LATTICRA_STATUS_OK && lat->error == LATTICRA_LAT_PARSE_OK;
}

static int lir_ok(const latticra_lir_module_t *lir) {
    return lir != 0 && lir->status == LATTICRA_STATUS_OK && lir->error == LATTICRA_LIR_OK;
}

static int lat_pipeline_ok(const latticra_lat_pipeline_result_t *lat_pipeline) {
    return lat_pipeline != 0 &&
           lat_pipeline->status == LATTICRA_STATUS_OK &&
           lat_pipeline->error == LATTICRA_LAT_PIPELINE_OK &&
           lat_pipeline->semantic_valid == 1 &&
           lat_pipeline->no_effect == 1 &&
           lat_pipeline->execution_allowed == 0 &&
           lat_pipeline->mutation_allowed == 0 &&
           lat_pipeline->server_allowed == 0 &&
           lat_pipeline->network_allowed == 0 &&
           lat_pipeline->recovery_allowed == 0 &&
           lat_pipeline->hardware_allowed == 0;
}

static void allow_matching_no_effect_mode(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result->record.policy != LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY || result->record.denial != LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED) return;
    if (request->requested_effect != LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE && request->requested_effect != LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ) return;

    if ((request->request_kind == LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT) && request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
        result->record.allowed_effect = request->requested_effect;
        return;
    }

    if ((request->request_kind == LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE) && request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
        result->record.allowed_effect = request->requested_effect;
        return;
    }

    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY && request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
        result->record.allowed_effect = request->requested_effect;
    }
}

latticra_status_t latticra_runtime_boundary_classify(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);
    if (request == 0) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    copy_runtime_id(request, result);
    result->record.request_kind = request->request_kind;
    result->record.requested_effect = request->requested_effect;
    result->record.mode = request->mode;
    result->record.operator_confirmation = request->operator_confirmation;
    result->record.source_span = request->source_span;
    copy_source_identity(request, result);
    copy_prerequisites(request, result);
    if (request->authority != 0) result->record.authority = *request->authority;
    if (request->task != 0) {
        result->record.task_policy = request->task->record.policy;
        result->record.task_reason = request->task->record.denial;
        copy_task_flags(request->task, result);
    }
    if (request->authority == 0) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (!authority_flags_ok(request->authority)) {
        result->record.denial = request->authority->status == LATTICRA_STATUS_OK ? LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS : LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT && !render_ok(request->render)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE && !lat_ok(request->lat)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE && !lir_ok(request->lir)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE && !lat_pipeline_ok(request->lat_pipeline)) {
        if (request->lat_pipeline != 0 && request->lat_pipeline->error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK) result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED;
        else if (request->lat_pipeline != 0 && (request->lat_pipeline->error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK || request->lat_pipeline->error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID)) result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_SEMANTIC_FAILED;
        else if (request->lat_pipeline != 0 && (request->lat_pipeline->error == LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION || request->lat_pipeline->network_allowed != 0)) result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS;
        else result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT && !task_result_ok(request->task)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED;
        finalize_report_refinement_metadata(request, result);
        return LATTICRA_STATUS_OK;
    }
    if (request->operator_confirmation != LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED;
    }
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_UNKNOWN) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST;
    }
    if (runtime_boundary_kind_is_future_gated(request->request_kind)) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED;
    }
    allow_matching_no_effect_mode(request, result);
    finalize_report_refinement_metadata(request, result);
    return LATTICRA_STATUS_OK;
}

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverlength-strings"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings"
#endif

latticra_status_t latticra_runtime_boundary_report(const latticra_runtime_boundary_result_t *result, char *buffer, size_t buffer_len) {
    int written;
    size_t offset;
    int extra;
    size_t used;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(buffer, buffer_len,
        "LATTICRA RUNTIME BOUNDARY REPORT\nruntime_id=%s\nrecord_count=%lu\nrequest=%s\nrequested_effect=%s\nallowed_effect=%s\nmode=%s\npolicy=%s\nreason=%s\ngate=%s\noperator_confirmation=%s\nreport_classification=%s\nboundary_domain=%s\nauthorization_state=%s\nevidence_level=%u\npolicy_matrix_cell=%s\nmatrix_effect_allowed=%d\nmatrix_mode_allowed=%d\nmatrix_requires_authority=%d\nmatrix_requires_future_gate=%d\n",
        result->record.runtime_id,
        (unsigned long)result->record_count,
        latticra_runtime_boundary_request_kind_label(result->record.request_kind),
        latticra_runtime_boundary_effect_label(result->record.requested_effect),
        latticra_runtime_boundary_effect_label(result->record.allowed_effect),
        latticra_runtime_boundary_mode_label(result->record.mode),
        latticra_runtime_boundary_policy_label(result->record.policy),
        latticra_runtime_boundary_denial_label(result->record.denial),
        latticra_runtime_boundary_gate_state_label(result->record.gate_state),
        latticra_runtime_boundary_operator_confirmation_label(result->record.operator_confirmation),
        latticra_runtime_boundary_report_classification_label(result->record.report_classification),
        latticra_runtime_boundary_domain_label(result->record.boundary_domain),
        latticra_runtime_boundary_authorization_state_label(result->record.authorization_state),
        result->record.evidence_level,
        latticra_runtime_boundary_policy_matrix_cell_label(result->record.policy_matrix_cell),
        result->record.matrix_effect_allowed,
        result->record.matrix_mode_allowed,
        result->record.matrix_requires_authority,
        result->record.matrix_requires_future_gate);
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    offset = (size_t)written;
    written = snprintf(buffer + offset, buffer_len - offset,
        "authority_status=%d\nauthority_status_label=%s\nauthority_validator=%s\nauthority_requested_effect=%s\nauthority_reason=%s\nauthority_no_effect=%d\nauthority_execution_allowed=%d\nauthority_mutation_allowed=%d\nauthority_server_allowed=%d\nauthority_network_allowed=%d\nauthority_recovery_allowed=%d\nauthority_hardware_allowed=%d\ntask_policy=%s\ntask_reason=%s\ntask_executed=%d\ntask_mutation_allowed=%d\ntask_server_interaction_allowed=%d\ntask_network_allowed=%d\ntask_recovery_allowed=%d\ntask_hardware_allowed=%d\nrender_status=%d\nrender_error=%d\nlat_status=%d\nlat_error=%d\nlir_status=%d\nlir_error=%d\nlat_pipeline_status=%d\nlat_pipeline_error=%s\nlat_pipeline_parse_error=%s\nlat_pipeline_span_start_offset=%lu\nlat_pipeline_span_end_offset=%lu\nlat_pipeline_span_start_line=%lu\nlat_pipeline_span_start_column=%lu\nlat_pipeline_span_end_line=%lu\nlat_pipeline_span_end_column=%lu\nlat_pipeline_semantic_error=%s\nlat_pipeline_model_error=%s\nlat_pipeline_lowering_error=%s\nlat_pipeline_lir_error=%s\nlat_pipeline_last_completed_stage=%s\nlat_pipeline_failed_stage=%s\nlat_pipeline_parse_ok=%d\nlat_pipeline_semantic_ok=%d\nlat_pipeline_model_ok=%d\nlat_pipeline_lowering_ok=%d\nlat_pipeline_lir_ok=%d\nlat_pipeline_no_effect_chain_ok=%d\nlat_pipeline_evidence_level=%u\nlat_pipeline_semantic_valid=%d\nlat_pipeline_module_name=%s\nlat_pipeline_source_len=%lu\n",
        (int)result->record.authority.status,
        result->record.authority.status_label,
        result->record.authority.validator_label,
        result->record.authority.requested_effect_label,
        result->record.authority.denial_reason,
        result->record.authority.no_effect,
        result->record.authority.execution_allowed,
        result->record.authority.mutation_allowed,
        result->record.authority.server_allowed,
        result->record.authority.network_allowed,
        result->record.authority.recovery_allowed,
        result->record.authority.hardware_allowed,
        latticra_nucleus_task_policy_label(result->record.task_policy),
        latticra_nucleus_task_denial_label(result->record.task_reason),
        result->record.task_executed,
        result->record.task_mutation_allowed,
        result->record.task_server_interaction_allowed,
        result->record.task_network_allowed,
        result->record.task_recovery_allowed,
        result->record.task_hardware_allowed,
        (int)result->record.render_status,
        (int)result->record.render_error,
        (int)result->record.lat_status,
        (int)result->record.lat_error,
        (int)result->record.lir_status,
        (int)result->record.lir_error,
        (int)result->record.lat_pipeline_status,
        runtime_lat_pipeline_error_label(result->record.lat_pipeline_error),
        runtime_lat_parse_error_label(result->record.lat_pipeline_parse_error),
        (unsigned long)result->record.lat_pipeline_span.start_offset,
        (unsigned long)result->record.lat_pipeline_span.end_offset,
        (unsigned long)result->record.lat_pipeline_span.start_line,
        (unsigned long)result->record.lat_pipeline_span.start_column,
        (unsigned long)result->record.lat_pipeline_span.end_line,
        (unsigned long)result->record.lat_pipeline_span.end_column,
        runtime_lat_semantic_error_label(result->record.lat_pipeline_semantic_error),
        runtime_lat_model_error_label(result->record.lat_pipeline_model_error),
        runtime_lat_to_lir_error_label(result->record.lat_pipeline_lowering_error),
        runtime_lir_error_label(result->record.lat_pipeline_lir_error),
        runtime_lat_pipeline_stage_label(result->record.lat_pipeline_last_completed_stage),
        runtime_lat_pipeline_stage_label(result->record.lat_pipeline_failed_stage),
        result->record.lat_pipeline_parse_ok,
        result->record.lat_pipeline_semantic_ok,
        result->record.lat_pipeline_model_ok,
        result->record.lat_pipeline_lowering_ok,
        result->record.lat_pipeline_lir_ok,
        result->record.lat_pipeline_no_effect_chain_ok,
        result->record.lat_pipeline_evidence_level,
        result->record.lat_pipeline_semantic_valid,
        result->record.lat_pipeline_module_name,
        (unsigned long)result->record.lat_pipeline_source_len);
    if (written < 0 || (size_t)written >= buffer_len - offset) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    offset += (size_t)written;
    written = snprintf(buffer + offset, buffer_len - offset,
        "lat_pipeline_declaration_count=%lu\nlat_pipeline_clause_count=%lu\nlat_pipeline_model_declaration_count=%lu\nlat_pipeline_model_clause_count=%lu\nlat_pipeline_first_declaration_node_index=%lu\nlat_pipeline_first_declaration_kind=%s\nlat_pipeline_first_declaration_name=%s\nlat_pipeline_first_declaration_source=%s\nlat_pipeline_first_declaration_parse_index=%lu\nlat_pipeline_first_declaration_first_clause_index=%lu\nlat_pipeline_first_declaration_clause_count=%lu\nlat_pipeline_first_declaration_source_index=%lu\nlat_pipeline_first_transition_source_index=%lu\nlat_pipeline_first_clause_node_index=%lu\nlat_pipeline_first_clause_role=%s\nlat_pipeline_first_clause_effect=%s\nlat_pipeline_first_clause_name=%s\nlat_pipeline_first_clause_operator=%s\nlat_pipeline_first_clause_value=%s\nlat_pipeline_node_count=%lu\nlat_pipeline_edge_count=%lu\nlat_pipeline_comment_count=%lu\nlat_pipeline_first_comment_start_offset=%lu\nlat_pipeline_first_comment_end_offset=%lu\nlat_pipeline_first_comment_start_line=%lu\nlat_pipeline_first_comment_start_column=%lu\nlat_pipeline_first_comment_end_line=%lu\nlat_pipeline_first_comment_end_column=%lu\n",
        (unsigned long)result->record.lat_pipeline_declaration_count,
        (unsigned long)result->record.lat_pipeline_clause_count,
        (unsigned long)result->record.lat_pipeline_model_declaration_count,
        (unsigned long)result->record.lat_pipeline_model_clause_count,
        (unsigned long)result->record.lat_pipeline_first_declaration_node_index,
        runtime_lat_declaration_kind_label(result->record.lat_pipeline_first_declaration_kind),
        result->record.lat_pipeline_first_declaration_name,
        result->record.lat_pipeline_first_declaration_source,
        (unsigned long)result->record.lat_pipeline_first_declaration_parse_index,
        (unsigned long)result->record.lat_pipeline_first_declaration_first_clause_index,
        (unsigned long)result->record.lat_pipeline_first_declaration_clause_count,
        (unsigned long)result->record.lat_pipeline_first_declaration_source_index,
        (unsigned long)result->record.lat_pipeline_first_transition_source_index,
        (unsigned long)result->record.lat_pipeline_first_clause_node_index,
        runtime_lat_model_clause_role_label(result->record.lat_pipeline_first_clause_role),
        runtime_lat_effect_label(result->record.lat_pipeline_first_clause_effect),
        result->record.lat_pipeline_first_clause_name,
        result->record.lat_pipeline_first_clause_operator,
        result->record.lat_pipeline_first_clause_value,
        (unsigned long)result->record.lat_pipeline_node_count,
        (unsigned long)result->record.lat_pipeline_edge_count,
        (unsigned long)result->record.lat_pipeline_comment_count,
        (unsigned long)result->record.lat_pipeline_first_comment_span.start_offset,
        (unsigned long)result->record.lat_pipeline_first_comment_span.end_offset,
        (unsigned long)result->record.lat_pipeline_first_comment_span.start_line,
        (unsigned long)result->record.lat_pipeline_first_comment_span.start_column,
        (unsigned long)result->record.lat_pipeline_first_comment_span.end_line,
        (unsigned long)result->record.lat_pipeline_first_comment_span.end_column);
    if (written < 0 || (size_t)written >= buffer_len - offset) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    offset += (size_t)written;
    written = snprintf(buffer + offset, buffer_len - offset,
        "lat_lir_source_kind=%s\nlat_lir_module_name=%s\nlat_lir_card_name=%s\nlat_lir_effect=%s\nlat_lir_boundary=%s\nlat_lir_report_classification=%s\nlat_lir_shape_kind=%s\nlat_lir_span_start_offset=%lu\nlat_lir_span_end_offset=%lu\nlat_lir_span_start_line=%lu\nlat_lir_span_start_column=%lu\nlat_lir_span_end_line=%lu\nlat_lir_span_end_column=%lu\nlat_lir_module_node_count=%lu\nlat_lir_module_edge_count=%lu\nlat_lir_binding_count=%lu\nlat_lir_text_count=%lu\nlat_lir_no_effect_chain_ok=%d\nlat_lir_evidence_level=%u\nlat_lir_no_effect=%d\nlat_lir_execution_allowed=%d\nlat_lir_mutation_allowed=%d\nlat_lir_server_allowed=%d\nlat_lir_network_allowed=%d\nlat_lir_recovery_allowed=%d\nlat_lir_hardware_allowed=%d\nlat_lir_contains_edge_count=%lu\nlat_lir_binds_edge_count=%lu\nlat_lir_annotates_edge_count=%lu\nlat_lir_orders_before_edge_count=%lu\nlat_lir_transition_edge_count=%lu\nlat_lir_has_lat_state_nodes=%d\nlat_lir_has_lat_transition_nodes=%d\nlat_lir_has_transition_source_edges=%d\nno_effect=%d\nexecution_allowed=%d\nmutation_allowed=%d\nfile_io_allowed=%d\nnetwork_allowed=%d\nserver_allowed=%d\nrecovery_allowed=%d\nrollback_allowed=%d\nhardware_allowed=%d\nboot_allowed=%d\nsource_identity=%s\nspan_start_offset=%lu\nspan_end_offset=%lu\nspan_start_line=%lu\nspan_start_column=%lu\nspan_end_line=%lu\nspan_end_column=%lu\n",
        runtime_lir_source_kind_label(result->record.lat_lir_source_kind),
        result->record.lat_lir_module_name,
        result->record.lat_lir_card_name,
        result->record.lat_lir_effect,
        result->record.lat_lir_boundary,
        runtime_lir_report_classification_label(result->record.lat_lir_report_classification),
        runtime_lir_shape_kind_label(result->record.lat_lir_shape_kind),
        (unsigned long)result->record.lat_lir_source_span.start_offset,
        (unsigned long)result->record.lat_lir_source_span.end_offset,
        (unsigned long)result->record.lat_lir_source_span.start_line,
        (unsigned long)result->record.lat_lir_source_span.start_column,
        (unsigned long)result->record.lat_lir_source_span.end_line,
        (unsigned long)result->record.lat_lir_source_span.end_column,
        (unsigned long)result->record.lat_lir_module_node_count,
        (unsigned long)result->record.lat_lir_module_edge_count,
        (unsigned long)result->record.lat_lir_binding_count,
        (unsigned long)result->record.lat_lir_text_count,
        result->record.lat_lir_no_effect_chain_ok,
        result->record.lat_lir_evidence_level,
        result->record.lat_lir_no_effect,
        result->record.lat_lir_execution_allowed,
        result->record.lat_lir_mutation_allowed,
        result->record.lat_lir_server_allowed,
        result->record.lat_lir_network_allowed,
        result->record.lat_lir_recovery_allowed,
        result->record.lat_lir_hardware_allowed,
        (unsigned long)result->record.lat_lir_contains_edge_count,
        (unsigned long)result->record.lat_lir_binds_edge_count,
        (unsigned long)result->record.lat_lir_annotates_edge_count,
        (unsigned long)result->record.lat_lir_orders_before_edge_count,
        (unsigned long)result->record.lat_lir_transition_edge_count,
        result->record.lat_lir_has_lat_state_nodes,
        result->record.lat_lir_has_lat_transition_nodes,
        result->record.lat_lir_has_transition_source_edges,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->file_io_allowed,
        result->network_allowed,
        result->server_allowed,
        result->recovery_allowed,
        result->rollback_allowed,
        result->hardware_allowed,
        result->boot_allowed,
        result->record.source_identity,
        (unsigned long)result->record.source_span.start_offset,
        (unsigned long)result->record.source_span.end_offset,
        (unsigned long)result->record.source_span.start_line,
        (unsigned long)result->record.source_span.start_column,
        (unsigned long)result->record.source_span.end_line,
        (unsigned long)result->record.source_span.end_column);
    if (written < 0 || (size_t)written >= buffer_len - offset) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    used = offset + (size_t)written;
    extra = snprintf(buffer + used, buffer_len - used,
        "lat_lir_lat_state_node_count=%lu\nlat_lir_lat_policy_node_count=%lu\nlat_lir_lat_transition_node_count=%lu\nlat_lir_lat_assertion_node_count=%lu\nlat_lir_lat_requirement_node_count=%lu\nlat_lir_lat_effect_declaration_node_count=%lu\nlat_lir_has_first_lat_node=%d\nlat_lir_first_lat_node_index=%lu\nlat_lir_first_lat_node_kind=%s\nlat_lir_first_lat_node_name=%s\nlat_lir_first_lat_node_value=%s\nlat_lir_first_lat_node_operator=%s\nlat_lir_first_lat_node_binding=%s\nlat_lir_first_lat_node_parent_index=%lu\nlat_lir_first_lat_node_first_child_index=%lu\nlat_lir_first_lat_node_child_count=%lu\nlat_lir_first_lat_node_span_start_offset=%lu\nlat_lir_first_lat_node_span_end_offset=%lu\nlat_lir_first_lat_node_span_start_line=%lu\nlat_lir_first_lat_node_span_start_column=%lu\nlat_lir_first_lat_node_span_end_line=%lu\nlat_lir_first_lat_node_span_end_column=%lu\nlat_lir_has_first_transition_node=%d\nlat_lir_first_transition_node_index=%lu\nlat_lir_first_transition_node_kind=%s\nlat_lir_first_transition_node_name=%s\nlat_lir_first_transition_node_value=%s\nlat_lir_first_transition_node_operator=%s\nlat_lir_first_transition_node_binding=%s\nlat_lir_first_transition_node_parent_index=%lu\nlat_lir_first_transition_node_first_child_index=%lu\nlat_lir_first_transition_node_child_count=%lu\nlat_lir_first_transition_node_span_start_offset=%lu\nlat_lir_first_transition_node_span_end_offset=%lu\nlat_lir_first_transition_node_span_start_line=%lu\nlat_lir_first_transition_node_span_start_column=%lu\nlat_lir_first_transition_node_span_end_line=%lu\nlat_lir_first_transition_node_span_end_column=%lu\nlat_lir_has_first_edge=%d\nlat_lir_first_edge_index=%lu\nlat_lir_first_edge_from_index=%lu\nlat_lir_first_edge_to_index=%lu\nlat_lir_first_edge_kind=%s\nlat_lir_first_edge_span_start_offset=%lu\nlat_lir_first_edge_span_end_offset=%lu\nlat_lir_first_edge_span_start_line=%lu\nlat_lir_first_edge_span_start_column=%lu\nlat_lir_first_edge_span_end_line=%lu\nlat_lir_first_edge_span_end_column=%lu\nlat_lir_has_first_transition_source_edge=%d\nlat_lir_first_transition_source_edge_index=%lu\nlat_lir_first_transition_source_edge_from_index=%lu\nlat_lir_first_transition_source_edge_to_index=%lu\nlat_lir_first_transition_source_edge_kind=%s\nlat_lir_first_transition_source_edge_from_node_kind=%s\nlat_lir_first_transition_source_edge_from_node_name=%s\nlat_lir_first_transition_source_edge_from_node_value=%s\nlat_lir_first_transition_source_edge_from_node_operator=%s\nlat_lir_first_transition_source_edge_from_node_binding=%s\nlat_lir_first_transition_source_edge_from_node_parent_index=%lu\nlat_lir_first_transition_source_edge_from_node_first_child_index=%lu\nlat_lir_first_transition_source_edge_from_node_child_count=%lu\nlat_lir_first_transition_source_edge_from_node_span_start_offset=%lu\nlat_lir_first_transition_source_edge_from_node_span_end_offset=%lu\nlat_lir_first_transition_source_edge_from_node_span_start_line=%lu\nlat_lir_first_transition_source_edge_from_node_span_start_column=%lu\nlat_lir_first_transition_source_edge_from_node_span_end_line=%lu\nlat_lir_first_transition_source_edge_from_node_span_end_column=%lu\nlat_lir_first_transition_source_edge_to_node_kind=%s\nlat_lir_first_transition_source_edge_to_node_name=%s\nlat_lir_first_transition_source_edge_to_node_value=%s\nlat_lir_first_transition_source_edge_to_node_operator=%s\nlat_lir_first_transition_source_edge_to_node_binding=%s\nlat_lir_first_transition_source_edge_to_node_parent_index=%lu\nlat_lir_first_transition_source_edge_to_node_first_child_index=%lu\nlat_lir_first_transition_source_edge_to_node_child_count=%lu\nlat_lir_first_transition_source_edge_to_node_span_start_offset=%lu\nlat_lir_first_transition_source_edge_to_node_span_end_offset=%lu\nlat_lir_first_transition_source_edge_to_node_span_start_line=%lu\nlat_lir_first_transition_source_edge_to_node_span_start_column=%lu\nlat_lir_first_transition_source_edge_to_node_span_end_line=%lu\nlat_lir_first_transition_source_edge_to_node_span_end_column=%lu\nlat_lir_first_transition_source_edge_span_start_offset=%lu\nlat_lir_first_transition_source_edge_span_end_offset=%lu\nlat_lir_first_transition_source_edge_span_start_line=%lu\nlat_lir_first_transition_source_edge_span_start_column=%lu\nlat_lir_first_transition_source_edge_span_end_line=%lu\nlat_lir_first_transition_source_edge_span_end_column=%lu\n",
        (unsigned long)result->record.lat_lir_lat_state_node_count,
        (unsigned long)result->record.lat_lir_lat_policy_node_count,
        (unsigned long)result->record.lat_lir_lat_transition_node_count,
        (unsigned long)result->record.lat_lir_lat_assertion_node_count,
        (unsigned long)result->record.lat_lir_lat_requirement_node_count,
        (unsigned long)result->record.lat_lir_lat_effect_declaration_node_count,
        result->record.lat_lir_has_first_lat_node,
        (unsigned long)result->record.lat_lir_first_lat_node_index,
        runtime_lir_node_kind_label(result->record.lat_lir_first_lat_node_kind),
        result->record.lat_lir_first_lat_node_name,
        result->record.lat_lir_first_lat_node_value,
        result->record.lat_lir_first_lat_node_operator,
        result->record.lat_lir_first_lat_node_binding,
        (unsigned long)result->record.lat_lir_first_lat_node_parent_index,
        (unsigned long)result->record.lat_lir_first_lat_node_first_child_index,
        (unsigned long)result->record.lat_lir_first_lat_node_child_count,
        (unsigned long)result->record.lat_lir_first_lat_node_span.start_offset,
        (unsigned long)result->record.lat_lir_first_lat_node_span.end_offset,
        (unsigned long)result->record.lat_lir_first_lat_node_span.start_line,
        (unsigned long)result->record.lat_lir_first_lat_node_span.start_column,
        (unsigned long)result->record.lat_lir_first_lat_node_span.end_line,
        (unsigned long)result->record.lat_lir_first_lat_node_span.end_column,
        result->record.lat_lir_has_first_transition_node,
        (unsigned long)result->record.lat_lir_first_transition_node_index,
        runtime_lir_node_kind_label(result->record.lat_lir_first_transition_node_kind),
        result->record.lat_lir_first_transition_node_name,
        result->record.lat_lir_first_transition_node_value,
        result->record.lat_lir_first_transition_node_operator,
        result->record.lat_lir_first_transition_node_binding,
        (unsigned long)result->record.lat_lir_first_transition_node_parent_index,
        (unsigned long)result->record.lat_lir_first_transition_node_first_child_index,
        (unsigned long)result->record.lat_lir_first_transition_node_child_count,
        (unsigned long)result->record.lat_lir_first_transition_node_span.start_offset,
        (unsigned long)result->record.lat_lir_first_transition_node_span.end_offset,
        (unsigned long)result->record.lat_lir_first_transition_node_span.start_line,
        (unsigned long)result->record.lat_lir_first_transition_node_span.start_column,
        (unsigned long)result->record.lat_lir_first_transition_node_span.end_line,
        (unsigned long)result->record.lat_lir_first_transition_node_span.end_column,
        result->record.lat_lir_has_first_edge,
        (unsigned long)result->record.lat_lir_first_edge_index,
        (unsigned long)result->record.lat_lir_first_edge_from_index,
        (unsigned long)result->record.lat_lir_first_edge_to_index,
        runtime_lir_edge_kind_label(result->record.lat_lir_first_edge_kind),
        (unsigned long)result->record.lat_lir_first_edge_span.start_offset,
        (unsigned long)result->record.lat_lir_first_edge_span.end_offset,
        (unsigned long)result->record.lat_lir_first_edge_span.start_line,
        (unsigned long)result->record.lat_lir_first_edge_span.start_column,
        (unsigned long)result->record.lat_lir_first_edge_span.end_line,
        (unsigned long)result->record.lat_lir_first_edge_span.end_column,
        result->record.lat_lir_has_first_transition_source_edge,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_index,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_index,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_index,
        runtime_lir_edge_kind_label(result->record.lat_lir_first_transition_source_edge_kind),
        runtime_lir_node_kind_label(result->record.lat_lir_first_transition_source_edge_from_node_kind),
        result->record.lat_lir_first_transition_source_edge_from_node_name,
        result->record.lat_lir_first_transition_source_edge_from_node_value,
        result->record.lat_lir_first_transition_source_edge_from_node_operator,
        result->record.lat_lir_first_transition_source_edge_from_node_binding,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_parent_index,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_first_child_index,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_child_count,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_span.start_offset,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_span.end_offset,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_span.start_line,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_span.start_column,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_span.end_line,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_from_node_span.end_column,
        runtime_lir_node_kind_label(result->record.lat_lir_first_transition_source_edge_to_node_kind),
        result->record.lat_lir_first_transition_source_edge_to_node_name,
        result->record.lat_lir_first_transition_source_edge_to_node_value,
        result->record.lat_lir_first_transition_source_edge_to_node_operator,
        result->record.lat_lir_first_transition_source_edge_to_node_binding,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_parent_index,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_first_child_index,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_child_count,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_span.start_offset,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_span.end_offset,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_span.start_line,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_span.start_column,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_span.end_line,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_to_node_span.end_column,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_span.start_offset,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_span.end_offset,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_span.start_line,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_span.start_column,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_span.end_line,
        (unsigned long)result->record.lat_lir_first_transition_source_edge_span.end_column);
    if (extra < 0 || used + (size_t)extra >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
