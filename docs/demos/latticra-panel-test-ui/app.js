const tabs = [
  ["dashboard", "Dashboard"],
  ["components", "Components"],
  ["authority", "Authority"],
  ["delivery", "Delivery"],
  ["updater", "Updater"],
  ["evidence", "Evidence"],
  ["review", "Review"],
  ["readiness", "Readiness"],
  ["console", "Console"],
];

const STORAGE_KEY = "latticra-panel-test-ui-state-v1";
const SAVED_RECEIPT_LIMIT = 8;
const SNAPSHOT_LABEL_MAX_LENGTH = 48;
const COMMAND_PALETTE_RESULT_LIMIT = 12;
const QA_REPLAY_VISIBLE_CHIP_LIMIT = 6;
const BLOCKER_FILTER_MAX_LENGTH = 64;

const components = [
  {
    id: "console",
    name: "Latticra Console",
    note: "Panel-aware command surface, no shell launch.",
    selected: true,
  },
  {
    id: "lat",
    name: "Lat language tooling",
    note: "Parser and lowering tools for local evidence.",
    selected: true,
  },
  {
    id: "lir",
    name: "LIR contracts",
    note: "Intermediate representation records and tests.",
    selected: true,
  },
  {
    id: "seal",
    name: "Latticra Seal",
    note: "Report-only capability and receipt dashboard.",
    selected: true,
  },
  {
    id: "nadia",
    name: "Nadia offline AI foundation",
    note: "Metadata-only local planning records.",
    selected: true,
  },
  {
    id: "docs",
    name: "Documentation and examples",
    note: "Local source records and validation material.",
    selected: true,
  },
  {
    id: "fedora",
    name: "Fedora validation files",
    note: "Static validation lane, no host mutation.",
    selected: false,
  },
  {
    id: "developer",
    name: "Developer CLI helpers",
    note: "Local helper wrappers for reviewed workflows.",
    selected: false,
  },
];

const coreComponentIds = new Set(["console", "lat", "lir", "seal", "nadia", "docs"]);

const evidence = [
  ["dry_run_plan_digest", "ready-for-review", "plan"],
  ["panel_ui_lane", "isolated-test", "lane"],
  ["main_gui_mutation_required", "0", "boundary"],
  ["edge_gui_mutation_required", "0", "boundary"],
  ["root_authority", "0", "authority"],
  ["network_authority", "0", "authority"],
  ["runtime_enforcement_authority", "0", "authority"],
  ["production_installer_claim", "0", "claim"],
];

const allowedCommands = new Map([
  ["status", "panel=test-ui-lane mode={mode} root_authority=0 network_authority=0"],
  ["plan", "plan=current components={components} prefix={prefix}"],
  ["dry-run", "dry_install=simulated receipt=queued writes=0"],
  ["save", "receipt=saved target=test-ui-lane"],
  ["updater status", "signed_updater_delivery_gate=closed network_fetch=0"],
  ["updater dry-run", "updater_preview=simulated apply_allowed=0"],
  ["mode dry", "mode=dry-run writes=blocked"],
  ["mode local", "mode=guarded-local user_local_writes=armed"],
  ["clear", ""],
]);

const receiptChecklistItems = [
  {
    id: "profile_recorded",
    label: "profile recorded",
    source: "Profile selector",
    defaultRecorded: true,
  },
  {
    id: "authority_fields_recorded",
    label: "authority fields recorded",
    source: "Authority boundary",
    defaultRecorded: true,
  },
  {
    id: "component_manifest_digest_recorded",
    label: "component manifest digest recorded",
    source: "Component toggles",
    defaultRecorded: true,
  },
  {
    id: "operator_local_mode_acknowledgement",
    label: "operator local-mode acknowledgement",
    source: "Workspace mode control",
    defaultRecorded: false,
    available: () => state.mode === "local",
    blockedReason: () => "guarded local mode required",
  },
  {
    id: "install_prefix_write_receipt",
    label: "install-prefix write receipt",
    source: "Install prefix guard",
    defaultRecorded: false,
    available: () => state.mode === "local" && state.prefixValid,
    blockedReason: () => (state.mode === "local" ? "accepted user-local prefix required" : "guarded local mode required"),
  },
];

const state = {
  activeTab: "dashboard",
  mode: "dry",
  progress: 72,
  profile: "Guided local panel",
  prefix: "~/.local",
  prefixValid: true,
  evidenceDetail: 2,
  evidenceFilter: "",
  blockerFilter: "",
  reviewFilter: "all",
  receiptDiffFilter: "all",
  promotionGateSelection: "artifact_integrity",
  migrationReviewSelection: "workbench_frame",
  qaScenarioSelection: "keyboard_path_sweep",
  engineBindingSelection: "plan_preview_binding",
  visualBaselineSelection: "desktop_review_baseline",
  releaseAcceptanceSelection: "local_ui_acceptance",
  accessibilityAuditSelection: "screen_reader_live_pass",
  readinessCompareSelection: "local_ui_proof",
  evidenceIntakeSelection: "local_ui_packet",
  traceabilitySelection: "local_ui_trace",
  productionBlockerSelection: "reproducible_artifact",
  events: [],
  runState: "ready",
  consoleStatus: "ready",
  consoleMessage: "ready",
  consoleLastCommand: "status",
  paletteQuery: "",
  paletteSelection: "command:status",
  receiptChecklist: defaultReceiptChecklistState(),
  savedReceipts: [],
  selectedReceiptId: "",
};

let pendingReadinessCompareScroll = false;
let pendingEvidenceIntakeScroll = false;
let pendingTraceabilityScroll = false;
let pendingAccessibilityAuditScroll = false;

const receiptFields = [
  {
    key: "schema",
    value: () => "latticra-panel-test-ui-receipt-v0",
    source: () => "static lane schema",
    status: () => "live",
  },
  {
    key: "profile",
    value: () => state.profile,
    source: () => "Profile selector",
    status: () => "live",
  },
  {
    key: "mode",
    value: () => (state.mode === "dry" ? "dry-run" : "guarded-local"),
    source: () => "Workspace mode control",
    status: () => (state.mode === "local" ? "guarded" : "live"),
  },
  {
    key: "prefix",
    value: () => state.prefix || "~/.local",
    source: () => "Install prefix guard",
    status: () => (state.prefixValid ? "live" : "blocked"),
  },
  {
    key: "components",
    value: () => selectedComponents().map((component) => component.id).join(",") || "none",
    source: () => "Component toggles",
    status: () => "live",
  },
  {
    key: "component_count",
    value: () => String(selectedComponents().length),
    source: () => "Component toggles",
    status: () => "live",
  },
  {
    key: "console_status",
    value: () => state.consoleStatus,
    source: () => "Console allowlist state",
    status: () => (state.consoleStatus === "blocked" ? "blocked" : "live"),
  },
  {
    key: "console_last_command",
    value: () => state.consoleLastCommand || "none",
    source: () => "Console command field",
    status: () => (state.consoleStatus === "blocked" ? "blocked" : "live"),
  },
  {
    key: "receipt_checklist_recorded",
    value: () => String(receiptChecklistSummary().recorded),
    source: () => "Delivery receipt checklist",
    status: () => "live",
  },
  {
    key: "receipt_checklist_pending",
    value: () => String(receiptChecklistSummary().pending + receiptChecklistSummary().blocked),
    source: () => "Delivery receipt checklist",
    status: () => (receiptChecklistSummary().pending + receiptChecklistSummary().blocked > 0 ? "guarded" : "live"),
  },
  {
    key: "root_authority",
    value: () => "0",
    source: () => "Authority boundary",
    status: () => "blocked",
  },
  {
    key: "network_authority",
    value: () => "0",
    source: () => "Authority boundary",
    status: () => "blocked",
  },
  {
    key: "runtime_enforcement_authority",
    value: () => "0",
    source: () => "Authority boundary",
    status: () => "blocked",
  },
  {
    key: "production_installer_ready",
    value: () => "0",
    source: () => "Production readiness ledger",
    status: () => "blocked",
  },
  {
    key: "production_blocker_filter",
    value: () => productionBlockerSummary().filter || "none",
    source: () => "Readiness blocker filter",
    status: () => (productionBlockerSummary().filter_active ? "guarded" : "live"),
  },
  {
    key: "production_blocker_visible",
    value: () => {
      const summary = productionBlockerSummary();
      return `${summary.visible}/${summary.total}`;
    },
    source: () => "Readiness blocker filter",
    status: () => "live",
  },
  {
    key: "main_gui_mutation_required",
    value: () => "0",
    source: () => "Test-lane boundary",
    status: () => "blocked",
  },
  {
    key: "edge_gui_mutation_required",
    value: () => "0",
    source: () => "Test-lane boundary",
    status: () => "blocked",
  },
];

const qualityGates = [
  {
    key: "responsive_layout",
    label: "Responsive layout",
    status: "verified",
    evidence: "desktop and mobile overflow checks pass",
    next: "keep dense workbench layout below overflow thresholds",
  },
  {
    key: "authority_boundary",
    label: "Authority boundary",
    status: "verified",
    evidence: "root, network, runtime, and production claims blocked",
    next: "preserve zero-authority receipt fields",
  },
  {
    key: "state_persistence",
    label: "State persistence",
    status: "verified",
    evidence: "local state reload and reset verified",
    next: "keep reset and replay state scoped to this lane",
  },
  {
    key: "receipt_mapping",
    label: "Receipt mapping",
    status: "verified",
    evidence: "live UI state maps to receipt fields",
    next: "continue binding new surfaces before guarded migration",
  },
  {
    key: "egui_migration_review",
    label: "egui migration review",
    status: "pending",
    evidence: "prototype-to-Rust migration remains separate",
    next: "compare against guarded Rust Panel before any port",
  },
  {
    key: "installer_engine_binding",
    label: "installer engine binding",
    status: "pending",
    evidence: "test lane is not bound to installer execution",
    next: "bind real installer events only after contract review",
  },
];

const reviewChecks = [
  {
    name: "Responsive workbench layout",
    state: "verified",
    evidence: "desktop and mobile overflow checks, inspector collapse, and tab rail scroll verified",
    key: "responsive_layout",
  },
  {
    name: "Authority and prefix guard",
    state: "verified",
    evidence: "system, root, and remote prefixes block plans before simulated runs",
    key: "prefix_guard",
  },
  {
    name: "Receipt preview and event trail",
    state: "verified",
    evidence: "operator actions are persisted and reflected in the no-effect JSON receipt preview",
    key: "receipt_event_model",
  },
  {
    name: "Keyboard and ARIA tab semantics",
    state: "verified",
    evidence: "tablist, tabpanel, radio mode, arrow, Home, and End navigation are present",
    key: "tab_semantics",
  },
  {
    name: "Production blocker visibility",
    state: "verified",
    evidence: "installer artifact, lifecycle, upgrade, rollback, and VM blockers stay visible",
    key: "blocker_ledger",
  },
  {
    name: "egui migration review",
    state: "pending",
    evidence: "requires side-by-side review against the guarded Rust Panel before porting",
    key: "egui_migration_review",
  },
  {
    name: "Installer engine state binding",
    state: "pending",
    evidence: "prototype still uses simulated no-effect state rather than installer execution state",
    key: "installer_engine_binding",
  },
  {
    name: "Production artifact evidence",
    state: "blocked",
    evidence: "release claim waits for reproducible artifact, signature, SBOM, transcript, and VM records",
    key: "production_artifact_evidence",
  },
];

const accessibilityAuditItems = [
  {
    key: "tab_rail_roving_focus",
    label: "Tab rail roving focus",
    status: "verified",
    path: "Arrow, Home, and End navigation across workspace tabs",
    evidence: "aria-selected, tabpanel visibility, and assistive tab announcements",
  },
  {
    key: "mode_radiogroup_keyboard",
    label: "Mode radio group",
    status: "verified",
    path: "Dry-run and guarded local mode use radio semantics with roving tabindex",
    evidence: "aria-checked updates and keyboard movement are bound to receipt state",
  },
  {
    key: "review_filter_keyboard",
    label: "Review filter radio group",
    status: "verified",
    path: "All, verified, pending, and blocked filters support arrow navigation",
    evidence: "filter state persists locally and updates the no-effect receipt",
  },
  {
    key: "receipt_diff_filter_keyboard",
    label: "Receipt diff filter",
    status: "verified",
    path: "All, changed, and same field views support keyboard review",
    evidence: "diff filter is replayed by URL and export/handoff manifests",
  },
  {
    key: "promotion_gate_listbox_keyboard",
    label: "Promotion gate listbox",
    status: "verified",
    path: "Promotion gate rows support option selection and arrow movement",
    evidence: "selected remediation detail is replayed with gate= and bound to receipts",
  },
  {
    key: "component_toggle_descriptions",
    label: "Component toggle descriptions",
    status: "verified",
    path: "Checkbox controls include descriptive text and visible focus state",
    evidence: "component selection updates assistive status and receipt component count",
  },
  {
    key: "console_blocked_focus_recovery",
    label: "Console blocked-command recovery",
    status: "verified",
    path: "Blocked allowlist commands return focus to the command field",
    evidence: "invalid state, visible console status, and receipt fields stay aligned",
  },
  {
    key: "receipt_preview_keyboard_focus",
    label: "Receipt preview focus",
    status: "verified",
    path: "No-effect receipt and manifests expose keyboard focus targets",
    evidence: "preformatted JSON regions have labels and remain local-only",
  },
  {
    key: "screen_reader_live_pass",
    label: "Screen-reader live pass",
    status: "pending",
    path: "Manual VoiceOver/NVDA-style pass before guarded Panel migration",
    evidence: "prototype has labels and live regions; external assistive-tech pass is still pending",
  },
  {
    key: "installer_engine_live_a11y",
    label: "Installer engine live accessibility",
    status: "pending",
    path: "Bind real installer progress and error states to live-region copy",
    evidence: "current lane is simulated and does not expose production installer runtime state",
  },
];

const migrationMap = [
  {
    key: "workbench_frame",
    label: "Workbench frame and tab rail",
    source: "test HTML/CSS lane",
    destination: "guarded Rust Panel egui frame",
    state: "candidate",
    guard: "preserve compact layout, explicit active tab state, and no edge GUI mutation",
    owner: "Panel migration",
    evidence: "desktop and mobile browser proof, tab semantics, and no-overflow checks",
    next: "compare layout density and active-tab behavior against the guarded Rust Panel",
    boundary: "test-lane design only; guarded Rust Panel stays unchanged",
  },
  {
    key: "prefix_guard",
    label: "Prefix guard",
    source: "validatePrefix() model",
    destination: "installer preflight gate",
    state: "candidate",
    guard: "keep user-local-only writes and blocked root/system/remote paths",
    owner: "installer safety",
    evidence: "prefix validation, blocked path copy, and receipt authority fields",
    next: "map accepted and blocked prefixes to installer preflight evidence",
    boundary: "no installer authority is granted from this prototype",
  },
  {
    key: "receipt_event_trail",
    label: "Receipt preview and event trail",
    source: "local no-effect receipt model",
    destination: "installer evidence binding",
    state: "needs binding",
    guard: "replace simulated events with signed evidence records before production claims",
    owner: "evidence binding",
    evidence: "saved snapshots, export validation, integrity digest, and QA handoff manifest",
    next: "replace simulated events with signed installer evidence records",
    boundary: "local no-effect receipt only; production evidence remains zero",
  },
  {
    key: "production_blocker_ledger",
    label: "Production blocker ledger",
    source: "readiness tab",
    destination: "release checklist and CI evidence",
    state: "blocked",
    guard: "requires artifact, SBOM, transcript, upgrade, rollback, and multi-VM evidence",
    owner: "release evidence",
    evidence: "readiness blocker list and promotion gate counts",
    next: "attach artifact, SBOM, transcript, rollback, and VM validation records",
    boundary: "cannot promote or mutate release GUI from this lane",
  },
];

const qaScenarios = [
  {
    key: "desktop_layout_review",
    label: "Desktop layout review",
    status: "verified",
    trigger: "Open the Review tab at the default desktop viewport",
    expected: "workbench, review evidence, migration map, and receipt surfaces fit without horizontal overflow",
    evidence: "desktop browser proof and screenshot remain local to the test lane",
    owner: "UI QA",
    next: "repeat after each visual slice before any guarded Panel migration",
    boundary: "viewport proof only; no production GUI mutation",
  },
  {
    key: "mobile_breakpoint_review",
    label: "Mobile breakpoint review",
    status: "verified",
    trigger: "Open Review at the 390px mobile breakpoint",
    expected: "stacked sections, listbox rows, and receipt controls stay readable with no horizontal overflow",
    evidence: "mobile browser proof and screenshot remain local to the test lane",
    owner: "UI QA",
    next: "keep mobile screenshots attached to each high-risk UI slice",
    boundary: "responsive test lane only",
  },
  {
    key: "keyboard_path_sweep",
    label: "Keyboard path sweep",
    status: "verified",
    trigger: "Use tab stops and arrow keys across tabs, filters, listboxes, and saved receipts",
    expected: "selected controls use roving tabindex, visible focus, assistive status, and receipt-aligned state",
    evidence: "mode, review, diff, promotion, and migration controls are keyboard verified",
    owner: "accessibility QA",
    next: "run the same sweep after adding each new selectable surface",
    boundary: "prototype keyboard behavior; manual screen-reader pass still pending",
  },
  {
    key: "receipt_replay_handoff",
    label: "Receipt replay handoff",
    status: "verified",
    trigger: "Save a local receipt and inspect the generated QA handoff URL and manifest",
    expected: "snapshot, digest, filters, gate, migration, and zero-authority boundary validate together",
    evidence: "handoff validation ledger reaches all-passed for local snapshots",
    owner: "release QA",
    next: "keep filter and selected-surface replay covered in every handoff change",
    boundary: "local no-effect artifact only",
  },
  {
    key: "guarded_panel_side_by_side",
    label: "Guarded Panel side-by-side",
    status: "pending",
    trigger: "Compare selected prototype surfaces against the guarded Rust Panel",
    expected: "candidate surfaces have matching behavior before any implementation migration",
    evidence: "migration drilldown lists candidates; guarded Panel port has not started",
    owner: "Panel migration",
    next: "run side-by-side egui review after prototype surfaces stabilize",
    boundary: "guarded Rust Panel remains unchanged",
  },
  {
    key: "production_claim_denial",
    label: "Production claim denial",
    status: "blocked",
    trigger: "Attempt to treat local UI evidence as release evidence",
    expected: "promotion stays blocked until artifact, SBOM, transcript, rollback, and VM evidence exists",
    evidence: "promotion gate and readiness blockers keep production claim authority at zero",
    owner: "release evidence",
    next: "collect real release evidence in the production lanes before promotion",
    boundary: "production_installer_claim=0",
  },
];

const engineBindingItems = [
  {
    key: "plan_preview_binding",
    label: "Plan preview binding",
    status: "verified",
    source: "renderPlan() simulated plan state",
    target: "installer plan payload",
    evidence: "profile, mode, prefix, component list, and authority fields render into the no-effect receipt",
    owner: "installer engine",
    next: "compare simulated plan fields with the real installer plan payload",
    boundary: "simulation only; no installer execution authority",
  },
  {
    key: "prefix_guard_binding",
    label: "Prefix guard binding",
    status: "verified",
    source: "validatePrefix() guard state",
    target: "installer preflight decision",
    evidence: "accepted and blocked prefix states map to receipt fields and visible guard copy",
    owner: "installer safety",
    next: "bind real preflight denial reasons to the same receipt fields",
    boundary: "user-local policy only; system paths remain blocked",
  },
  {
    key: "receipt_snapshot_binding",
    label: "Receipt snapshot binding",
    status: "verified",
    source: "local receipt snapshots and event trail",
    target: "installer evidence ledger",
    evidence: "saved snapshots, diff detail, export validation, and QA handoff stay local-only",
    owner: "evidence binding",
    next: "replace simulated snapshot events with signed installer evidence rows",
    boundary: "not production evidence",
  },
  {
    key: "run_monitor_progress_binding",
    label: "Run monitor progress binding",
    status: "pending",
    source: "dry-run monitor progress and log copy",
    target: "installer progress event stream",
    evidence: "current progress is UI-simulated and not sourced from a live installer process",
    owner: "installer engine",
    next: "map real plan, start, progress, complete, and failure events to the monitor",
    boundary: "runtime execution authority remains zero",
  },
  {
    key: "error_live_region_binding",
    label: "Error and live-region binding",
    status: "pending",
    source: "console status, toast, and assistive-status region",
    target: "installer error and recovery states",
    evidence: "blocked commands announce correctly; live installer errors are not bound yet",
    owner: "accessibility QA",
    next: "bind installer errors to visible status, focus recovery, and assistive announcements",
    boundary: "manual screen-reader pass still pending",
  },
  {
    key: "production_execution_binding",
    label: "Production execution binding",
    status: "blocked",
    source: "test-lane dry-run simulation",
    target: "production installer execution",
    evidence: "artifact, SBOM, transcript, rollback, and multi-VM release evidence are missing",
    owner: "release evidence",
    next: "keep production execution closed until release evidence exists",
    boundary: "production_installer_claim=0",
  },
];

const engineEventAdapterItems = [
  {
    key: "plan_payload_event",
    label: "Plan payload event",
    status: "verified",
    phase: "plan.payload",
    source: "renderPlan() no-effect plan",
    binding: "plan_preview_binding",
    evidence: "profile, mode, prefix, component list, and authority fields map into the local receipt",
    next: "compare the local adapter shape against the real installer plan event",
    boundary: "adapter contract only; no live installer process is attached",
  },
  {
    key: "preflight_decision_event",
    label: "Preflight decision event",
    status: "verified",
    phase: "preflight.decision",
    source: "validatePrefix() guard result",
    binding: "prefix_guard_binding",
    evidence: "accepted and blocked prefix decisions render visibly and in receipt authority fields",
    next: "bind real preflight denial reasons to the same UI fields",
    boundary: "user-local prefix policy remains a no-effect test-lane guard",
  },
  {
    key: "run_started_event",
    label: "Run started event",
    status: "pending",
    phase: "run.started",
    source: "dry-run action state",
    binding: "run_monitor_progress_binding",
    evidence: "current run start is simulated by the UI and not sourced from installer runtime",
    next: "map installer start event to monitor state and receipt trail",
    boundary: "runtime execution authority remains zero",
  },
  {
    key: "progress_tick_event",
    label: "Progress tick event",
    status: "pending",
    phase: "run.progress",
    source: "simulated progress counter and log copy",
    binding: "run_monitor_progress_binding",
    evidence: "progress is local-only and has no live installer event source",
    next: "stream real progress ticks into the monitor without changing host state",
    boundary: "progress proof is not production evidence",
  },
  {
    key: "error_recovery_event",
    label: "Error recovery event",
    status: "pending",
    phase: "run.error",
    source: "console status, toast, and assistive-status region",
    binding: "error_live_region_binding",
    evidence: "blocked command errors announce locally; installer runtime errors are not connected",
    next: "bind installer errors to visible status, focus recovery, and live-region copy",
    boundary: "manual assistive-tech pass remains pending",
  },
  {
    key: "execution_authority_event",
    label: "Execution authority event",
    status: "blocked",
    phase: "run.execute",
    source: "test-lane dry-run button",
    binding: "production_execution_binding",
    evidence: "artifact, SBOM, lifecycle transcript, rollback, and VM evidence are missing",
    next: "keep production execution closed until release evidence exists",
    boundary: "production_installer_claim=0",
  },
];

const visualBaselineItems = [
  {
    key: "desktop_review_baseline",
    label: "Desktop Review baseline",
    status: "verified",
    viewport: "1280x900",
    evidence: "Review tab sections render without horizontal overflow or console errors",
    owner: "UI QA",
    next: "refresh screenshot evidence after each Review surface change",
    boundary: "local screenshot proof only",
  },
  {
    key: "mobile_review_baseline",
    label: "Mobile Review baseline",
    status: "verified",
    viewport: "390x900",
    evidence: "Review evidence, listboxes, and details stack without clipping",
    owner: "UI QA",
    next: "repeat on every mobile-affecting layout change",
    boundary: "responsive test-lane proof only",
  },
  {
    key: "receipt_handoff_baseline",
    label: "Receipt and handoff baseline",
    status: "verified",
    viewport: "1280x900",
    evidence: "saved receipt, export preview, validation ledger, and handoff manifest remain readable",
    owner: "release QA",
    next: "capture after receipt schema or handoff filter changes",
    boundary: "not production evidence",
  },
  {
    key: "focus_state_baseline",
    label: "Focus state baseline",
    status: "verified",
    viewport: "keyboard sweep",
    evidence: "selected rows, filters, tabs, toggles, and receipt controls expose visible focus",
    owner: "accessibility QA",
    next: "recheck after every selectable surface is added",
    boundary: "manual assistive-tech certification still pending",
  },
  {
    key: "guarded_panel_visual_compare",
    label: "Guarded Panel visual compare",
    status: "pending",
    viewport: "egui side-by-side",
    evidence: "prototype baselines exist; guarded Rust Panel comparison has not been run",
    owner: "Panel migration",
    next: "compare candidate surfaces before any guarded Panel implementation change",
    boundary: "guarded Rust Panel remains unchanged",
  },
  {
    key: "release_visual_signoff",
    label: "Release visual signoff",
    status: "blocked",
    viewport: "production matrix",
    evidence: "release visual signoff waits for artifact, SBOM, transcript, rollback, and VM evidence",
    owner: "release evidence",
    next: "keep release signoff closed until production evidence exists",
    boundary: "production_installer_claim=0",
  },
];

const releaseAcceptanceItems = [
  {
    key: "local_ui_acceptance",
    label: "Local UI evidence acceptance",
    status: "verified",
    source: "evidence matrix, visual baseline, QA runbook",
    evidence: "local receipt, browser, screenshot, and handoff proof are present",
    owner: "UI QA",
    next: "keep local proof refreshed after each test-lane surface change",
    boundary: "local proof only; not production release evidence",
  },
  {
    key: "receipt_handoff_acceptance",
    label: "Receipt and handoff acceptance",
    status: "verified",
    source: "saved receipts, export validation, QA handoff",
    evidence: "local export digest and handoff validation can replay selected surfaces",
    owner: "release QA",
    next: "preserve filter and selected-surface replay in each new ledger",
    boundary: "handoff_mutates_state=0",
  },
  {
    key: "accessibility_acceptance",
    label: "Accessibility acceptance",
    status: "pending",
    source: "accessibility audit",
    evidence: "keyboard and labels are verified; manual assistive-tech pass remains pending",
    owner: "accessibility QA",
    next: "complete manual screen-reader pass before guarded Panel migration",
    boundary: "production_accessibility_claim=0",
  },
  {
    key: "guarded_panel_acceptance",
    label: "Guarded Panel migration acceptance",
    status: "pending",
    source: "migration map and visual compare",
    evidence: "prototype candidates exist; side-by-side Rust Panel comparison is not complete",
    owner: "Panel migration",
    next: "compare selected surfaces against the guarded Rust Panel before porting",
    boundary: "main_gui_mutation_required=0",
  },
  {
    key: "installer_engine_acceptance",
    label: "Installer engine acceptance",
    status: "pending",
    source: "installer engine binding matrix",
    evidence: "simulated state is mapped; live installer events are not bound",
    owner: "installer engine",
    next: "replace simulated progress and errors with real installer event streams",
    boundary: "runtime_enforcement_authority=0",
  },
  {
    key: "production_evidence_acceptance",
    label: "Production evidence acceptance",
    status: "blocked",
    source: "promotion gate and blocker ledger",
    evidence: "artifact, signature, SBOM, transcripts, rollback, and VM evidence are missing",
    owner: "release evidence",
    next: "collect production release evidence outside the test UI lane",
    boundary: "production_evidence_claim=0",
  },
  {
    key: "release_authority_acceptance",
    label: "Release authority acceptance",
    status: "blocked",
    source: "promotion decision record",
    evidence: "can_promote remains false and production installer claim authority is zero",
    owner: "release owner",
    next: "keep release authority closed until every production gate is proven",
    boundary: "production_installer_claim=0",
  },
];

const reviewFilterOptions = ["all", "verified", "pending", "blocked"];
const receiptDiffFilterOptions = ["all", "changed", "same"];

const productionBlockers = [
  {
    group: "Installer artifacts",
    items: [
      {
        key: "reproducible_artifact",
        label: "Reproducible artifact",
        status: "blocked",
        evidence: "installer_artifact_reproducible=0",
        owner: "release evidence",
        next: "record reproducible artifact digest and build provenance",
        source: "artifact pipeline",
      },
      {
        key: "artifact_signature",
        label: "Artifact signature",
        status: "blocked",
        evidence: "installer_artifact_signature_recorded=0",
        owner: "release evidence",
        next: "attach signing evidence and verification transcript",
        source: "signing pipeline",
      },
      {
        key: "sbom_evidence",
        label: "SBOM evidence",
        status: "blocked",
        evidence: "installer_sbom_recorded=0",
        owner: "supply chain",
        next: "attach release SBOM and dependency attestation",
        source: "supply-chain review",
      },
    ],
  },
  {
    group: "Install lifecycle evidence",
    items: [
      {
        key: "production_preflight_guard",
        label: "Production preflight guard",
        status: "blocked",
        evidence: "installer_preflight_guard_present=0",
        owner: "installer safety",
        next: "bind production preflight denial reasons to release evidence",
        source: "installer preflight",
      },
      {
        key: "install_transcript",
        label: "Install transcript",
        status: "blocked",
        evidence: "installer_install_transcript_recorded=0",
        owner: "installer QA",
        next: "capture successful install transcript on supported targets",
        source: "installer lifecycle",
      },
      {
        key: "uninstall_transcript",
        label: "Uninstall transcript",
        status: "blocked",
        evidence: "installer_uninstall_transcript_recorded=0",
        owner: "installer QA",
        next: "capture uninstall and cleanup transcript",
        source: "installer lifecycle",
      },
    ],
  },
  {
    group: "Upgrade and recovery",
    items: [
      {
        key: "upgrade_path",
        label: "Upgrade path",
        status: "blocked",
        evidence: "installer_upgrade_path_validated=0",
        owner: "recovery QA",
        next: "validate upgrade from prior release state",
        source: "upgrade scenario",
      },
      {
        key: "rollback_path",
        label: "Rollback path",
        status: "blocked",
        evidence: "installer_rollback_path_validated=0",
        owner: "recovery QA",
        next: "validate rollback after failed or cancelled install",
        source: "rollback scenario",
      },
      {
        key: "multi_vm_validation",
        label: "Multi-VM validation",
        status: "blocked",
        evidence: "installer_multi_vm_validation_completed=0",
        owner: "platform QA",
        next: "complete supported VM validation matrix",
        source: "platform matrix",
      },
    ],
  },
];

const readinessComparisonItems = [
  {
    key: "local_ui_proof",
    label: "Local UI proof",
    status: "verified",
    localProof: "browser QA, receipt preview, handoff replay, and local guard checks are present",
    productionRequirement: "not production release evidence",
    owner: "UI QA",
    next: "keep local proof refreshed after each test-lane UI slice",
    boundary: "local proof only; can_promote=false",
  },
  {
    key: "guarded_panel_migration",
    label: "Guarded Panel migration",
    status: "pending",
    localProof: "candidate surfaces are mapped in the migration review ledger",
    productionRequirement: "side-by-side egui behavior review before any guarded Panel migration",
    owner: "Panel migration",
    next: "compare selected prototype surfaces against the guarded Rust Panel",
    boundary: "main_gui_mutation_required=0 in this lane",
  },
  {
    key: "installer_engine_binding",
    label: "Installer engine binding",
    status: "pending",
    localProof: "simulated plan, prefix, monitor, receipt, and error bindings are mapped",
    productionRequirement: "live installer event stream, progress, failure, and recovery states",
    owner: "installer engine",
    next: "replace simulated UI state with real installer event records",
    boundary: "runtime_enforcement_authority=0",
  },
  {
    key: "release_artifacts",
    label: "Release artifacts",
    status: "blocked",
    localProof: "UI exposes missing artifact, signature, and SBOM evidence",
    productionRequirement: "reproducible artifact digest, signature verification, and SBOM attestation",
    owner: "release evidence",
    next: "attach artifact, signature, and SBOM production records outside the test lane",
    boundary: "production_evidence_claim=0",
  },
  {
    key: "lifecycle_validation",
    label: "Lifecycle validation",
    status: "blocked",
    localProof: "preflight, install, and uninstall blockers are visible",
    productionRequirement: "production preflight guard plus install and uninstall transcripts",
    owner: "installer QA",
    next: "capture supported-target lifecycle transcripts in production validation lanes",
    boundary: "host_write_authority=0",
  },
  {
    key: "recovery_matrix",
    label: "Recovery matrix",
    status: "blocked",
    localProof: "upgrade, rollback, and multi-VM gaps are tracked as blocker rows",
    productionRequirement: "validated upgrade path, rollback path, and supported VM matrix",
    owner: "recovery QA",
    next: "complete upgrade, rollback, and multi-VM validation outside the UI prototype",
    boundary: "production_installer_claim=0",
  },
];

const releaseEvidenceIntakeItems = [
  {
    key: "local_ui_packet",
    label: "Local UI proof packet",
    status: "local-only",
    packet: "browser QA, static guard, receipt replay, and mobile layout proof",
    source: "isolated test UI lane",
    decision: "accepted for local QA review only",
    reviewer: "UI QA",
    next: "refresh the local packet after each UI refinement",
    boundary: "production_evidence_claim=0",
  },
  {
    key: "guarded_panel_packet",
    label: "Guarded Panel migration packet",
    status: "waiting",
    packet: "side-by-side egui behavior notes and parity screenshots",
    source: "guarded Rust Panel review",
    decision: "waiting for migration evidence",
    reviewer: "Panel migration",
    next: "collect guarded Panel parity review before migration",
    boundary: "main_gui_mutation_required=0",
  },
  {
    key: "installer_runtime_packet",
    label: "Installer runtime packet",
    status: "waiting",
    packet: "live event stream, progress, failure, and recovery binding records",
    source: "installer engine",
    decision: "waiting for live runtime records",
    reviewer: "installer engine",
    next: "replace simulated state with installer event evidence",
    boundary: "runtime_enforcement_authority=0",
  },
  {
    key: "artifact_signature_packet",
    label: "Artifact and signature packet",
    status: "blocked",
    packet: "reproducible artifact digest, detached signature, and SBOM attestation",
    source: "release artifact lane",
    decision: "blocked until production artifact evidence exists",
    reviewer: "release evidence",
    next: "attach artifact digest, signature verification, and SBOM record",
    boundary: "production_artifact_claim=0",
  },
  {
    key: "lifecycle_transcript_packet",
    label: "Lifecycle transcript packet",
    status: "blocked",
    packet: "preflight denial, install, uninstall, and reset transcripts",
    source: "installer validation",
    decision: "blocked until supported-target transcripts exist",
    reviewer: "installer QA",
    next: "capture lifecycle transcripts outside the UI prototype",
    boundary: "host_write_authority=0",
  },
  {
    key: "recovery_validation_packet",
    label: "Recovery validation packet",
    status: "blocked",
    packet: "upgrade, rollback, failed-run recovery, and multi-VM validation",
    source: "recovery matrix",
    decision: "blocked until recovery matrix evidence exists",
    reviewer: "recovery QA",
    next: "complete recovery validation before release promotion",
    boundary: "production_installer_claim=0",
  },
];

const traceabilityItems = [
  {
    key: "local_ui_trace",
    label: "Local UI trace",
    status: "covered",
    blockers: "none",
    intake: "local_ui_packet",
    gate: "local_ui_evidence",
    acceptance: "local_ui_acceptance",
    owner: "UI QA",
    evidence: "receipt, QA handoff, browser checks, and static guard stay local-only",
    next: "refresh local proof after each UI refinement",
    boundary: "production_evidence_claim=0",
  },
  {
    key: "migration_trace",
    label: "Guarded Panel migration trace",
    status: "waiting",
    blockers: "guarded_panel_migration",
    intake: "guarded_panel_packet",
    gate: "main_panel_migration_review",
    acceptance: "guarded_panel_acceptance",
    owner: "Panel migration",
    evidence: "prototype surfaces are mapped, but guarded egui parity review is not complete",
    next: "capture side-by-side guarded Rust Panel review before migration",
    boundary: "main_gui_mutation_required=0",
  },
  {
    key: "installer_runtime_trace",
    label: "Installer runtime trace",
    status: "waiting",
    blockers: "installer_engine_binding",
    intake: "installer_runtime_packet",
    gate: "installer_engine_binding",
    acceptance: "installer_engine_acceptance",
    owner: "installer engine",
    evidence: "simulated plan, prefix, progress, and error states are mapped",
    next: "bind real installer event streams before any release claim",
    boundary: "runtime_enforcement_authority=0",
  },
  {
    key: "artifact_supply_chain_trace",
    label: "Artifact and supply-chain trace",
    status: "blocked",
    blockers: "reproducible_artifact, artifact_signature, sbom_evidence",
    intake: "artifact_signature_packet",
    gate: "artifact_integrity / sbom_attestation",
    acceptance: "production_evidence_acceptance",
    owner: "release evidence",
    evidence: "artifact digest, detached signature, and SBOM evidence are missing",
    next: "attach artifact digest, signature verification, and SBOM attestation",
    boundary: "production_evidence_claim=0",
  },
  {
    key: "lifecycle_trace",
    label: "Lifecycle transcript trace",
    status: "blocked",
    blockers: "production_preflight_guard, install_transcript, uninstall_transcript",
    intake: "lifecycle_transcript_packet",
    gate: "lifecycle_transcripts",
    acceptance: "production_evidence_acceptance",
    owner: "installer QA",
    evidence: "preflight, install, uninstall, and reset transcripts are missing",
    next: "capture lifecycle transcripts outside the UI prototype",
    boundary: "host_write_authority=0",
  },
  {
    key: "recovery_trace",
    label: "Recovery matrix trace",
    status: "blocked",
    blockers: "upgrade_path, rollback_path, multi_vm_validation",
    intake: "recovery_validation_packet",
    gate: "upgrade_rollback_recovery / multi_vm_validation",
    acceptance: "release_authority_acceptance",
    owner: "recovery QA",
    evidence: "upgrade, rollback, failed-run recovery, and multi-VM validation are missing",
    next: "complete recovery validation before release promotion",
    boundary: "production_installer_claim=0",
  },
];

const evidenceMatrix = [
  {
    key: "local_ui_lane",
    label: "Local UI lane",
    status: "verified",
    evidence: "receipt preview, handoff manifest, static checks, and browser QA",
    boundary: "isolated prototype only",
  },
  {
    key: "saved_receipt_replay",
    label: "Saved receipt replay",
    status: "verified",
    evidence: "snapshot replay, digest refresh, and missing snapshot guard",
    boundary: "local storage state only",
  },
  {
    key: "export_integrity",
    label: "Export integrity",
    status: "verified",
    evidence: "local digest, validation ledger, and non-production watermark",
    boundary: "download preview only",
  },
  {
    key: "main_panel_migration",
    label: "Guarded Rust Panel migration",
    status: "pending",
    evidence: "requires side-by-side review before any egui port",
    boundary: "main GUI unchanged",
  },
  {
    key: "installer_engine_binding",
    label: "Installer engine binding",
    status: "pending",
    evidence: "requires real installer execution state instead of simulated lane state",
    boundary: "runtime authority remains zero",
  },
  {
    key: "production_release_evidence",
    label: "Production release evidence",
    status: "blocked",
    evidence: "artifact, signature, SBOM, transcript, rollback, and VM records missing",
    boundary: "production claim closed",
  },
];

const promotionGateItems = [
  {
    key: "local_ui_evidence",
    label: "Local UI evidence",
    status: "verified",
    required: "receipt preview, evidence matrix, QA handoff, and browser checks",
    evidence: "test-lane proof exists but remains non-production evidence",
    owner: "UI QA",
    next: "keep local proof attached to the no-effect receipt",
  },
  {
    key: "main_panel_migration_review",
    label: "Guarded Rust Panel migration review",
    status: "pending",
    required: "side-by-side egui review before any implementation migration",
    evidence: "prototype surface has not been ported to the guarded Panel",
    owner: "Panel migration",
    next: "compare selected test-lane surfaces against the guarded Rust Panel",
  },
  {
    key: "installer_engine_binding",
    label: "Installer engine binding",
    status: "pending",
    required: "replace simulated state with installer execution state",
    evidence: "runtime authority remains zero in this lane",
    owner: "installer engine",
    next: "map real execution events to receipt fields before release claims",
  },
  {
    key: "artifact_integrity",
    label: "Artifact integrity",
    status: "blocked",
    required: "reproducible artifact, digest, and release signature",
    evidence: "installer_artifact_reproducible=0; installer_artifact_signature_recorded=0",
    owner: "release evidence",
    next: "record reproducible artifact digest and signing evidence",
  },
  {
    key: "sbom_attestation",
    label: "SBOM attestation",
    status: "blocked",
    required: "release SBOM and dependency evidence",
    evidence: "installer_sbom_recorded=0",
    owner: "supply chain",
    next: "attach release SBOM and dependency attestation",
  },
  {
    key: "lifecycle_transcripts",
    label: "Lifecycle transcripts",
    status: "blocked",
    required: "production preflight, install, and uninstall transcripts",
    evidence: "preflight, install, and uninstall records are missing",
    owner: "installer QA",
    next: "capture preflight, install, and uninstall transcripts",
  },
  {
    key: "upgrade_rollback_recovery",
    label: "Upgrade and rollback recovery",
    status: "blocked",
    required: "validated upgrade path and rollback path",
    evidence: "installer_upgrade_path_validated=0; installer_rollback_path_validated=0",
    owner: "recovery QA",
    next: "run upgrade and rollback validation scenarios",
  },
  {
    key: "multi_vm_validation",
    label: "Multi-VM validation",
    status: "blocked",
    required: "repeatable validation across supported VM targets",
    evidence: "installer_multi_vm_validation_completed=0",
    owner: "platform QA",
    next: "complete supported VM validation matrix",
  },
];

const receiptDiffFields = [
  {
    key: "mode",
    label: "mode",
    read: (receipt) => receipt.mode || "unknown",
  },
  {
    key: "prefix",
    label: "prefix",
    read: (receipt) => receipt.prefix || "unknown",
  },
  {
    key: "prefix_guard",
    label: "prefix guard",
    read: (receipt) => receipt.prefix_guard || "unknown",
  },
  {
    key: "profile",
    label: "profile",
    read: (receipt) => receipt.profile || "unknown",
  },
  {
    key: "component_count",
    label: "components",
    read: (receipt) => String(receipt.component_count || 0),
  },
  {
    key: "selected_components",
    label: "component ids",
    read: (receipt) => (Array.isArray(receipt.selected_components) && receipt.selected_components.length > 0 ? receipt.selected_components.join(",") : "none"),
  },
  {
    key: "checklist_recorded",
    label: "checklist recorded",
    read: (receipt) => String(receipt.receipt_checklist?.summary?.recorded || 0),
  },
  {
    key: "checklist_pending",
    label: "checklist pending",
    read: (receipt) => String((receipt.receipt_checklist?.summary?.pending || 0) + (receipt.receipt_checklist?.summary?.blocked || 0)),
  },
  {
    key: "schema_blocked",
    label: "blocked fields",
    read: (receipt) => String(receipt.schema_provenance?.blocked || 0),
  },
  {
    key: "console_status",
    label: "console status",
    read: (receipt) => receipt.console?.status || "unknown",
  },
  {
    key: "event_count",
    label: "event count",
    read: (receipt) => String(receipt.event_count || 0),
  },
  {
    key: "review_filter",
    label: "review filter",
    read: (receipt) => receipt.review_filter || "all",
  },
  {
    key: "blocker_filter",
    label: "blocker filter",
    read: (receipt) => receipt.production_blocker_drilldown?.summary?.filter || "none",
  },
  {
    key: "blocker_visible",
    label: "blocker visible",
    read: (receipt) => {
      const summary = receipt.production_blocker_drilldown?.summary;
      return summary ? `${summary.visible}/${summary.total}` : "0/0";
    },
  },
];

const receiptContextDriftFields = [
  {
    key: "readiness_compare",
    label: "readiness comparison",
    read: (context) => context.readiness_compare,
  },
  {
    key: "comparison_alignment",
    label: "comparison alignment",
    read: (context) => context.comparison_alignment,
  },
  {
    key: "readiness_trace",
    label: "readiness trace",
    read: (context) => context.readiness_trace,
  },
  {
    key: "trace_alignment",
    label: "trace alignment",
    read: (context) => context.trace_alignment,
  },
  {
    key: "evidence_intake",
    label: "evidence intake",
    read: (context) => context.evidence_intake,
  },
  {
    key: "promotion_gate",
    label: "promotion gate",
    read: (context) => context.promotion_gate,
  },
  {
    key: "release_acceptance",
    label: "release acceptance",
    read: (context) => context.release_acceptance,
  },
  {
    key: "production_blocker",
    label: "production blocker",
    read: (context) => context.production_blocker,
  },
  {
    key: "handoff_scope_source",
    label: "handoff scope source",
    read: (context) => context.handoff_scope_source,
  },
  {
    key: "local_authority_boundary",
    label: "local authority boundary",
    read: (context) => context.local_authority_boundary,
  },
];

function qs(selector, root = document) {
  return root.querySelector(selector);
}

function qsa(selector, root = document) {
  return Array.from(root.querySelectorAll(selector));
}

function selectedComponents() {
  return components.filter((component) => component.selected);
}

function componentSummaryText() {
  return `${selectedComponents().length} of ${components.length} selected`;
}

function componentHealthRows() {
  return components.map((component, index) => {
    const core = coreComponentIds.has(component.id);
    const status = component.selected ? (core ? "core_selected" : "optional_selected") : core ? "core_missing" : "omitted";
    return {
      id: component.id,
      label: component.name,
      note: component.note,
      order: index + 1,
      core,
      selected: component.selected,
      status,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    };
  });
}

function componentHealthSummary(rows = componentHealthRows()) {
  const selected = rows.filter((row) => row.selected).length;
  const omitted = rows.length - selected;
  const core = rows.filter((row) => row.core).length;
  const coreSelected = rows.filter((row) => row.core && row.selected).length;
  const optionalSelected = rows.filter((row) => !row.core && row.selected).length;
  const coreMissing = core - coreSelected;
  return {
    state: coreMissing > 0 ? "blocked" : "ready",
    selected,
    omitted,
    total: rows.length,
    core,
    core_selected: coreSelected,
    core_missing: coreMissing,
    optional_selected: optionalSelected,
    coverage_label: `${coreSelected}/${core}`,
    badge: coreMissing > 0 ? "core missing" : "core ready",
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function deliveryPlanRows() {
  const selected = selectedComponents();
  const mode = state.mode === "dry" ? "dry-run" : "guarded-local";
  const prefix = state.prefix || "~/.local";
  const prefixGuard = state.prefixValid ? "accepted" : "blocked";
  const componentIds = selected.map((component) => component.id).join(",") || "none";
  return [
    {
      key: "profile",
      label: "profile",
      value: state.profile,
      status: "ready",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "mode",
      label: "mode",
      value: mode,
      status: state.mode === "local" ? "guarded" : "ready",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "prefix_guard",
      label: "prefix_guard",
      value: prefixGuard,
      status: state.prefixValid ? "ready" : "blocked",
      prefix,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "components",
      label: "components",
      value: componentIds,
      status: selected.length > 0 ? "ready" : "blocked",
      count: selected.length,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "authority_boundary",
      label: "authority_boundary",
      value: "root=0 network=0 runtime=0 production=0 main=0 edge=0",
      status: "guarded",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
  ];
}

function deliveryPlanSummary(rows = deliveryPlanRows()) {
  const componentRow = rows.find((row) => row.key === "components");
  const prefixRow = rows.find((row) => row.key === "prefix_guard");
  const modeRow = rows.find((row) => row.key === "mode");
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const guarded = rows.filter((row) => row.status === "guarded").length;
  return {
    state: blocked > 0 ? "blocked" : "ready",
    badge: blocked > 0 ? "blocked" : "current",
    mode: modeRow?.value || "dry-run",
    prefix: prefixRow?.prefix || state.prefix || "~/.local",
    prefix_guard: prefixRow?.value || "blocked",
    components: componentRow?.count || 0,
    guarded,
    blocked,
    boundary: "production=0 / runtime=0 / main=0 / edge=0",
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function deliveryPlanPreviewText(rows = deliveryPlanRows()) {
  return rows
    .map((row) => {
      if (row.key === "prefix_guard") {
        return `prefix=${row.prefix}\nprefix_guard=${row.value}`;
      }
      return `${row.label}=${row.value}`;
    })
    .join("\n");
}

function evidenceQueueRows(filter = state.evidenceFilter) {
  const normalized = (filter || "").trim().toLowerCase();
  return evidence.map(([key, value, group], index) => {
    const status = group === "plan" || group === "lane" ? "ready" : "guarded";
    const haystack = `${key} ${value} ${group}`.toLowerCase();
    return {
      key,
      value,
      group,
      status,
      visible: normalized.length === 0 || haystack.includes(normalized),
      order: index + 1,
      filter: normalized || "none",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    };
  });
}

function evidenceQueueSummary(rows = evidenceQueueRows()) {
  const visibleRows = rows.filter((row) => row.visible);
  const guarded = visibleRows.filter((row) => row.status === "guarded").length;
  const ready = visibleRows.filter((row) => row.status === "ready").length;
  const filter = rows[0]?.filter || "none";
  return {
    state: visibleRows.length > 0 ? "ready" : "empty",
    total: rows.length,
    visible: visibleRows.length,
    ready,
    guarded,
    filter,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function eventTrailRows() {
  return state.events
    .map((event, index) => ({
      key: `event_${index + 1}`,
      label: event.label,
      detail: event.detail,
      timestamp: event.timestamp,
      status: event.level === "blocked" ? "blocked" : "ready",
      order: index + 1,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    }))
    .reverse();
}

function eventTrailSummary(rows = eventTrailRows()) {
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const ready = rows.filter((row) => row.status === "ready").length;
  const latest = rows[0]?.label || "none";
  return {
    state: rows.length === 0 ? "empty" : blocked > 0 ? "review" : "ready",
    total: rows.length,
    ready,
    blocked,
    latest,
    retained_limit: 24,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function receiptPreviewRows() {
  const checklist = receiptChecklistSummary();
  const checklistStatus = checklist.blocked > 0 ? "blocked" : checklist.pending > 0 ? "review" : "ready";
  const boundary = {
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
  return [
    {
      key: "schema",
      label: "schema",
      value: "latticra-panel-test-ui-receipt-v0",
      status: "ready",
      local_only: true,
      ...boundary,
    },
    {
      key: "event_count",
      label: "events",
      value: String(state.events.length),
      status: "ready",
      local_only: true,
      ...boundary,
    },
    {
      key: "checklist",
      label: "checklist",
      value: `${checklist.recorded}/${checklist.total}`,
      status: checklistStatus,
      pending: checklist.pending,
      blocked: checklist.blocked,
      local_only: true,
      ...boundary,
    },
    {
      key: "scope",
      label: "scope",
      value: "local-only",
      status: "ready",
      local_only: true,
      ...boundary,
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      value: "production=0 / host=0 / runtime=0 / main=0 / edge=0",
      status: "guarded",
      local_only: true,
      ...boundary,
    },
  ];
}

function receiptPreviewSummary(rows = receiptPreviewRows()) {
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const review = rows.filter((row) => row.status === "review" || row.status === "guarded").length;
  const checklist = rows.find((row) => row.key === "checklist");
  const schema = rows.find((row) => row.key === "schema");
  const events = rows.find((row) => row.key === "event_count");
  const scope = rows.find((row) => row.key === "scope");
  return {
    state: blocked > 0 || review > 0 ? "review" : "ready",
    schema: schema?.value || "receipt-v0",
    event_count: Number(events?.value || 0),
    checklist: checklist?.value || "0/0",
    checklist_pending: checklist?.pending || 0,
    checklist_blocked: checklist?.blocked || 0,
    scope: scope?.value || "local-only",
    row_count: rows.length,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function updaterGateRows() {
  const previewRecorded = state.events.some((event) => event.label === "Updater preview");
  return [
    {
      key: "manifest",
      label: "Manifest",
      detail: "signed manifest missing",
      status: "blocked",
      required: true,
    },
    {
      key: "artifact_hash",
      label: "Artifact hash",
      detail: "release hash missing",
      status: "blocked",
      required: true,
    },
    {
      key: "rollback_plan",
      label: "Rollback plan",
      detail: "rollback receipt missing",
      status: "blocked",
      required: true,
    },
    {
      key: "operator_confirmation",
      label: "Operator confirmation",
      detail: "production apply not confirmed",
      status: "blocked",
      required: true,
    },
    {
      key: "preview_simulation",
      label: "Preview simulation",
      detail: previewRecorded ? "local preview event recorded" : "local preview available",
      status: previewRecorded ? "ready" : "available",
      required: false,
    },
  ].map((row, index) => ({
    ...row,
    order: index + 1,
    can_apply: false,
    local_only: true,
    production_evidence_claim: 0,
    network_fetch_authority: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function updaterGateSummary(rows = updaterGateRows()) {
  const requiredRows = rows.filter((row) => row.required);
  const blocked = requiredRows.filter((row) => row.status === "blocked").length;
  const ready = rows.filter((row) => row.status === "ready").length;
  const preview = rows.find((row) => row.key === "preview_simulation");
  return {
    state: blocked > 0 ? "closed" : "ready",
    badge: blocked > 0 ? "gate closed" : "ready",
    title: blocked > 0 ? "Signed delivery gate closed" : "Signed delivery ready",
    blocked,
    ready,
    required: requiredRows.length,
    preview_status: preview?.status || "available",
    can_apply: false,
    boundary: "apply=false / production=0 / network=0 / main=0 / edge=0",
    local_only: true,
    production_evidence_claim: 0,
    network_fetch_authority: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.network_fetch_authority === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0 &&
        row.can_apply === false,
    ),
  };
}

function evidenceDetailState(level = state.evidenceDetail) {
  const normalized = Math.max(1, Math.min(3, Math.round(Number(level) || 2)));
  const labels = {
    1: { key: "compact", label: "Compact", detail: "summary-first" },
    2: { key: "balanced", label: "Balanced", detail: "review-balanced" },
    3: { key: "full", label: "Full", detail: "expanded evidence" },
  };
  return {
    level: normalized,
    ...labels[normalized],
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function evidenceDetailSummary(detail = evidenceDetailState()) {
  return {
    level: detail.level,
    key: detail.key,
    label: detail.label,
    detail: detail.detail,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function profileScopeState(profile = state.profile) {
  const profiles = {
    "Guided local panel": {
      key: "guided_local",
      label: "Guided local",
      scope: "default local install flow",
      intent: "plan-first local panel review",
    },
    "Seal report-only": {
      key: "seal_report",
      label: "Seal report",
      scope: "receipt and seal review only",
      intent: "report-only evidence review",
    },
    "LC standalone": {
      key: "lc_standalone",
      label: "LC standalone",
      scope: "standalone lattice core path",
      intent: "component-specific standalone review",
    },
    "Fedora validation": {
      key: "fedora_validation",
      label: "Fedora validation",
      scope: "Fedora packaging checks",
      intent: "distribution validation review",
    },
  };
  const selected = profiles[profile] || profiles["Guided local panel"];
  return {
    profile,
    ...selected,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function profileScopeSummary(scope = profileScopeState()) {
  return {
    profile: scope.profile,
    key: scope.key,
    label: scope.label,
    scope: scope.scope,
    intent: scope.intent,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function primaryActionRailRows() {
  return qsa(".topbar-actions [data-action]").map((button, index) => ({
    key: button.dataset.action || `action-${index + 1}`,
    label: button.getAttribute("aria-label") || button.textContent.trim(),
    intent: button.dataset.actionIntent || "local",
    priority: Number(button.dataset.actionPriority || index + 1),
    enabled: !button.disabled && button.getAttribute("aria-disabled") !== "true",
    has_icon: Boolean(button.querySelector(".action-icon")),
    described_by: button.getAttribute("aria-describedby") || "none",
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function primaryActionRailSummary(rows = primaryActionRailRows()) {
  return {
    action_count: rows.length,
    enabled_count: rows.filter((row) => row.enabled).length,
    iconized_count: rows.filter((row) => row.has_icon).length,
    primary_action: rows.find((row) => row.priority === 1)?.key || "none",
    all_actions_iconized: rows.length > 0 && rows.every((row) => row.has_icon),
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function setPrimaryActionLabel(action, label) {
  const button = qs(`[data-action="${action}"]`);
  if (!(button instanceof HTMLButtonElement)) {
    return;
  }
  const labelNode = qs(".action-label", button);
  if (labelNode) {
    labelNode.textContent = label;
  } else {
    button.textContent = label;
  }
  button.setAttribute("aria-label", label);
  button.title = label;
}

function workspacePostureRows() {
  const local = state.mode === "local";
  const planText = qs("#plan-state")?.textContent || "plan ready for review";
  const prefixText = qs("#prefix-state")?.textContent || "writes require guarded mode";
  return [
    {
      key: "plan_flow",
      label: "Plan-first flow",
      state: planText.includes("regenerated") ? "ready" : "ready",
      badge: planText.includes("regenerated") ? "refreshed" : "ready",
      detail: planText,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "prefix_guard",
      label: "User-local prefix",
      state: state.prefixValid ? (local ? "armed" : "guarded") : "blocked",
      badge: state.prefixValid ? (local ? "armed" : "guarded") : "blocked",
      detail: prefixText,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: local && state.prefixValid ? "user-local-only" : 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "root_authority",
      label: "Root authority",
      state: "denied",
      badge: "denied",
      detail: "denied",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "production_claim",
      label: "Production claim",
      state: "blocked",
      badge: "blocked",
      detail: "not released",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
  ];
}

function workspacePostureSummary(rows = workspacePostureRows()) {
  const blockedStates = ["blocked", "denied"];
  return {
    total: rows.length,
    ready: rows.filter((row) => row.state === "ready" || row.state === "armed").length,
    guarded: rows.filter((row) => row.state === "guarded").length,
    blocked: rows.filter((row) => blockedStates.includes(row.state)).length,
    layout_guard: "responsive-min-width",
    wrap_guard: "normal-word-wrap",
    layout_stable: true,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function dashboardAuthorityTone(status) {
  if (status === "allowed" || status === "armed") {
    return "ok";
  }
  if (status === "blocked") {
    return "stop";
  }
  return "warn";
}

function dashboardAuthorityRows() {
  const local = state.mode === "local";
  const writeState = !state.prefixValid ? "blocked" : local ? "armed" : "guarded";
  const writeDetail = !state.prefixValid
    ? "blocked by prefix guard"
    : local
      ? "armed for accepted user-local prefix"
      : "requires guarded mode";
  const hostWriteScope = local && state.prefixValid ? "user-local-only" : 0;
  return [
    {
      key: "dry_run_plan",
      label: "Dry-run plan",
      status: "allowed",
      detail: "no-effect plan and receipt preview only",
      host_write_scope: 0,
    },
    {
      key: "user_local_writes",
      label: "User-local writes",
      status: writeState,
      detail: writeDetail,
      host_write_scope: hostWriteScope,
    },
    {
      key: "system_mutation",
      label: "System mutation",
      status: "blocked",
      detail: "root and system prefixes denied",
      host_write_scope: 0,
    },
    {
      key: "network_fetch",
      label: "Network fetch",
      status: "blocked",
      detail: "network authority held at zero",
      host_write_scope: 0,
    },
  ].map((row) => ({
    ...row,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: row.host_write_scope,
    root_authority: 0,
    network_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function dashboardAuthoritySummary(rows = dashboardAuthorityRows()) {
  const localWrite = rows.find((row) => row.key === "user_local_writes");
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const guarded = rows.filter((row) => row.status === "guarded").length;
  const armed = rows.filter((row) => row.status === "armed").length;
  const allowed = rows.filter((row) => row.status === "allowed").length;
  const hostWriteScope = localWrite?.host_write_scope || 0;
  return {
    total: rows.length,
    allowed,
    guarded,
    armed,
    blocked,
    local_scope: guarded + armed,
    user_local_state: localWrite?.status || "blocked",
    host_write_scope: hostWriteScope,
    decision: armed > 0 && blocked === 2 ? "user_local_armed" : "locked",
    badge: armed > 0 && blocked === 2 ? "local armed" : "production locked",
    production_authority_zero: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.root_authority === 0 &&
        row.network_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    root_authority: 0,
    network_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function runMonitorTone(status) {
  if (status === "blocked") {
    return "stop";
  }
  if (status === "running") {
    return "info";
  }
  return "ok";
}

function runMonitorState() {
  const badgeText = (qs("#run-badge")?.textContent || "ready").trim().toLowerCase();
  const status = ["ready", "running", "complete", "blocked"].includes(badgeText) ? badgeText : "ready";
  const logLines = qsa("#recent-log p").map((line) => line.textContent.trim()).filter(Boolean);
  return {
    status,
    title: qs("#run-monitor-title")?.textContent.trim() || "Idle, plan current",
    progress: state.progress,
    progress_label: qs("#progress-label")?.textContent.trim() || "Evidence completeness",
    prefix_guard: state.prefixValid ? "accepted" : "blocked",
    mode: state.mode === "local" ? "guarded-local" : "dry-run",
    last_log: logLines[logLines.length - 1] || "none",
    runtime_authority: 0,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    local_only: true,
  };
}

function runMonitorRows(summary = runMonitorState()) {
  return [
    {
      key: "status",
      label: "Status",
      value: summary.status,
      status: summary.status,
    },
    {
      key: "progress",
      label: "Progress",
      value: `${summary.progress}%`,
      status: summary.progress >= 80 ? "complete" : "running",
    },
    {
      key: "mode",
      label: "Mode",
      value: summary.mode,
      status: summary.mode,
    },
    {
      key: "prefix_guard",
      label: "Prefix guard",
      value: summary.prefix_guard,
      status: summary.prefix_guard,
    },
    {
      key: "last_log",
      label: "Last log",
      value: summary.last_log,
      status: summary.status,
    },
    {
      key: "runtime_boundary",
      label: "Runtime boundary",
      value: "runtime=0 production=0 main=0 edge=0",
      status: "blocked",
    },
  ].map((row) => ({
    ...row,
    local_only: true,
    production_evidence_claim: 0,
    runtime_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function runMonitorSummary(rows = runMonitorRows()) {
  const current = runMonitorState();
  return {
    status: current.status,
    title: current.title,
    progress: current.progress,
    progress_label: current.progress_label,
    prefix_guard: current.prefix_guard,
    mode: current.mode,
    last_log: current.last_log,
    row_count: rows.length,
    local_only: rows.every((row) => row.local_only === true),
    runtime_authority: 0,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function operatorWorkflowTone(status) {
  if (status === "complete" || status === "available") {
    return "ok";
  }
  if (status === "blocked") {
    return "stop";
  }
  return "warn";
}

function operatorWorkflowRows() {
  const profile = profileScopeState();
  const run = runMonitorSummary();
  const selectedCount = selectedComponents().length;
  const planReady = state.prefixValid && selectedCount > 0;
  const runComplete = run.status === "complete";
  const runCurrent = run.status === "running";
  const runBlocked = run.status === "blocked";
  const localReady = state.mode === "local" && state.prefixValid;
  return [
    {
      key: "profile",
      label: "Profile selected",
      status: profile.profile ? "complete" : "current",
      detail: `${profile.label} / ${selectedCount} components selected`,
    },
    {
      key: "plan_review",
      label: "Plan review",
      status: !state.prefixValid ? "blocked" : state.progress >= 78 ? "complete" : "current",
      detail: planReady
        ? "component manifest, prefix, and authority fields checked"
        : "prefix or component selection needs review",
    },
    {
      key: "dry_install",
      label: "Dry-install run",
      status: runBlocked ? "blocked" : runComplete ? "complete" : runCurrent ? "current" : "pending",
      detail: runComplete
        ? "receipt queued in local evidence"
        : runCurrent
          ? "local no-effect simulation running"
          : "receipt and engine log stay in evidence",
    },
    {
      key: "guarded_local",
      label: "Guarded local install",
      status: localReady ? "available" : "blocked",
      detail: localReady ? "guarded user-local simulation available" : "locked until explicit local mode is active",
    },
  ].map((row, index) => ({
    ...row,
    order: index + 1,
    local_only: true,
    production_evidence_claim: 0,
    runtime_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function operatorWorkflowSummary(rows = operatorWorkflowRows()) {
  const complete = rows.filter((row) => row.status === "complete").length;
  const current = rows.filter((row) => row.status === "current").length;
  const available = rows.filter((row) => row.status === "available").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const next = rows.find((row) => row.status === "current") || rows.find((row) => row.status === "pending") || rows[rows.length - 1];
  return {
    total: rows.length,
    complete,
    current,
    available,
    blocked,
    next_step: next?.key || "none",
    next_label: next?.label || "none",
    state: blocked > 1 ? "blocked" : available > 0 ? "guarded_local_ready" : complete >= 3 ? "ready_for_receipt" : "plan_review",
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    runtime_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function workspaceRouteRows() {
  const tabLabel = tabs.find(([id]) => id === state.activeTab)?.[1] || "Dashboard";
  const detail = evidenceDetailState();
  const profile = profileScopeState();
  return [
    {
      key: "tab",
      label: "tab",
      value: state.activeTab,
      display: `tab ${tabLabel.toLowerCase()}`,
    },
    {
      key: "profile",
      label: "profile",
      value: state.profile,
      display: `profile ${profile.label.toLowerCase()}`,
    },
    {
      key: "detail",
      label: "detail",
      value: detail.level,
      display: `detail ${detail.level} ${detail.label.toLowerCase()}`,
    },
    {
      key: "boundary",
      label: "boundary",
      value: "local-only",
      display: "local only",
    },
  ].map((row) => ({
    ...row,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function workspaceRouteSummary(rows = workspaceRouteRows()) {
  const byKey = Object.fromEntries(rows.map((row) => [row.key, row]));
  const detail = evidenceDetailState(byKey.detail?.value || state.evidenceDetail);
  const profile = profileScopeState(byKey.profile?.value || state.profile);
  return {
    active_tab: byKey.tab?.value || state.activeTab,
    active_tab_label: tabs.find(([id]) => id === state.activeTab)?.[1] || "Dashboard",
    profile: profile.profile,
    profile_scope: profile.scope,
    profile_key: profile.key,
    evidence_detail: detail.level,
    evidence_detail_label: detail.label,
    chip_count: rows.length,
    boundary: byKey.boundary?.value || "local-only",
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function readinessRailState(progress = state.progress) {
  const score = Math.max(0, Math.min(100, Math.round(Number(progress) || 0)));
  const local = state.mode === "local";
  let band = "needs_review";
  let label = "needs local review";
  if (score >= 85) {
    band = "local_high";
    label = "local proof high";
  } else if (score >= 72) {
    band = "local_review";
    label = "local proof review";
  }
  return {
    score,
    band,
    label,
    mode: local ? "guarded-local" : "dry-run",
    writes: local ? "armed" : "blocked",
    gate: "closed",
    can_promote: false,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function readinessRailRows(summary = readinessRailState()) {
  return [
    {
      key: "score",
      label: "Score",
      value: `${summary.score}%`,
      status: summary.band,
    },
    {
      key: "band",
      label: "Band",
      value: summary.label,
      status: summary.band,
    },
    {
      key: "mode",
      label: "Mode",
      value: summary.mode,
      status: summary.mode,
    },
    {
      key: "writes",
      label: "Writes",
      value: summary.writes,
      status: summary.writes,
    },
    {
      key: "gate",
      label: "Gate",
      value: summary.gate,
      status: "blocked",
    },
  ].map((row) => ({
    ...row,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function readinessRailSummary(rows = readinessRailRows()) {
  const byKey = Object.fromEntries(rows.map((row) => [row.key, row]));
  const score = Math.max(0, Math.min(100, Number.parseInt(byKey.score?.value || state.progress, 10) || 0));
  const summary = readinessRailState(score);
  return {
    score: summary.score,
    band: summary.band,
    label: summary.label,
    mode: byKey.mode?.value || summary.mode,
    writes: byKey.writes?.value || summary.writes,
    gate: byKey.gate?.value || summary.gate,
    can_promote: false,
    row_count: rows.length,
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function qualityGateTone(status) {
  if (status === "verified") {
    return "ok";
  }
  if (status === "blocked") {
    return "stop";
  }
  return "warn";
}

function qualityGateRows() {
  return qualityGates.map((gate, index) => ({
    key: gate.key,
    label: gate.label,
    status: gate.status,
    evidence: gate.evidence,
    next: gate.next,
    order: index + 1,
    can_promote: false,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function qualityGateSummary(rows = qualityGateRows()) {
  const verified = rows.filter((row) => row.status === "verified").length;
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const decision = pending === 0 && blocked === 0 && rows.length > 0 ? "ready" : "blocked";
  return {
    total: rows.length,
    verified,
    pending,
    blocked,
    decision,
    badge: decision === "ready" ? "ready" : "not ready",
    can_promote: false,
    local_only: rows.every((row) => row.local_only === true),
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function brandMetadataState() {
  const head = document.head;
  const preload = qs('link[rel="preload"][as="image"][href="assets/latticra-emblem.png"]', head);
  const icon = qs('link[rel="icon"][href="assets/latticra-emblem.png"]', head);
  const touchIcon = qs('link[rel="apple-touch-icon"][href="assets/latticra-emblem.png"]', head);
  const applicationName = qs('meta[name="application-name"]', head)?.getAttribute("content") || "";
  const themeColor = qs('meta[name="theme-color"]', head)?.getAttribute("content") || "";
  const preloadLinked = preload instanceof HTMLLinkElement;
  const faviconLinked = icon instanceof HTMLLinkElement;
  const touchIconLinked = touchIcon instanceof HTMLLinkElement;
  return {
    application_name: applicationName,
    theme_color: themeColor,
    preload_link: preloadLinked,
    favicon_link: faviconLinked,
    touch_icon_link: touchIconLinked,
    metadata_ready:
      applicationName === "Latticra Panel" &&
      themeColor === "#f4f7fa" &&
      preloadLinked &&
      faviconLinked &&
      touchIconLinked,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function brandEmblemState() {
  const image = qs("#brand-emblem");
  const mark = qs(".brand-mark");
  const metadata = brandMetadataState();
  const loaded = image instanceof HTMLImageElement && image.complete && image.naturalWidth > 0;
  const fallbackVisible =
    mark instanceof HTMLElement &&
    (mark.classList.contains("is-missing") ||
      (image instanceof HTMLImageElement && image.complete && image.naturalWidth === 0));
  return {
    asset: "assets/latticra-emblem.png",
    status: fallbackVisible ? "fallback" : loaded ? "loaded" : "pending",
    loaded,
    fallback_visible: fallbackVisible,
    intrinsic_width: image instanceof HTMLImageElement ? image.naturalWidth || 0 : 0,
    intrinsic_height: image instanceof HTMLImageElement ? image.naturalHeight || 0 : 0,
    reserved_width: 42,
    reserved_height: 42,
    browser_metadata_ready: metadata.metadata_ready,
    metadata,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function wireBrandEmblem() {
  const image = qs("#brand-emblem");
  const mark = qs(".brand-mark");
  if (!(image instanceof HTMLImageElement) || !(mark instanceof HTMLElement)) {
    return;
  }
  const setLoaded = () => {
    mark.classList.remove("is-missing");
    renderReceiptPreview();
  };
  const setMissing = () => {
    mark.classList.add("is-missing");
    renderReceiptPreview();
  };
  image.addEventListener("load", setLoaded);
  image.addEventListener("error", setMissing);
  if (image.complete) {
    if (image.naturalWidth > 0) {
      setLoaded();
    } else {
      setMissing();
    }
  }
}

function visualIdentityState() {
  const image = qs("#visual-identity-asset");
  const brand = brandEmblemState();
  const loaded = image instanceof HTMLImageElement && image.complete && image.naturalWidth > 0;
  const missing = image instanceof HTMLImageElement && image.complete && image.naturalWidth === 0;
  const assetStatus = missing ? "missing" : loaded ? "loaded" : "pending";
  const brandStatus = brand.fallback_visible
    ? "fallback"
    : brand.loaded && brand.browser_metadata_ready
      ? "ready"
      : brand.loaded
        ? "loaded"
        : brand.status;
  const state = missing
    ? "missing"
    : brand.fallback_visible
      ? "fallback"
      : assetStatus === "loaded" && brandStatus === "ready"
        ? "ready"
        : "pending";
  return {
    state,
    asset: "../../assets/latticra-panel.png",
    asset_status: assetStatus,
    asset_loaded: loaded,
    asset_intrinsic_size:
      image instanceof HTMLImageElement && image.naturalWidth > 0 && image.naturalHeight > 0
        ? `${image.naturalWidth}x${image.naturalHeight}`
        : "pending",
    asset_reserved_size:
      image instanceof HTMLImageElement
        ? `${image.getAttribute("width") || "0"}x${image.getAttribute("height") || "0"}`
        : "0x0",
    brand_status: brandStatus,
    brand_asset: brand.asset,
    brand_metadata_ready: brand.browser_metadata_ready,
    boundary: "production=0 / main=0 / edge=0",
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: true,
  };
}

function visualIdentityRows(identity = visualIdentityState()) {
  return [
    {
      key: "shared_panel_asset",
      label: "Shared panel asset",
      status: identity.asset_status === "loaded" ? "ready" : identity.asset_status,
      value: identity.asset_intrinsic_size,
      note: identity.asset_status === "loaded" ? "loaded from shared docs asset" : "waiting for browser image decode",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "header_emblem",
      label: "Header emblem",
      status: identity.brand_status,
      value: identity.brand_asset,
      note: identity.brand_metadata_ready ? "browser metadata ready" : "browser metadata pending",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "authority_boundary",
      label: "Authority boundary",
      status: identity.zero_authority ? "ready" : "blocked",
      value: identity.boundary,
      note: "visual identity does not mutate main or edge GUI code",
      local_only: true,
      production_evidence_claim: identity.production_evidence_claim,
      host_write_authority: identity.host_write_authority,
      runtime_enforcement_authority: identity.runtime_enforcement_authority,
      main_gui_mutation_required: identity.main_gui_mutation_required,
      edge_gui_mutation_required: identity.edge_gui_mutation_required,
    },
  ];
}

function visualIdentitySummary(rows = visualIdentityRows()) {
  const asset = rows.find((row) => row.key === "shared_panel_asset");
  const brand = rows.find((row) => row.key === "header_emblem");
  const boundary = rows.find((row) => row.key === "authority_boundary");
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked" || row.status === "missing").length;
  const ready = rows.filter((row) => row.status === "ready").length;
  const state = blocked > 0 ? "missing" : brand?.status === "fallback" ? "fallback" : pending > 0 ? "pending" : "ready";
  return {
    state,
    title:
      state === "ready"
        ? "Workbench identity ready"
        : state === "fallback"
          ? "Emblem fallback active"
          : state === "missing"
            ? "Visual asset needs review"
            : "Visual identity loading",
    ready,
    pending,
    blocked,
    asset_status: asset?.status || "pending",
    asset_size: asset?.value || "pending",
    brand_status: brand?.status || "pending",
    boundary: boundary?.value || "production=0 / main=0 / edge=0",
    zero_authority: boundary?.status === "ready",
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function wireVisualIdentityAsset() {
  const image = qs("#visual-identity-asset");
  if (!(image instanceof HTMLImageElement)) {
    return;
  }
  const refresh = () => renderReceiptPreview();
  image.addEventListener("load", refresh);
  image.addEventListener("error", refresh);
  if (image.complete) {
    refresh();
  }
}

function defaultReceiptChecklistState() {
  return Object.fromEntries(receiptChecklistItems.map((item) => [item.id, item.defaultRecorded]));
}

function receiptChecklistRows() {
  return receiptChecklistItems.map((item) => {
    const available = item.available ? item.available() : true;
    const storedRecorded = Boolean(state.receiptChecklist[item.id]);
    const recorded = available && storedRecorded;
    const status = recorded ? "recorded" : available ? "pending" : "blocked";
    const note = recorded ? "recorded in no-effect receipt" : available ? "pending operator evidence" : item.blockedReason();
    return {
      id: item.id,
      label: item.label,
      source: item.source,
      available,
      recorded,
      status,
      note,
    };
  });
}

function receiptChecklistSummary(rows = receiptChecklistRows()) {
  return {
    total: rows.length,
    recorded: rows.filter((row) => row.status === "recorded").length,
    pending: rows.filter((row) => row.status === "pending").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
  };
}

function receiptSnapshotSummary(receipt) {
  const checklist = receipt.receipt_checklist?.summary || {};
  const schema = receipt.schema_provenance || {};
  return {
    mode: receipt.mode || "unknown",
    prefix: receipt.prefix || "unknown",
    prefix_guard: receipt.prefix_guard || "unknown",
    events: Number(receipt.event_count || 0),
    checklist_recorded: Number(checklist.recorded || 0),
    checklist_pending: Number(checklist.pending || 0) + Number(checklist.blocked || 0),
    schema_blocked: Number(schema.blocked || 0),
    components: Number(receipt.component_count || 0),
  };
}

function createReceiptSnapshot() {
  const receipt = buildReceiptPreview();
  const savedAt = nowStamp();
  return {
    id: `receipt-${Date.now()}`,
    label: `receipt ${savedAt.slice(11, 19)}`,
    saved_at: savedAt,
    receipt,
    summary: receiptSnapshotSummary(receipt),
  };
}

function normalizeSnapshotLabel(value, fallback = "receipt") {
  const label = String(value || "").replace(/\s+/g, " ").trim().slice(0, SNAPSHOT_LABEL_MAX_LENGTH);
  return label || fallback;
}

function selectedSavedReceiptIndex() {
  return state.savedReceipts.findIndex((snapshot) => snapshot.id === state.selectedReceiptId);
}

function selectedSavedReceipt() {
  const index = selectedSavedReceiptIndex();
  return index >= 0 ? state.savedReceipts[index] : null;
}

function updateSelectedReceiptLabel(value, record = false) {
  const snapshot = selectedSavedReceipt();
  if (!snapshot) {
    assistiveStatus("No saved receipt selected for relabeling.");
    return;
  }
  const previous = snapshot.label;
  snapshot.label = normalizeSnapshotLabel(value, previous);
  renderReceiptPreview();
  safeWriteState();
  assistiveStatus(`${snapshot.label} label updated for local receipt comparison.`);
  if (record && snapshot.label !== previous) {
    recordEvent("Receipt snapshot relabeled", `${snapshot.id}=${snapshot.label}`);
  }
}

function deleteSelectedSavedReceipt() {
  const index = selectedSavedReceiptIndex();
  if (index < 0) {
    notify("No saved receipt selected", "warning");
    assistiveStatus("No saved receipt selected for deletion.");
    return;
  }

  const [removed] = state.savedReceipts.splice(index, 1);
  const next = state.savedReceipts[index] || state.savedReceipts[index - 1] || null;
  state.selectedReceiptId = next ? next.id : "";
  renderReceiptPreview();
  safeWriteState();
  notify("Saved receipt deleted");
  assistiveStatus(`${removed.label} deleted from local test-lane snapshots. ${state.savedReceipts.length} saved receipts remain.`);
  recordEvent("Receipt snapshot deleted", `${removed.id} removed from local test-lane state`);
}

function signedDelta(value) {
  if (value > 0) {
    return `+${value}`;
  }
  return String(value);
}

function receiptDiffRows(snapshot, currentReceipt = buildReceiptPreview()) {
  if (!snapshot) {
    return [];
  }
  const savedReceipt = snapshot.receipt || {};
  return receiptDiffFields.map((field) => {
    const saved = field.read(savedReceipt);
    const current = field.read(currentReceipt);
    const changed = saved !== current;
    return {
      key: field.key,
      label: field.label,
      saved,
      current,
      status: changed ? "changed" : "same",
      changed,
    };
  });
}

function receiptDiffSummary(snapshot, currentReceipt = buildReceiptPreview()) {
  const rows = receiptDiffRows(snapshot, currentReceipt);
  const changedCount = rows.filter((row) => row.changed).length;
  const visibleRows = receiptDiffVisibleRows(rows);
  return {
    row_count: rows.length,
    changed_count: changedCount,
    active_filter: state.receiptDiffFilter,
    visible_count: visibleRows.length,
    status: snapshot ? (changedCount > 0 ? "changed" : "same") : "none",
    rows,
  };
}

function savedReceiptTrustRows(snapshot = selectedSavedReceipt(), currentReceipt = null, artifact = null) {
  const diff = artifact?.field_comparison || (snapshot && currentReceipt
    ? receiptDiffSummary(snapshot, currentReceipt)
    : { status: snapshot ? "pending" : "none", changed_count: 0, row_count: 0 });
  const exportState = artifact
    ? exportValidationSummary(artifact)
    : { status: snapshot ? "pending" : "none", passed: 0, total: 0 };
  const boundary = {
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
  return [
    {
      key: "saved_count",
      label: "saved",
      value: `${state.savedReceipts.length}/${SAVED_RECEIPT_LIMIT}`,
      status: state.savedReceipts.length > 0 ? "ready" : "review",
      local_only: true,
      ...boundary,
    },
    {
      key: "selected_snapshot",
      label: "selected",
      value: snapshot?.label || "none",
      status: snapshot ? "ready" : "review",
      local_only: true,
      ...boundary,
    },
    {
      key: "diff_state",
      label: "diff",
      value: snapshot && currentReceipt ? `${diff.status}:${diff.changed_count}/${diff.row_count}` : diff.status,
      status: snapshot && currentReceipt && diff.status === "same" ? "ready" : "review",
      local_only: true,
      ...boundary,
    },
    {
      key: "export_validation",
      label: "export",
      value: artifact ? `${exportState.status}:${exportState.passed}/${exportState.total}` : exportState.status,
      status: artifact && exportState.status === "passed" ? "ready" : "review",
      local_only: true,
      ...boundary,
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      value: "production=0 / host=0 / main=0 / edge=0",
      status: "ready",
      local_only: true,
      ...boundary,
    },
  ];
}

function savedReceiptTrustSummary(rows = savedReceiptTrustRows()) {
  const selected = rows.find((row) => row.key === "selected_snapshot");
  const count = rows.find((row) => row.key === "saved_count");
  const diff = rows.find((row) => row.key === "diff_state");
  const exportState = rows.find((row) => row.key === "export_validation");
  const review = rows.filter((row) => row.status === "review").length;
  return {
    state: selected?.value === "none" ? "empty" : review > 0 ? "review" : "ready",
    saved_count: count?.value || `0/${SAVED_RECEIPT_LIMIT}`,
    selected: selected?.value || "none",
    diff: diff?.value || "none",
    export_state: exportState?.value || "none",
    row_count: rows.length,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function alignmentStateFromSummary(summary = {}) {
  const total = Number(summary.total || 0);
  const review = Number(summary.review || 0);
  if (total <= 0) {
    return "none";
  }
  return review > 0 ? "review" : "aligned";
}

function alignmentTextFromSummary(summary = {}) {
  const stateText = alignmentStateFromSummary(summary);
  const aligned = Number(summary.aligned || 0);
  const total = Number(summary.total || 0);
  return `${stateText}:${aligned}/${total}`;
}

function selectedReceiptRowKey(section) {
  return section?.selected?.key || "none";
}

function receiptLocalAuthorityText(receipt = {}) {
  const authority = receipt.authority || {};
  const production = Number(authority.production_installer_claim ?? 0);
  const main = Number(authority.main_gui_mutation_required ?? 0);
  const edge = Number(authority.edge_gui_mutation_required ?? 0);
  const root = Number(authority.root_authority ?? 0);
  const network = Number(authority.network_authority ?? 0);
  const runtime = Number(authority.runtime_enforcement_authority ?? 0);
  const localOnly = production === 0 && main === 0 && edge === 0 && root === 0 && network === 0 && runtime === 0;
  return localOnly
    ? "local-only:production=0 main=0 edge=0"
    : `authority-review:production=${production} main=${main} edge=${edge}`;
}

function receiptHandoffScopeSourceText(context) {
  const hasReviewFocus =
    context.readiness_compare !== "none" &&
    context.readiness_trace !== "none" &&
    context.production_blocker !== "none";
  const hasAlignmentState =
    !context.comparison_alignment.startsWith("none:") && !context.trace_alignment.startsWith("none:");
  return hasReviewFocus && hasAlignmentState && context.local_authority_boundary.startsWith("local-only")
    ? "covered:compare+trace+blocker+local"
    : "review-context-incomplete";
}

function receiptReviewContext(receipt = {}) {
  const context = {
    readiness_compare: selectedReceiptRowKey(receipt.readiness_comparison),
    comparison_alignment: alignmentTextFromSummary(receipt.readiness_comparison?.alignment?.summary),
    readiness_trace: selectedReceiptRowKey(receipt.readiness_traceability),
    trace_alignment: alignmentTextFromSummary(receipt.readiness_traceability?.alignment?.summary),
    evidence_intake: selectedReceiptRowKey(receipt.release_evidence_intake),
    promotion_gate: selectedReceiptRowKey(receipt.promotion_gate),
    release_acceptance: selectedReceiptRowKey(receipt.release_acceptance),
    production_blocker: selectedReceiptRowKey(receipt.production_blocker_drilldown),
    local_authority_boundary: receiptLocalAuthorityText(receipt),
  };
  return {
    ...context,
    handoff_scope_source: receiptHandoffScopeSourceText(context),
  };
}

function receiptContextDriftRows(snapshot, currentReceipt = buildReceiptPreview()) {
  if (!snapshot) {
    return [];
  }
  const savedContext = receiptReviewContext(snapshot.receipt || {});
  const currentContext = receiptReviewContext(currentReceipt || {});
  return receiptContextDriftFields.map((field) => {
    const saved = field.read(savedContext) || "none";
    const current = field.read(currentContext) || "none";
    const changed = saved !== current;
    return {
      key: field.key,
      label: field.label,
      saved,
      current,
      status: changed ? "changed" : "same",
      changed,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    };
  });
}

function receiptContextDriftSummary(snapshot, currentReceipt = buildReceiptPreview()) {
  const rows = receiptContextDriftRows(snapshot, currentReceipt);
  const changedCount = rows.filter((row) => row.changed).length;
  const currentContext = receiptReviewContext(currentReceipt || {});
  return {
    row_count: rows.length,
    changed_count: changedCount,
    same_count: rows.length - changedCount,
    status: snapshot ? (changedCount > 0 ? "changed" : "same") : "none",
    selected_compare: currentContext.readiness_compare,
    selected_trace: currentContext.readiness_trace,
    selected_blocker: currentContext.production_blocker,
    handoff_scope_source: currentContext.handoff_scope_source,
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    rows,
  };
}

function receiptDiffVisibleRows(rows) {
  if (state.receiptDiffFilter === "all") {
    return rows;
  }
  return rows.filter((row) => row.status === state.receiptDiffFilter);
}

function compareSavedReceipt(snapshot, currentReceipt = null) {
  if (!snapshot) {
    return {
      label: "none",
      events: "0",
      checklist: "0",
      blocked: "0",
      mode: "same",
      prefix: "same",
    };
  }
  const current = receiptSnapshotSummary(currentReceipt || buildReceiptPreview());
  const saved = snapshot.summary || receiptSnapshotSummary(snapshot.receipt || {});
  return {
    label: snapshot.label,
    events: signedDelta(current.events - saved.events),
    checklist: signedDelta(current.checklist_recorded - saved.checklist_recorded),
    blocked: signedDelta(current.schema_blocked - saved.schema_blocked),
    mode: current.mode === saved.mode ? "same" : `${saved.mode} -> ${current.mode}`,
    prefix: current.prefix === saved.prefix ? "same" : `${saved.prefix} -> ${current.prefix}`,
  };
}

function receiptExportFilename(snapshot) {
  return `${snapshot.id}-local-preview.json`;
}

function stableStringify(value) {
  if (Array.isArray(value)) {
    return `[${value.map((item) => stableStringify(item)).join(",")}]`;
  }
  if (value && typeof value === "object") {
    return `{${Object.keys(value)
      .sort()
      .map((key) => `${JSON.stringify(key)}:${stableStringify(value[key])}`)
      .join(",")}}`;
  }
  return JSON.stringify(value);
}

function localDigest(value) {
  const text = stableStringify(value);
  let hash = 0x811c9dc5;
  for (let index = 0; index < text.length; index += 1) {
    hash ^= text.charCodeAt(index);
    hash = Math.imul(hash, 0x01000193);
  }
  return `fnv1a32-${(hash >>> 0).toString(16).padStart(8, "0")}`;
}

function exportIntegrityPayload(artifact) {
  return {
    artifact_schema: artifact.artifact_schema,
    boundary: artifact.boundary,
    snapshot_lifecycle: artifact.snapshot_lifecycle,
    selected_snapshot: artifact.selected_snapshot,
    current_comparison: artifact.current_comparison,
    field_comparison: artifact.field_comparison,
    context_drift: artifact.context_drift,
  };
}

function buildExportIntegrity(artifact) {
  return {
    algorithm: "fnv1a32-local-preview",
    digest_scope: "boundary+snapshot_lifecycle+selected_snapshot+current_comparison+field_comparison+context_drift",
    payload_digest: localDigest(exportIntegrityPayload(artifact)),
    local_only: true,
  };
}

function passFail(pass) {
  return pass ? "passed" : "blocked";
}

function exportValidationRows(artifact) {
  if (!artifact) {
    return [];
  }
  const boundary = artifact.boundary || {};
  const comparison = artifact.field_comparison || {};
  const contextDrift = artifact.context_drift || {};
  const integrity = artifact.integrity || {};
  return [
    {
      key: "artifact_schema",
      label: "local preview schema",
      status: passFail(artifact.artifact_schema === "latticra-panel-test-ui-local-export-v0"),
      detail: artifact.artifact_schema || "missing",
    },
    {
      key: "watermark",
      label: "not production watermark",
      status: passFail(boundary.watermark === "NOT PRODUCTION EVIDENCE"),
      detail: boundary.watermark || "missing",
    },
    {
      key: "production_evidence",
      label: "production evidence blocked",
      status: passFail(boundary.production_evidence === 0),
      detail: `production_evidence=${boundary.production_evidence ?? "missing"}`,
    },
    {
      key: "host_write_authority",
      label: "host write authority blocked",
      status: passFail(boundary.host_write_authority === 0),
      detail: `host_write_authority=${boundary.host_write_authority ?? "missing"}`,
    },
    {
      key: "gui_mutation_boundary",
      label: "main and edge GUI mutation blocked",
      status: passFail(boundary.main_gui_mutation_required === 0 && boundary.edge_gui_mutation_required === 0),
      detail: `main=${boundary.main_gui_mutation_required ?? "missing"} edge=${boundary.edge_gui_mutation_required ?? "missing"}`,
    },
    {
      key: "selected_snapshot",
      label: "selected snapshot embedded",
      status: passFail(Boolean(artifact.selected_snapshot?.id && artifact.selected_snapshot?.receipt)),
      detail: artifact.selected_snapshot?.id || "missing",
    },
    {
      key: "field_comparison",
      label: "field comparison complete",
      status: passFail(comparison.row_count === receiptDiffFields.length),
      detail: `${comparison.row_count || 0} fields`,
    },
    {
      key: "diff_filter",
      label: "diff filter recorded",
      status: passFail(comparison.active_filter === state.receiptDiffFilter),
      detail: `filter=${comparison.active_filter || "missing"}`,
    },
    {
      key: "context_drift",
      label: "review context drift embedded",
      status: passFail(
        contextDrift.row_count === receiptContextDriftFields.length &&
          ["same", "changed"].includes(contextDrift.status) &&
          contextDrift.production_evidence_claim === 0
      ),
      detail: `${contextDrift.changed_count || 0}/${contextDrift.row_count || 0} changed`,
    },
    {
      key: "integrity_digest",
      label: "local integrity digest",
      status: passFail(
        integrity.payload_digest === buildExportIntegrity(artifact).payload_digest &&
          integrity.algorithm === "fnv1a32-local-preview" &&
          integrity.local_only === true
      ),
      detail: integrity.payload_digest || "missing",
    },
  ];
}

function exportValidationSummary(artifact) {
  const rows = exportValidationRows(artifact);
  const passed = rows.filter((row) => row.status === "passed").length;
  return {
    total: rows.length,
    passed,
    blocked: rows.length - passed,
    status: rows.length > 0 && passed === rows.length ? "passed" : "blocked",
    rows,
  };
}

function buildQaHandoffUrl(snapshot = null, artifact = null) {
  const url = new URL(window.location.href);
  url.search = "";
  url.hash = "";
  const params = new URLSearchParams();
  params.set("tab", "evidence");
  params.set("mode", state.mode);
  params.set("prefix", state.prefix || "~/.local");
  params.set("review", state.reviewFilter);
  params.set("blocker", state.blockerFilter);
  params.set("diff", state.receiptDiffFilter);
  params.set("gate", state.promotionGateSelection);
  params.set("migration", state.migrationReviewSelection);
  params.set("scenario", state.qaScenarioSelection);
  params.set("engine", state.engineBindingSelection);
  params.set("visual", state.visualBaselineSelection);
  params.set("acceptance", state.releaseAcceptanceSelection);
  params.set("a11y", state.accessibilityAuditSelection);
  params.set("compare", state.readinessCompareSelection);
  params.set("intake", state.evidenceIntakeSelection);
  params.set("trace", state.traceabilitySelection);
  params.set("blockerItem", state.productionBlockerSelection);
  params.set("qa", "handoff");
  if (snapshot?.id) {
    params.set("snapshot", snapshot.id);
  }
  if (artifact?.integrity?.payload_digest) {
    params.set("digest", artifact.integrity.payload_digest);
  }
  url.search = params.toString();
  return url.toString();
}

function qaHandoffUrlParams(handoff) {
  try {
    return new URL(handoff.url).searchParams;
  } catch {
    return new URLSearchParams();
  }
}

function qaHandoffReplayRequest(snapshot = null, artifact = null) {
  const params = new URLSearchParams(window.location.search);
  const requestedSnapshotId = params.get("snapshot") || "none";
  const requestedDigest = params.get("digest") || "none";
  const requested = params.get("qa") === "handoff" && (params.has("snapshot") || params.has("digest"));
  const localSnapshotPresent =
    requestedSnapshotId !== "none" && state.savedReceipts.some((item) => item.id === requestedSnapshotId);
  const restoredSelectedSnapshot = Boolean(requested && snapshot?.id && snapshot.id === requestedSnapshotId);
  const currentDigest = artifact?.integrity?.payload_digest || "none";
  const digestStatus =
    requestedDigest === "none" ? "none" : requestedDigest === currentDigest ? "matched" : "refreshed";
  return {
    requested,
    requested_snapshot_id: requestedSnapshotId,
    requested_digest: requestedDigest,
    local_snapshot_present: localSnapshotPresent,
    local_snapshot_status: requested ? (localSnapshotPresent ? "present" : "missing") : "none",
    restored_selected_snapshot: restoredSelectedSnapshot,
    current_digest: currentDigest,
    digest_status: digestStatus,
    replay_is_local_only: true,
    replay_mutates_state: 0,
  };
}

function qaHandoffReviewContext() {
  const compareAlignment = readinessComparisonAlignmentSummary();
  const traceAlignment = traceabilityAlignmentSummary();
  return {
    readiness_compare: state.readinessCompareSelection,
    compare_alignment_state: compareAlignment.review > 0 ? "review" : "aligned",
    compare_alignment_action: compareAlignment.action_label,
    compare_alignment_aligned: compareAlignment.aligned,
    compare_alignment_review: compareAlignment.review,
    compare_alignment_total: compareAlignment.total,
    readiness_trace: state.traceabilitySelection,
    trace_alignment_state: traceAlignment.review > 0 ? "review" : "aligned",
    trace_alignment_action: traceAlignment.action_label,
    trace_alignment_aligned: traceAlignment.aligned,
    trace_alignment_review: traceAlignment.review,
    trace_alignment_total: traceAlignment.total,
    evidence_intake: state.evidenceIntakeSelection,
    promotion_gate: state.promotionGateSelection,
    release_acceptance: state.releaseAcceptanceSelection,
    production_blocker: state.productionBlockerSelection,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function qaHandoffScopeRows(handoff) {
  if (!handoff || !handoff.selected_snapshot) {
    return [];
  }
  const params = qaHandoffUrlParams(handoff);
  const filters = handoff.filters || {};
  const context = handoff.selected_review_context || {};
  const boundary = handoff.boundary || {};
  return [
    {
      key: "selected_comparison",
      label: "selected comparison",
      status: passFail(params.get("compare") === filters.compare && context.readiness_compare === filters.compare),
      detail: `compare=${filters.compare || "missing"} context=${context.readiness_compare || "missing"}`,
    },
    {
      key: "comparison_alignment",
      label: "comparison alignment state",
      status: passFail(context.compare_alignment_total > 0 && ["review", "aligned"].includes(context.compare_alignment_state)),
      detail: `${context.compare_alignment_state || "missing"}: ${context.compare_alignment_aligned ?? "missing"}/${context.compare_alignment_total ?? "missing"} aligned`,
    },
    {
      key: "readiness_trace",
      label: "readiness trace",
      status: passFail(params.get("trace") === filters.trace && context.readiness_trace === filters.trace),
      detail: `trace=${filters.trace || "missing"} context=${context.readiness_trace || "missing"}`,
    },
    {
      key: "trace_alignment",
      label: "trace alignment state",
      status: passFail(context.trace_alignment_total > 0 && ["review", "aligned"].includes(context.trace_alignment_state)),
      detail: `${context.trace_alignment_state || "missing"}: ${context.trace_alignment_aligned ?? "missing"}/${context.trace_alignment_total ?? "missing"} aligned`,
    },
    {
      key: "blocker_focus",
      label: "production blocker focus",
      status: passFail(params.get("blockerItem") === filters.blocker_item && context.production_blocker === filters.blocker_item),
      detail: `blocker=${filters.blocker_item || "missing"} context=${context.production_blocker || "missing"}`,
    },
    {
      key: "local_authority_boundary",
      label: "local authority boundary",
      status: passFail(
        boundary.production_evidence === 0 &&
          boundary.host_write_authority === 0 &&
          boundary.main_gui_mutation_required === 0 &&
          boundary.edge_gui_mutation_required === 0 &&
          context.production_evidence_claim === 0 &&
          context.main_gui_mutation_required === 0 &&
          context.edge_gui_mutation_required === 0
      ),
      detail: `production=${boundary.production_evidence ?? "missing"} host=${boundary.host_write_authority ?? "missing"} main=${boundary.main_gui_mutation_required ?? "missing"} edge=${boundary.edge_gui_mutation_required ?? "missing"}`,
    },
  ].map((row) => ({
    ...row,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function qaHandoffScopeSummary(handoff) {
  const rows = qaHandoffScopeRows(handoff);
  const passed = rows.filter((row) => row.status === "passed").length;
  return {
    total: rows.length,
    passed,
    blocked: rows.length - passed,
    status: rows.length > 0 && passed === rows.length ? "passed" : "blocked",
    selected_compare: handoff?.selected_review_context?.readiness_compare || "none",
    selected_trace: handoff?.selected_review_context?.readiness_trace || "none",
    selected_blocker: handoff?.selected_review_context?.production_blocker || "none",
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function qaHandoffValidationRows(handoff, artifact = null) {
  if (!handoff || !handoff.selected_snapshot) {
    return [];
  }
  const params = qaHandoffUrlParams(handoff);
  const boundary = handoff.boundary || {};
  const filters = handoff.filters || {};
  const urlParameters = handoff.url_parameters || {};
  const selectedSnapshotId = handoff.selected_snapshot?.id || "";
  const artifactSnapshotId = artifact?.selected_snapshot?.id || "";
  const artifactDigest = artifact?.integrity?.payload_digest || "none";
  const replaySnapshotId = params.get("snapshot") || "";
  const replayDigest = params.get("digest") || "";
  const exportValidation = exportValidationSummary(artifact);
  const contextDrift = handoff.context_drift || artifact?.context_drift || {};
  return [
    {
      key: "handoff_schema",
      label: "handoff schema",
      status: passFail(handoff.handoff_schema === "latticra-panel-test-ui-qa-handoff-v0"),
      detail: handoff.handoff_schema || "missing",
    },
    {
      key: "route_parameters",
      label: "evidence route and QA flag",
      status: passFail(params.get("tab") === "evidence" && params.get("qa") === "handoff"),
      detail: `tab=${params.get("tab") || "missing"} qa=${params.get("qa") || "missing"}`,
    },
    {
      key: "mode_prefix_parameters",
      label: "mode and prefix parameters",
      status: passFail(params.get("mode") === urlParameters.mode && params.get("prefix") === urlParameters.prefix),
      detail: `mode=${params.get("mode") || "missing"} prefix=${params.get("prefix") || "missing"}`,
    },
    {
      key: "filter_parameters",
      label: "review filters recorded",
      status: passFail(
        params.get("review") === filters.review &&
          params.get("blocker") === filters.blocker &&
          params.get("diff") === filters.diff &&
          params.get("gate") === filters.gate &&
          params.get("migration") === filters.migration &&
          params.get("scenario") === filters.scenario &&
          params.get("engine") === filters.engine &&
          params.get("visual") === filters.visual &&
          params.get("acceptance") === filters.acceptance &&
          params.get("a11y") === filters.a11y &&
          params.get("compare") === filters.compare &&
          params.get("intake") === filters.intake &&
          params.get("trace") === filters.trace &&
          params.get("blockerItem") === filters.blocker_item
      ),
      detail: `review=${params.get("review") || "missing"} blocker=${params.get("blocker") || "none"} diff=${params.get("diff") || "missing"} gate=${params.get("gate") || "missing"} migration=${params.get("migration") || "missing"} scenario=${params.get("scenario") || "missing"} engine=${params.get("engine") || "missing"} visual=${params.get("visual") || "missing"} acceptance=${params.get("acceptance") || "missing"} a11y=${params.get("a11y") || "missing"} compare=${params.get("compare") || "missing"} intake=${params.get("intake") || "missing"} trace=${params.get("trace") || "missing"} blockerItem=${params.get("blockerItem") || "missing"}`,
    },
    {
      key: "selected_snapshot",
      label: "selected snapshot aligned",
      status: passFail(Boolean(selectedSnapshotId && artifactSnapshotId && selectedSnapshotId === artifactSnapshotId)),
      detail: selectedSnapshotId || "missing",
    },
    {
      key: "snapshot_replay_parameters",
      label: "snapshot replay parameters",
      status: passFail(
        Boolean(selectedSnapshotId) &&
          replaySnapshotId === selectedSnapshotId &&
          replayDigest !== "none" &&
          replayDigest === handoff.export_integrity_digest
      ),
      detail: `snapshot=${replaySnapshotId || "missing"} digest=${replayDigest || "missing"}`,
    },
    {
      key: "digest_alignment",
      label: "export digest aligned",
      status: passFail(handoff.export_integrity_digest !== "none" && handoff.export_integrity_digest === artifactDigest),
      detail: handoff.export_integrity_digest || "missing",
    },
    {
      key: "export_validation",
      label: "export validation passed",
      status: passFail(
        handoff.export_validation_status === "passed" &&
          exportValidation.status === "passed" &&
          handoff.export_validation_passed === handoff.export_validation_total
      ),
      detail: `${handoff.export_validation_passed}/${handoff.export_validation_total} passed`,
    },
    {
      key: "saved_context_drift",
      label: "saved review context aligned",
      status: passFail(
        contextDrift.status === "same" &&
          contextDrift.row_count === receiptContextDriftFields.length &&
          contextDrift.production_evidence_claim === 0
      ),
      detail: `${contextDrift.changed_count ?? "missing"}/${contextDrift.row_count ?? "missing"} changed`,
    },
    {
      key: "local_only_boundary",
      label: "local-only handoff boundary",
      status: passFail(
        boundary.test_ui_lane === 1 &&
          boundary.production_evidence === 0 &&
          boundary.host_write_authority === 0 &&
          boundary.clipboard_write_authority === 0 &&
          boundary.handoff_mutates_state === 0
      ),
      detail: `production=${boundary.production_evidence ?? "missing"} host=${boundary.host_write_authority ?? "missing"} clipboard=${boundary.clipboard_write_authority ?? "missing"}`,
    },
    {
      key: "gui_mutation_boundary",
      label: "main and edge GUI mutation blocked",
      status: passFail(boundary.main_gui_mutation_required === 0 && boundary.edge_gui_mutation_required === 0),
      detail: `main=${boundary.main_gui_mutation_required ?? "missing"} edge=${boundary.edge_gui_mutation_required ?? "missing"}`,
    },
  ];
}

function qaHandoffValidationSummary(handoff, artifact = null) {
  const rows = qaHandoffValidationRows(handoff, artifact);
  const passed = rows.filter((row) => row.status === "passed").length;
  return {
    total: rows.length,
    passed,
    blocked: rows.length - passed,
    status: rows.length > 0 && passed === rows.length ? "passed" : "blocked",
    rows,
  };
}

function buildQaHandoff(snapshot, artifact = null) {
  const exportArtifact = artifact || (snapshot ? buildReceiptExportArtifact(snapshot) : null);
  const validation = exportValidationSummary(exportArtifact);
  const handoff = {
    handoff_schema: "latticra-panel-test-ui-qa-handoff-v0",
    generated_at: nowStamp(),
    url: buildQaHandoffUrl(snapshot, exportArtifact),
    url_parameters: {
      tab: "evidence",
      mode: state.mode,
      prefix: state.prefix || "~/.local",
      review: state.reviewFilter,
      blocker: state.blockerFilter,
      diff: state.receiptDiffFilter,
      gate: state.promotionGateSelection,
      migration: state.migrationReviewSelection,
      scenario: state.qaScenarioSelection,
      engine: state.engineBindingSelection,
      visual: state.visualBaselineSelection,
      acceptance: state.releaseAcceptanceSelection,
      a11y: state.accessibilityAuditSelection,
      compare: state.readinessCompareSelection,
      intake: state.evidenceIntakeSelection,
      trace: state.traceabilitySelection,
      blocker_item: state.productionBlockerSelection,
      qa: "handoff",
      snapshot: snapshot?.id || "none",
      digest: exportArtifact?.integrity?.payload_digest || "none",
    },
    boundary: {
      test_ui_lane: 1,
      production_evidence: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
      clipboard_write_authority: 0,
      handoff_mutates_state: 0,
    },
    mode: state.mode === "dry" ? "dry-run" : "guarded-local",
    prefix: state.prefix || "~/.local",
    prefix_guard: state.prefixValid ? "accepted" : "blocked",
    filters: {
      review: state.reviewFilter,
      blocker: state.blockerFilter,
      diff: state.receiptDiffFilter,
      gate: state.promotionGateSelection,
      migration: state.migrationReviewSelection,
      scenario: state.qaScenarioSelection,
      engine: state.engineBindingSelection,
      visual: state.visualBaselineSelection,
      acceptance: state.releaseAcceptanceSelection,
      a11y: state.accessibilityAuditSelection,
      compare: state.readinessCompareSelection,
      intake: state.evidenceIntakeSelection,
      trace: state.traceabilitySelection,
      blocker_item: state.productionBlockerSelection,
    },
    selected_review_context: qaHandoffReviewContext(),
    selected_snapshot: snapshot
      ? {
          id: snapshot.id,
          label: snapshot.label,
          saved_at: snapshot.saved_at,
        }
      : null,
    component_count: selectedComponents().length,
    selected_components: selectedComponents().map((component) => component.id),
    export_integrity_digest: exportArtifact?.integrity?.payload_digest || "none",
    export_validation_status: validation.status,
    export_validation_passed: validation.passed,
    export_validation_total: validation.total,
    context_drift: exportArtifact?.context_drift || receiptContextDriftSummary(null, {}),
    replay_request: qaHandoffReplayRequest(snapshot, exportArtifact),
  };
  return {
    ...handoff,
    handoff_scope: {
      summary: qaHandoffScopeSummary(handoff),
      rows: qaHandoffScopeRows(handoff),
    },
    handoff_validation: qaHandoffValidationSummary(handoff, exportArtifact),
  };
}

function buildReceiptExportArtifact(snapshot, currentReceipt = null) {
  if (!snapshot) {
    return null;
  }
  const comparisonReceipt = currentReceipt || buildReceiptPreview();
  const artifact = {
    artifact_schema: "latticra-panel-test-ui-local-export-v0",
    exported_at: nowStamp(),
    boundary: {
      watermark: "NOT PRODUCTION EVIDENCE",
      artifact_kind: "local no-effect preview",
      test_ui_lane: 1,
      production_evidence: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    snapshot_lifecycle: {
      retention_limit: SAVED_RECEIPT_LIMIT,
      local_only: true,
      relabel_mutates_test_lane_state_only: true,
      delete_mutates_test_lane_state_only: true,
    },
    selected_snapshot: {
      id: snapshot.id,
      label: snapshot.label,
      saved_at: snapshot.saved_at,
      summary: snapshot.summary,
      receipt: snapshot.receipt,
    },
    current_comparison: compareSavedReceipt(snapshot, comparisonReceipt),
    field_comparison: receiptDiffSummary(snapshot, comparisonReceipt),
    context_drift: receiptContextDriftSummary(snapshot, comparisonReceipt),
  };
  const artifactWithIntegrity = {
    ...artifact,
    integrity: buildExportIntegrity(artifact),
  };
  return {
    ...artifactWithIntegrity,
    export_validation: exportValidationSummary(artifactWithIntegrity),
  };
}

function receiptFieldRows() {
  return receiptFields.map((field) => ({
    key: field.key,
    value: field.value(),
    source: field.source(),
    status: field.status(),
  }));
}

function schemaStatusSummary(rows = receiptFieldRows()) {
  return {
    total: rows.length,
    live: rows.filter((row) => row.status === "live").length,
    guarded: rows.filter((row) => row.status === "guarded").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
  };
}

function productionBlockerCount() {
  return productionBlockers.reduce((count, section) => count + section.items.length, 0);
}

function productionBlockerRows() {
  return productionBlockers.flatMap((section) =>
    section.items.map((item) => ({
      key: item.key,
      label: item.label,
      status: item.status,
      group: section.group,
      source: item.source,
      evidence: item.evidence,
      owner: item.owner,
      next_action: item.next,
      selected: item.key === state.productionBlockerSelection,
      local_only: true,
      can_promote: false,
      production_evidence_claim: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    }))
  );
}

function normalizeBlockerFilter(value = state.blockerFilter) {
  return String(value || "").trim().slice(0, BLOCKER_FILTER_MAX_LENGTH);
}

function productionBlockerMatchesFilter(row, normalizedFilter) {
  if (!normalizedFilter) {
    return true;
  }
  return `${row.group} ${row.label} ${row.status} ${row.evidence} ${row.owner} ${row.next_action}`
    .toLowerCase()
    .includes(normalizedFilter.toLowerCase());
}

function productionBlockerVisibleRows(rows = productionBlockerRows(), filter = state.blockerFilter) {
  const normalized = normalizeBlockerFilter(filter);
  return rows.filter((row) => productionBlockerMatchesFilter(row, normalized));
}

function productionBlockerSummary(rows = productionBlockerRows()) {
  const filter = normalizeBlockerFilter();
  const visibleRows = productionBlockerVisibleRows(rows, filter);
  const selected =
    rows.find((row) => row.key === state.productionBlockerSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0];
  return {
    total: rows.length,
    visible: visibleRows.length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    filter,
    filter_active: filter.length > 0,
    filter_limit: BLOCKER_FILTER_MAX_LENGTH,
    filter_status: filter.length > 0 ? "filtered" : "all",
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    selected_owner: selected?.owner || "none",
    local_only: rows.every((row) => row.local_only === true),
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function productionBlockerProofRows(row = selectedProductionBlockerRow()) {
  if (!row) {
    return [];
  }
  return [
    {
      key: "missing_evidence",
      label: "missing evidence",
      expected: row.evidence,
      current: row.status,
      status: "blocked",
      evidence: row.next_action,
    },
    {
      key: "proof_owner",
      label: "proof owner",
      expected: row.owner,
      current: row.source,
      status: "blocked",
      evidence: `${row.group} / ${row.label}`,
    },
    {
      key: "release_acceptance",
      label: "release acceptance",
      expected: "production evidence packet recorded outside test lane",
      current: "not accepted",
      status: "blocked",
      evidence: "can_promote=false",
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      expected: "claim=0 host=0 main=0 edge=0",
      current: "closed in test lane",
      status: "verified",
      evidence: "production evidence cannot be created by this UI lane",
    },
  ].map((proofRow) => ({
    ...proofRow,
    selected_blocker_key: row.key,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function productionBlockerProofSummary(rows = productionBlockerProofRows()) {
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: state.productionBlockerSelection,
    release_evidence_ready: false,
    local_only: rows.every((row) => row.local_only === true),
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function readinessComparisonRows() {
  return readinessComparisonItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    local_proof: item.localProof,
    production_requirement: item.productionRequirement,
    owner: item.owner,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.readinessCompareSelection,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function readinessComparisonSummary(rows = readinessComparisonRows()) {
  const selected =
    rows.find((row) => row.key === state.readinessCompareSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0];
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending: rows.filter((row) => row.status === "pending").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    local_proof_only: true,
    can_promote: false,
    production_blocker_count: productionBlockerCount(),
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function readinessComparisonProofRows(row = selectedReadinessComparisonRow()) {
  if (!row) {
    return [];
  }
  const requirementStatus = row.status === "verified" ? "blocked" : row.status;
  return [
    {
      key: "local_proof_scope",
      label: "local proof scope",
      current: "available / verified",
      status: "verified",
      expected: "isolated UI proof can be reviewed locally",
      evidence: row.local_proof,
      selected_compare_key: row.key,
      local_only: true,
      can_promote: false,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "production_requirement",
      label: "production requirement",
      current: row.status === "verified" ? "not production evidence" : row.status,
      status: requirementStatus,
      expected: row.production_requirement,
      evidence: `owner=${row.owner}; ${row.boundary}`,
      selected_compare_key: row.key,
      local_only: true,
      can_promote: false,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "release_acceptance",
      label: "release acceptance",
      current: "not accepted / blocked",
      status: "blocked",
      expected: "production evidence packet accepted outside test lane",
      evidence: `next=${row.next_action}; can_promote=false`,
      selected_compare_key: row.key,
      local_only: true,
      can_promote: false,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      current: "closed in test lane / verified",
      status: "verified",
      expected: "claim=0 host=0 runtime=0 main=0 edge=0",
      evidence: "selected comparison can review evidence but cannot promote or mutate guarded GUIs",
      selected_compare_key: row.key,
      local_only: true,
      can_promote: false,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
  ];
}

function readinessComparisonProofSummary(rows = readinessComparisonProofRows()) {
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending: rows.filter((row) => row.status === "pending").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: state.readinessCompareSelection,
    release_evidence_ready: false,
    local_only: rows.every((row) => row.local_only === true),
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function readinessComparisonContextTarget(row = selectedReadinessComparisonRow()) {
  const targets = {
    local_ui_proof: {
      trace: "local_ui_trace",
      blockers: "none",
      intake_packet: "local_ui_packet",
      promotion_gate: "local_ui_evidence",
      acceptance_gate: "local_ui_acceptance",
    },
    guarded_panel_migration: {
      trace: "migration_trace",
      blockers: "none",
      intake_packet: "guarded_panel_packet",
      promotion_gate: "main_panel_migration_review",
      acceptance_gate: "guarded_panel_acceptance",
    },
    installer_engine_binding: {
      trace: "installer_runtime_trace",
      blockers: "none",
      intake_packet: "installer_runtime_packet",
      promotion_gate: "installer_engine_binding",
      acceptance_gate: "installer_engine_acceptance",
    },
    release_artifacts: {
      trace: "artifact_supply_chain_trace",
      blockers: "reproducible_artifact, artifact_signature, sbom_evidence",
      intake_packet: "artifact_signature_packet",
      promotion_gate: "artifact_integrity / sbom_attestation",
      acceptance_gate: "production_evidence_acceptance",
    },
    lifecycle_validation: {
      trace: "lifecycle_trace",
      blockers: "production_preflight_guard, install_transcript, uninstall_transcript",
      intake_packet: "lifecycle_transcript_packet",
      promotion_gate: "lifecycle_transcripts",
      acceptance_gate: "production_evidence_acceptance",
    },
    recovery_matrix: {
      trace: "recovery_trace",
      blockers: "upgrade_path, rollback_path, multi_vm_validation",
      intake_packet: "recovery_validation_packet",
      promotion_gate: "upgrade_rollback_recovery / multi_vm_validation",
      acceptance_gate: "release_authority_acceptance",
    },
  };
  return targets[row?.key] || targets.local_ui_proof;
}

function readinessComparisonAlignmentRows(row = selectedReadinessComparisonRow()) {
  if (!row) {
    return [];
  }
  const target = readinessComparisonContextTarget(row);
  const blockerKeys = traceabilityKeyList(target.blockers);
  const gateKeys = traceabilityKeyList(target.promotion_gate);
  const checks = [
    {
      key: "trace_path",
      label: "trace path",
      expected: target.trace,
      current: state.traceabilitySelection,
      aligned: target.trace === state.traceabilitySelection,
    },
    {
      key: "intake_packet",
      label: "intake packet",
      expected: target.intake_packet,
      current: state.evidenceIntakeSelection,
      aligned: target.intake_packet === state.evidenceIntakeSelection,
    },
    {
      key: "promotion_gate",
      label: "promotion gate",
      expected: target.promotion_gate,
      current: state.promotionGateSelection,
      aligned: gateKeys.includes(state.promotionGateSelection),
    },
    {
      key: "acceptance_gate",
      label: "acceptance gate",
      expected: target.acceptance_gate,
      current: state.releaseAcceptanceSelection,
      aligned: target.acceptance_gate === state.releaseAcceptanceSelection,
    },
    {
      key: "blocker_selection",
      label: "blocker selection",
      expected: target.blockers,
      current: blockerKeys.length === 0 ? "not applicable" : state.productionBlockerSelection,
      aligned: blockerKeys.length === 0 || blockerKeys.includes(state.productionBlockerSelection),
    },
  ];
  return checks.map((item) => ({
    ...item,
    compare_key: row.key,
    status: item.aligned ? "aligned" : "review",
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function readinessComparisonAlignmentSummary(rows = readinessComparisonAlignmentRows()) {
  return {
    total: rows.length,
    aligned: rows.filter((row) => row.status === "aligned").length,
    review: rows.filter((row) => row.status === "review").length,
    selected_compare: state.readinessCompareSelection,
    action_state: rows.some((row) => row.status === "review") ? "align_available" : "aligned",
    action_label: rows.some((row) => row.status === "review") ? "Align comparison context" : "Comparison context aligned",
    local_only: rows.every((row) => row.local_only),
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function evidenceIntakeRows() {
  return releaseEvidenceIntakeItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    packet: item.packet,
    source: item.source,
    decision: item.decision,
    reviewer: item.reviewer,
    next_action: item.next,
    boundary: item.boundary,
    evidence: item.packet,
    selected: item.key === state.evidenceIntakeSelection,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function evidenceIntakeSummary(rows = evidenceIntakeRows()) {
  const selected =
    rows.find((row) => row.key === state.evidenceIntakeSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0];
  return {
    total: rows.length,
    local_only: rows.filter((row) => row.status === "local-only").length,
    waiting: rows.filter((row) => row.status === "waiting").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    selected_decision: selected?.decision || "none",
    intake_authority: 0,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function evidenceIntakeContractRows(row = selectedEvidenceIntakeRow()) {
  if (!row) {
    return [];
  }
  const decisionStatus = row.status === "local-only" ? "verified" : row.status === "waiting" ? "pending" : "blocked";
  const proofCurrent =
    row.status === "local-only"
      ? "local proof present"
      : row.status === "waiting"
        ? "awaiting production packet"
        : "missing production packet";
  return [
    {
      key: "packet_scope",
      label: "packet scope",
      expected: row.packet,
      current: row.source,
      status: "verified",
      evidence: row.packet,
    },
    {
      key: "intake_decision",
      label: "intake decision",
      expected: row.decision,
      current: row.status,
      status: decisionStatus,
      evidence: row.next_action,
    },
    {
      key: "required_proof",
      label: "required proof",
      expected: row.packet,
      current: proofCurrent,
      status: decisionStatus,
      evidence: row.status === "local-only" ? "accepted for local QA review only" : row.decision,
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      expected: "claim=0 host=0 runtime=0 main=0 edge=0",
      current: "closed in test lane",
      status: "verified",
      evidence: row.boundary,
    },
  ].map((contractRow) => ({
    ...contractRow,
    selected_intake_key: row.key,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function evidenceIntakeContractSummary(rows = evidenceIntakeContractRows()) {
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: state.evidenceIntakeSelection,
    can_promote: false,
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function traceabilityRows() {
  return traceabilityItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    blockers: item.blockers,
    intake_packet: item.intake,
    promotion_gate: item.gate,
    acceptance_gate: item.acceptance,
    owner: item.owner,
    evidence: item.evidence,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.traceabilitySelection,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function traceabilitySummary(rows = traceabilityRows()) {
  const selected =
    rows.find((row) => row.key === state.traceabilitySelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0];
  return {
    total: rows.length,
    covered: rows.filter((row) => row.status === "covered").length,
    waiting: rows.filter((row) => row.status === "waiting").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    selected_gate: selected?.promotion_gate || "none",
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function traceabilityKeyList(value) {
  if (!value || value === "none") {
    return [];
  }
  return value.split(",").flatMap((chunk) => chunk.split("/")).map((item) => item.trim()).filter(Boolean);
}

function traceabilityAlignmentRows(row = selectedTraceabilityRow()) {
  if (!row) {
    return [];
  }
  const blockerKeys = traceabilityKeyList(row.blockers);
  const gateKeys = traceabilityKeyList(row.promotion_gate);
  const checks = [
    {
      key: "intake_packet",
      label: "intake packet",
      expected: row.intake_packet,
      current: state.evidenceIntakeSelection,
      aligned: row.intake_packet === state.evidenceIntakeSelection,
    },
    {
      key: "promotion_gate",
      label: "promotion gate",
      expected: row.promotion_gate,
      current: state.promotionGateSelection,
      aligned: gateKeys.includes(state.promotionGateSelection),
    },
    {
      key: "acceptance_gate",
      label: "acceptance gate",
      expected: row.acceptance_gate,
      current: state.releaseAcceptanceSelection,
      aligned: row.acceptance_gate === state.releaseAcceptanceSelection,
    },
    {
      key: "blocker_selection",
      label: "blocker selection",
      expected: row.blockers,
      current: blockerKeys.length === 0 ? "not applicable" : state.productionBlockerSelection,
      aligned: blockerKeys.length === 0 || blockerKeys.includes(state.productionBlockerSelection),
    },
  ];
  return checks.map((item) => ({
    ...item,
    trace_key: row.key,
    status: item.aligned ? "aligned" : "review",
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function traceabilityAlignmentSummary(rows = traceabilityAlignmentRows()) {
  return {
    total: rows.length,
    aligned: rows.filter((row) => row.status === "aligned").length,
    review: rows.filter((row) => row.status === "review").length,
    selected_trace: state.traceabilitySelection,
    action_state: rows.some((row) => row.status === "review") ? "align_available" : "aligned",
    action_label: rows.some((row) => row.status === "review") ? "Align local context" : "Context aligned",
    local_only: rows.every((row) => row.local_only),
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function isPromotionGateKey(key) {
  return promotionGateItems.some((item) => item.key === key);
}

function isMigrationReviewKey(key) {
  return migrationMap.some((item) => item.key === key);
}

function isQaScenarioKey(key) {
  return qaScenarios.some((item) => item.key === key);
}

function isEngineBindingKey(key) {
  return engineBindingItems.some((item) => item.key === key);
}

function isVisualBaselineKey(key) {
  return visualBaselineItems.some((item) => item.key === key);
}

function isReleaseAcceptanceKey(key) {
  return releaseAcceptanceItems.some((item) => item.key === key);
}

function isAccessibilityAuditKey(key) {
  return accessibilityAuditItems.some((item) => item.key === key);
}

function isReadinessCompareKey(key) {
  return readinessComparisonItems.some((item) => item.key === key);
}

function isEvidenceIntakeKey(key) {
  return releaseEvidenceIntakeItems.some((item) => item.key === key);
}

function isTraceabilityKey(key) {
  return traceabilityItems.some((item) => item.key === key);
}

function isProductionBlockerKey(key) {
  return productionBlockerRows().some((item) => item.key === key);
}

function commandPaletteAuditRows(rows, config) {
  return rows.map((row) => ({
    key: `${config.prefix}:${row.key}`,
    kind: "jump",
    label: row.label,
    detail: [config.label, row.group, row.status].filter(Boolean).join(" / "),
    evidence: [row.evidence, row.path, row.local_proof, row.production_requirement, row.next_action, row.owner, row.source, row.boundary]
      .filter(Boolean)
      .join(" | ") || "local UI review target",
    tab: config.tab,
    target: config.target,
    target_key: row.key,
    status: row.status,
    local_only: true,
    shell_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    production_evidence_claim: 0,
  }));
}

function commandPaletteItems() {
  const commandRows = [
    ["status", "Read current lane status"],
    ["plan", "Regenerate the local no-effect plan"],
    ["dry-run", "Queue a no-effect dry-install simulation"],
    ["updater status", "Inspect the closed signed updater gate"],
    ["mode dry", "Return to dry-run mode"],
    ["mode local", "Arm guarded user-local simulation"],
  ].map(([command, detail]) => ({
    key: `command:${command}`,
    kind: "command",
    label: command,
    detail,
    evidence: "allowlisted panel command only",
    command,
    tab: "console",
    target: "console_command",
    target_key: command,
    status: "allowlisted",
    local_only: true,
    shell_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    production_evidence_claim: 0,
  }));

  const tabRows = tabs.map(([id, label]) => ({
    key: `tab:${id}`,
    kind: "tab",
    label: `Open ${label}`,
    detail: `Workspace tab / ${label}`,
    evidence: "local navigation only",
    tab: id,
    target: "workspace_tab",
    target_key: id,
    status: id === state.activeTab ? "current" : "local",
    local_only: true,
    shell_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    production_evidence_claim: 0,
  }));

  return [
    ...commandRows,
    ...tabRows,
    ...commandPaletteAuditRows(productionBlockerRows(), {
      prefix: "blocker",
      label: "Production blocker",
      tab: "readiness",
      target: "production_blocker",
    }),
    ...commandPaletteAuditRows(readinessComparisonRows(), {
      prefix: "compare",
      label: "Readiness compare",
      tab: "readiness",
      target: "readiness_compare",
    }),
    ...commandPaletteAuditRows(evidenceIntakeRows(), {
      prefix: "intake",
      label: "Evidence intake",
      tab: "readiness",
      target: "evidence_intake",
    }),
    ...commandPaletteAuditRows(traceabilityRows(), {
      prefix: "trace",
      label: "Traceability",
      tab: "readiness",
      target: "traceability",
    }),
    ...commandPaletteAuditRows(promotionGateRows(), {
      prefix: "gate",
      label: "Promotion gate",
      tab: "readiness",
      target: "promotion_gate",
    }),
    ...commandPaletteAuditRows(migrationReviewRows(), {
      prefix: "migration",
      label: "Migration review",
      tab: "review",
      target: "migration_review",
    }),
    ...commandPaletteAuditRows(qaScenarioRows(), {
      prefix: "scenario",
      label: "QA scenario",
      tab: "review",
      target: "qa_scenario",
    }),
    ...commandPaletteAuditRows(engineBindingRows(), {
      prefix: "engine",
      label: "Installer binding",
      tab: "review",
      target: "engine_binding",
    }),
    ...commandPaletteAuditRows(visualBaselineRows(), {
      prefix: "visual",
      label: "Visual baseline",
      tab: "review",
      target: "visual_baseline",
    }),
    ...commandPaletteAuditRows(releaseAcceptanceRows(), {
      prefix: "acceptance",
      label: "Release acceptance",
      tab: "review",
      target: "release_acceptance",
    }),
    ...commandPaletteAuditRows(accessibilityAuditRows(), {
      prefix: "a11y",
      label: "Accessibility evidence",
      tab: "review",
      target: "accessibility_audit",
    }),
  ];
}

function commandPaletteVisibleRows(query = state.paletteQuery) {
  const normalized = query.trim().toLowerCase();
  const rows = commandPaletteItems();
  if (!normalized) {
    return rows;
  }
  return rows.filter((row) =>
    [
      row.key,
      row.kind,
      row.label,
      row.detail,
      row.evidence,
      row.command,
      row.tab,
      row.target,
      row.target_key,
      row.status,
    ]
      .filter(Boolean)
      .some((value) => String(value).toLowerCase().includes(normalized))
  );
}

function selectedCommandPaletteItem(rows = commandPaletteVisibleRows()) {
  return rows.find((row) => row.key === state.paletteSelection) || rows[0] || null;
}

function isCommandPaletteKey(key) {
  return commandPaletteItems().some((row) => row.key === key);
}

function commandPaletteReceiptRows(rows = commandPaletteVisibleRows()) {
  return rows.slice(0, COMMAND_PALETTE_RESULT_LIMIT).map((row) => ({
    key: row.key,
    kind: row.kind,
    label: row.label,
    status: row.status,
    tab: row.tab,
    target: row.target,
    target_key: row.target_key,
    local_only: row.local_only,
    shell_authority: row.shell_authority,
    host_write_authority: row.host_write_authority,
    main_gui_mutation_required: row.main_gui_mutation_required,
    edge_gui_mutation_required: row.edge_gui_mutation_required,
    production_evidence_claim: row.production_evidence_claim,
  }));
}

function commandPaletteSummary(rows = commandPaletteVisibleRows()) {
  const selected = selectedCommandPaletteItem(rows);
  return {
    query: state.paletteQuery || "empty",
    total: commandPaletteItems().length,
    filtered: rows.length,
    visible: Math.min(rows.length, COMMAND_PALETTE_RESULT_LIMIT),
    selected_key: selected?.key || "none",
    selected_label: selected?.label || "none",
    selected_status: selected?.status || "none",
    selected_tab: selected?.tab || "none",
    selected_target: selected?.target || "none",
    keyboard_accessible: true,
    local_only: true,
    shell_authority: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    production_evidence_claim: 0,
  };
}

function commandPaletteOptionId(key) {
  return `palette-option-${key.replace(/[^a-z0-9_-]/gi, "-")}`;
}

function commandPaletteTone(status) {
  if (status === "blocked") {
    return "stop";
  }
  if (status === "pending" || status === "needs binding") {
    return "warn";
  }
  if (status === "covered" || status === "verified" || status === "candidate" || status === "allowlisted") {
    return "ok";
  }
  return "info";
}

function nowStamp() {
  return new Date().toISOString();
}

function activeModeLabel() {
  return state.mode === "dry" ? "dry-run" : "guarded local";
}

function assistiveStatus(message) {
  const status = qs("#assistive-status");
  if (status) {
    status.textContent = message;
  }
}

function queryParams() {
  return new URLSearchParams(window.location.search);
}

function qaReplaySpecs() {
  return [
    {
      param: "qa",
      label: "QA flag",
      applied: () => queryParams().get("qa") || "none",
      valid: (value) => Boolean(value),
      captureOnly: true,
    },
    {
      param: "tab",
      label: "Tab",
      applied: () => state.activeTab,
      valid: (value) => tabs.some(([id]) => id === value),
    },
    {
      param: "mode",
      label: "Mode",
      applied: () => state.mode,
      valid: (value) => value === "dry" || value === "local",
    },
    {
      param: "prefix",
      label: "Prefix",
      applied: () => state.prefix,
      valid: (value) => Boolean(value),
    },
    {
      param: "review",
      label: "Review",
      applied: () => state.reviewFilter,
      valid: (value) => reviewFilterOptions.includes(value),
    },
    {
      param: "diff",
      label: "Diff",
      applied: () => state.receiptDiffFilter,
      valid: (value) => receiptDiffFilterOptions.includes(value),
    },
    {
      param: "gate",
      label: "Gate",
      applied: () => state.promotionGateSelection,
      valid: isPromotionGateKey,
    },
    {
      param: "migration",
      label: "Migration",
      applied: () => state.migrationReviewSelection,
      valid: isMigrationReviewKey,
    },
    {
      param: "scenario",
      label: "Scenario",
      applied: () => state.qaScenarioSelection,
      valid: isQaScenarioKey,
    },
    {
      param: "engine",
      label: "Engine",
      applied: () => state.engineBindingSelection,
      valid: isEngineBindingKey,
    },
    {
      param: "visual",
      label: "Visual",
      applied: () => state.visualBaselineSelection,
      valid: isVisualBaselineKey,
    },
    {
      param: "acceptance",
      label: "Acceptance",
      applied: () => state.releaseAcceptanceSelection,
      valid: isReleaseAcceptanceKey,
    },
    {
      param: "a11y",
      label: "Accessibility",
      applied: () => state.accessibilityAuditSelection,
      valid: isAccessibilityAuditKey,
    },
    {
      param: "compare",
      label: "Compare",
      applied: () => state.readinessCompareSelection,
      valid: isReadinessCompareKey,
    },
    {
      param: "intake",
      label: "Intake",
      applied: () => state.evidenceIntakeSelection,
      valid: isEvidenceIntakeKey,
    },
    {
      param: "trace",
      label: "Trace",
      applied: () => state.traceabilitySelection,
      valid: isTraceabilityKey,
    },
    {
      param: "blocker",
      label: "Blocker filter",
      applied: () => state.blockerFilter || "empty",
      valid: () => true,
    },
    {
      param: "blockerItem",
      label: "Blocker item",
      applied: () => state.productionBlockerSelection,
      valid: isProductionBlockerKey,
    },
    {
      param: "snapshot",
      label: "Snapshot",
      applied: () => queryParams().get("snapshot") || "none",
      valid: (value) => Boolean(value),
      captureOnly: true,
    },
    {
      param: "digest",
      label: "Digest",
      applied: () => queryParams().get("digest") || "none",
      valid: (value) => Boolean(value),
      captureOnly: true,
    },
  ];
}

function qaReplayRows(params = queryParams()) {
  return qaReplaySpecs().map((spec) => {
    const requested = params.has(spec.param);
    const requestedValue = requested ? params.get(spec.param) || "empty" : "not requested";
    const valid = requested && spec.valid(requestedValue === "empty" ? "" : requestedValue);
    return {
      key: spec.param,
      label: spec.label,
      requested,
      requested_value: requestedValue,
      applied_value: spec.applied(),
      status: !requested ? "not requested" : valid ? (spec.captureOnly ? "captured" : "applied") : "ignored",
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    };
  });
}

function qaReplayVisibleRows(rows = qaReplayRows(), limit = QA_REPLAY_VISIBLE_CHIP_LIMIT) {
  const activeRows = rows.filter((row) => row.requested);
  const displayRows = activeRows.length > 0 ? activeRows : rows.slice(0, 3);
  const visibleRows = displayRows.slice(0, limit);
  return {
    rows: visibleRows,
    total_chips: displayRows.length,
    visible_chips: visibleRows.length,
    hidden_chips: Math.max(displayRows.length - visibleRows.length, 0),
    chip_limit: limit,
    chip_layout: "bounded-wrap",
    overflow_guard: "no-horizontal-scroll",
  };
}

function qaReplaySummary(rows = qaReplayRows(), params = queryParams()) {
  const requested = rows.filter((row) => row.requested);
  const knownKeys = qaReplaySpecs().map((spec) => spec.param);
  const extraParams = Array.from(params.keys()).filter((key) => !knownKeys.includes(key));
  const visible = qaReplayVisibleRows(rows);
  return {
    active: requested.length > 0 || extraParams.length > 0,
    route: state.activeTab,
    qa: params.get("qa") || "none",
    requested: requested.length,
    applied: requested.filter((row) => row.status === "applied" || row.status === "captured").length,
    ignored: requested.filter((row) => row.status === "ignored").length,
    extra_params: extraParams.length,
    visible_chips: visible.visible_chips,
    hidden_chips: visible.hidden_chips,
    chip_limit: visible.chip_limit,
    chip_layout: visible.chip_layout,
    overflow_guard: visible.overflow_guard,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function inspectorLiveEvidenceRows() {
  const priority = new Map([
    ["dry_run_plan_digest", 1],
    ["panel_ui_lane", 2],
    ["production_installer_claim", 3],
    ["main_gui_mutation_required", 4],
    ["edge_gui_mutation_required", 5],
    ["root_authority", 6],
    ["network_authority", 7],
    ["runtime_enforcement_authority", 8],
  ]);
  const baseRows = evidence.map(([key, value, source], index) => {
    const boundaryKey =
      key.includes("authority") ||
      key.includes("mutation") ||
      key.includes("claim") ||
      key.includes("enforcement");
    return {
      key,
      label: key,
      value,
      source,
      status: boundaryKey ? "guarded" : "ready",
      order: priority.get(key) || index + 20,
      local_only: true,
      production_evidence_claim: 0,
      host_write_authority: 0,
      runtime_enforcement_authority: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    };
  });
  const eventRows = state.events.slice(-2).reverse().map((event, index) => ({
    key: `event_${index + 1}`,
    label: event.label.toLowerCase().replace(/[^a-z0-9]+/g, "_").replace(/^_|_$/g, "") || "event",
    value: event.detail,
    source: "event",
    status: event.level === "blocked" ? "blocked" : "ready",
    order: index - 2,
    timestamp: event.timestamp,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
  return [...eventRows, ...baseRows].sort((a, b) => a.order - b.order);
}

function inspectorLiveEvidenceSummary(rows = inspectorLiveEvidenceRows()) {
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const guarded = rows.filter((row) => row.status === "guarded").length;
  const ready = rows.filter((row) => row.status === "ready").length;
  const visibleRows = rows.slice(0, 5);
  const latest = visibleRows[0]?.label || "none";
  return {
    state: blocked > 0 ? "blocked" : guarded > 0 ? "review" : "ready",
    title: blocked > 0 ? "Evidence needs review" : "Receipt evidence ready",
    row_count: rows.length,
    visible_count: visibleRows.length,
    ready,
    guarded,
    blocked,
    latest,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    zero_authority: rows.every(
      (row) =>
        row.production_evidence_claim === 0 &&
        row.host_write_authority === 0 &&
        row.runtime_enforcement_authority === 0 &&
        row.main_gui_mutation_required === 0 &&
        row.edge_gui_mutation_required === 0,
    ),
  };
}

function contextInspectorSummary() {
  const replay = qaReplaySummary();
  const liveEvidence = inspectorLiveEvidenceSummary();
  const brand = brandEmblemState();
  const visualIdentity = visualIdentitySummary();
  const componentHealth = componentHealthSummary();
  const primaryActions = primaryActionRailSummary();
  const posture = workspacePostureSummary();
  const route = workspaceRouteSummary();
  const profile = profileScopeSummary();
  const readinessRail = readinessRailSummary();
  const quality = qualityGateSummary();
  const dashboardAuthority = dashboardAuthoritySummary();
  const runMonitor = runMonitorSummary();
  const workflow = operatorWorkflowSummary();
  const deliveryPlan = deliveryPlanSummary();
  const updaterGate = updaterGateSummary();
  const evidenceQueue = evidenceQueueSummary();
  const eventTrail = eventTrailSummary();
  const receiptPreview = receiptPreviewSummary();
  const saved = selectedSavedReceipt();
  const savedTrust = savedReceiptTrustSummary();
  const promotion = selectedPromotionGateRow();
  const blocker = selectedProductionBlockerRow();
  const blockerSummary = productionBlockerSummary();
  const acceptance = selectedReleaseAcceptanceRow();
  const compare = selectedReadinessComparisonRow();
  const compareAlignment = readinessComparisonAlignmentSummary();
  const trace = selectedTraceabilityRow();
  const traceAlignment = traceabilityAlignmentSummary();
  return {
    active_tab: state.activeTab,
    live_evidence_state: liveEvidence.state,
    live_evidence_visible: liveEvidence.visible_count,
    live_evidence_total: liveEvidence.row_count,
    live_evidence_guarded: liveEvidence.guarded,
    live_evidence_latest: liveEvidence.latest,
    live_evidence_zero_authority: liveEvidence.zero_authority,
    brand_emblem_status: brand.status,
    brand_emblem_asset: brand.asset,
    brand_emblem_fallback: brand.fallback_visible,
    brand_emblem_intrinsic_size:
      brand.intrinsic_width > 0 && brand.intrinsic_height > 0
        ? `${brand.intrinsic_width}x${brand.intrinsic_height}`
        : "pending",
    brand_metadata_status: brand.browser_metadata_ready ? "browser identity ready" : "browser identity pending",
    visual_identity_state: visualIdentity.state,
    visual_identity_asset_status: visualIdentity.asset_status,
    visual_identity_asset_size: visualIdentity.asset_size,
    visual_identity_brand_status: visualIdentity.brand_status,
    visual_identity_zero_authority: visualIdentity.zero_authority,
    component_health_state: componentHealth.state,
    component_health_selected: componentHealth.selected,
    component_health_total: componentHealth.total,
    component_health_omitted: componentHealth.omitted,
    component_health_core_coverage: componentHealth.coverage_label,
    component_health_zero_authority: componentHealth.zero_authority,
    primary_action_count: primaryActions.action_count,
    primary_action_iconized_count: primaryActions.iconized_count,
    primary_action_key: primaryActions.primary_action,
    primary_action_rail_status:
      primaryActions.all_actions_iconized && primaryActions.action_count === primaryActions.enabled_count
        ? "ready"
        : "review",
    posture_ready: posture.ready,
    posture_guarded: posture.guarded,
    posture_blocked: posture.blocked,
    posture_layout_guard: posture.layout_guard,
    posture_wrap_guard: posture.wrap_guard,
    posture_layout_stable: posture.layout_stable,
    posture_zero_authority: posture.zero_authority,
    workspace_route_tab: route.active_tab,
    workspace_route_profile: route.profile,
    workspace_route_profile_scope: route.profile_scope,
    workspace_route_detail: route.evidence_detail,
    workspace_route_detail_label: route.evidence_detail_label,
    workspace_route_boundary: route.boundary,
    profile_scope_label: profile.label,
    profile_scope_text: profile.scope,
    profile_scope_intent: profile.intent,
    readiness_rail_score: readinessRail.score,
    readiness_rail_band: readinessRail.band,
    readiness_rail_label: readinessRail.label,
    readiness_rail_gate: readinessRail.gate,
    readiness_rail_can_promote: readinessRail.can_promote,
    quality_gate_decision: quality.decision,
    quality_gate_verified: quality.verified,
    quality_gate_pending: quality.pending,
    quality_gate_blocked: quality.blocked,
    quality_gate_can_promote: quality.can_promote,
    quality_gate_zero_authority: quality.zero_authority,
    dashboard_authority_decision: dashboardAuthority.decision,
    dashboard_authority_badge: dashboardAuthority.badge,
    dashboard_authority_allowed: dashboardAuthority.allowed,
    dashboard_authority_local_scope: dashboardAuthority.local_scope,
    dashboard_authority_blocked: dashboardAuthority.blocked,
    dashboard_authority_host_scope: dashboardAuthority.host_write_scope,
    dashboard_authority_production_zero: dashboardAuthority.production_authority_zero,
    run_monitor_status: runMonitor.status,
    run_monitor_progress: runMonitor.progress,
    run_monitor_prefix_guard: runMonitor.prefix_guard,
    run_monitor_runtime_authority: runMonitor.runtime_authority,
    run_monitor_last_log: runMonitor.last_log,
    operator_workflow_state: workflow.state,
    operator_workflow_complete: workflow.complete,
    operator_workflow_current: workflow.current,
    operator_workflow_blocked: workflow.blocked,
    operator_workflow_next: workflow.next_step,
    delivery_plan_state: deliveryPlan.state,
    delivery_plan_mode: deliveryPlan.mode,
    delivery_plan_components: deliveryPlan.components,
    delivery_plan_prefix_guard: deliveryPlan.prefix_guard,
    delivery_plan_zero_authority: deliveryPlan.zero_authority,
    updater_gate_state: updaterGate.state,
    updater_gate_blocked: updaterGate.blocked,
    updater_gate_required: updaterGate.required,
    updater_gate_preview_status: updaterGate.preview_status,
    updater_gate_can_apply: updaterGate.can_apply,
    updater_gate_zero_authority: updaterGate.zero_authority,
    evidence_queue_state: evidenceQueue.state,
    evidence_queue_visible: evidenceQueue.visible,
    evidence_queue_total: evidenceQueue.total,
    evidence_queue_guarded: evidenceQueue.guarded,
    evidence_queue_filter: evidenceQueue.filter,
    evidence_queue_zero_authority: evidenceQueue.zero_authority,
    event_trail_state: eventTrail.state,
    event_trail_total: eventTrail.total,
    event_trail_blocked: eventTrail.blocked,
    event_trail_latest: eventTrail.latest,
    event_trail_zero_authority: eventTrail.zero_authority,
    receipt_preview_state: receiptPreview.state,
    receipt_preview_schema: receiptPreview.schema,
    receipt_preview_events: receiptPreview.event_count,
    receipt_preview_checklist: receiptPreview.checklist,
    receipt_preview_scope: receiptPreview.scope,
    receipt_preview_zero_authority: receiptPreview.zero_authority,
    saved_receipt_trust_state: savedTrust.state,
    saved_receipt_trust_count: savedTrust.saved_count,
    saved_receipt_trust_selected: savedTrust.selected,
    saved_receipt_trust_diff: savedTrust.diff,
    saved_receipt_trust_export: savedTrust.export_state,
    saved_receipt_trust_zero_authority: savedTrust.zero_authority,
    promotion_gate: promotion?.label || "none",
    promotion_status: promotion?.status || "none",
    production_blocker: blocker?.label || "none",
    production_blocker_status: blocker?.status || "none",
    production_blocker_visible: blockerSummary.visible,
    production_blocker_total: blockerSummary.total,
    production_blocker_filter: blockerSummary.filter || "none",
    production_blocker_filter_status: blockerSummary.filter_status,
    production_blocker_filter_limit: blockerSummary.filter_limit,
    release_acceptance: acceptance?.label || "none",
    release_acceptance_status: acceptance?.status || "none",
    readiness_compare: compare?.label || "none",
    readiness_compare_status: compare?.status || "none",
    compare_alignment: compareAlignment.action_label,
    compare_alignment_status: compareAlignment.review > 0 ? "review" : "aligned",
    compare_alignment_aligned: compareAlignment.aligned,
    compare_alignment_review: compareAlignment.review,
    readiness_trace: trace?.label || "none",
    readiness_trace_status: trace?.status || "none",
    trace_alignment: traceAlignment.action_label,
    trace_alignment_status: traceAlignment.review > 0 ? "review" : "aligned",
    trace_alignment_aligned: traceAlignment.aligned,
    trace_alignment_review: traceAlignment.review,
    qa_replay_state: replay.active ? (replay.ignored > 0 ? "partial" : "active") : "none",
    qa_replay_requested: replay.requested,
    qa_replay_ignored: replay.ignored,
    qa_replay_visible_chips: replay.visible_chips,
    qa_replay_hidden_chips: replay.hidden_chips,
    qa_replay_overflow_guard: replay.overflow_guard,
    saved_receipt: saved?.label || "none",
    saved_receipt_id: saved?.id || "none",
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    runtime_enforcement_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function renderQaReplayStrip() {
  const strip = qs("#qa-replay-strip");
  const rows = qaReplayRows();
  const summary = qaReplaySummary(rows);
  const visible = qaReplayVisibleRows(rows);
  strip.dataset.replayStatus = summary.active ? (summary.ignored > 0 ? "partial" : "active") : "idle";
  strip.dataset.replayChipLayout = summary.chip_layout;
  strip.dataset.replayOverflowGuard = summary.overflow_guard;
  qs("#qa-replay-state").textContent = summary.active ? (summary.ignored > 0 ? "partial replay" : "replay active") : "no replay";
  qs("#qa-replay-summary").textContent =
    `${summary.requested} requested / ${summary.applied} applied / ${summary.ignored} ignored / chips ${summary.visible_chips}/${summary.visible_chips + summary.hidden_chips}`;
  qs("#qa-replay-boundary").textContent = `production=${summary.production_evidence_claim} main=${summary.main_gui_mutation_required} edge=${summary.edge_gui_mutation_required}`;

  const chips = qs("#qa-replay-chips");
  chips.innerHTML = "";
  chips.dataset.replayVisibleCount = String(summary.visible_chips);
  chips.dataset.replayHiddenCount = String(summary.hidden_chips);
  visible.rows.forEach((row) => {
    const chip = document.createElement("span");
    chip.className = "qa-replay-chip";
    chip.dataset.replayParamStatus = row.status;
    const label = document.createElement("strong");
    label.textContent = row.label;
    const value = document.createElement("code");
    value.textContent = row.requested ? `${row.requested_value} -> ${row.applied_value}` : row.status;
    chip.append(label, value);
    chips.append(chip);
  });
  if (summary.hidden_chips > 0) {
    const summaryChip = document.createElement("span");
    summaryChip.className = "qa-replay-chip";
    summaryChip.dataset.replayParamStatus = "summary";
    const label = document.createElement("strong");
    label.textContent = "More";
    const value = document.createElement("code");
    value.textContent = `${summary.hidden_chips} retained in receipt rows`;
    summaryChip.append(label, value);
    chips.append(summaryChip);
  }
}

function renderVisualIdentityPanel() {
  const rows = visualIdentityRows();
  const summary = visualIdentitySummary(rows);
  const panel = qs("#visual-identity-panel");
  if (panel instanceof HTMLElement) {
    panel.dataset.visualState = summary.state;
  }
  qs("#visual-identity-title").textContent = summary.title;
  qs("#visual-identity-asset-state").textContent =
    summary.asset_size === "pending" ? summary.asset_status : `${summary.asset_status} ${summary.asset_size}`;
  qs("#visual-identity-brand-state").textContent = summary.brand_status;
  qs("#visual-identity-boundary-state").textContent =
    `main ${summary.main_gui_mutation_required} / edge ${summary.edge_gui_mutation_required}`;
  qs("#visual-identity-boundary").textContent = summary.boundary;
}

function renderInspectorLiveEvidence() {
  const rows = inspectorLiveEvidenceRows();
  const summary = inspectorLiveEvidenceSummary(rows);
  const card = qs("#inspector-live-evidence");
  if (card instanceof HTMLElement) {
    card.dataset.liveEvidenceState = summary.state;
  }
  const badge = qs("#inspector-live-evidence-count");
  badge.textContent = String(summary.visible_count);
  badge.classList.toggle("ok", summary.state === "ready" || summary.state === "review");
  badge.classList.toggle("stop", summary.state === "blocked");
  qs("#inspector-live-evidence-title").textContent = summary.title;

  const mini = qs("#mini-log");
  mini.innerHTML = "";
  rows.slice(0, 5).forEach((row) => {
    const line = document.createElement("p");
    line.dataset.liveEvidenceKey = row.key;
    line.dataset.liveEvidenceStatus = row.status;
    line.textContent = `${row.label}=${row.value}`;
    mini.append(line);
  });
  qs("#inspector-live-evidence-boundary").textContent =
    `production=${summary.production_evidence_claim} / runtime=${summary.runtime_enforcement_authority} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
}

function renderContextInspector() {
  const summary = contextInspectorSummary();
  qs("#context-live-evidence").textContent =
    `${summary.live_evidence_state}: ${summary.live_evidence_visible}/${summary.live_evidence_total} visible / guarded ${summary.live_evidence_guarded} / latest ${summary.live_evidence_latest} / zero authority ${summary.live_evidence_zero_authority ? "yes" : "no"}`;
  qs("#context-active-tab").textContent = summary.active_tab;
  qs("#context-brand-emblem").textContent =
    `${summary.brand_emblem_status} / ${summary.brand_emblem_intrinsic_size} / ${summary.brand_metadata_status}`;
  qs("#context-visual-identity").textContent =
    `${summary.visual_identity_state}: asset ${summary.visual_identity_asset_status} / brand ${summary.visual_identity_brand_status} / zero authority ${summary.visual_identity_zero_authority ? "yes" : "no"}`;
  qs("#context-action-rail").textContent =
    `${summary.primary_action_rail_status}: ${summary.primary_action_count} actions / ${summary.primary_action_iconized_count} icons / primary ${summary.primary_action_key}`;
  qs("#context-posture-strip").textContent =
    `${summary.posture_ready} ready / ${summary.posture_guarded} guarded / ${summary.posture_blocked} blocked / layout ${summary.posture_layout_stable ? "stable" : "review"} / zero authority ${summary.posture_zero_authority ? "yes" : "no"}`;
  qs("#context-component-health").textContent =
    `${summary.component_health_state}: ${summary.component_health_selected}/${summary.component_health_total} selected / core ${summary.component_health_core_coverage} / omitted ${summary.component_health_omitted} / zero authority ${summary.component_health_zero_authority ? "yes" : "no"}`;
  qs("#context-workspace-route").textContent =
    `${summary.workspace_route_tab} / ${summary.workspace_route_profile} / detail ${summary.workspace_route_detail} ${summary.workspace_route_detail_label.toLowerCase()} / ${summary.workspace_route_boundary}`;
  qs("#context-profile-scope").textContent =
    `${summary.profile_scope_label}: ${summary.profile_scope_text}`;
  qs("#context-readiness-rail").textContent =
    `${summary.readiness_rail_score}% / ${summary.readiness_rail_label} / gate ${summary.readiness_rail_gate}`;
  qs("#context-production-gates").textContent =
    `${summary.quality_gate_decision}: ${summary.quality_gate_verified} verified / ${summary.quality_gate_pending} pending / promote ${summary.quality_gate_can_promote ? "yes" : "no"}`;
  qs("#context-dashboard-authority").textContent =
    `${summary.dashboard_authority_badge}: host ${summary.dashboard_authority_host_scope} / ${summary.dashboard_authority_blocked} blocked / production zero ${summary.dashboard_authority_production_zero ? "yes" : "no"}`;
  qs("#context-run-monitor").textContent =
    `${summary.run_monitor_status}: ${summary.run_monitor_progress}% / prefix ${summary.run_monitor_prefix_guard} / runtime ${summary.run_monitor_runtime_authority}`;
  qs("#context-operator-workflow").textContent =
    `${summary.operator_workflow_state}: ${summary.operator_workflow_complete} complete / ${summary.operator_workflow_current} current / ${summary.operator_workflow_blocked} blocked / next ${summary.operator_workflow_next}`;
  qs("#context-delivery-plan").textContent =
    `${summary.delivery_plan_state}: ${summary.delivery_plan_components} components / ${summary.delivery_plan_mode} / prefix ${summary.delivery_plan_prefix_guard} / zero authority ${summary.delivery_plan_zero_authority ? "yes" : "no"}`;
  qs("#context-updater-gate").textContent =
    `${summary.updater_gate_state}: ${summary.updater_gate_blocked}/${summary.updater_gate_required} blocked / preview ${summary.updater_gate_preview_status} / apply ${summary.updater_gate_can_apply ? "yes" : "no"} / zero authority ${summary.updater_gate_zero_authority ? "yes" : "no"}`;
  qs("#context-promotion-gate").textContent = `${summary.promotion_gate} / ${summary.promotion_status}`;
  qs("#context-production-blocker").textContent =
    `${summary.production_blocker} / ${summary.production_blocker_status} / ${summary.production_blocker_visible}/${summary.production_blocker_total} visible / filter ${summary.production_blocker_filter}`;
  qs("#context-release-acceptance").textContent = `${summary.release_acceptance} / ${summary.release_acceptance_status}`;
  qs("#context-readiness-compare").textContent = `${summary.readiness_compare} / ${summary.readiness_compare_status}`;
  qs("#context-compare-alignment").textContent =
    `${summary.compare_alignment_status}: ${summary.compare_alignment_aligned} aligned, ${summary.compare_alignment_review} review`;
  qs("#context-readiness-trace").textContent = `${summary.readiness_trace} / ${summary.readiness_trace_status}`;
  qs("#context-trace-alignment").textContent =
    `${summary.trace_alignment_status}: ${summary.trace_alignment_aligned} aligned, ${summary.trace_alignment_review} review`;
  qs("#context-evidence-queue").textContent =
    `${summary.evidence_queue_state}: ${summary.evidence_queue_visible}/${summary.evidence_queue_total} visible / guarded ${summary.evidence_queue_guarded} / filter ${summary.evidence_queue_filter} / zero authority ${summary.evidence_queue_zero_authority ? "yes" : "no"}`;
  qs("#context-event-trail").textContent =
    `${summary.event_trail_state}: ${summary.event_trail_total} events / blocked ${summary.event_trail_blocked} / latest ${summary.event_trail_latest} / zero authority ${summary.event_trail_zero_authority ? "yes" : "no"}`;
  qs("#context-receipt-preview").textContent =
    `${summary.receipt_preview_state}: ${summary.receipt_preview_schema} / events ${summary.receipt_preview_events} / checklist ${summary.receipt_preview_checklist} / ${summary.receipt_preview_scope} / zero authority ${summary.receipt_preview_zero_authority ? "yes" : "no"}`;
  qs("#context-qa-replay").textContent =
    summary.qa_replay_state === "none"
      ? "none"
      : `${summary.qa_replay_state}: ${summary.qa_replay_requested} requested, ${summary.qa_replay_ignored} ignored, chips ${summary.qa_replay_visible_chips}/${summary.qa_replay_visible_chips + summary.qa_replay_hidden_chips}, ${summary.qa_replay_overflow_guard}`;
  qs("#context-saved-receipt").textContent =
    `${summary.saved_receipt_trust_state}: ${summary.saved_receipt_trust_count} saved / selected ${summary.saved_receipt_trust_selected} / diff ${summary.saved_receipt_trust_diff} / export ${summary.saved_receipt_trust_export} / zero authority ${summary.saved_receipt_trust_zero_authority ? "yes" : "no"}`;
}

function renderWorkspaceRoute() {
  workspaceRouteRows().forEach((row) => {
    const chip = qs(`[data-route-chip="${row.key}"]`);
    if (chip) {
      chip.textContent = row.display;
    }
  });
}

function renderReadinessRail() {
  const summary = readinessRailState();
  const rail = qs("#readiness-rail");
  if (rail instanceof HTMLElement) {
    rail.dataset.readinessBand = summary.band;
  }
  const score = qs("#readiness-score");
  if (score) {
    score.textContent = `${summary.score}%`;
  }
  const band = qs("#readiness-band");
  if (band) {
    band.textContent = summary.label;
  }
  const meter = qs("#readiness-meter");
  if (meter instanceof HTMLElement) {
    meter.style.width = `${summary.score}%`;
    meter.dataset.readinessBand = summary.band;
  }
  qs("#rail-mode").textContent = summary.mode;
  qs("#rail-writes").textContent = summary.writes;
  qs("#rail-gate").textContent = summary.gate;
}

function renderDashboardAuthorityCard() {
  const rows = dashboardAuthorityRows();
  const summary = dashboardAuthoritySummary(rows);
  const card = qs("#dashboard-authority-card");
  if (card instanceof HTMLElement) {
    card.dataset.authorityDecision = summary.decision;
  }
  qs("#dashboard-authority-title").textContent = `${summary.blocked} blocked, ${summary.user_local_state} writes`;
  const badge = qs("#dashboard-authority-badge");
  badge.textContent = summary.badge;
  badge.classList.toggle("ok", summary.decision === "user_local_armed");
  badge.classList.toggle("warn", summary.user_local_state === "guarded");
  badge.classList.toggle("stop", summary.decision === "locked");
  qs("#dashboard-authority-allowed").textContent = String(summary.allowed);
  qs("#dashboard-authority-local").textContent = String(summary.local_scope);
  qs("#dashboard-authority-blocked").textContent = String(summary.blocked);
  qs("#host-write-fact").textContent = String(summary.host_write_scope);
  qs("#dashboard-authority-boundary").textContent =
    `host=${summary.host_write_scope} / root=${summary.root_authority} / network=${summary.network_authority} / runtime=${summary.runtime_enforcement_authority} / production=${summary.production_evidence_claim}`;

  const list = qs("#dashboard-authority-list");
  list.innerHTML = "";
  rows.forEach((row) => {
    const item = document.createElement("div");
    item.dataset.authorityKey = row.key;
    item.dataset.authorityState = row.status;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${dashboardAuthorityTone(row.status)}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "authority-row-detail";
    const label = document.createElement("strong");
    label.textContent = row.label;
    const note = document.createElement("small");
    note.textContent = row.detail;
    if (row.key === "user_local_writes") {
      note.id = "local-write-row";
    }
    detail.append(label, note);

    const status = document.createElement("span");
    status.className = `badge ${dashboardAuthorityTone(row.status)} authority-state`;
    status.textContent = row.status;

    item.append(swatch, detail, status);
    list.append(item);
  });
}

function renderRunMonitorState() {
  const summary = runMonitorSummary();
  const monitor = qs("#run-monitor");
  if (monitor instanceof HTMLElement) {
    monitor.dataset.runState = summary.status;
    monitor.dataset.prefixGuard = summary.prefix_guard;
  }
  const badge = qs("#run-badge");
  if (badge) {
    badge.className = `badge ${runMonitorTone(summary.status)}`;
    badge.textContent = summary.status;
  }
  qs("#run-monitor-state").textContent = summary.status;
  qs("#run-monitor-prefix").textContent = summary.prefix_guard;
  qs("#run-monitor-runtime").textContent = String(summary.runtime_authority);
  qs("#run-monitor-boundary").textContent =
    `runtime=${summary.runtime_authority} / production=${summary.production_evidence_claim} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
}

function renderOperatorWorkflow() {
  const rows = operatorWorkflowRows();
  const summary = operatorWorkflowSummary(rows);
  const card = qs("#operator-workflow-card");
  if (card instanceof HTMLElement) {
    card.dataset.workflowState = summary.state;
  }
  qs("#operator-workflow-title").textContent =
    summary.state === "guarded_local_ready"
      ? "Guarded local is available for review"
      : summary.state === "ready_for_receipt"
        ? "Receipt evidence is ready to inspect"
        : "Plan, dry-run, then inspect receipts";
  const badge = qs("#operator-workflow-badge");
  badge.className = `badge ${operatorWorkflowTone(summary.blocked > 1 ? "blocked" : summary.available > 0 ? "available" : "current")}`;
  badge.textContent = summary.next_label.toLowerCase();
  qs("#operator-workflow-done").textContent = String(summary.complete);
  qs("#operator-workflow-current").textContent = String(summary.current + summary.available);
  qs("#operator-workflow-blocked").textContent = String(summary.blocked);
  qs("#operator-workflow-boundary").textContent =
    `production=${summary.production_evidence_claim} / runtime=${summary.runtime_authority} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;

  rows.forEach((row) => {
    const item = qs(`[data-workflow-step="${row.key}"]`);
    if (!(item instanceof HTMLElement)) {
      return;
    }
    item.dataset.stepState = row.status;
    item.classList.toggle("is-done", row.status === "complete" || row.status === "available");
    item.classList.toggle("is-current", row.status === "current");
    const domKey = row.key === "plan_review" ? "plan" : row.key === "dry_install" ? "run" : row.key === "guarded_local" ? "local" : "profile";
    const detail = row.key === "profile" ? qs("#step-profile") : qs(`#workflow-${domKey}-detail`);
    if (detail) {
      detail.textContent = row.detail;
    }
    const state = qs(`#workflow-${domKey}-state`);
    if (state) {
      state.textContent = row.status;
    }
  });
}

function renderEvidenceDetailControl() {
  const detail = evidenceDetailState();
  const range = qs("#detail-range");
  if (range instanceof HTMLInputElement) {
    range.value = String(detail.level);
    range.dataset.detailLevel = detail.key;
    range.setAttribute("aria-valuetext", `${detail.label} evidence detail`);
  }
  const output = qs("#detail-range-status");
  if (output) {
    output.textContent = `${detail.label} evidence`;
  }
  const surface = qs(".workspace-surface");
  if (surface instanceof HTMLElement) {
    surface.dataset.evidenceDetail = detail.key;
  }
}

function renderProfileScopeControl() {
  const scope = profileScopeState();
  const select = qs("#profile-select");
  if (select instanceof HTMLSelectElement) {
    select.dataset.profileScope = scope.key;
  }
  const status = qs("#profile-scope-status");
  if (status) {
    status.textContent = scope.scope;
  }
  const surface = qs(".workspace-surface");
  if (surface instanceof HTMLElement) {
    surface.dataset.profileScope = scope.key;
  }
}

function renderWorkspacePostureStrip() {
  const rows = workspacePostureRows();
  rows.forEach((row) => {
    const card = qs(`[data-posture-key="${row.key}"]`);
    if (!(card instanceof HTMLElement)) {
      return;
    }
    card.dataset.postureState = row.state;
    const detail = card.querySelector("small");
    if (detail) {
      detail.textContent = row.detail;
    }
    const badge = card.querySelector(".status-card-badge");
    if (badge) {
      badge.textContent = row.badge;
    }
    const dot = card.querySelector(".status-dot");
    if (dot) {
      dot.className = `status-dot ${row.state === "ready" || row.state === "armed" ? "ok" : row.state === "guarded" ? "warn" : "stop"}`;
    }
  });
}

function operatorFocusDockRows() {
  const blocker = selectedProductionBlockerRow();
  const acceptance = selectedReleaseAcceptanceRow();
  const compare = selectedReadinessComparisonRow();
  const compareAlignment = readinessComparisonAlignmentSummary();
  const trace = selectedTraceabilityRow();
  const traceAlignment = traceabilityAlignmentSummary();
  const palette = selectedCommandPaletteItem(commandPaletteVisibleRows());
  const saved = selectedSavedReceipt();
  return [
    {
      key: "active_tab",
      label: "tab",
      value: state.activeTab,
      detail: "workspace route",
      status: "local",
      tab: state.activeTab,
      target: "workspace_tab",
      target_key: state.activeTab,
    },
    {
      key: "readiness_compare",
      label: "compare",
      value: compare?.label || "none",
      detail: compare?.owner || "readiness review",
      status: compare?.status || "none",
      tab: "readiness",
      target: "readiness_compare",
      target_key: compare?.key || "none",
    },
    {
      key: "compare_alignment",
      label: "compare align",
      value: compareAlignment.action_label,
      detail: `${compareAlignment.aligned} aligned / ${compareAlignment.review} review`,
      status: compareAlignment.review > 0 ? "review" : "aligned",
      tab: "readiness",
      target: "compare_alignment",
      target_key: compare?.key || "none",
    },
    {
      key: "production_blocker",
      label: "blocker",
      value: blocker?.label || "none",
      detail: blocker?.owner || "release evidence",
      status: blocker?.status || "none",
      tab: "readiness",
      target: "production_blocker",
      target_key: blocker?.key || "none",
    },
    {
      key: "release_acceptance",
      label: "acceptance",
      value: acceptance?.label || "none",
      detail: acceptance?.owner || "release QA",
      status: acceptance?.status || "none",
      tab: "review",
      target: "release_acceptance",
      target_key: acceptance?.key || "none",
    },
    {
      key: "readiness_trace",
      label: "trace",
      value: trace?.label || "none",
      detail: trace ? `${traceAlignment.aligned}/${traceAlignment.total} aligned` : "no selected trace",
      status: trace?.status || "none",
      tab: "readiness",
      target: "traceability",
      target_key: trace?.key || "none",
    },
    {
      key: "trace_alignment",
      label: "alignment",
      value: traceAlignment.action_label,
      detail: `${traceAlignment.aligned} aligned / ${traceAlignment.review} review`,
      status: traceAlignment.review > 0 ? "review" : "aligned",
      tab: "readiness",
      target: "trace_alignment",
      target_key: trace?.key || "none",
    },
    {
      key: "command_palette",
      label: "palette",
      value: palette?.label || "none",
      detail: palette?.kind || "jump",
      status: palette?.status || "empty",
      tab: "console",
      target: "command_palette",
      target_key: palette?.key || "none",
    },
    {
      key: "saved_receipt",
      label: "receipt",
      value: saved?.label || "none",
      detail: saved?.saved_at || "local snapshot",
      status: saved ? "saved" : "empty",
      tab: "evidence",
      target: "saved_receipt",
      target_key: saved?.id || "none",
    },
  ].map((row) => ({
    ...row,
    local_only: true,
    host_write_authority: 0,
    shell_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function operatorFocusDockSummary(rows = operatorFocusDockRows()) {
  return {
    total: rows.length,
    actionable: rows.filter((row) => row.target_key !== "none").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    pending: rows.filter((row) => row.status === "pending" || row.status === "needs binding" || row.status === "empty").length,
    active_tab: state.activeTab,
    local_only: rows.every((row) => row.local_only),
    host_write_authority: 0,
    shell_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function renderOperatorFocusDock() {
  const dock = qs("#focus-dock-items");
  if (!dock) {
    return;
  }
  const rows = operatorFocusDockRows();
  const summary = operatorFocusDockSummary(rows);
  qs("#focus-dock-summary").textContent = `${summary.actionable} selected review targets`;
  qs("#focus-dock-boundary").textContent =
    `production=${summary.production_evidence_claim} host=${summary.host_write_authority} main=${summary.main_gui_mutation_required} edge=${summary.edge_gui_mutation_required}`;
  dock.innerHTML = "";
  rows.forEach((row) => {
    const button = document.createElement("button");
    button.type = "button";
    button.className = "focus-dock-button";
    button.dataset.focusDock = row.key;
    button.dataset.focusStatus = row.status;
    button.setAttribute("aria-label", `${row.label}: ${row.value}. ${row.detail}. ${row.status}.`);

    const label = document.createElement("span");
    label.textContent = row.label;
    const value = document.createElement("strong");
    value.textContent = row.value;
    const detail = document.createElement("code");
    detail.textContent = `${row.status} / ${row.detail}`;
    button.append(label, value, detail);
    dock.append(button);
  });
}

function activateOperatorFocusDockRow(key) {
  const row = operatorFocusDockRows().find((item) => item.key === key);
  if (!row || row.target_key === "none") {
    assistiveStatus("No local target is selected for that focus dock item.");
    return;
  }
  setTab(row.tab);
  if (row.target === "production_blocker") {
    setProductionBlockerSelection(row.target_key, false, true);
  } else if (row.target === "readiness_compare") {
    setReadinessCompareSelection(row.target_key, false, true);
  } else if (row.target === "compare_alignment") {
    setReadinessCompareSelection(row.target_key, false, false);
    requestAnimationFrame(() => {
      qs("[data-action='align-readiness-compare-context']")?.focus({ preventScroll: true });
    });
  } else if (row.target === "release_acceptance") {
    setReleaseAcceptanceSelection(row.target_key, false, true);
  } else if (row.target === "traceability") {
    setTraceabilitySelection(row.target_key, false, true);
  } else if (row.target === "trace_alignment") {
    setTraceabilitySelection(row.target_key, false, false);
    requestAnimationFrame(() => {
      qs("[data-action='align-trace-context']")?.focus({ preventScroll: true });
    });
  } else if (row.target === "command_palette") {
    setCommandPaletteSelection(row.target_key, false, true);
  } else if (row.target === "saved_receipt") {
    selectSavedReceipt(row.target_key, false, true);
  } else if (row.target === "workspace_tab") {
    qs(`[data-tab="${row.target_key}"]`)?.focus({ preventScroll: true });
  }
  assistiveStatus(`Focus dock opened ${row.label} ${row.value}.`);
  recordEvent("Focus dock jump", `${row.target}=${row.target_key} tab=${row.tab}`);
  safeWriteState();
}

function renderCommandPalette() {
  const input = qs("#palette-search");
  const list = qs("#palette-results");
  if (!input || !list) {
    return;
  }
  const rows = commandPaletteVisibleRows();
  const selected = selectedCommandPaletteItem(rows);
  state.paletteSelection = selected?.key || "";
  input.value = state.paletteQuery;
  input.setAttribute("aria-activedescendant", selected ? commandPaletteOptionId(selected.key) : "");
  qs("#palette-count").textContent = `${rows.length}`;
  qs("#palette-status").textContent =
    rows.length === 0
      ? "no local targets match"
      : `showing ${Math.min(rows.length, COMMAND_PALETTE_RESULT_LIMIT)} of ${rows.length} local targets`;

  list.innerHTML = "";
  rows.slice(0, COMMAND_PALETTE_RESULT_LIMIT).forEach((row) => {
    const option = document.createElement("button");
    option.type = "button";
    option.className = "palette-row";
    option.classList.toggle("is-selected", row.key === state.paletteSelection);
    option.id = commandPaletteOptionId(row.key);
    option.dataset.paletteAction = row.key;
    option.setAttribute("role", "option");
    option.setAttribute("aria-selected", String(row.key === state.paletteSelection));
    option.tabIndex = row.key === state.paletteSelection ? 0 : -1;

    const detail = document.createElement("span");
    detail.className = "palette-row-detail";
    const label = document.createElement("strong");
    label.textContent = row.label;
    const route = document.createElement("small");
    route.textContent = `${row.kind} / ${row.tab}`;
    const evidence = document.createElement("code");
    evidence.textContent = row.evidence;
    detail.append(label, route, evidence);

    const kind = document.createElement("span");
    kind.className = `badge palette-kind ${commandPaletteTone(row.status)}`;
    kind.textContent = row.status;

    option.append(detail, kind);
    list.append(option);
  });
}

function setCommandPaletteSelection(key, announce = false, focusAfterRender = false) {
  if (!isCommandPaletteKey(key)) {
    return;
  }
  state.paletteSelection = key;
  renderCommandPalette();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-palette-action]", "paletteAction", key);
  }
  if (announce) {
    const selected = commandPaletteItems().find((row) => row.key === key);
    assistiveStatus(`Palette target ${selected?.label || key} selected.`);
  }
}

function moveCommandPaletteFocus(currentButton, direction) {
  const buttons = qsa("[data-palette-action]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0 || buttons.length === 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setCommandPaletteSelection(next.dataset.paletteAction, true, true);
}

function focusCommandPaletteSelection() {
  const rows = commandPaletteVisibleRows();
  const selected = selectedCommandPaletteItem(rows);
  if (!selected) {
    return;
  }
  setCommandPaletteSelection(selected.key, true, true);
}

function activateCommandPaletteItem(key) {
  const item = commandPaletteItems().find((row) => row.key === key);
  if (!item) {
    return;
  }
  state.paletteSelection = item.key;
  renderCommandPalette();
  renderReceiptPreview();

  if (item.kind === "command") {
    setTab("console");
    qs("#console-input").value = item.command;
    runCommand(item.command);
    recordEvent("Palette command", `command=${item.command}`);
    return;
  }

  setTab(item.tab);
  if (item.target === "promotion_gate") {
    setPromotionGateSelection(item.target_key, false, true);
  } else if (item.target === "production_blocker") {
    setProductionBlockerSelection(item.target_key, false, true);
  } else if (item.target === "readiness_compare") {
    setReadinessCompareSelection(item.target_key, false, true);
  } else if (item.target === "evidence_intake") {
    setEvidenceIntakeSelection(item.target_key, false, true);
  } else if (item.target === "traceability") {
    setTraceabilitySelection(item.target_key, false, true);
  } else if (item.target === "migration_review") {
    setMigrationReviewSelection(item.target_key, false, true);
  } else if (item.target === "qa_scenario") {
    setQaScenarioSelection(item.target_key, false, true);
  } else if (item.target === "engine_binding") {
    setEngineBindingSelection(item.target_key, false, true);
  } else if (item.target === "visual_baseline") {
    setVisualBaselineSelection(item.target_key, false, true);
  } else if (item.target === "release_acceptance") {
    setReleaseAcceptanceSelection(item.target_key, false, true);
  } else if (item.target === "accessibility_audit") {
    setAccessibilityAuditSelection(item.target_key, false, true);
  }

  assistiveStatus(`Palette jumped to ${item.label}. ${item.status}.`);
  recordEvent("Palette jump", `${item.target}=${item.target_key} tab=${item.tab}`);
  notify("Palette jump complete");
  safeWriteState();
}

function buildReceiptPreview() {
  const selectedSnapshot = selectedSavedReceipt();
  const traceAlignmentRows = traceabilityAlignmentRows();
  const traceAlignmentSummary = traceabilityAlignmentSummary(traceAlignmentRows);
  const receipt = {
    schema: "latticra-panel-test-ui-receipt-v0",
    lane: "isolated-test-ui",
    generated_at: nowStamp(),
    active_tab: state.activeTab,
    profile: state.profile,
    profile_scope: profileScopeSummary(),
    mode: state.mode === "dry" ? "dry-run" : "guarded-local",
    prefix: state.prefix,
    prefix_guard: state.prefixValid ? "accepted" : "blocked",
    evidence_detail: evidenceDetailSummary(),
    readiness_rail: {
      summary: readinessRailSummary(),
      rows: readinessRailRows(),
    },
    qa_replay: {
      summary: qaReplaySummary(),
      rows: qaReplayRows(),
    },
    brand_emblem: brandEmblemState(),
    visual_identity_panel: {
      summary: visualIdentitySummary(),
      rows: visualIdentityRows(),
    },
    primary_action_rail: {
      summary: primaryActionRailSummary(),
      rows: primaryActionRailRows(),
    },
    workspace_posture: {
      summary: workspacePostureSummary(),
      rows: workspacePostureRows(),
    },
    workspace_route: {
      summary: workspaceRouteSummary(),
      rows: workspaceRouteRows(),
    },
    component_health: {
      summary: componentHealthSummary(),
      rows: componentHealthRows(),
    },
    delivery_plan: {
      summary: deliveryPlanSummary(),
      rows: deliveryPlanRows(),
    },
    signed_updater_gate: {
      summary: updaterGateSummary(),
      rows: updaterGateRows(),
    },
    evidence_queue: {
      summary: evidenceQueueSummary(),
      rows: evidenceQueueRows(),
    },
    event_trail: {
      summary: eventTrailSummary(),
      rows: eventTrailRows().slice(0, 6),
    },
    receipt_preview_state: {
      summary: receiptPreviewSummary(),
      rows: receiptPreviewRows(),
    },
    inspector_live_evidence: {
      summary: inspectorLiveEvidenceSummary(),
      rows: inspectorLiveEvidenceRows(),
    },
    context_inspector: contextInspectorSummary(),
    operator_focus_dock: {
      summary: operatorFocusDockSummary(),
      rows: operatorFocusDockRows(),
    },
    command_palette: {
      summary: commandPaletteSummary(),
      rows: commandPaletteReceiptRows(),
    },
    readiness_comparison: {
      summary: readinessComparisonSummary(),
      rows: readinessComparisonRows(),
      selected: selectedReadinessComparisonRow(),
      proof: {
        summary: readinessComparisonProofSummary(),
        rows: readinessComparisonProofRows(),
      },
      alignment: {
        summary: readinessComparisonAlignmentSummary(),
        rows: readinessComparisonAlignmentRows(),
      },
    },
    release_evidence_intake: {
      summary: evidenceIntakeSummary(),
      rows: evidenceIntakeRows(),
      selected: selectedEvidenceIntakeRow(),
      contract: {
        summary: evidenceIntakeContractSummary(),
        rows: evidenceIntakeContractRows(),
      },
    },
    readiness_traceability: {
      summary: traceabilitySummary(),
      rows: traceabilityRows(),
      selected: selectedTraceabilityRow(),
      alignment: {
        summary: traceAlignmentSummary,
        rows: traceAlignmentRows,
        action_state: traceAlignmentSummary.action_state,
        action_label: traceAlignmentSummary.action_label,
      },
    },
    selected_components: selectedComponents().map((component) => component.id),
    component_count: selectedComponents().length,
    receipt_checklist: {
      summary: receiptChecklistSummary(),
      items: receiptChecklistRows().map((row) => ({
        id: row.id,
        label: row.label,
        status: row.status,
        recorded: row.recorded,
        source: row.source,
        note: row.note,
      })),
    },
    schema_provenance: schemaStatusSummary(),
    console: {
      status: state.consoleStatus,
      message: state.consoleMessage,
      last_command: state.consoleLastCommand || "none",
      allowlist_enforced: true,
      blocked_commands_mutate_execution_state: false,
    },
    production_quality_gates: {
      summary: qualityGateSummary(),
      rows: qualityGateRows(),
    },
    dashboard_authority: {
      summary: dashboardAuthoritySummary(),
      rows: dashboardAuthorityRows(),
    },
    run_monitor: {
      summary: runMonitorSummary(),
      rows: runMonitorRows(),
    },
    operator_workflow: {
      summary: operatorWorkflowSummary(),
      rows: operatorWorkflowRows(),
    },
    authority: {
      root_authority: 0,
      network_authority: 0,
      runtime_enforcement_authority: 0,
      production_installer_claim: 0,
      main_gui_mutation_required: 0,
      edge_gui_mutation_required: 0,
    },
    evidence_matrix: {
      summary: evidenceMatrixSummary(),
      rows: evidenceMatrixRows(),
    },
    migration_review: {
      summary: migrationReviewSummary(),
      rows: migrationReviewRows(),
      selected: selectedMigrationReviewRow(),
      parity: {
        summary: migrationParitySummary(),
        rows: migrationParityRows(),
      },
    },
    qa_runbook: {
      summary: qaScenarioSummary(),
      rows: qaScenarioRows(),
      selected: selectedQaScenarioRow(),
    },
    installer_engine_binding: {
      summary: engineBindingSummary(),
      rows: engineBindingRows(),
      selected: selectedEngineBindingRow(),
      contract: {
        summary: engineBindingContractSummary(),
        rows: engineBindingContractRows(),
      },
      event_adapter: {
        summary: engineEventAdapterSummary(),
        rows: engineEventAdapterRows(),
      },
    },
    visual_baseline: {
      summary: visualBaselineSummary(),
      rows: visualBaselineRows(),
      selected: selectedVisualBaselineRow(),
    },
    release_acceptance: {
      summary: releaseAcceptanceSummary(),
      rows: releaseAcceptanceRows(),
      selected: selectedReleaseAcceptanceRow(),
    },
    promotion_gate: {
      summary: promotionGateSummary(),
      rows: promotionGateRows(),
      selected: selectedPromotionGateRow(),
    },
    production_blocker_drilldown: {
      summary: productionBlockerSummary(),
      rows: productionBlockerRows(),
      selected: selectedProductionBlockerRow(),
      proof: {
        summary: productionBlockerProofSummary(),
        rows: productionBlockerProofRows(),
      },
    },
    accessibility_audit: {
      summary: accessibilityAuditSummary(),
      rows: accessibilityAuditRows(),
      selected: selectedAccessibilityAuditRow(),
    },
    review_filter: state.reviewFilter,
    saved_receipts: {
      count: state.savedReceipts.length,
      limit: SAVED_RECEIPT_LIMIT,
      retention_policy: "latest-local-no-effect-snapshots",
      selected_id: state.selectedReceiptId || "none",
      selected_label: selectedSnapshot ? selectedSnapshot.label : "none",
      local_only: true,
      cleanup_only_mutates_test_lane_state: true,
      field_diff_ready: Boolean(selectedSnapshot),
      field_diff_row_count: selectedSnapshot ? receiptDiffFields.length : 0,
      field_diff_filter: state.receiptDiffFilter,
      context_drift_ready: Boolean(selectedSnapshot),
      context_drift_status: "none",
      context_drift_changed: 0,
      context_drift_total: 0,
      context_drift_selected_compare: "none",
      context_drift_selected_trace: "none",
      context_drift_selected_blocker: "none",
      context_drift_handoff_scope_source: "none",
      export_validation_ready: false,
      export_validation_status: "blocked",
      export_validation_passed: 0,
      export_validation_total: 0,
      export_integrity_digest: "none",
      export_preview_watermark: "NOT PRODUCTION EVIDENCE",
      export_preview_ready: Boolean(selectedSnapshot),
      qa_handoff_ready: false,
      qa_handoff_schema: "latticra-panel-test-ui-qa-handoff-v0",
      qa_handoff_url: "none",
      qa_handoff_export_validation_status: "blocked",
      qa_handoff_context_drift_status: "none",
      qa_handoff_context_drift_changed: 0,
      qa_handoff_context_drift_total: 0,
      qa_handoff_scope_status: "blocked",
      qa_handoff_scope_passed: 0,
      qa_handoff_scope_total: 0,
      qa_handoff_scope_selected_compare: "none",
      qa_handoff_scope_selected_trace: "none",
      qa_handoff_scope_selected_blocker: "none",
      qa_handoff_validation_status: "blocked",
      qa_handoff_validation_passed: 0,
      qa_handoff_validation_total: 0,
      qa_handoff_replay_snapshot_id: selectedSnapshot ? selectedSnapshot.id : "none",
      qa_handoff_replay_digest: "none",
      qa_handoff_replay_request_status: "none",
      qa_handoff_replay_requested_snapshot_id: "none",
      qa_handoff_replay_requested_digest: "none",
      qa_handoff_replay_local_snapshot_status: "none",
      qa_handoff_replay_restored: false,
      qa_handoff_replay_digest_status: "none",
      qa_handoff_local_only: true,
      trust_summary: savedReceiptTrustSummary(savedReceiptTrustRows(selectedSnapshot, null, null)),
      trust_rows: savedReceiptTrustRows(selectedSnapshot, null, null),
    },
    event_count: state.events.length,
    recent_events: state.events.slice(-6),
    accessibility: {
      assistive_status_present: true,
      decorative_status_hidden: true,
      active_tab_announcement: state.activeTab,
      mode_roving_tabindex: true,
      mode_keyboard_navigation: true,
      component_toggle_descriptions: true,
      component_toggle_focus_visible: true,
      console_status_surface: true,
      console_blocked_focus_recovery: true,
    },
  };
  const selectedArtifact = selectedSnapshot ? buildReceiptExportArtifact(selectedSnapshot, receipt) : null;
  const selectedTrustRows = savedReceiptTrustRows(selectedSnapshot, receipt, selectedArtifact);
  receipt.saved_receipts.trust_summary = savedReceiptTrustSummary(selectedTrustRows);
  receipt.saved_receipts.trust_rows = selectedTrustRows;
  const selectedContextDrift = selectedArtifact?.context_drift || receiptContextDriftSummary(null, receipt);
  receipt.saved_receipts.context_drift_status = selectedContextDrift.status;
  receipt.saved_receipts.context_drift_changed = selectedContextDrift.changed_count;
  receipt.saved_receipts.context_drift_total = selectedContextDrift.row_count;
  receipt.saved_receipts.context_drift_selected_compare = selectedContextDrift.selected_compare;
  receipt.saved_receipts.context_drift_selected_trace = selectedContextDrift.selected_trace;
  receipt.saved_receipts.context_drift_selected_blocker = selectedContextDrift.selected_blocker;
  receipt.saved_receipts.context_drift_handoff_scope_source = selectedContextDrift.handoff_scope_source;
  const selectedExportValidation = exportValidationSummary(selectedArtifact);
  receipt.saved_receipts.export_validation_ready = Boolean(selectedArtifact);
  receipt.saved_receipts.export_validation_status = selectedExportValidation.status;
  receipt.saved_receipts.export_validation_passed = selectedExportValidation.passed;
  receipt.saved_receipts.export_validation_total = selectedExportValidation.total;
  receipt.saved_receipts.export_integrity_digest = selectedArtifact?.integrity?.payload_digest || "none";
  const selectedQaHandoff = buildQaHandoff(selectedSnapshot, selectedArtifact);
  receipt.saved_receipts.qa_handoff_ready = Boolean(selectedArtifact);
  receipt.saved_receipts.qa_handoff_url = selectedArtifact ? selectedQaHandoff.url : "none";
  receipt.saved_receipts.qa_handoff_export_validation_status = selectedQaHandoff.export_validation_status;
  receipt.saved_receipts.qa_handoff_context_drift_status = selectedQaHandoff.context_drift.status;
  receipt.saved_receipts.qa_handoff_context_drift_changed = selectedQaHandoff.context_drift.changed_count;
  receipt.saved_receipts.qa_handoff_context_drift_total = selectedQaHandoff.context_drift.row_count;
  receipt.saved_receipts.qa_handoff_scope_status = selectedQaHandoff.handoff_scope.summary.status;
  receipt.saved_receipts.qa_handoff_scope_passed = selectedQaHandoff.handoff_scope.summary.passed;
  receipt.saved_receipts.qa_handoff_scope_total = selectedQaHandoff.handoff_scope.summary.total;
  receipt.saved_receipts.qa_handoff_scope_selected_compare = selectedQaHandoff.handoff_scope.summary.selected_compare;
  receipt.saved_receipts.qa_handoff_scope_selected_trace = selectedQaHandoff.handoff_scope.summary.selected_trace;
  receipt.saved_receipts.qa_handoff_scope_selected_blocker = selectedQaHandoff.handoff_scope.summary.selected_blocker;
  receipt.saved_receipts.qa_handoff_validation_status = selectedQaHandoff.handoff_validation.status;
  receipt.saved_receipts.qa_handoff_validation_passed = selectedQaHandoff.handoff_validation.passed;
  receipt.saved_receipts.qa_handoff_validation_total = selectedQaHandoff.handoff_validation.total;
  receipt.saved_receipts.qa_handoff_replay_snapshot_id = selectedQaHandoff.url_parameters.snapshot;
  receipt.saved_receipts.qa_handoff_replay_digest = selectedQaHandoff.url_parameters.digest;
  receipt.saved_receipts.qa_handoff_replay_request_status = replayRequestStatus(selectedQaHandoff.replay_request);
  receipt.saved_receipts.qa_handoff_replay_requested_snapshot_id =
    selectedQaHandoff.replay_request.requested_snapshot_id;
  receipt.saved_receipts.qa_handoff_replay_requested_digest = selectedQaHandoff.replay_request.requested_digest;
  receipt.saved_receipts.qa_handoff_replay_local_snapshot_status =
    selectedQaHandoff.replay_request.local_snapshot_status;
  receipt.saved_receipts.qa_handoff_replay_restored = selectedQaHandoff.replay_request.restored_selected_snapshot;
  receipt.saved_receipts.qa_handoff_replay_digest_status = selectedQaHandoff.replay_request.digest_status;
  receipt.saved_receipts.qa_handoff_local_only =
    selectedQaHandoff.boundary.production_evidence === 0 &&
    selectedQaHandoff.boundary.host_write_authority === 0 &&
    selectedQaHandoff.boundary.clipboard_write_authority === 0 &&
    selectedQaHandoff.boundary.handoff_mutates_state === 0 &&
    selectedQaHandoff.replay_request.replay_is_local_only === true &&
    selectedQaHandoff.replay_request.replay_mutates_state === 0 &&
    selectedQaHandoff.boundary.main_gui_mutation_required === 0 &&
    selectedQaHandoff.boundary.edge_gui_mutation_required === 0;
  return receipt;
}

function renderReceiptPreview() {
  renderEventTrailSummary();
  renderReceiptPreviewSummary();
  renderProfileScopeControl();
  renderEvidenceDetailControl();
  renderReadinessRail();
  renderDashboardAuthorityCard();
  renderRunMonitorState();
  renderOperatorWorkflow();
  renderWorkspaceRoute();
  renderWorkspacePostureStrip();
  renderComponentStack();
  renderDeliveryPlanState();
  renderUpdaterGate();
  renderQaReplayStrip();
  renderVisualIdentityPanel();
  renderInspectorLiveEvidence();
  renderContextInspector();
  renderCommandPalette();
  renderOperatorFocusDock();
  qs("#receipt-preview").textContent = JSON.stringify(buildReceiptPreview(), null, 2);
  renderSavedReceipts();
}

function renderReceiptPreviewSummary(summary = receiptPreviewSummary()) {
  const panel = qs("#receipt-preview-summary");
  if (panel instanceof HTMLElement) {
    panel.dataset.receiptPreviewState = summary.state;
  }
  qs("#receipt-preview-schema").textContent = summary.schema.replace("latticra-panel-test-ui-", "");
  qs("#receipt-preview-events").textContent = String(summary.event_count);
  qs("#receipt-preview-checklist").textContent = summary.checklist;
  qs("#receipt-preview-scope").textContent = summary.scope;
  qs("#receipt-preview-boundary").textContent =
    `production=${summary.production_evidence_claim} / host=${summary.host_write_authority} / runtime=${summary.runtime_enforcement_authority} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
}

function renderEventTrailSummary(summary = eventTrailSummary()) {
  const panel = qs("#event-trail-summary");
  if (panel instanceof HTMLElement) {
    panel.dataset.eventTrailState = summary.state;
  }
  qs("#event-count").textContent = `${summary.total} events`;
  qs("#event-trail-total").textContent = String(summary.total);
  qs("#event-trail-blocked").textContent = String(summary.blocked);
  qs("#event-trail-retained").textContent = `${summary.total}/${summary.retained_limit}`;
  qs("#event-trail-latest").textContent = summary.latest;
  qs("#event-trail-boundary").textContent =
    `production=${summary.production_evidence_claim} / host=${summary.host_write_authority} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
}

function renderEventTrail() {
  const trail = qs("#event-trail");
  trail.innerHTML = "";
  const rows = eventTrailRows();
  renderEventTrailSummary(eventTrailSummary(rows));
  if (rows.length === 0) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "No operator events recorded in this test lane.";
    trail.append(empty);
    renderReceiptPreview();
    return;
  }
  rows.forEach((event) => {
    const row = document.createElement("article");
    row.className = "event-row";
    row.dataset.eventStatus = event.status;
    const swatch = document.createElement("span");
    swatch.className = `swatch ${event.status === "blocked" ? "stop" : "ok"}`;
    swatch.setAttribute("aria-hidden", "true");
    const copy = document.createElement("div");
    const label = document.createElement("strong");
    label.textContent = event.label;
    const detail = document.createElement("small");
    detail.textContent = event.detail;
    const timestamp = document.createElement("code");
    timestamp.textContent = event.timestamp;
    copy.append(label, detail, timestamp);
    row.append(swatch, copy);
    trail.append(row);
  });
  renderReceiptPreview();
}

function renderReceiptDelta(snapshot) {
  const delta = compareSavedReceipt(snapshot);
  qs("#selected-receipt-label").textContent = delta.label;
  qs("#receipt-delta-events").textContent = delta.events;
  qs("#receipt-delta-checklist").textContent = delta.checklist;
  qs("#receipt-delta-blocked").textContent = delta.blocked;
  qs("#receipt-delta-mode").textContent = delta.mode;
  qs("#receipt-delta-prefix").textContent = delta.prefix;
}

function renderSavedReceiptTrust(snapshot, artifact = null) {
  const rows = savedReceiptTrustRows(snapshot, artifact?.selected_snapshot?.receipt || null, artifact);
  const summary = savedReceiptTrustSummary(rows);
  const panel = qs("#saved-receipt-trust");
  if (panel instanceof HTMLElement) {
    panel.dataset.savedReceiptState = summary.state;
  }
  qs("#saved-receipt-trust-count").textContent = summary.saved_count;
  qs("#saved-receipt-trust-selected").textContent = summary.selected;
  qs("#saved-receipt-trust-diff").textContent = summary.diff;
  qs("#saved-receipt-trust-export").textContent = summary.export_state;
  qs("#saved-receipt-trust-boundary").textContent =
    `production=${summary.production_evidence_claim} / host=${summary.host_write_authority} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
  const context = qs("#context-saved-receipt");
  if (context) {
    context.textContent =
      `${summary.state}: ${summary.saved_count} saved / selected ${summary.selected} / diff ${summary.diff} / export ${summary.export_state} / zero authority ${summary.zero_authority ? "yes" : "no"}`;
  }
}

function appendReceiptDiffCell(row, text, className) {
  const cell = document.createElement("span");
  cell.className = className;
  cell.textContent = text;
  row.append(cell);
}

function renderReceiptDiffDetail(snapshot) {
  const list = qs("#receipt-diff-list");
  const count = qs("#receipt-diff-count");
  if (!list || !count) {
    return;
  }

  const summary = receiptDiffSummary(snapshot);
  const visibleRows = receiptDiffVisibleRows(summary.rows);
  count.textContent = `${summary.changed_count} changes`;
  count.classList.toggle("ok", Boolean(snapshot) && summary.changed_count === 0);
  count.classList.toggle("warn", !snapshot || summary.changed_count > 0);
  qsa("[data-receipt-diff-filter]").forEach((button) => {
    const active = button.dataset.receiptDiffFilter === state.receiptDiffFilter;
    button.classList.toggle("is-active", active);
    button.setAttribute("aria-checked", String(active));
    button.tabIndex = active ? 0 : -1;
  });
  qs("#receipt-diff-filter-count").textContent = `${visibleRows.length} of ${summary.row_count} fields`;
  list.innerHTML = "";

  if (!snapshot) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "Save or select a receipt to inspect stable field-level differences.";
    list.append(empty);
    return;
  }

  const header = document.createElement("div");
  header.className = "receipt-diff-row is-header";
  header.role = "row";
  appendReceiptDiffCell(header, "field", "diff-field");
  appendReceiptDiffCell(header, "saved", "diff-saved");
  appendReceiptDiffCell(header, "current", "diff-current");
  appendReceiptDiffCell(header, "status", "diff-status");
  list.append(header);

  if (visibleRows.length === 0) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "No receipt fields match the current diff filter.";
    list.append(empty);
    return;
  }

  visibleRows.forEach((item) => {
    const row = document.createElement("div");
    row.className = "receipt-diff-row";
    row.role = "row";
    row.dataset.diffStatus = item.status;
    row.dataset.diffField = item.key;
    appendReceiptDiffCell(row, item.label, "diff-field");
    appendReceiptDiffCell(row, item.saved, "diff-saved");
    appendReceiptDiffCell(row, item.current, "diff-current");
    appendReceiptDiffCell(row, item.status, "diff-status");
    list.append(row);
  });
}

function appendReceiptContextDriftCell(row, text, className) {
  const cell = document.createElement("span");
  cell.className = className;
  cell.textContent = text;
  row.append(cell);
}

function renderReceiptContextDrift(snapshot) {
  const list = qs("#receipt-context-drift-list");
  const count = qs("#receipt-context-drift-count");
  if (!list || !count) {
    return;
  }

  const summary = receiptContextDriftSummary(snapshot);
  count.textContent = snapshot
    ? summary.changed_count > 0
      ? `${summary.changed_count}/${summary.row_count} changed`
      : "aligned"
    : "no snapshot";
  count.classList.toggle("ok", Boolean(snapshot) && summary.changed_count === 0);
  count.classList.toggle("warn", !snapshot || summary.changed_count > 0);
  list.innerHTML = "";

  if (!snapshot) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "Save or select a receipt to inspect selected review context drift.";
    list.append(empty);
    return;
  }

  const header = document.createElement("div");
  header.className = "receipt-context-drift-row is-header";
  header.role = "row";
  appendReceiptContextDriftCell(header, "context", "context-drift-field");
  appendReceiptContextDriftCell(header, "saved", "context-drift-saved");
  appendReceiptContextDriftCell(header, "current", "context-drift-current");
  appendReceiptContextDriftCell(header, "status", "context-drift-status");
  list.append(header);

  summary.rows.forEach((item) => {
    const row = document.createElement("div");
    row.className = "receipt-context-drift-row";
    row.role = "row";
    row.dataset.contextDriftStatus = item.status;
    row.dataset.contextDriftField = item.key;
    appendReceiptContextDriftCell(row, item.label, "context-drift-field");
    appendReceiptContextDriftCell(row, item.saved, "context-drift-saved");
    appendReceiptContextDriftCell(row, item.current, "context-drift-current");
    appendReceiptContextDriftCell(row, item.status, "context-drift-status");
    list.append(row);
  });
}

function renderReceiptExportValidation(artifact) {
  const list = qs("#receipt-export-validation-list");
  const count = qs("#receipt-export-validation-count");
  if (!list || !count) {
    return;
  }

  const summary = exportValidationSummary(artifact);
  count.textContent = summary.total > 0 ? `${summary.passed}/${summary.total} passed` : "0 passed";
  count.classList.toggle("ok", summary.status === "passed");
  count.classList.toggle("warn", summary.status !== "passed");
  list.innerHTML = "";

  if (!artifact) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "Select a saved receipt to validate the local export preview.";
    list.append(empty);
    return;
  }

  summary.rows.forEach((item) => {
    const row = document.createElement("article");
    row.className = "receipt-export-validation-row";
    row.dataset.validationStatus = item.status;
    row.dataset.validationKey = item.key;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "passed" ? "ok" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");
    const body = document.createElement("div");
    const title = document.createElement("strong");
    title.textContent = item.label;
    const detail = document.createElement("small");
    detail.textContent = item.detail;
    body.append(title, detail);
    const status = document.createElement("code");
    status.textContent = item.status;
    row.append(swatch, body, status);
    list.append(row);
  });
}

function renderQaHandoffValidation(handoff) {
  const list = qs("#qa-handoff-validation-list");
  const count = qs("#qa-handoff-validation-count");
  if (!list || !count) {
    return;
  }

  const summary = handoff?.handoff_validation || qaHandoffValidationSummary(null, null);
  count.textContent = summary.total > 0 ? `${summary.passed}/${summary.total} passed` : "0 passed";
  count.classList.toggle("ok", summary.status === "passed");
  count.classList.toggle("warn", summary.status !== "passed");
  list.innerHTML = "";

  if (!handoff) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "Select a saved receipt to validate the QA handoff link.";
    list.append(empty);
    return;
  }

  summary.rows.forEach((item) => {
    const row = document.createElement("article");
    row.className = "qa-handoff-validation-row";
    row.dataset.validationStatus = item.status;
    row.dataset.validationKey = item.key;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "passed" ? "ok" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");
    const body = document.createElement("div");
    const title = document.createElement("strong");
    title.textContent = item.label;
    const detail = document.createElement("small");
    detail.textContent = item.detail;
    body.append(title, detail);
    const status = document.createElement("code");
    status.textContent = item.status;
    row.append(swatch, body, status);
    list.append(row);
  });
}

function renderQaHandoffScope(handoff) {
  const list = qs("#qa-handoff-scope-list");
  const count = qs("#qa-handoff-scope-count");
  if (!list || !count) {
    return;
  }

  const scope = handoff?.handoff_scope || {
    summary: qaHandoffScopeSummary(null),
    rows: qaHandoffScopeRows(null),
  };
  count.textContent = scope.summary.total > 0 ? `${scope.summary.passed}/${scope.summary.total} covered` : "0 covered";
  count.classList.toggle("ok", scope.summary.status === "passed");
  count.classList.toggle("warn", scope.summary.status !== "passed");
  list.innerHTML = "";

  if (!handoff) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "Select a saved receipt to review handoff scope.";
    list.append(empty);
    return;
  }

  scope.rows.forEach((item) => {
    const row = document.createElement("article");
    row.className = "qa-handoff-scope-row";
    row.dataset.scopeStatus = item.status;
    row.dataset.scopeKey = item.key;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "passed" ? "ok" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");
    const body = document.createElement("div");
    const title = document.createElement("strong");
    title.textContent = item.label;
    const detail = document.createElement("small");
    detail.textContent = item.detail;
    body.append(title, detail);
    const status = document.createElement("code");
    status.textContent = item.status;
    row.append(swatch, body, status);
    list.append(row);
  });
}

function replayRequestStatus(replayRequest) {
  if (!replayRequest?.requested) {
    return "no request";
  }
  if (!replayRequest.restored_selected_snapshot) {
    return "missing";
  }
  return replayRequest.digest_status === "refreshed" ? "refreshed" : "restored";
}

function renderQaHandoffReplayRequest(replayRequest) {
  const status = qs("#qa-handoff-replay-status");
  if (!status || !replayRequest) {
    return;
  }
  const statusText = replayRequestStatus(replayRequest);
  status.textContent = statusText;
  status.classList.toggle("ok", statusText === "restored");
  status.classList.toggle("warn", statusText === "no request" || statusText === "refreshed");
  status.classList.toggle("stop", statusText === "missing");
  qs("#qa-handoff-requested-snapshot").textContent = replayRequest.requested_snapshot_id;
  qs("#qa-handoff-requested-digest").textContent = replayRequest.requested_digest;
  qs("#qa-handoff-local-snapshot-state").textContent = replayRequest.local_snapshot_status;
  qs("#qa-handoff-replay-restored").textContent = replayRequest.restored_selected_snapshot ? "yes" : "no";
  qs("#qa-handoff-replay-digest-state").textContent = replayRequest.digest_status;
}

function setLocalActionLink(link, ready, href = "", download = "") {
  if (!(link instanceof HTMLAnchorElement)) {
    return;
  }
  link.classList.toggle("is-disabled", !ready);
  link.setAttribute("aria-disabled", String(!ready));
  link.tabIndex = ready ? 0 : -1;
  if (!ready) {
    link.removeAttribute("href");
    link.removeAttribute("download");
    return;
  }
  link.href = href;
  if (download) {
    link.download = download;
  } else {
    link.removeAttribute("download");
  }
}

function disabledLocalActionLink(target) {
  const link = target instanceof Element ? target.closest("a[aria-disabled='true']") : null;
  return link instanceof HTMLAnchorElement ? link : null;
}

function renderQaHandoff(snapshot, artifact = null) {
  const pre = qs("#qa-handoff-manifest");
  const link = qs("#qa-handoff-link");
  const status = qs("#qa-handoff-status");
  if (!pre || !link || !status) {
    return;
  }

  const handoff = buildQaHandoff(snapshot, artifact);
  const hasSnapshot = Boolean(snapshot && artifact);
  const ready = hasSnapshot && handoff.handoff_validation.status === "passed";
  status.textContent = hasSnapshot ? (ready ? "ready" : "blocked") : "no snapshot";
  status.classList.toggle("ok", ready);
  status.classList.toggle("warn", !ready && !hasSnapshot);
  status.classList.toggle("stop", !ready && hasSnapshot);
  qs("#qa-handoff-mode").textContent = handoff.mode;
  qs("#qa-handoff-diff").textContent = handoff.filters.diff;
  qs("#qa-handoff-digest").textContent = handoff.export_integrity_digest;
  qs("#qa-handoff-selected").textContent = handoff.selected_snapshot?.label || "none";
  renderQaHandoffScope(handoff);
  renderQaHandoffReplayRequest(handoff.replay_request);

  if (!hasSnapshot) {
    pre.textContent = "No saved receipt selected.";
    setLocalActionLink(link, false);
    renderQaHandoffScope(null);
    renderQaHandoffValidation(null);
    return;
  }

  pre.textContent = JSON.stringify(handoff, null, 2);
  setLocalActionLink(link, ready, handoff.url);
  renderQaHandoffValidation(handoff);
}

function renderReceiptExportPreview(snapshot, artifact = buildReceiptExportArtifact(snapshot)) {
  const pre = qs("#receipt-export-artifact");
  const link = qs("#receipt-export-download");
  if (!pre || !link) {
    return;
  }
  if (!artifact) {
    qs("#receipt-export-filename").textContent = "none";
    qs("#receipt-export-selected").textContent = "none";
    qs("#receipt-export-size").textContent = "0 bytes";
    qs("#receipt-export-digest").textContent = "none";
    pre.textContent = "No saved receipt selected.";
    setLocalActionLink(link, false);
    renderSavedReceiptTrust(null, null);
    renderReceiptExportValidation(null);
    renderQaHandoff(null, null);
    return;
  }

  const text = JSON.stringify(artifact, null, 2);
  const filename = receiptExportFilename(snapshot);
  qs("#receipt-export-filename").textContent = filename;
  qs("#receipt-export-selected").textContent = snapshot.label;
  qs("#receipt-export-size").textContent = `${new Blob([text]).size} bytes`;
  qs("#receipt-export-digest").textContent = artifact.integrity.payload_digest;
  pre.textContent = text;
  setLocalActionLink(
    link,
    exportValidationSummary(artifact).status === "passed",
    `data:application/json;charset=utf-8,${encodeURIComponent(text)}`,
    filename
  );
  renderReceiptExportValidation(artifact);
  renderQaHandoff(snapshot, artifact);
}

function renderSavedReceipts() {
  const list = qs("#saved-receipts-list");
  const count = qs("#saved-receipt-count");
  if (!list || !count) {
    return;
  }
  const limit = qs("#saved-receipt-limit");
  const labelInput = qs("#saved-receipt-label-input");
  const deleteButton = qs("[data-action='delete-saved-receipt']");

  count.textContent = `${state.savedReceipts.length} saved`;
  count.classList.toggle("ok", state.savedReceipts.length > 0);
  count.classList.toggle("warn", state.savedReceipts.length === 0);
  if (limit) {
    limit.textContent = `retains last ${SAVED_RECEIPT_LIMIT} local snapshots`;
  }
  list.innerHTML = "";

  if (state.savedReceipts.length === 0) {
    if (labelInput instanceof HTMLInputElement) {
      labelInput.value = "";
      labelInput.placeholder = "No snapshot selected";
      labelInput.disabled = true;
    }
    if (deleteButton instanceof HTMLButtonElement) {
      deleteButton.disabled = true;
      deleteButton.setAttribute("aria-disabled", "true");
    }
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "No saved receipt snapshots yet.";
    list.append(empty);
    renderReceiptDelta(null);
    renderReceiptDiffDetail(null);
    renderReceiptContextDrift(null);
    renderSavedReceiptTrust(null, null);
    renderReceiptExportPreview(null, null);
    return;
  }

  if (!state.savedReceipts.some((snapshot) => snapshot.id === state.selectedReceiptId)) {
    state.selectedReceiptId = state.savedReceipts[state.savedReceipts.length - 1].id;
  }

  state.savedReceipts
    .slice()
    .reverse()
    .forEach((snapshot) => {
      const active = snapshot.id === state.selectedReceiptId;
      const button = document.createElement("button");
      button.className = "saved-receipt-option";
      button.type = "button";
      button.role = "option";
      button.dataset.savedReceipt = snapshot.id;
      button.setAttribute("aria-selected", String(active));
      button.tabIndex = active ? 0 : -1;

      const title = document.createElement("strong");
      title.textContent = snapshot.label;
      const meta = document.createElement("small");
      meta.textContent = `${snapshot.summary.mode} | ${snapshot.summary.prefix} | events=${snapshot.summary.events}`;
      const saved = document.createElement("code");
      saved.textContent = snapshot.saved_at;
      button.append(title, meta, saved);
      list.append(button);
    });

  const snapshot = selectedSavedReceipt();
  if (labelInput instanceof HTMLInputElement) {
    labelInput.disabled = !snapshot;
    labelInput.placeholder = snapshot ? "Edit selected snapshot label" : "No snapshot selected";
    labelInput.value = snapshot ? snapshot.label : "";
  }
  if (deleteButton instanceof HTMLButtonElement) {
    deleteButton.disabled = !snapshot;
    deleteButton.setAttribute("aria-disabled", String(!snapshot));
  }
  const artifact = buildReceiptExportArtifact(snapshot);
  renderSavedReceiptTrust(snapshot, artifact);
  renderReceiptDelta(snapshot);
  renderReceiptDiffDetail(snapshot);
  renderReceiptContextDrift(snapshot);
  renderReceiptExportPreview(snapshot, artifact);
}

function selectSavedReceipt(snapshotId, record = false, focusAfterRender = false) {
  if (!state.savedReceipts.some((snapshot) => snapshot.id === snapshotId)) {
    return;
  }
  state.selectedReceiptId = snapshotId;
  renderSavedReceipts();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-saved-receipt]", "savedReceipt", snapshotId);
  }
  if (record) {
    const snapshot = selectedSavedReceipt();
    assistiveStatus(`${snapshot.label} selected for receipt comparison.`);
  }
}

function moveSavedReceiptFocus(currentButton, direction) {
  const buttons = qsa("[data-saved-receipt]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0 || buttons.length === 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  const nextId = next.dataset.savedReceipt;
  selectSavedReceipt(nextId, true, true);
}

function retainSelectableLedgerFocus(selector, dataKey, key) {
  const focus = () => {
    qsa(selector)
      .find((button) => button.dataset[dataKey] === key)
      ?.focus({ preventScroll: true });
  };
  focus();
  requestAnimationFrame(focus);
}

function recordEvent(label, detail, level = "info") {
  state.events.push({
    timestamp: nowStamp(),
    label,
    detail,
    level,
  });
  state.events = state.events.slice(-24);
  renderEventTrail();
  safeWriteState();
}

function notify(message, level = "info") {
  const region = qs("#toast-region");
  region.textContent = "";
  const toast = document.createElement("div");
  toast.className = `toast${level === "warning" ? " is-warning" : ""}`;
  toast.textContent = message;
  region.append(toast);
  window.setTimeout(() => {
    if (toast.parentElement) {
      toast.remove();
    }
  }, 2600);
  assistiveStatus(message);
}

function validatePrefix(prefix) {
  const value = prefix.trim();
  if (!value) {
    return { valid: false, message: "prefix is required" };
  }
  if (value.includes("://")) {
    return { valid: false, message: "remote prefixes are blocked" };
  }
  if (
    value === "/" ||
    value.startsWith("/usr") ||
    value.startsWith("/etc") ||
    value.startsWith("/var") ||
    value.startsWith("/bin") ||
    value.startsWith("/sbin")
  ) {
    return { valid: false, message: "system prefixes are blocked" };
  }
  if (value.startsWith("~/.local") || value.startsWith("$HOME/.local") || value.startsWith("/home/")) {
    return { valid: true, message: "user-local prefix accepted" };
  }
  return { valid: false, message: "prefix must stay user-local" };
}

function renderPrefixValidation() {
  const result = validatePrefix(state.prefix);
  state.prefixValid = result.valid;
  const input = qs("#prefix-input");
  const status = qs("#prefix-validation");
  input.setAttribute("aria-invalid", String(!result.valid));
  status.textContent = result.message;
  status.classList.toggle("is-invalid", !result.valid);
  qs("#prefix-guard-fact").textContent = result.valid ? "accepted" : "blocked";
  return result;
}

function safeReadState() {
  try {
    const value = localStorage.getItem(STORAGE_KEY);
    return value ? JSON.parse(value) : null;
  } catch {
    return null;
  }
}

function safeWriteState() {
  try {
    localStorage.setItem(
      STORAGE_KEY,
      JSON.stringify({
        activeTab: state.activeTab,
        mode: state.mode,
        progress: state.progress,
        profile: state.profile,
        prefix: state.prefix,
        prefixValid: state.prefixValid,
        evidenceDetail: state.evidenceDetail,
        evidenceFilter: state.evidenceFilter,
        blockerFilter: state.blockerFilter,
        reviewFilter: state.reviewFilter,
        receiptDiffFilter: state.receiptDiffFilter,
        promotionGateSelection: state.promotionGateSelection,
        migrationReviewSelection: state.migrationReviewSelection,
        qaScenarioSelection: state.qaScenarioSelection,
        engineBindingSelection: state.engineBindingSelection,
        visualBaselineSelection: state.visualBaselineSelection,
        releaseAcceptanceSelection: state.releaseAcceptanceSelection,
        accessibilityAuditSelection: state.accessibilityAuditSelection,
        readinessCompareSelection: state.readinessCompareSelection,
        evidenceIntakeSelection: state.evidenceIntakeSelection,
        traceabilitySelection: state.traceabilitySelection,
        productionBlockerSelection: state.productionBlockerSelection,
        consoleStatus: state.consoleStatus,
        consoleMessage: state.consoleMessage,
        consoleLastCommand: state.consoleLastCommand,
        paletteQuery: state.paletteQuery,
        paletteSelection: state.paletteSelection,
        receiptChecklist: state.receiptChecklist,
        savedReceipts: state.savedReceipts,
        selectedReceiptId: state.selectedReceiptId,
        events: state.events,
        components: components.map((component) => ({
          id: component.id,
          selected: component.selected,
        })),
      })
    );
    qs("#state-persistence-fact").textContent = "saved";
  } catch {
    qs("#state-persistence-fact").textContent = "unavailable";
  }
}

function applyStoredState() {
  const stored = safeReadState();
  if (!stored || typeof stored !== "object") {
    return;
  }
  if (stored.mode === "dry" || stored.mode === "local") {
    state.mode = stored.mode;
  }
  if (typeof stored.progress === "number") {
    state.progress = Math.max(0, Math.min(100, Math.round(stored.progress)));
  }
  if (typeof stored.profile === "string") {
    state.profile = stored.profile;
  }
  if (typeof stored.prefix === "string") {
    state.prefix = stored.prefix;
  }
  if (typeof stored.evidenceDetail === "number") {
    state.evidenceDetail = Math.max(1, Math.min(3, Math.round(stored.evidenceDetail)));
  }
  if (typeof stored.evidenceFilter === "string") {
    state.evidenceFilter = stored.evidenceFilter.slice(0, 64);
  }
  if (typeof stored.blockerFilter === "string") {
    state.blockerFilter = normalizeBlockerFilter(stored.blockerFilter);
  }
  if (reviewFilterOptions.includes(stored.reviewFilter)) {
    state.reviewFilter = stored.reviewFilter;
  }
  if (receiptDiffFilterOptions.includes(stored.receiptDiffFilter)) {
    state.receiptDiffFilter = stored.receiptDiffFilter;
  }
  if (isPromotionGateKey(stored.promotionGateSelection)) {
    state.promotionGateSelection = stored.promotionGateSelection;
  }
  if (isMigrationReviewKey(stored.migrationReviewSelection)) {
    state.migrationReviewSelection = stored.migrationReviewSelection;
  }
  if (isQaScenarioKey(stored.qaScenarioSelection)) {
    state.qaScenarioSelection = stored.qaScenarioSelection;
  }
  if (isEngineBindingKey(stored.engineBindingSelection)) {
    state.engineBindingSelection = stored.engineBindingSelection;
  }
  if (isVisualBaselineKey(stored.visualBaselineSelection)) {
    state.visualBaselineSelection = stored.visualBaselineSelection;
  }
  if (isReleaseAcceptanceKey(stored.releaseAcceptanceSelection)) {
    state.releaseAcceptanceSelection = stored.releaseAcceptanceSelection;
  }
  if (isAccessibilityAuditKey(stored.accessibilityAuditSelection)) {
    state.accessibilityAuditSelection = stored.accessibilityAuditSelection;
  }
  if (isReadinessCompareKey(stored.readinessCompareSelection)) {
    state.readinessCompareSelection = stored.readinessCompareSelection;
  }
  if (isEvidenceIntakeKey(stored.evidenceIntakeSelection)) {
    state.evidenceIntakeSelection = stored.evidenceIntakeSelection;
  }
  if (isTraceabilityKey(stored.traceabilitySelection)) {
    state.traceabilitySelection = stored.traceabilitySelection;
  }
  if (isProductionBlockerKey(stored.productionBlockerSelection)) {
    state.productionBlockerSelection = stored.productionBlockerSelection;
  }
  if (["ready", "accepted", "blocked"].includes(stored.consoleStatus)) {
    state.consoleStatus = stored.consoleStatus;
  }
  if (typeof stored.consoleMessage === "string") {
    state.consoleMessage = stored.consoleMessage;
  }
  if (typeof stored.consoleLastCommand === "string") {
    state.consoleLastCommand = stored.consoleLastCommand;
  }
  if (typeof stored.paletteQuery === "string") {
    state.paletteQuery = stored.paletteQuery.slice(0, 64);
  }
  if (typeof stored.paletteSelection === "string" && isCommandPaletteKey(stored.paletteSelection)) {
    state.paletteSelection = stored.paletteSelection;
  }
  if (stored.receiptChecklist && typeof stored.receiptChecklist === "object") {
    receiptChecklistItems.forEach((item) => {
      if (typeof stored.receiptChecklist[item.id] === "boolean") {
        state.receiptChecklist[item.id] = stored.receiptChecklist[item.id];
      }
    });
  }
  if (Array.isArray(stored.savedReceipts)) {
    state.savedReceipts = stored.savedReceipts
      .filter(
        (snapshot) =>
          snapshot &&
          typeof snapshot.id === "string" &&
          typeof snapshot.label === "string" &&
          typeof snapshot.saved_at === "string" &&
          snapshot.receipt &&
          typeof snapshot.receipt === "object"
      )
      .map((snapshot) => ({
        id: snapshot.id,
        label: normalizeSnapshotLabel(snapshot.label),
        saved_at: snapshot.saved_at,
        receipt: snapshot.receipt,
        summary: snapshot.summary && typeof snapshot.summary === "object" ? snapshot.summary : receiptSnapshotSummary(snapshot.receipt),
      }))
      .slice(-SAVED_RECEIPT_LIMIT);
  }
  if (typeof stored.selectedReceiptId === "string") {
    state.selectedReceiptId = stored.selectedReceiptId;
  }
  if (state.selectedReceiptId && !state.savedReceipts.some((snapshot) => snapshot.id === state.selectedReceiptId)) {
    state.selectedReceiptId = "";
  }
  if (Array.isArray(stored.events)) {
    state.events = stored.events
      .filter((event) =>
        event &&
        typeof event.timestamp === "string" &&
        typeof event.label === "string" &&
        typeof event.detail === "string" &&
        typeof event.level === "string"
      )
      .slice(-24);
  }
  if (tabs.some(([id]) => id === stored.activeTab)) {
    state.activeTab = stored.activeTab;
  }
  if (Array.isArray(stored.components)) {
    stored.components.forEach((storedComponent) => {
      const component = components.find((item) => item.id === storedComponent.id);
      if (component && typeof storedComponent.selected === "boolean") {
        component.selected = storedComponent.selected;
      }
    });
  }
}

function applyUrlStateOverrides() {
  const params = new URLSearchParams(window.location.search);
  const mode = params.get("mode");
  const tab = params.get("tab");
  const prefix = params.get("prefix");
  const blocker = params.get("blocker");
  const review = params.get("review");
  const diff = params.get("diff");
  const gate = params.get("gate");
  const migration = params.get("migration");
  const scenario = params.get("scenario");
  const engine = params.get("engine");
  const visual = params.get("visual");
  const acceptance = params.get("acceptance");
  const a11y = params.get("a11y");
  const compare = params.get("compare");
  const intake = params.get("intake");
  const trace = params.get("trace");
  const blockerItem = params.get("blockerItem");
  const snapshot = params.get("snapshot");
  if (mode === "dry" || mode === "local") {
    state.mode = mode;
  }
  if (tab && tabs.some(([id]) => id === tab)) {
    state.activeTab = tab;
  }
  if (prefix) {
    state.prefix = prefix;
  }
  if (blocker !== null) {
    state.blockerFilter = normalizeBlockerFilter(blocker);
  }
  if (reviewFilterOptions.includes(review)) {
    state.reviewFilter = review;
  }
  if (receiptDiffFilterOptions.includes(diff)) {
    state.receiptDiffFilter = diff;
  }
  if (isPromotionGateKey(gate)) {
    state.promotionGateSelection = gate;
  }
  if (isMigrationReviewKey(migration)) {
    state.migrationReviewSelection = migration;
  }
  if (isQaScenarioKey(scenario)) {
    state.qaScenarioSelection = scenario;
  }
  if (isEngineBindingKey(engine)) {
    state.engineBindingSelection = engine;
  }
  if (isVisualBaselineKey(visual)) {
    state.visualBaselineSelection = visual;
  }
  if (isReleaseAcceptanceKey(acceptance)) {
    state.releaseAcceptanceSelection = acceptance;
  }
  if (isAccessibilityAuditKey(a11y)) {
    state.accessibilityAuditSelection = a11y;
    pendingAccessibilityAuditScroll = true;
  }
  if (isReadinessCompareKey(compare)) {
    state.readinessCompareSelection = compare;
    pendingReadinessCompareScroll = true;
  }
  if (isEvidenceIntakeKey(intake)) {
    state.evidenceIntakeSelection = intake;
    pendingEvidenceIntakeScroll = true;
  }
  if (isTraceabilityKey(trace)) {
    state.traceabilitySelection = trace;
    pendingTraceabilityScroll = true;
  }
  if (isProductionBlockerKey(blockerItem)) {
    state.productionBlockerSelection = blockerItem;
  }
  if (snapshot && state.savedReceipts.some((item) => item.id === snapshot)) {
    state.selectedReceiptId = snapshot;
  }
}

function setTab(tab) {
  state.activeTab = tab;
  qsa("[data-tab]").forEach((button) => {
    const active = button.dataset.tab === tab;
    button.classList.toggle("is-active", active);
    button.setAttribute("aria-selected", String(active));
    button.tabIndex = active ? 0 : -1;
  });
  qsa("[data-view]").forEach((view) => {
    const active = view.dataset.view === tab;
    view.classList.toggle("is-active", active);
    view.setAttribute("aria-hidden", String(!active));
  });
  const title = tabs.find(([id]) => id === tab)?.[1] || "Dashboard";
  qs("#workspace-title").textContent = title;
  assistiveStatus(`${title} selected. ${activeModeLabel()} mode. Production claims blocked.`);
  renderReceiptPreview();
  scrollReadinessCompareSelectionIntoView();
  scrollEvidenceIntakeSelectionIntoView();
  scrollTraceabilitySelectionIntoView();
  scrollAccessibilityAuditSelectionIntoView();
  safeWriteState();
}

function moveTabFocus(currentButton, direction) {
  const buttons = qsa("[data-tab]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setTab(next.dataset.tab);
  next.focus();
}

function moveModeFocus(currentButton, direction) {
  const buttons = qsa("[data-mode]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setMode(next.dataset.mode);
  next.focus();
}

function renderComponentStack() {
  const stack = qs("#component-stack");
  const rows = componentHealthRows();
  const summary = componentHealthSummary(rows);
  const selectedRows = rows.filter((row) => row.selected);
  stack.innerHTML = "";
  selectedRows.forEach((component) => {
    const row = document.createElement("div");
    row.className = "component-row";
    row.dataset.componentState = component.status;

    const copy = document.createElement("div");
    const title = document.createElement("strong");
    title.textContent = component.label;
    const note = document.createElement("small");
    note.textContent = component.note;
    copy.append(title, note);

    const badge = document.createElement("span");
    badge.className = "badge ok";
    badge.textContent = component.core ? "core" : "optional";

    row.append(copy, badge);
    stack.append(row);
  });
  if (summary.omitted > 0) {
    const row = document.createElement("div");
    row.className = "component-row";
    row.dataset.componentState = "omitted";

    const copy = document.createElement("div");
    const title = document.createElement("strong");
    title.textContent = `${summary.omitted} optional omitted`;
    const note = document.createElement("small");
    note.textContent = "omitted components stay local review state, not production evidence";
    copy.append(title, note);

    const badge = document.createElement("span");
    badge.className = "badge";
    badge.textContent = "review";

    row.append(copy, badge);
    stack.append(row);
  }

  const card = qs("#component-health-card");
  if (card instanceof HTMLElement) {
    card.dataset.componentHealth = summary.state;
  }
  const badge = qs("#component-health-badge");
  badge.textContent = summary.badge;
  badge.classList.toggle("ok", summary.state === "ready");
  badge.classList.toggle("stop", summary.state === "blocked");
  qs("#component-count").textContent = `${summary.selected} selected`;
  qs("#component-health-selected").textContent = String(summary.selected);
  qs("#component-health-omitted").textContent = String(summary.omitted);
  qs("#component-health-core").textContent = summary.coverage_label;
  qs("#component-health-boundary").textContent =
    `production=${summary.production_evidence_claim} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
  qs("#component-selection-summary").textContent = componentSummaryText();
}

function renderDeliveryPlanState() {
  const rows = deliveryPlanRows();
  const summary = deliveryPlanSummary(rows);
  const panel = qs("#delivery-plan-preview");
  if (panel instanceof HTMLElement) {
    panel.dataset.planState = summary.state;
  }
  const badge = qs("#plan-badge");
  badge.textContent = summary.badge;
  badge.classList.toggle("ok", summary.state === "ready");
  badge.classList.toggle("stop", summary.state === "blocked");
  qs("#delivery-plan-components").textContent = String(summary.components);
  qs("#delivery-plan-prefix").textContent = summary.prefix_guard;
  qs("#delivery-plan-authority").textContent = String(summary.host_write_authority);
  qs("#plan-preview").textContent = deliveryPlanPreviewText(rows);
  qs("#delivery-plan-boundary").textContent = summary.boundary;
}

function renderUpdaterGate() {
  const rows = updaterGateRows();
  const summary = updaterGateSummary(rows);
  const board = qs("#signed-updater-gate");
  if (board instanceof HTMLElement) {
    board.dataset.updaterState = summary.state;
  }
  qs("#signed-updater-title").textContent = summary.title;
  const badge = qs("#signed-updater-badge");
  badge.textContent = summary.badge;
  badge.classList.toggle("stop", summary.state === "closed");
  badge.classList.toggle("ok", summary.state === "ready");
  qs("#signed-updater-blocked").textContent = String(summary.blocked);
  qs("#signed-updater-preview").textContent = summary.preview_status;
  qs("#signed-updater-apply").textContent = String(summary.can_apply);
  qs("#signed-updater-boundary").textContent = summary.boundary;

  const list = qs("#signed-updater-list");
  list.innerHTML = "";
  rows.filter((row) => row.required).forEach((row) => {
    const item = document.createElement("article");
    item.dataset.updaterGate = row.key;
    item.dataset.updaterStatus = row.status;

    const label = document.createElement("strong");
    label.textContent = row.label;
    const detail = document.createElement("small");
    detail.textContent = row.detail;
    const status = document.createElement("span");
    status.className = `badge ${row.status === "blocked" ? "stop" : "ok"}`;
    status.textContent = row.status === "blocked" ? "missing" : row.status;

    item.append(label, detail, status);
    list.append(item);
  });
}

function renderComponentTable(filter = "") {
  const table = qs("#component-table");
  const normalized = filter.trim().toLowerCase();
  table.innerHTML = "";
  components
    .filter((component) => {
      return (
        component.name.toLowerCase().includes(normalized) ||
        component.note.toLowerCase().includes(normalized)
      );
    })
    .forEach((component) => {
      const noteId = `component-note-${component.id}`;
      const stateLabel = component.selected ? "selected" : "not selected";
      const row = document.createElement("article");
      row.className = "component-row";
      row.setAttribute("aria-label", `${component.name}, ${stateLabel}`);
      row.innerHTML = `
        <div>
          <strong>${component.name}</strong>
          <small id="${noteId}">${component.note}</small>
        </div>
        <label class="switch" aria-label="${component.name}, ${stateLabel}" aria-describedby="${noteId} component-toggle-policy">
          <input type="checkbox" data-component="${component.id}" aria-describedby="${noteId} component-toggle-policy" ${component.selected ? "checked" : ""}>
          <span aria-hidden="true"></span>
        </label>
      `;
      table.append(row);
    });
}

function focusComponentToggle(componentId) {
  window.setTimeout(() => {
    const input = qs(`[data-component="${componentId}"]`);
    if (!input) {
      return;
    }
    input.focus({ preventScroll: true });
    input.closest(".component-row")?.classList.add("is-focused");
  }, 0);
}

function renderReceiptChecklist() {
  const list = qs("#receipt-checklist");
  const rows = receiptChecklistRows();
  const summary = receiptChecklistSummary(rows);
  list.innerHTML = "";
  rows.forEach((item) => {
    const noteId = `receipt-check-${item.id}-note`;
    const row = document.createElement("label");
    row.className = "receipt-check-row";
    row.dataset.checkStatus = item.status;

    const input = document.createElement("input");
    input.type = "checkbox";
    input.dataset.receiptCheck = item.id;
    input.checked = item.recorded;
    input.disabled = !item.available;
    input.setAttribute("aria-describedby", `${noteId} receipt-checklist-policy`);

    const copy = document.createElement("span");
    copy.className = "receipt-check-copy";
    const title = document.createElement("strong");
    title.textContent = item.label;
    const note = document.createElement("small");
    note.id = noteId;
    note.textContent = `${item.source} - ${item.note}`;
    copy.append(title, note);

    const status = document.createElement("span");
    status.className = `check-status is-${item.status}`;
    status.textContent = item.status;

    row.append(input, copy, status);
    list.append(row);
  });

  const count = qs("#receipt-checklist-count");
  count.textContent =
    summary.blocked > 0
      ? `${summary.recorded} recorded, ${summary.blocked} blocked`
      : `${summary.recorded} recorded, ${summary.pending} pending`;
  count.classList.toggle("ok", summary.pending === 0 && summary.blocked === 0);
  count.classList.toggle("warn", summary.pending > 0 && summary.blocked === 0);
  count.classList.toggle("stop", summary.blocked > 0);
}

function focusReceiptCheck(checkId) {
  window.setTimeout(() => {
    const input = qs(`[data-receipt-check="${checkId}"]`);
    if (!input || input.disabled) {
      return;
    }
    input.focus({ preventScroll: true });
    input.closest(".receipt-check-row")?.classList.add("is-focused");
  }, 0);
}

function renderReceiptSchemaSummary(summary) {
  qs("#schema-live-count").textContent = String(summary.live);
  qs("#schema-guarded-count").textContent = String(summary.guarded);
  qs("#schema-blocked-count").textContent = String(summary.blocked);
}

function renderReceiptSchema() {
  const map = qs("#receipt-schema-map");
  const rows = receiptFieldRows();
  map.innerHTML = "";
  rows.forEach((field) => {
    const row = document.createElement("article");
    row.className = "schema-row";
    row.dataset.schemaStatus = field.status;

    const fieldCell = document.createElement("div");
    const key = document.createElement("strong");
    key.textContent = field.key;
    const source = document.createElement("small");
    source.textContent = field.source;
    fieldCell.append(key, source);

    const value = document.createElement("code");
    value.textContent = field.value;

    const status = document.createElement("span");
    status.className = `schema-status is-${field.status}`;
    status.textContent = field.status;

    row.append(fieldCell, value, status);
    map.append(row);
  });
  renderReceiptSchemaSummary(schemaStatusSummary(rows));
}

function renderQualityGates() {
  const list = qs("#quality-gates");
  list.innerHTML = "";
  const rows = qualityGateRows();
  const summary = qualityGateSummary(rows);
  const card = qs("#quality-gate-card");
  if (card instanceof HTMLElement) {
    card.dataset.qualityDecision = summary.decision;
  }
  qs("#quality-gate-title").textContent = `${summary.verified} verified, ${summary.pending} pending`;
  qs("#quality-gate-badge").textContent = summary.badge;
  qs("#quality-gate-badge").classList.toggle("ok", summary.decision === "ready");
  qs("#quality-gate-badge").classList.toggle("warn", summary.decision !== "ready");
  qs("#quality-gate-badge").classList.toggle("stop", summary.blocked > 0);
  qs("#quality-gate-verified").textContent = String(summary.verified);
  qs("#quality-gate-pending").textContent = String(summary.pending);
  qs("#quality-gate-promote").textContent = String(summary.can_promote);
  qs("#quality-gate-boundary").textContent =
    `can_promote=${summary.can_promote} / production=${summary.production_evidence_claim} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
  rows.forEach((gate) => {
    const row = document.createElement("div");
    row.className = "quality-row";
    row.dataset.qualityGate = gate.key;
    row.dataset.qualityStatus = gate.status;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${qualityGateTone(gate.status)}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("div");
    const label = document.createElement("strong");
    label.textContent = gate.label;
    const evidence = document.createElement("small");
    evidence.textContent = gate.evidence;
    const next = document.createElement("span");
    next.className = "quality-row-next";
    next.textContent = gate.next;
    detail.append(label, evidence, next);

    const status = document.createElement("code");
    status.textContent = gate.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function reviewCount(stateName) {
  return reviewChecks.filter((check) => check.state === stateName).length;
}

function evidenceMatrixRows() {
  return evidenceMatrix.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    evidence: item.evidence,
    boundary: item.boundary,
    local_only: true,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function evidenceMatrixSummary(rows = evidenceMatrixRows()) {
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending: rows.filter((row) => row.status === "pending").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function renderEvidenceMatrix() {
  const list = qs("#evidence-matrix-list");
  if (!list) {
    return;
  }
  const rows = evidenceMatrixRows();
  const summary = evidenceMatrixSummary(rows);
  qs("#evidence-matrix-verified-count").textContent = `${summary.verified} verified`;
  qs("#evidence-matrix-pending-count").textContent = `${summary.pending} pending`;
  qs("#evidence-matrix-blocked-count").textContent = `${summary.blocked} blocked`;
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("article");
    row.className = "evidence-matrix-row";
    row.dataset.evidenceStatus = item.status;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("div");
    const label = document.createElement("strong");
    label.textContent = item.label;
    const evidence = document.createElement("small");
    evidence.textContent = item.evidence;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, evidence, boundary);

    const stateBadge = document.createElement("span");
    stateBadge.className = `badge matrix-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    stateBadge.textContent = item.status;

    row.append(swatch, detail, stateBadge);
    list.append(row);
  });
}

function accessibilityAuditRows() {
  return accessibilityAuditItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    path: item.path,
    evidence: item.evidence,
    selected: item.key === state.accessibilityAuditSelection,
    local_only: true,
    production_accessibility_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function accessibilityAuditSummary(rows = accessibilityAuditRows()) {
  const selected = selectedAccessibilityAuditRow();
  const pending = rows.filter((row) => row.status === "pending").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    selected_evidence: selected?.evidence || "none",
    pending_manual_review: pending,
    local_only: rows.every((row) => row.local_only === true),
    production_accessibility_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedAccessibilityAuditRow() {
  const rows = accessibilityAuditRows();
  return (
    rows.find((row) => row.key === state.accessibilityAuditSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0]
  );
}

function renderAccessibilityAuditDetail(row = selectedAccessibilityAuditRow()) {
  if (!row) {
    return;
  }
  qs("#accessibility-evidence-detail-title").textContent = row.label;
  qs("#accessibility-evidence-detail-state").textContent = row.status;
  qs("#accessibility-evidence-detail-path").textContent = row.path;
  qs("#accessibility-evidence-detail-gap").textContent = row.evidence;
}

function renderAccessibilityAudit() {
  const list = qs("#accessibility-audit-list");
  if (!list) {
    return;
  }
  const rows = accessibilityAuditRows();
  const summary = accessibilityAuditSummary(rows);
  const selected = selectedAccessibilityAuditRow();
  qs("#accessibility-audit-verified-count").textContent = `${summary.verified} verified`;
  qs("#accessibility-audit-pending-count").textContent = `${summary.pending} pending`;
  qs("#accessibility-audit-blocked-count").textContent = `${summary.blocked} blocked`;
  renderAccessibilityAuditDetail(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "accessibility-audit-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.accessibilityAudit = item.key;
    row.dataset.auditStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("div");
    const label = document.createElement("strong");
    label.textContent = item.label;
    const path = document.createElement("small");
    path.textContent = item.path;
    const evidence = document.createElement("code");
    evidence.textContent = `${item.key}: ${item.evidence}`;
    detail.append(label, path, evidence);

    const status = document.createElement("span");
    status.className = `badge audit-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setAccessibilityAuditSelection(key, record = false, focusAfterRender = false) {
  if (!isAccessibilityAuditKey(key)) {
    return;
  }
  state.accessibilityAuditSelection = key;
  renderAccessibilityAudit();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-accessibility-audit]", "accessibilityAudit", key);
  }
  if (record) {
    const selected = selectedAccessibilityAuditRow();
    assistiveStatus(`Accessibility evidence ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Accessibility evidence selected", `a11y=${selected.key} status=${selected.status}`);
  }
}

function moveAccessibilityAuditFocus(currentButton, direction) {
  const buttons = qsa("[data-accessibility-audit]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setAccessibilityAuditSelection(next.dataset.accessibilityAudit, true, true);
}

function scrollAccessibilityAuditSelectionIntoView() {
  if (!pendingAccessibilityAuditScroll || state.activeTab !== "review") {
    return;
  }
  pendingAccessibilityAuditScroll = false;
  requestAnimationFrame(() => {
    const selected = qsa("[data-accessibility-audit]").find(
      (row) => row.dataset.accessibilityAudit === state.accessibilityAuditSelection
    );
    selected?.scrollIntoView({ block: "center", inline: "nearest" });
  });
}

function renderReviewChecks() {
  const verified = reviewCount("verified");
  const pending = reviewCount("pending");
  const blocked = reviewCount("blocked");
  qs("#review-verified-count").textContent = `${verified} verified`;
  qs("#review-pending-count").textContent = `${pending} pending`;
  qs("#review-blocked-count").textContent = `${blocked} blocked`;
  qs("#review-release-badge").textContent = blocked > 0 ? "claims blocked" : pending > 0 ? "migration pending" : "review clear";
  qs("#review-release-badge").classList.toggle("ok", blocked === 0 && pending === 0);
  qs("#review-release-badge").classList.toggle("warn", blocked === 0 && pending > 0);
  qs("#review-release-badge").classList.toggle("stop", blocked > 0);

  qsa("[data-review-filter]").forEach((button) => {
    const active = button.dataset.reviewFilter === state.reviewFilter;
    button.classList.toggle("is-active", active);
    button.setAttribute("aria-checked", String(active));
    button.tabIndex = active ? 0 : -1;
  });

  const list = qs("#review-checks");
  list.innerHTML = "";
  const visibleChecks =
    state.reviewFilter === "all" ? reviewChecks : reviewChecks.filter((check) => check.state === state.reviewFilter);
  qs("#review-filter-count").textContent = `${visibleChecks.length} of ${reviewChecks.length} checks`;
  if (visibleChecks.length === 0) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "No review checks match the current state.";
    list.append(empty);
    return;
  }
  visibleChecks.forEach((check) => {
    const row = document.createElement("article");
    row.className = "review-row";
    row.innerHTML = `
      <span class="swatch ${check.state === "verified" ? "ok" : check.state === "pending" ? "warn" : "stop"}" aria-hidden="true"></span>
      <div>
        <strong>${check.name}</strong>
        <small>${check.evidence}</small>
      </div>
      <code>${check.key}=${check.state}</code>
    `;
    list.append(row);
  });
}

function setReviewFilter(filter, record = false) {
  if (!reviewFilterOptions.includes(filter)) {
    return;
  }
  state.reviewFilter = filter;
  renderReviewChecks();
  renderReceiptPreview();
  safeWriteState();
  if (record) {
    const visibleCount = state.reviewFilter === "all" ? reviewChecks.length : reviewCount(state.reviewFilter);
    assistiveStatus(`Review filter ${filter} selected. ${visibleCount} checks visible.`);
    recordEvent("Review filter changed", `review_filter=${filter}`);
  }
}

function moveReviewFilterFocus(currentButton, direction) {
  const buttons = qsa("[data-review-filter]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setReviewFilter(next.dataset.reviewFilter, true);
  next.focus();
}

function receiptDiffFilterCount(filter) {
  const summary = receiptDiffSummary(selectedSavedReceipt());
  if (filter === "all") {
    return summary.row_count;
  }
  return summary.rows.filter((row) => row.status === filter).length;
}

function setReceiptDiffFilter(filter, record = false) {
  if (!receiptDiffFilterOptions.includes(filter)) {
    return;
  }
  state.receiptDiffFilter = filter;
  renderSavedReceipts();
  renderReceiptPreview();
  safeWriteState();
  if (record) {
    assistiveStatus(`Receipt diff filter ${filter} selected. ${receiptDiffFilterCount(filter)} fields visible.`);
    recordEvent("Receipt diff filter changed", `receipt_diff_filter=${filter}`);
  }
}

function moveReceiptDiffFilterFocus(currentButton, direction) {
  const buttons = qsa("[data-receipt-diff-filter]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setReceiptDiffFilter(next.dataset.receiptDiffFilter, true);
  next.focus();
}

function qaScenarioRows() {
  return qaScenarios.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    trigger: item.trigger,
    expected_result: item.expected,
    evidence: item.evidence,
    owner: item.owner,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.qaScenarioSelection,
    local_only: true,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function qaScenarioSummary(rows = qaScenarioRows()) {
  const selected =
    rows.find((row) => row.key === state.qaScenarioSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0];
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    runbook_complete: pending === 0 && blocked === 0,
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedQaScenarioRow() {
  const rows = qaScenarioRows();
  return (
    rows.find((row) => row.key === state.qaScenarioSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0]
  );
}

function renderQaScenarioDetail(row = selectedQaScenarioRow()) {
  if (!row) {
    return;
  }
  qs("#qa-scenario-detail-title").textContent = row.label;
  qs("#qa-scenario-detail-state").textContent = row.status;
  qs("#qa-scenario-detail-owner").textContent = row.owner;
  qs("#qa-scenario-detail-next").textContent = row.next_action;
}

function renderQaRunbook() {
  const list = qs("#qa-scenario-list");
  if (!list) {
    return;
  }
  const rows = qaScenarioRows();
  const summary = qaScenarioSummary(rows);
  const selected = selectedQaScenarioRow();
  qs("#qa-scenario-verified-count").textContent = `${summary.verified} verified`;
  qs("#qa-scenario-pending-count").textContent = `${summary.pending} pending`;
  qs("#qa-scenario-blocked-count").textContent = `${summary.blocked} blocked`;
  renderQaScenarioDetail(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "qa-scenario-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.qaScenario = item.key;
    row.dataset.qaScenarioStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "qa-scenario-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const trigger = document.createElement("small");
    trigger.textContent = item.trigger;
    const expected = document.createElement("p");
    expected.textContent = item.expected_result;
    const evidence = document.createElement("code");
    evidence.textContent = `${item.key}: ${item.evidence}`;
    detail.append(label, trigger, expected, evidence);

    const status = document.createElement("span");
    status.className = `badge qa-scenario-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setQaScenarioSelection(key, record = false, focusAfterRender = false) {
  if (!isQaScenarioKey(key)) {
    return;
  }
  state.qaScenarioSelection = key;
  renderQaRunbook();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-qa-scenario]", "qaScenario", key);
  }
  if (record) {
    const selected = selectedQaScenarioRow();
    assistiveStatus(`QA scenario ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("QA scenario selected", `scenario=${selected.key} status=${selected.status}`);
  }
}

function moveQaScenarioFocus(currentButton, direction) {
  const buttons = qsa("[data-qa-scenario]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setQaScenarioSelection(next.dataset.qaScenario, true, true);
}

function engineBindingRows() {
  return engineBindingItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    source: item.source,
    target: item.target,
    evidence: item.evidence,
    owner: item.owner,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.engineBindingSelection,
    simulated_source: true,
    live_installer_binding: false,
    local_only: true,
    production_execution_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function engineBindingSummary(rows = engineBindingRows()) {
  const selected =
    rows.find((row) => row.key === state.engineBindingSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0];
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    live_binding_complete: false,
    local_only: rows.every((row) => row.local_only === true),
    production_execution_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function engineBindingContractRows(row = selectedEngineBindingRow()) {
  if (!row) {
    return [];
  }
  const liveStatus = row.live_installer_binding ? "verified" : row.status === "blocked" ? "blocked" : "pending";
  const liveCurrent = row.live_installer_binding ? "bound" : "not bound";
  return [
    {
      key: "source_surface",
      label: "source surface",
      expected: row.source,
      current: "visible in test lane",
      status: "verified",
      evidence: row.evidence,
    },
    {
      key: "receipt_mapping",
      label: "receipt mapping",
      expected: "selected binding, status counts, and evidence route",
      current: "receipt-bound",
      status: "verified",
      evidence: `${row.key} appears in installer_engine_binding.selected`,
    },
    {
      key: "live_event_source",
      label: "live event source",
      expected: row.target,
      current: liveCurrent,
      status: liveStatus,
      evidence: row.live_installer_binding
        ? "live installer event source is connected"
        : "selected surface still uses simulated local state",
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      expected: "execution=0 production=0 main=0 edge=0",
      current: "closed in test lane",
      status: "verified",
      evidence: row.boundary,
    },
  ].map((contractRow) => ({
    ...contractRow,
    selected_binding_key: row.key,
    local_only: true,
    production_execution_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function engineBindingContractSummary(rows = engineBindingContractRows()) {
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: state.engineBindingSelection,
    live_binding_complete: rows.every((row) => row.key !== "live_event_source" || row.status === "verified"),
    local_only: rows.every((row) => row.local_only === true),
    production_execution_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function engineEventAdapterRows() {
  return engineEventAdapterItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    phase: item.phase,
    source: item.source,
    binding: item.binding,
    evidence: item.evidence,
    next_action: item.next,
    boundary: item.boundary,
    adapter_contract_visible: true,
    live_installer_event_bound: false,
    local_only: true,
    production_execution_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function engineEventAdapterSummary(rows = engineEventAdapterRows()) {
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    live_event_adapter_complete: false,
    local_only: rows.every((row) => row.local_only === true),
    production_execution_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedEngineBindingRow() {
  const rows = engineBindingRows();
  return (
    rows.find((row) => row.key === state.engineBindingSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0]
  );
}

function renderEngineBindingDetail(row = selectedEngineBindingRow()) {
  if (!row) {
    return;
  }
  qs("#engine-binding-detail-title").textContent = row.label;
  qs("#engine-binding-detail-state").textContent = row.status;
  qs("#engine-binding-detail-owner").textContent = row.owner;
  qs("#engine-binding-detail-next").textContent = row.next_action;
}

function renderEngineBindingContract(row = selectedEngineBindingRow()) {
  const list = qs("#engine-binding-contract-list");
  const statusBadge = qs("#engine-binding-contract-status");
  if (!list || !statusBadge) {
    return;
  }
  const rows = engineBindingContractRows(row);
  const summary = engineBindingContractSummary(rows);
  const badgeClass = summary.blocked > 0 ? "stop" : summary.pending > 0 ? "warn" : "ok";
  statusBadge.className = `badge ${badgeClass}`;
  statusBadge.textContent =
    summary.blocked > 0 ? `${summary.blocked} blocked` : summary.pending > 0 ? `${summary.pending} pending` : "verified";
  list.innerHTML = "";
  rows.forEach((item) => {
    const contractRow = document.createElement("div");
    contractRow.className = "engine-binding-contract-row";
    contractRow.dataset.contractStatus = item.status;
    contractRow.setAttribute("role", "listitem");

    const title = document.createElement("strong");
    title.textContent = item.label;
    const current = document.createElement("span");
    current.textContent = `${item.current} / ${item.status}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    const evidence = document.createElement("code");
    evidence.textContent = `evidence: ${item.evidence}`;

    contractRow.append(title, current, expected, evidence);
    list.append(contractRow);
  });
}

function renderEngineEventAdapter() {
  const list = qs("#engine-event-adapter-list");
  if (!list) {
    return;
  }
  const rows = engineEventAdapterRows();
  const summary = engineEventAdapterSummary(rows);
  qs("#engine-event-adapter-verified-count").textContent = `${summary.verified} verified`;
  qs("#engine-event-adapter-pending-count").textContent = `${summary.pending} pending`;
  qs("#engine-event-adapter-blocked-count").textContent = `${summary.blocked} blocked`;
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("div");
    row.className = "engine-event-adapter-row";
    row.dataset.eventStatus = item.status;
    row.setAttribute("role", "listitem");

    const label = document.createElement("strong");
    label.textContent = item.label;
    const phase = document.createElement("span");
    phase.textContent = `${item.phase} / ${item.status}`;
    const binding = document.createElement("code");
    binding.textContent = `binding: ${item.binding}`;
    const evidence = document.createElement("code");
    evidence.textContent = `evidence: ${item.evidence}`;
    const boundary = document.createElement("code");
    boundary.textContent = `boundary: ${item.boundary}`;

    row.append(label, phase, binding, evidence, boundary);
    list.append(row);
  });
}

function renderEngineBinding() {
  const list = qs("#engine-binding-list");
  if (!list) {
    return;
  }
  const rows = engineBindingRows();
  const summary = engineBindingSummary(rows);
  const selected = selectedEngineBindingRow();
  qs("#engine-binding-verified-count").textContent = `${summary.verified} verified`;
  qs("#engine-binding-pending-count").textContent = `${summary.pending} pending`;
  qs("#engine-binding-blocked-count").textContent = `${summary.blocked} blocked`;
  renderEngineBindingDetail(selected);
  renderEngineBindingContract(selected);
  renderEngineEventAdapter();
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "engine-binding-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.engineBinding = item.key;
    row.dataset.engineBindingStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "engine-binding-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const route = document.createElement("small");
    route.textContent = `${item.source} -> ${item.target}`;
    const evidence = document.createElement("p");
    evidence.textContent = item.evidence;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, route, evidence, boundary);

    const status = document.createElement("span");
    status.className = `badge engine-binding-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setEngineBindingSelection(key, record = false, focusAfterRender = false) {
  if (!isEngineBindingKey(key)) {
    return;
  }
  state.engineBindingSelection = key;
  renderEngineBinding();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-engine-binding]", "engineBinding", key);
  }
  if (record) {
    const selected = selectedEngineBindingRow();
    assistiveStatus(`Installer engine binding ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Installer engine binding selected", `engine=${selected.key} status=${selected.status}`);
  }
}

function moveEngineBindingFocus(currentButton, direction) {
  const buttons = qsa("[data-engine-binding]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setEngineBindingSelection(next.dataset.engineBinding, true, true);
}

function visualBaselineRows() {
  return visualBaselineItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    viewport: item.viewport,
    evidence: item.evidence,
    owner: item.owner,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.visualBaselineSelection,
    local_only: true,
    visual_regression_claim: item.status === "verified" ? "local-baseline" : "not-cleared",
    production_visual_signoff: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function visualBaselineSummary(rows = visualBaselineRows()) {
  const selected =
    rows.find((row) => row.key === state.visualBaselineSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0];
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    local_baseline_complete: pending === 0 && blocked === 0,
    local_only: rows.every((row) => row.local_only === true),
    production_visual_signoff: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedVisualBaselineRow() {
  const rows = visualBaselineRows();
  return (
    rows.find((row) => row.key === state.visualBaselineSelection) ||
    rows.find((row) => row.status === "pending") ||
    rows[0]
  );
}

function renderVisualBaselineDetail(row = selectedVisualBaselineRow()) {
  if (!row) {
    return;
  }
  qs("#visual-baseline-detail-title").textContent = row.label;
  qs("#visual-baseline-detail-state").textContent = row.status;
  qs("#visual-baseline-detail-owner").textContent = row.owner;
  qs("#visual-baseline-detail-next").textContent = row.next_action;
}

function renderVisualBaseline() {
  const list = qs("#visual-baseline-list");
  if (!list) {
    return;
  }
  const rows = visualBaselineRows();
  const summary = visualBaselineSummary(rows);
  const selected = selectedVisualBaselineRow();
  qs("#visual-baseline-verified-count").textContent = `${summary.verified} verified`;
  qs("#visual-baseline-pending-count").textContent = `${summary.pending} pending`;
  qs("#visual-baseline-blocked-count").textContent = `${summary.blocked} blocked`;
  renderVisualBaselineDetail(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "visual-baseline-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.visualBaseline = item.key;
    row.dataset.visualBaselineStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "visual-baseline-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const viewport = document.createElement("small");
    viewport.textContent = item.viewport;
    const evidence = document.createElement("p");
    evidence.textContent = item.evidence;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, viewport, evidence, boundary);

    const status = document.createElement("span");
    status.className = `badge visual-baseline-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setVisualBaselineSelection(key, record = false, focusAfterRender = false) {
  if (!isVisualBaselineKey(key)) {
    return;
  }
  state.visualBaselineSelection = key;
  renderVisualBaseline();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-visual-baseline]", "visualBaseline", key);
  }
  if (record) {
    const selected = selectedVisualBaselineRow();
    assistiveStatus(`Visual baseline ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Visual baseline selected", `visual=${selected.key} status=${selected.status}`);
  }
}

function moveVisualBaselineFocus(currentButton, direction) {
  const buttons = qsa("[data-visual-baseline]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setVisualBaselineSelection(next.dataset.visualBaseline, true, true);
}

function releaseAcceptanceRows() {
  return releaseAcceptanceItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    source: item.source,
    evidence: item.evidence,
    owner: item.owner,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.releaseAcceptanceSelection,
    local_only: true,
    ready_for_release: false,
    can_promote: false,
    production_evidence_claim: 0,
    production_installer_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function releaseAcceptanceSummary(rows = releaseAcceptanceRows()) {
  const selected =
    rows.find((row) => row.key === state.releaseAcceptanceSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0];
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    ready_for_release: false,
    can_promote: false,
    local_acceptance_complete: pending === 0 && blocked === 0,
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    production_installer_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedReleaseAcceptanceRow() {
  const rows = releaseAcceptanceRows();
  return (
    rows.find((row) => row.key === state.releaseAcceptanceSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0]
  );
}

function renderReleaseAcceptanceDetail(row = selectedReleaseAcceptanceRow()) {
  if (!row) {
    return;
  }
  qs("#release-acceptance-detail-title").textContent = row.label;
  qs("#release-acceptance-detail-state").textContent = row.status;
  qs("#release-acceptance-detail-owner").textContent = row.owner;
  qs("#release-acceptance-detail-next").textContent = row.next_action;
}

function renderReleaseAcceptance() {
  const list = qs("#release-acceptance-list");
  if (!list) {
    return;
  }
  const rows = releaseAcceptanceRows();
  const summary = releaseAcceptanceSummary(rows);
  const selected = selectedReleaseAcceptanceRow();
  qs("#release-acceptance-verified-count").textContent = `${summary.verified} verified`;
  qs("#release-acceptance-pending-count").textContent = `${summary.pending} pending`;
  qs("#release-acceptance-blocked-count").textContent = `${summary.blocked} blocked`;
  renderReleaseAcceptanceDetail(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "release-acceptance-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.releaseAcceptance = item.key;
    row.dataset.releaseAcceptanceStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "release-acceptance-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const source = document.createElement("small");
    source.textContent = item.source;
    const evidence = document.createElement("p");
    evidence.textContent = item.evidence;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, source, evidence, boundary);

    const status = document.createElement("span");
    status.className = `badge release-acceptance-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setReleaseAcceptanceSelection(key, record = false, focusAfterRender = false) {
  if (!isReleaseAcceptanceKey(key)) {
    return;
  }
  state.releaseAcceptanceSelection = key;
  renderReleaseAcceptance();
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-release-acceptance]", "releaseAcceptance", key);
  }
  if (record) {
    const selected = selectedReleaseAcceptanceRow();
    assistiveStatus(`Release acceptance ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Release acceptance selected", `acceptance=${selected.key} status=${selected.status}`);
  }
}

function moveReleaseAcceptanceFocus(currentButton, direction) {
  const buttons = qsa("[data-release-acceptance]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setReleaseAcceptanceSelection(next.dataset.releaseAcceptance, true, true);
}

function migrationReviewRows() {
  return migrationMap.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.state,
    source: item.source,
    destination: item.destination,
    guard: item.guard,
    evidence: item.evidence,
    owner: item.owner,
    next_action: item.next,
    boundary: item.boundary,
    selected: item.key === state.migrationReviewSelection,
    migrated_to_main_gui: false,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
    local_only: true,
  }));
}

function migrationReviewSummary(rows = migrationReviewRows()) {
  const selected =
    rows.find((row) => row.key === state.migrationReviewSelection) ||
    rows.find((row) => row.status === "needs binding") ||
    rows[0];
  return {
    total: rows.length,
    candidate: rows.filter((row) => row.status === "candidate").length,
    needs_binding: rows.filter((row) => row.status === "needs binding").length,
    blocked: rows.filter((row) => row.status === "blocked").length,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    local_only: rows.every((row) => row.local_only === true),
    migrated_to_main_gui: false,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function migrationParityRows(row = selectedMigrationReviewRow()) {
  if (!row) {
    return [];
  }
  const guardedCompareStatus = row.status === "blocked" ? "blocked" : "pending";
  const receiptStatus = row.status === "needs binding" ? "pending" : "verified";
  return [
    {
      key: "prototype_evidence",
      label: "prototype evidence",
      expected: row.source,
      current: "captured in test lane",
      status: "verified",
      evidence: row.evidence,
    },
    {
      key: "guarded_panel_compare",
      label: "guarded Panel compare",
      expected: row.destination,
      current: row.status === "blocked" ? "blocked before port" : "comparison pending",
      status: guardedCompareStatus,
      evidence: row.guard,
    },
    {
      key: "receipt_data_contract",
      label: "receipt data contract",
      expected: "selected migration row, route, guard, and next action",
      current: receiptStatus === "verified" ? "receipt-bound" : "binding pending",
      status: receiptStatus,
      evidence: `${row.key} appears in migration_review.selected`,
    },
    {
      key: "authority_boundary",
      label: "authority boundary",
      expected: "main=0 edge=0 production=0",
      current: "closed in test lane",
      status: "verified",
      evidence: row.boundary,
    },
  ].map((parityRow) => ({
    ...parityRow,
    selected_migration_key: row.key,
    local_only: true,
    guarded_panel_mutation_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function migrationParitySummary(rows = migrationParityRows()) {
  const pending = rows.filter((row) => row.status === "pending").length;
  const blocked = rows.filter((row) => row.status === "blocked").length;
  return {
    total: rows.length,
    verified: rows.filter((row) => row.status === "verified").length,
    pending,
    blocked,
    selected_key: state.migrationReviewSelection,
    can_migrate_to_guarded_panel: false,
    local_only: rows.every((row) => row.local_only === true),
    guarded_panel_mutation_authority: 0,
    production_evidence_claim: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedMigrationReviewRow() {
  const rows = migrationReviewRows();
  return (
    rows.find((row) => row.key === state.migrationReviewSelection) ||
    rows.find((row) => row.status === "needs binding") ||
    rows[0]
  );
}

function renderMigrationReviewDetail(row = selectedMigrationReviewRow()) {
  if (!row) {
    return;
  }
  qs("#migration-detail-title").textContent = row.label;
  qs("#migration-detail-state").textContent = row.status;
  qs("#migration-detail-owner").textContent = row.owner;
  qs("#migration-detail-next").textContent = row.next_action;
}

function renderMigrationParity(row = selectedMigrationReviewRow()) {
  const list = qs("#migration-parity-list");
  const statusBadge = qs("#migration-parity-status");
  if (!list || !statusBadge) {
    return;
  }
  const rows = migrationParityRows(row);
  const summary = migrationParitySummary(rows);
  const badgeClass = summary.blocked > 0 ? "stop" : summary.pending > 0 ? "warn" : "ok";
  statusBadge.className = `badge ${badgeClass}`;
  statusBadge.textContent =
    summary.blocked > 0 ? `${summary.blocked} blocked` : summary.pending > 0 ? `${summary.pending} pending` : "verified";
  list.innerHTML = "";
  rows.forEach((item) => {
    const parityRow = document.createElement("div");
    parityRow.className = "migration-parity-row";
    parityRow.dataset.parityStatus = item.status;
    parityRow.setAttribute("role", "listitem");

    const title = document.createElement("strong");
    title.textContent = item.label;
    const current = document.createElement("span");
    current.textContent = `${item.current} / ${item.status}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    const evidence = document.createElement("code");
    evidence.textContent = `evidence: ${item.evidence}`;

    parityRow.append(title, current, expected, evidence);
    list.append(parityRow);
  });
}

function renderMigrationMap() {
  const map = qs("#migration-map");
  if (!map) {
    return;
  }
  const rows = migrationReviewRows();
  const selected = selectedMigrationReviewRow();
  renderMigrationReviewDetail(selected);
  renderMigrationParity(selected);
  map.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "migration-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.migrationStatus = item.status;
    row.dataset.migrationReview = item.key;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const detail = document.createElement("span");
    detail.className = "migration-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const route = document.createElement("small");
    route.textContent = `${item.source} -> ${item.destination}`;
    const guard = document.createElement("p");
    guard.textContent = item.guard;
    const evidence = document.createElement("code");
    evidence.textContent = `${item.key}: ${item.evidence}`;
    detail.append(label, route, guard, evidence);

    const status = document.createElement("span");
    status.className = `badge migration-state ${item.status === "candidate" ? "ok" : item.status === "needs binding" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(detail, status);
    map.append(row);
  });
}

function setMigrationReviewSelection(key, record = false, focusAfterRender = false) {
  if (!isMigrationReviewKey(key)) {
    return;
  }
  state.migrationReviewSelection = key;
  renderMigrationMap();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-migration-review]", "migrationReview", key);
  }
  if (record) {
    const selected = selectedMigrationReviewRow();
    assistiveStatus(`Migration surface ${selected.label} selected. State ${selected.status}.`);
    recordEvent("Migration surface selected", `migration=${selected.key} state=${selected.status}`);
  }
}

function moveMigrationReviewFocus(currentButton, direction) {
  const buttons = qsa("[data-migration-review]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setMigrationReviewSelection(next.dataset.migrationReview, true, true);
}

function selectedReadinessComparisonRow() {
  const rows = readinessComparisonRows();
  return (
    rows.find((row) => row.key === state.readinessCompareSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0]
  );
}

function renderReadinessCompareDetail(row = selectedReadinessComparisonRow()) {
  if (!row) {
    return;
  }
  qs("#readiness-compare-detail-title").textContent = row.label;
  qs("#readiness-compare-detail-local").textContent = row.local_proof;
  qs("#readiness-compare-detail-production").textContent = row.production_requirement;
  qs("#readiness-compare-detail-next").textContent = row.next_action;
}

function renderReadinessCompareProof(row = selectedReadinessComparisonRow()) {
  const list = qs("#readiness-compare-proof-list");
  const statusBadge = qs("#readiness-compare-proof-status");
  if (!list || !statusBadge) {
    return;
  }
  const rows = readinessComparisonProofRows(row);
  const summary = readinessComparisonProofSummary(rows);
  statusBadge.className = `badge ${summary.blocked > 0 ? "stop" : summary.pending > 0 ? "warn" : "ok"}`;
  statusBadge.textContent = summary.blocked > 0 ? `${summary.blocked} blocked` : summary.pending > 0 ? `${summary.pending} pending` : "verified";
  list.innerHTML = "";
  rows.forEach((item) => {
    const proofRow = document.createElement("div");
    proofRow.className = "readiness-compare-proof-row";
    proofRow.dataset.proofStatus = item.status;
    proofRow.setAttribute("role", "listitem");

    const title = document.createElement("strong");
    title.textContent = item.label;
    const current = document.createElement("span");
    current.textContent = `${item.current} / ${item.status}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    const evidence = document.createElement("code");
    evidence.textContent = `evidence: ${item.evidence}`;

    proofRow.append(title, current, expected, evidence);
    list.append(proofRow);
  });
}

function renderReadinessCompareAlignment(row = selectedReadinessComparisonRow()) {
  const list = qs("#readiness-compare-alignment-list");
  if (!list || !row) {
    return;
  }
  const rows = readinessComparisonAlignmentRows(row);
  const summary = readinessComparisonAlignmentSummary(rows);
  const status = qs("#readiness-compare-alignment-status");
  status.textContent = summary.review > 0 ? `${summary.review} review` : "aligned";
  status.classList.toggle("ok", summary.review === 0);
  status.classList.toggle("warn", summary.review > 0);
  const action = qs("[data-action='align-readiness-compare-context']");
  action.textContent = summary.action_label;
  action.dataset.alignActionState = summary.action_state;
  action.setAttribute("aria-label", `${summary.action_label}. ${summary.aligned} aligned and ${summary.review} need review.`);
  action.setAttribute("aria-disabled", String(summary.review === 0));
  list.innerHTML = "";
  rows.forEach((item) => {
    const check = document.createElement("div");
    check.className = "readiness-compare-alignment-row";
    check.dataset.alignmentStatus = item.status;
    check.setAttribute("role", "listitem");

    const detail = document.createElement("div");
    const label = document.createElement("strong");
    label.textContent = item.label;
    const current = document.createElement("small");
    current.textContent = `current: ${item.current}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    detail.append(label, current, expected);

    const badge = document.createElement("span");
    badge.className = `badge readiness-compare-alignment-state ${item.status === "aligned" ? "ok" : "warn"}`;
    badge.textContent = item.status;

    check.append(detail, badge);
    list.append(check);
  });
}

function renderReadinessCompare() {
  const list = qs("#readiness-compare-list");
  if (!list) {
    return;
  }
  const rows = readinessComparisonRows();
  const summary = readinessComparisonSummary(rows);
  const selected = selectedReadinessComparisonRow();
  qs("#readiness-compare-status").textContent = summary.can_promote ? "ready" : "local proof only";
  qs("#readiness-compare-local").textContent = `${summary.verified} verified`;
  qs("#readiness-compare-production").textContent = `${summary.blocked} blocked / ${summary.pending} pending`;
  qs("#readiness-compare-selected").textContent = `${selected.label} / ${selected.status}`;
  qs("#readiness-compare-authority").textContent = String(summary.production_evidence_claim);
  renderReadinessCompareDetail(selected);
  renderReadinessCompareProof(selected);
  renderReadinessCompareAlignment(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "readiness-compare-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.readinessCompare = item.key;
    row.dataset.readinessCompareStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "readiness-compare-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const local = document.createElement("small");
    local.textContent = item.local_proof;
    const production = document.createElement("p");
    production.textContent = item.production_requirement;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, local, production, boundary);

    const status = document.createElement("span");
    status.className = `badge readiness-compare-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setReadinessCompareSelection(key, record = false, focusAfterRender = false) {
  if (!isReadinessCompareKey(key)) {
    return;
  }
  state.readinessCompareSelection = key;
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-readiness-compare]", "readinessCompare", key);
  }
  if (record) {
    const selected = selectedReadinessComparisonRow();
    assistiveStatus(`Readiness comparison ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Readiness comparison selected", `compare=${selected.key} status=${selected.status}`);
  }
}

function moveReadinessCompareFocus(currentButton, direction) {
  const buttons = qsa("[data-readiness-compare]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setReadinessCompareSelection(next.dataset.readinessCompare, true, true);
}

function alignReadinessComparisonContext(record = true) {
  const selected = selectedReadinessComparisonRow();
  if (!selected) {
    return;
  }
  const currentSummary = readinessComparisonAlignmentSummary();
  if (currentSummary.review === 0) {
    qs("[data-action='align-readiness-compare-context']")?.focus({ preventScroll: true });
    assistiveStatus(`Readiness comparison context already aligned for ${selected.label}.`);
    notify("Comparison context already aligned");
    return;
  }
  const target = readinessComparisonContextTarget(selected);
  const gateKeys = traceabilityKeyList(target.promotion_gate);
  const blockerKeys = traceabilityKeyList(target.blockers);
  const gate = gateKeys.find(isPromotionGateKey);
  const blocker = blockerKeys.find(isProductionBlockerKey);
  if (isTraceabilityKey(target.trace)) {
    state.traceabilitySelection = target.trace;
  }
  if (isEvidenceIntakeKey(target.intake_packet)) {
    state.evidenceIntakeSelection = target.intake_packet;
  }
  if (gate) {
    state.promotionGateSelection = gate;
  }
  if (isReleaseAcceptanceKey(target.acceptance_gate)) {
    state.releaseAcceptanceSelection = target.acceptance_gate;
  }
  if (blocker) {
    state.productionBlockerSelection = blocker;
  }
  renderReadinessCompare();
  renderEvidenceIntake();
  renderTraceabilityMatrix();
  renderPromotionGate();
  renderReleaseAcceptance();
  renderProductionBlockers(state.blockerFilter);
  renderReceiptPreview();
  safeWriteState();
  requestAnimationFrame(() => {
    qs("[data-action='align-readiness-compare-context']")?.focus({ preventScroll: true });
  });
  if (record) {
    const summary = readinessComparisonAlignmentSummary();
    assistiveStatus(`Readiness comparison context aligned for ${selected.label}. ${summary.aligned} aligned, ${summary.review} review.`);
    recordEvent("Readiness comparison context aligned", `compare=${selected.key} aligned=${summary.aligned} review=${summary.review}`);
    notify("Comparison context aligned");
  }
}

function scrollReadinessCompareSelectionIntoView() {
  if (!pendingReadinessCompareScroll || state.activeTab !== "readiness") {
    return;
  }
  pendingReadinessCompareScroll = false;
  requestAnimationFrame(() => {
    if (!window.matchMedia("(max-width: 700px)").matches) {
      return;
    }
    const selected = qsa("[data-readiness-compare]").find(
      (row) => row.dataset.readinessCompare === state.readinessCompareSelection
    );
    selected?.scrollIntoView({ block: "center", inline: "nearest" });
  });
}

function selectedEvidenceIntakeRow() {
  const rows = evidenceIntakeRows();
  return (
    rows.find((row) => row.key === state.evidenceIntakeSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0]
  );
}

function evidenceIntakeTone(status) {
  if (status === "local-only") {
    return "ok";
  }
  return status === "waiting" ? "warn" : "stop";
}

function renderEvidenceIntakeDetail(row = selectedEvidenceIntakeRow()) {
  if (!row) {
    return;
  }
  qs("#evidence-intake-detail-title").textContent = row.label;
  qs("#evidence-intake-detail-packet").textContent = row.packet;
  qs("#evidence-intake-detail-decision").textContent = row.decision;
  qs("#evidence-intake-detail-next").textContent = row.next_action;
}

function renderEvidenceIntakeContract(row = selectedEvidenceIntakeRow()) {
  const list = qs("#evidence-intake-contract-list");
  const statusBadge = qs("#evidence-intake-contract-status");
  if (!list || !statusBadge) {
    return;
  }
  const rows = evidenceIntakeContractRows(row);
  const summary = evidenceIntakeContractSummary(rows);
  const badgeClass = summary.blocked > 0 ? "stop" : summary.pending > 0 ? "warn" : "ok";
  statusBadge.className = `badge ${badgeClass}`;
  statusBadge.textContent =
    summary.blocked > 0 ? `${summary.blocked} blocked` : summary.pending > 0 ? `${summary.pending} pending` : "verified";
  list.innerHTML = "";
  rows.forEach((item) => {
    const contractRow = document.createElement("div");
    contractRow.className = "evidence-intake-contract-row";
    contractRow.dataset.contractStatus = item.status;
    contractRow.setAttribute("role", "listitem");

    const title = document.createElement("strong");
    title.textContent = item.label;
    const current = document.createElement("span");
    current.textContent = `${item.current} / ${item.status}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    const evidence = document.createElement("code");
    evidence.textContent = `evidence: ${item.evidence}`;

    contractRow.append(title, current, expected, evidence);
    list.append(contractRow);
  });
}

function renderEvidenceIntake() {
  const list = qs("#evidence-intake-list");
  if (!list) {
    return;
  }
  const rows = evidenceIntakeRows();
  const summary = evidenceIntakeSummary(rows);
  const selected = selectedEvidenceIntakeRow();
  qs("#evidence-intake-status").textContent = summary.blocked > 0 ? "intake blocked" : "local intake only";
  qs("#evidence-intake-local").textContent = `${summary.local_only} local-only`;
  qs("#evidence-intake-waiting").textContent = `${summary.waiting} waiting`;
  qs("#evidence-intake-blocked").textContent = `${summary.blocked} blocked`;
  qs("#evidence-intake-authority").textContent = String(summary.intake_authority);
  renderEvidenceIntakeDetail(selected);
  renderEvidenceIntakeContract(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "evidence-intake-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.evidenceIntake = item.key;
    row.dataset.evidenceIntakeStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${evidenceIntakeTone(item.status)}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "evidence-intake-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const packet = document.createElement("small");
    packet.textContent = item.packet;
    const decision = document.createElement("p");
    decision.textContent = item.decision;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, packet, decision, boundary);

    const status = document.createElement("span");
    status.className = `badge evidence-intake-state ${evidenceIntakeTone(item.status)}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setEvidenceIntakeSelection(key, record = false, focusAfterRender = false) {
  if (!isEvidenceIntakeKey(key)) {
    return;
  }
  state.evidenceIntakeSelection = key;
  renderEvidenceIntake();
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-evidence-intake]", "evidenceIntake", key);
  }
  if (record) {
    const selected = selectedEvidenceIntakeRow();
    assistiveStatus(`Evidence intake ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Evidence intake selected", `intake=${selected.key} status=${selected.status}`);
  }
}

function moveEvidenceIntakeFocus(currentButton, direction) {
  const buttons = qsa("[data-evidence-intake]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setEvidenceIntakeSelection(next.dataset.evidenceIntake, true, true);
}

function scrollEvidenceIntakeSelectionIntoView() {
  if (!pendingEvidenceIntakeScroll || state.activeTab !== "readiness") {
    return;
  }
  pendingEvidenceIntakeScroll = false;
  requestAnimationFrame(() => {
    if (!window.matchMedia("(max-width: 700px)").matches) {
      return;
    }
    const selected = qsa("[data-evidence-intake]").find(
      (row) => row.dataset.evidenceIntake === state.evidenceIntakeSelection
    );
    selected?.scrollIntoView({ block: "center", inline: "nearest" });
  });
}

function selectedTraceabilityRow() {
  const rows = traceabilityRows();
  return (
    rows.find((row) => row.key === state.traceabilitySelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0]
  );
}

function traceabilityTone(status) {
  if (status === "covered" || status === "verified") {
    return "ok";
  }
  return status === "waiting" ? "warn" : "stop";
}

function renderTraceabilityDetail(row = selectedTraceabilityRow()) {
  if (!row) {
    return;
  }
  qs("#traceability-detail-title").textContent = row.label;
  qs("#traceability-detail-blockers").textContent = row.blockers;
  qs("#traceability-detail-packet").textContent = row.intake_packet;
  qs("#traceability-detail-gate").textContent = row.promotion_gate;
  qs("#traceability-detail-acceptance").textContent = row.acceptance_gate;
  qs("#traceability-detail-next").textContent = row.next_action;
}

function renderTraceabilityAlignment(row = selectedTraceabilityRow()) {
  const list = qs("#traceability-alignment-list");
  if (!list || !row) {
    return;
  }
  const rows = traceabilityAlignmentRows(row);
  const summary = traceabilityAlignmentSummary(rows);
  const status = qs("#traceability-alignment-status");
  status.textContent = summary.review > 0 ? `${summary.review} review` : "aligned";
  status.classList.toggle("ok", summary.review === 0);
  status.classList.toggle("warn", summary.review > 0);
  const action = qs("[data-action='align-trace-context']");
  action.textContent = summary.action_label;
  action.dataset.alignActionState = summary.action_state;
  action.setAttribute("aria-label", `${summary.action_label}. ${summary.aligned} aligned and ${summary.review} need review.`);
  action.setAttribute("aria-disabled", String(summary.review === 0));
  list.innerHTML = "";
  rows.forEach((item) => {
    const check = document.createElement("div");
    check.className = "traceability-alignment-row";
    check.dataset.alignmentStatus = item.status;
    check.setAttribute("role", "listitem");

    const detail = document.createElement("div");
    const label = document.createElement("strong");
    label.textContent = item.label;
    const current = document.createElement("small");
    current.textContent = `current: ${item.current}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    detail.append(label, current, expected);

    const badge = document.createElement("span");
    badge.className = `badge traceability-alignment-state ${item.status === "aligned" ? "ok" : "warn"}`;
    badge.textContent = item.status;

    check.append(detail, badge);
    list.append(check);
  });
}

function renderTraceabilityMatrix() {
  const list = qs("#traceability-list");
  if (!list) {
    return;
  }
  const rows = traceabilityRows();
  const summary = traceabilitySummary(rows);
  const selected = selectedTraceabilityRow();
  const status = qs("#traceability-status");
  status.textContent = summary.blocked > 0 ? "trace blocked" : "trace covered";
  status.classList.toggle("ok", summary.blocked === 0);
  status.classList.toggle("warn", summary.blocked === 0 && summary.waiting > 0);
  status.classList.toggle("stop", summary.blocked > 0);
  qs("#traceability-covered").textContent = `${summary.covered} covered`;
  qs("#traceability-waiting").textContent = `${summary.waiting} waiting`;
  qs("#traceability-blocked").textContent = `${summary.blocked} blocked`;
  qs("#traceability-authority").textContent = String(summary.production_evidence_claim);
  renderTraceabilityDetail(selected);
  renderTraceabilityAlignment(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "traceability-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.traceability = item.key;
    row.dataset.traceabilityStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${traceabilityTone(item.status)}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "traceability-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const route = document.createElement("small");
    route.textContent = `${item.blockers} -> ${item.intake_packet} -> ${item.promotion_gate} -> ${item.acceptance_gate}`;
    const evidence = document.createElement("p");
    evidence.textContent = item.evidence;
    const boundary = document.createElement("code");
    boundary.textContent = `${item.key}: ${item.boundary}`;
    detail.append(label, route, evidence, boundary);

    const status = document.createElement("span");
    status.className = `badge traceability-state ${traceabilityTone(item.status)}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setTraceabilitySelection(key, record = false, focusAfterRender = false) {
  if (!isTraceabilityKey(key)) {
    return;
  }
  state.traceabilitySelection = key;
  renderTraceabilityMatrix();
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-traceability]", "traceability", key);
  }
  if (record) {
    const selected = selectedTraceabilityRow();
    assistiveStatus(`Traceability path ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Traceability path selected", `trace=${selected.key} status=${selected.status}`);
  }
}

function moveTraceabilityFocus(currentButton, direction) {
  const buttons = qsa("[data-traceability]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setTraceabilitySelection(next.dataset.traceability, true, true);
}

function alignTraceabilityContext(record = true) {
  const selected = selectedTraceabilityRow();
  if (!selected) {
    return;
  }
  const currentSummary = traceabilityAlignmentSummary();
  if (currentSummary.review === 0) {
    qs("[data-action='align-trace-context']")?.focus({ preventScroll: true });
    assistiveStatus(`Trace context already aligned for ${selected.label}.`);
    notify("Trace context already aligned");
    return;
  }
  const gateKeys = traceabilityKeyList(selected.promotion_gate);
  const blockerKeys = traceabilityKeyList(selected.blockers);
  const gate = gateKeys.find(isPromotionGateKey);
  const blocker = blockerKeys.find(isProductionBlockerKey);
  if (isEvidenceIntakeKey(selected.intake_packet)) {
    state.evidenceIntakeSelection = selected.intake_packet;
  }
  if (gate) {
    state.promotionGateSelection = gate;
  }
  if (isReleaseAcceptanceKey(selected.acceptance_gate)) {
    state.releaseAcceptanceSelection = selected.acceptance_gate;
  }
  if (blocker) {
    state.productionBlockerSelection = blocker;
  }
  renderEvidenceIntake();
  renderPromotionGate();
  renderReleaseAcceptance();
  renderProductionBlockers(state.blockerFilter);
  renderTraceabilityMatrix();
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  requestAnimationFrame(() => {
    qs("[data-action='align-trace-context']")?.focus({ preventScroll: true });
  });
  if (record) {
    const summary = traceabilityAlignmentSummary();
    assistiveStatus(`Trace context aligned for ${selected.label}. ${summary.aligned} aligned, ${summary.review} review.`);
    recordEvent("Trace context aligned", `trace=${selected.key} aligned=${summary.aligned} review=${summary.review}`);
    notify("Trace context aligned");
  }
}

function scrollTraceabilitySelectionIntoView() {
  if (!pendingTraceabilityScroll || state.activeTab !== "readiness") {
    return;
  }
  pendingTraceabilityScroll = false;
  requestAnimationFrame(() => {
    if (!window.matchMedia("(max-width: 700px)").matches) {
      return;
    }
    const selected = qsa("[data-traceability]").find(
      (row) => row.dataset.traceability === state.traceabilitySelection
    );
    selected?.scrollIntoView({ block: "center", inline: "nearest" });
  });
}

function promotionGateRows() {
  return promotionGateItems.map((item) => ({
    key: item.key,
    label: item.label,
    status: item.status,
    required: item.required,
    evidence: item.evidence,
    owner: item.owner,
    next_action: item.next,
    selected: item.key === state.promotionGateSelection,
    local_only: true,
    can_promote: false,
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  }));
}

function promotionGateSummary(rows = promotionGateRows()) {
  const blocked = rows.filter((row) => row.status === "blocked").length;
  const pending = rows.filter((row) => row.status === "pending").length;
  const verified = rows.filter((row) => row.status === "verified").length;
  const decision = blocked > 0 ? "blocked" : pending > 0 ? "pending" : "ready";
  const selected = rows.find((row) => row.key === state.promotionGateSelection) || rows.find((row) => row.status === "blocked") || rows[0];
  return {
    total: rows.length,
    verified,
    pending,
    blocked,
    decision,
    selected_key: selected?.key || "none",
    selected_status: selected?.status || "none",
    can_promote: false,
    missing_production_evidence: productionBlockerCount(),
    local_only: rows.every((row) => row.local_only === true),
    production_evidence_claim: 0,
    host_write_authority: 0,
    main_gui_mutation_required: 0,
    edge_gui_mutation_required: 0,
  };
}

function selectedPromotionGateRow() {
  const rows = promotionGateRows();
  return rows.find((row) => row.key === state.promotionGateSelection) || rows.find((row) => row.status === "blocked") || rows[0];
}

function renderPromotionGateDetail(row = selectedPromotionGateRow()) {
  if (!row) {
    return;
  }
  qs("#promotion-detail-title").textContent = row.label;
  qs("#promotion-detail-status").textContent = row.status;
  qs("#promotion-detail-owner").textContent = row.owner;
  qs("#promotion-detail-next").textContent = row.next_action;
}

function renderPromotionGate() {
  const list = qs("#promotion-gate-list");
  if (!list) {
    return;
  }
  const rows = promotionGateRows();
  const summary = promotionGateSummary(rows);
  const selected = selectedPromotionGateRow();
  qs("#promotion-gate-status").textContent = summary.decision === "ready" ? "ready" : summary.decision;
  qs("#promotion-gate-status").classList.toggle("ok", summary.decision === "ready");
  qs("#promotion-gate-status").classList.toggle("warn", summary.decision === "pending");
  qs("#promotion-gate-status").classList.toggle("stop", summary.decision === "blocked");
  qs("#promotion-decision").textContent = summary.can_promote ? "ready to promote" : "promotion blocked";
  qs("#promotion-evidence-missing").textContent = `${summary.missing_production_evidence} missing`;
  qs("#promotion-pending-count").textContent = `${summary.pending} pending`;
  qs("#promotion-claim-authority").textContent = String(summary.production_evidence_claim);
  renderPromotionGateDetail(selected);
  list.innerHTML = "";
  rows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "promotion-gate-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.promotionStatus = item.status;
    row.dataset.promotionGate = item.key;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = `swatch ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "promotion-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const required = document.createElement("small");
    required.textContent = item.required;
    const evidence = document.createElement("code");
    evidence.textContent = `${item.key}: ${item.evidence}`;
    detail.append(label, required, evidence);

    const status = document.createElement("span");
    status.className = `badge promotion-state ${item.status === "verified" ? "ok" : item.status === "pending" ? "warn" : "stop"}`;
    status.textContent = item.status;

    row.append(swatch, detail, status);
    list.append(row);
  });
}

function setPromotionGateSelection(key, record = false, focusAfterRender = false) {
  if (!isPromotionGateKey(key)) {
    return;
  }
  state.promotionGateSelection = key;
  renderPromotionGate();
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-promotion-gate]", "promotionGate", key);
  }
  if (record) {
    const selected = selectedPromotionGateRow();
    assistiveStatus(`Promotion gate ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Promotion gate selected", `promotion_gate=${selected.key}`);
  }
}

function movePromotionGateFocus(currentButton, direction) {
  const buttons = qsa("[data-promotion-gate]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setPromotionGateSelection(next.dataset.promotionGate, true, true);
}

function renderProductionBlockers(filter = "") {
  const board = qs("#blocker-board");
  const normalized = normalizeBlockerFilter(filter);
  state.blockerFilter = normalized;
  const rows = productionBlockerRows();
  const summary = productionBlockerSummary(rows);
  const selected = selectedProductionBlockerRow();
  renderProductionBlockerDetail(selected);
  renderProductionBlockerProof(selected);
  board.innerHTML = "";
  const visibleRows = productionBlockerVisibleRows(rows, normalized);
  qs("#blocker-count").textContent = `${summary.blocked} open`;
  qs("#blocker-search").value = normalized;
  qs("#blocker-filter-summary").textContent =
    summary.filter_active
      ? `${summary.visible} of ${summary.total} blockers for "${summary.filter}"`
      : `${summary.visible} of ${summary.total} blockers`;

  visibleRows.forEach((item) => {
    const row = document.createElement("button");
    row.type = "button";
    row.className = "blocker-row";
    row.classList.toggle("is-selected", item.key === selected.key);
    row.dataset.productionBlocker = item.key;
    row.dataset.productionBlockerStatus = item.status;
    row.setAttribute("role", "option");
    row.setAttribute("aria-selected", String(item.key === selected.key));
    row.tabIndex = item.key === selected.key ? 0 : -1;

    const swatch = document.createElement("span");
    swatch.className = "swatch stop";
    swatch.setAttribute("aria-hidden", "true");

    const detail = document.createElement("span");
    detail.className = "blocker-row-detail";
    const label = document.createElement("strong");
    label.textContent = item.label;
    const group = document.createElement("small");
    group.textContent = `${item.group} / ${item.source}`;
    const next = document.createElement("p");
    next.textContent = item.next_action;
    const evidence = document.createElement("code");
    evidence.textContent = item.evidence;
    detail.append(label, group, next, evidence);

    const status = document.createElement("span");
    status.className = "badge stop blocker-state";
    status.textContent = item.status;

    row.append(swatch, detail, status);
    board.append(row);
  });

  if (visibleRows.length === 0) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "No blockers match the current filter.";
    board.append(empty);
  }
}

function selectedProductionBlockerRow() {
  const rows = productionBlockerRows();
  return (
    rows.find((row) => row.key === state.productionBlockerSelection) ||
    rows.find((row) => row.status === "blocked") ||
    rows[0]
  );
}

function renderProductionBlockerDetail(row = selectedProductionBlockerRow()) {
  if (!row) {
    return;
  }
  qs("#blocker-detail-title").textContent = row.label;
  qs("#blocker-detail-status").textContent = row.status;
  qs("#blocker-detail-owner").textContent = row.owner;
  qs("#blocker-detail-next").textContent = row.next_action;
}

function renderProductionBlockerProof(row = selectedProductionBlockerRow()) {
  const list = qs("#blocker-proof-list");
  const statusBadge = qs("#blocker-proof-status");
  if (!list || !statusBadge) {
    return;
  }
  const rows = productionBlockerProofRows(row);
  const summary = productionBlockerProofSummary(rows);
  statusBadge.className = "badge stop";
  statusBadge.textContent = `${summary.blocked} blocked`;
  list.innerHTML = "";
  rows.forEach((item) => {
    const proofRow = document.createElement("div");
    proofRow.className = "blocker-proof-row";
    proofRow.dataset.proofStatus = item.status;
    proofRow.setAttribute("role", "listitem");

    const title = document.createElement("strong");
    title.textContent = item.label;
    const current = document.createElement("span");
    current.textContent = `${item.current} / ${item.status}`;
    const expected = document.createElement("code");
    expected.textContent = `expected: ${item.expected}`;
    const evidence = document.createElement("code");
    evidence.textContent = `evidence: ${item.evidence}`;

    proofRow.append(title, current, expected, evidence);
    list.append(proofRow);
  });
}

function setProductionBlockerSelection(key, record = false, focusAfterRender = false) {
  if (!isProductionBlockerKey(key)) {
    return;
  }
  state.productionBlockerSelection = key;
  renderProductionBlockers(state.blockerFilter);
  renderReadinessCompare();
  renderReceiptPreview();
  safeWriteState();
  if (focusAfterRender) {
    retainSelectableLedgerFocus("[data-production-blocker]", "productionBlocker", key);
  }
  if (record) {
    const selected = selectedProductionBlockerRow();
    assistiveStatus(`Production blocker ${selected.label} selected. Status ${selected.status}.`);
    recordEvent("Production blocker selected", `blockerItem=${selected.key} status=${selected.status}`);
  }
}

function moveProductionBlockerFocus(currentButton, direction) {
  const buttons = qsa("[data-production-blocker]");
  const currentIndex = buttons.indexOf(currentButton);
  if (currentIndex < 0) {
    return;
  }
  const nextIndex = (currentIndex + direction + buttons.length) % buttons.length;
  const next = buttons[nextIndex];
  setProductionBlockerSelection(next.dataset.productionBlocker, true, true);
}

function renderEvidence(filter = "") {
  const list = qs("#evidence-list");
  state.evidenceFilter = filter.trim().slice(0, 64);
  const rows = evidenceQueueRows(state.evidenceFilter);
  const summary = evidenceQueueSummary(rows);
  list.innerHTML = "";
  rows
    .filter((row) => row.visible)
    .forEach((row) => {
      const item = document.createElement("article");
      item.className = "evidence-item";
      item.dataset.evidenceKey = row.key;
      item.dataset.evidenceStatus = row.status;
      item.innerHTML = `<div><strong>${row.key}</strong><small>${row.group}</small></div><code>${row.value}</code>`;
      list.append(item);
    });
  if (summary.visible === 0) {
    const empty = document.createElement("article");
    empty.className = "empty-state";
    empty.textContent = "No evidence rows match the current filter.";
    list.append(empty);
  }
  const strip = qs("#evidence-queue-strip");
  if (strip instanceof HTMLElement) {
    strip.dataset.evidenceQueueState = summary.state;
  }
  qs("#evidence-queue-visible").textContent = String(summary.visible);
  qs("#evidence-queue-guarded").textContent = String(summary.guarded);
  qs("#evidence-queue-filter").textContent = summary.filter;
  qs("#evidence-queue-filter-summary").textContent =
    `${summary.visible} of ${summary.total} evidence rows`;
  qs("#evidence-queue-boundary").textContent =
    `production=${summary.production_evidence_claim} / host=${summary.host_write_authority} / main=${summary.main_gui_mutation_required} / edge=${summary.edge_gui_mutation_required}`;
}

function setProgress(progress, label) {
  state.progress = Math.max(0, Math.min(100, progress));
  qs("#progress-percent").textContent = `${state.progress}%`;
  qs("#readiness-score").textContent = `${state.progress}%`;
  qs("#progress-fill").style.width = `${state.progress}%`;
  qs("#readiness-meter").style.width = `${state.progress}%`;
  if (label) {
    qs("#progress-label").textContent = label;
  }
  renderReadinessRail();
  renderReceiptPreview();
  safeWriteState();
}

function appendLog(message) {
  const log = qs("#recent-log");
  const line = document.createElement("p");
  line.textContent = message;
  log.append(line);
  log.scrollTop = log.scrollHeight;
}

function appendTerminal(command, output) {
  const terminal = qs("#terminal");
  const prompt = document.createElement("p");
  prompt.textContent = `> ${command}`;
  terminal.append(prompt);
  if (output) {
    const line = document.createElement("p");
    line.textContent = output;
    terminal.append(line);
  }
  terminal.scrollTop = terminal.scrollHeight;
}

function focusConsoleInput(select = false) {
  window.setTimeout(() => {
    const input = qs("#console-input");
    if (!input) {
      return;
    }
    input.focus({ preventScroll: true });
    if (select) {
      input.select();
    }
  }, 0);
}

function setConsoleStatus(status, message, announce = false) {
  const normalized = ["ready", "accepted", "blocked"].includes(status) ? status : "ready";
  state.consoleStatus = normalized;
  state.consoleMessage = message;
  const chip = qs("#console-status");
  if (chip) {
    chip.textContent = normalized === "blocked" ? "blocked command" : normalized;
    chip.title = message;
    chip.classList.toggle("is-ready", normalized === "ready");
    chip.classList.toggle("is-accepted", normalized === "accepted");
    chip.classList.toggle("is-blocked", normalized === "blocked");
  }
  const input = qs("#console-input");
  if (input) {
    input.setAttribute("aria-invalid", String(normalized === "blocked"));
  }
  renderReceiptSchema();
  renderReceiptPreview();
  safeWriteState();
  if (announce) {
    assistiveStatus(`Console ${message}.`);
  }
}

function renderPlan() {
  renderPrefixValidation();
  renderDeliveryPlanState();
  renderReceiptChecklist();
  renderReceiptSchema();
  renderReceiptPreview();
}

function setMode(mode) {
  state.mode = mode;
  qsa(".mode-option").forEach((button) => {
    const active = button.dataset.mode === mode;
    button.classList.toggle("is-active", active);
    button.setAttribute("aria-checked", String(active));
    button.tabIndex = active ? 0 : -1;
  });
  const local = mode === "local";
  renderReadinessRail();
  qs("#prefix-state").textContent = local ? "guarded writes armed" : "writes require guarded mode";
  renderDashboardAuthorityCard();
  setPrimaryActionLabel("run-dry", local ? "Run guarded local" : "Run dry-install");
  renderPlan();
  safeWriteState();
  assistiveStatus(local ? "Guarded local mode selected. User-local write simulation armed." : "Dry-run mode selected. Writes blocked.");
}

function resetState() {
  try {
    localStorage.removeItem(STORAGE_KEY);
  } catch {
    // The UI still resets in memory if local persistence is unavailable.
  }
  state.activeTab = "dashboard";
  state.mode = "dry";
  state.progress = 72;
  state.profile = "Guided local panel";
  state.prefix = "~/.local";
  state.prefixValid = true;
  state.evidenceDetail = 2;
  state.evidenceFilter = "";
  state.blockerFilter = "";
  state.reviewFilter = "all";
  state.receiptDiffFilter = "all";
  state.promotionGateSelection = "artifact_integrity";
  state.migrationReviewSelection = "workbench_frame";
  state.qaScenarioSelection = "keyboard_path_sweep";
  state.engineBindingSelection = "plan_preview_binding";
  state.visualBaselineSelection = "desktop_review_baseline";
  state.releaseAcceptanceSelection = "local_ui_acceptance";
  state.accessibilityAuditSelection = "screen_reader_live_pass";
  state.readinessCompareSelection = "local_ui_proof";
  state.evidenceIntakeSelection = "local_ui_packet";
  state.traceabilitySelection = "local_ui_trace";
  state.productionBlockerSelection = "reproducible_artifact";
  state.consoleStatus = "ready";
  state.consoleMessage = "ready";
  state.consoleLastCommand = "status";
  state.paletteQuery = "";
  state.paletteSelection = "command:status";
  state.receiptChecklist = defaultReceiptChecklistState();
  state.savedReceipts = [];
  state.selectedReceiptId = "";
  state.events = [];
  components.forEach((component) => {
    component.selected = ["console", "lat", "lir", "seal", "nadia", "docs"].includes(component.id);
  });
  qs("#profile-select").value = state.profile;
  qs("#prefix-input").value = state.prefix;
  qs("#detail-range").value = String(state.evidenceDetail);
  qs("#evidence-search").value = state.evidenceFilter;
  qs("#blocker-search").value = state.blockerFilter;
  qs("#console-input").value = state.consoleLastCommand;
  qs("#palette-search").value = state.paletteQuery;
  qs("#step-profile").textContent = state.profile;
  qs("#inspector-title").textContent = state.profile;
  renderComponentStack();
  renderComponentTable(qs("#component-search").value);
  renderEvidence(state.evidenceFilter);
  renderQaRunbook();
  renderEngineBinding();
  renderVisualBaseline();
  renderReleaseAcceptance();
  renderAccessibilityAudit();
  renderReadinessCompare();
  renderEvidenceIntake();
  renderTraceabilityMatrix();
  renderMigrationMap();
  renderPromotionGate();
  renderReviewChecks();
  renderEventTrail();
  setConsoleStatus(state.consoleStatus, state.consoleMessage);
  setMode(state.mode);
  setTab(state.activeTab);
  setProgress(state.progress, "Evidence completeness");
  appendLog("[state] local test-lane state reset");
  notify("State reset");
  recordEvent("State reset", "Local test-lane state returned to defaults");
}

function runAction(action) {
  if (action === "generate-plan") {
    renderPlan();
    notify(state.prefixValid ? "Plan refreshed" : "Plan refreshed with blocked prefix guard", state.prefixValid ? "info" : "warning");
    qs("#plan-state").textContent = "plan regenerated";
    qs("#plan-badge").textContent = "refreshed";
    appendLog("[plan] regenerated test lane plan");
    recordEvent("Plan generated", state.prefixValid ? "Plan refreshed with accepted prefix guard" : "Plan refreshed with blocked prefix guard", state.prefixValid ? "info" : "blocked");
    setProgress(78, "Plan review coverage");
    return;
  }
  if (action === "run-dry") {
    renderPlan();
    if (!state.prefixValid) {
      qs("#run-badge").textContent = "blocked";
      appendLog("[guard] run blocked by prefix validation");
      notify("Run blocked by prefix validation", "warning");
      recordEvent("Run blocked", "Prefix guard denied the requested run", "blocked");
      return;
    }
    const label = state.mode === "local" ? "guarded local simulation" : "dry-install simulation";
    qs("#run-monitor-title").textContent = label;
    qs("#run-badge").textContent = "running";
    appendLog(`[run] ${label} started`);
    renderReceiptPreview();
    setTimeout(() => {
      qs("#run-badge").textContent = "complete";
      appendLog(`[receipt] ${label} receipt queued`);
      recordEvent("Receipt queued", label);
      setProgress(state.mode === "local" ? 84 : 82, "Receipt evidence coverage");
      notify("Receipt queued");
    }, 260);
    return;
  }
  if (action === "save-evidence") {
    appendLog("[receipt] test-ui-lane receipt saved");
    recordEvent("Receipt saved", "No-effect test-lane receipt saved to preview state");
    const snapshot = createReceiptSnapshot();
    state.savedReceipts.push(snapshot);
    state.savedReceipts = state.savedReceipts.slice(-SAVED_RECEIPT_LIMIT);
    state.selectedReceiptId = snapshot.id;
    renderSavedReceipts();
    renderReceiptPreview();
    setProgress(88, "Receipt save coverage");
    safeWriteState();
    notify("Receipt snapshot saved");
    return;
  }
  if (action === "align-trace-context") {
    alignTraceabilityContext(true);
    return;
  }
  if (action === "align-readiness-compare-context") {
    alignReadinessComparisonContext(true);
    return;
  }
  if (action === "delete-saved-receipt") {
    deleteSelectedSavedReceipt();
    return;
  }
  if (action === "reset-state") {
    resetState();
    return;
  }
  if (action === "updater-preview") {
    appendLog("[updater] preview simulated; signed delivery gate remains closed");
    recordEvent("Updater preview", "Signed delivery gate remains closed");
    setProgress(80, "Updater preview evidence");
    notify("Updater preview complete");
    return;
  }
  if (action === "clear-events") {
    state.events = [];
    renderEventTrail();
    safeWriteState();
    notify("Events cleared");
    return;
  }
  if (action === "clear-console") {
    qs("#terminal").innerHTML = "";
    state.consoleLastCommand = "clear";
    setConsoleStatus("ready", "ready");
    focusConsoleInput();
  }
}

function runCommand(command) {
  const rawCommand = command.trim();
  const normalized = command.trim().replace(/\s+/g, " ").toLowerCase();
  state.consoleLastCommand = normalized || "empty command";
  if (normalized === "clear") {
    runAction("clear-console");
    setConsoleStatus("ready", "ready");
    focusConsoleInput(true);
    return;
  }
  const template = allowedCommands.get(normalized);
  if (!template) {
    appendTerminal(rawCommand || "(empty)", "blocked: command outside panel allowlist");
    setConsoleStatus("blocked", `blocked: ${normalized || "empty command"}`, true);
    notify("Console command blocked", "warning");
    recordEvent("Console command blocked", normalized || "empty command", "blocked");
    focusConsoleInput(true);
    return;
  }
  if (normalized === "mode dry") {
    setMode("dry");
  }
  if (normalized === "mode local") {
    setMode("local");
  }
  if (normalized === "plan") {
    renderPlan();
  }
  const output = template
    .replace("{mode}", state.mode === "dry" ? "dry-run" : "guarded-local")
    .replace("{components}", String(selectedComponents().length))
    .replace("{prefix}", qs("#prefix-input").value.trim() || "~/.local");
  appendTerminal(rawCommand, output);
  setConsoleStatus("accepted", `accepted: ${normalized}`, true);
  recordEvent("Console command", normalized);
  focusConsoleInput(true);
  safeWriteState();
}

function wireEvents() {
  document.addEventListener("click", (event) => {
    const disabledLink = disabledLocalActionLink(event.target);
    if (disabledLink) {
      event.preventDefault();
      assistiveStatus(`${disabledLink.textContent.trim()} is blocked until its local validation gates pass.`);
      return;
    }
    if (!(event.target instanceof Element)) {
      return;
    }
    const button = event.target.closest("[data-saved-receipt]");
    if (button instanceof HTMLButtonElement) {
      selectSavedReceipt(button.dataset.savedReceipt, true, true);
    }
    const promotionButton = event.target.closest("[data-promotion-gate]");
    if (promotionButton instanceof HTMLButtonElement) {
      setPromotionGateSelection(promotionButton.dataset.promotionGate, true, true);
    }
    const migrationButton = event.target.closest("[data-migration-review]");
    if (migrationButton instanceof HTMLButtonElement) {
      setMigrationReviewSelection(migrationButton.dataset.migrationReview, true, true);
    }
    const qaScenarioButton = event.target.closest("[data-qa-scenario]");
    if (qaScenarioButton instanceof HTMLButtonElement) {
      setQaScenarioSelection(qaScenarioButton.dataset.qaScenario, true, true);
    }
    const engineBindingButton = event.target.closest("[data-engine-binding]");
    if (engineBindingButton instanceof HTMLButtonElement) {
      setEngineBindingSelection(engineBindingButton.dataset.engineBinding, true, true);
    }
    const visualBaselineButton = event.target.closest("[data-visual-baseline]");
    if (visualBaselineButton instanceof HTMLButtonElement) {
      setVisualBaselineSelection(visualBaselineButton.dataset.visualBaseline, true, true);
    }
    const releaseAcceptanceButton = event.target.closest("[data-release-acceptance]");
    if (releaseAcceptanceButton instanceof HTMLButtonElement) {
      setReleaseAcceptanceSelection(releaseAcceptanceButton.dataset.releaseAcceptance, true, true);
    }
    const accessibilityAuditButton = event.target.closest("[data-accessibility-audit]");
    if (accessibilityAuditButton instanceof HTMLButtonElement) {
      setAccessibilityAuditSelection(accessibilityAuditButton.dataset.accessibilityAudit, true, true);
    }
    const readinessCompareButton = event.target.closest("[data-readiness-compare]");
    if (readinessCompareButton instanceof HTMLButtonElement) {
      setReadinessCompareSelection(readinessCompareButton.dataset.readinessCompare, true, true);
    }
    const evidenceIntakeButton = event.target.closest("[data-evidence-intake]");
    if (evidenceIntakeButton instanceof HTMLButtonElement) {
      setEvidenceIntakeSelection(evidenceIntakeButton.dataset.evidenceIntake, true, true);
    }
    const traceabilityButton = event.target.closest("[data-traceability]");
    if (traceabilityButton instanceof HTMLButtonElement) {
      setTraceabilitySelection(traceabilityButton.dataset.traceability, true, true);
    }
    const productionBlockerButton = event.target.closest("[data-production-blocker]");
    if (productionBlockerButton instanceof HTMLButtonElement) {
      setProductionBlockerSelection(productionBlockerButton.dataset.productionBlocker, true, true);
    }
    const paletteButton = event.target.closest("[data-palette-action]");
    if (paletteButton instanceof HTMLButtonElement) {
      activateCommandPaletteItem(paletteButton.dataset.paletteAction);
    }
    const focusDockButton = event.target.closest("[data-focus-dock]");
    if (focusDockButton instanceof HTMLButtonElement) {
      activateOperatorFocusDockRow(focusDockButton.dataset.focusDock);
    }
  });
  document.addEventListener("keydown", (event) => {
    if ((event.metaKey || event.ctrlKey) && event.key.toLowerCase() === "k") {
      event.preventDefault();
      setTab("console");
      renderCommandPalette();
      qs("#palette-search").focus();
      assistiveStatus("Command palette focused. Local targets only.");
      return;
    }
    if (!(event.target instanceof Element)) {
      return;
    }
    const paletteButton = event.target.closest("[data-palette-action]");
    if (paletteButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveCommandPaletteFocus(paletteButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveCommandPaletteFocus(paletteButton, -1);
      }
      if (event.key === "Enter" || event.key === " ") {
        event.preventDefault();
        activateCommandPaletteItem(paletteButton.dataset.paletteAction);
      }
      return;
    }
    const promotionButton = event.target.closest("[data-promotion-gate]");
    if (promotionButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        movePromotionGateFocus(promotionButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        movePromotionGateFocus(promotionButton, -1);
      }
      return;
    }
    const migrationButton = event.target.closest("[data-migration-review]");
    if (migrationButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveMigrationReviewFocus(migrationButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveMigrationReviewFocus(migrationButton, -1);
      }
      return;
    }
    const qaScenarioButton = event.target.closest("[data-qa-scenario]");
    if (qaScenarioButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveQaScenarioFocus(qaScenarioButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveQaScenarioFocus(qaScenarioButton, -1);
      }
      return;
    }
    const engineBindingButton = event.target.closest("[data-engine-binding]");
    if (engineBindingButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveEngineBindingFocus(engineBindingButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveEngineBindingFocus(engineBindingButton, -1);
      }
      return;
    }
    const visualBaselineButton = event.target.closest("[data-visual-baseline]");
    if (visualBaselineButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveVisualBaselineFocus(visualBaselineButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveVisualBaselineFocus(visualBaselineButton, -1);
      }
      return;
    }
    const releaseAcceptanceButton = event.target.closest("[data-release-acceptance]");
    if (releaseAcceptanceButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveReleaseAcceptanceFocus(releaseAcceptanceButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveReleaseAcceptanceFocus(releaseAcceptanceButton, -1);
      }
      return;
    }
    const accessibilityAuditButton = event.target.closest("[data-accessibility-audit]");
    if (accessibilityAuditButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveAccessibilityAuditFocus(accessibilityAuditButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveAccessibilityAuditFocus(accessibilityAuditButton, -1);
      }
      return;
    }
    const readinessCompareButton = event.target.closest("[data-readiness-compare]");
    if (readinessCompareButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveReadinessCompareFocus(readinessCompareButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveReadinessCompareFocus(readinessCompareButton, -1);
      }
      return;
    }
    const evidenceIntakeButton = event.target.closest("[data-evidence-intake]");
    if (evidenceIntakeButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveEvidenceIntakeFocus(evidenceIntakeButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveEvidenceIntakeFocus(evidenceIntakeButton, -1);
      }
      return;
    }
    const traceabilityButton = event.target.closest("[data-traceability]");
    if (traceabilityButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveTraceabilityFocus(traceabilityButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveTraceabilityFocus(traceabilityButton, -1);
      }
      return;
    }
    const productionBlockerButton = event.target.closest("[data-production-blocker]");
    if (productionBlockerButton instanceof HTMLButtonElement) {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveProductionBlockerFocus(productionBlockerButton, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveProductionBlockerFocus(productionBlockerButton, -1);
      }
      return;
    }
    const button = event.target.closest("[data-saved-receipt]");
    if (!(button instanceof HTMLButtonElement)) {
      return;
    }
    if (event.key === "ArrowRight" || event.key === "ArrowDown") {
      event.preventDefault();
      moveSavedReceiptFocus(button, 1);
    }
    if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
      event.preventDefault();
      moveSavedReceiptFocus(button, -1);
    }
  });
  qsa("[data-tab]").forEach((button) => {
    button.addEventListener("click", () => setTab(button.dataset.tab));
    button.addEventListener("keydown", (event) => {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveTabFocus(button, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveTabFocus(button, -1);
      }
      if (event.key === "Home") {
        event.preventDefault();
        const first = qs("[data-tab]");
        setTab(first.dataset.tab);
        first.focus();
      }
      if (event.key === "End") {
        event.preventDefault();
        const buttons = qsa("[data-tab]");
        const last = buttons[buttons.length - 1];
        setTab(last.dataset.tab);
        last.focus();
      }
    });
  });
  qsa("[data-tab-jump]").forEach((button) => {
    button.addEventListener("click", () => setTab(button.dataset.tabJump));
  });
  qsa("[data-mode]").forEach((button) => {
    button.addEventListener("click", () => setMode(button.dataset.mode));
    button.addEventListener("keydown", (event) => {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveModeFocus(button, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveModeFocus(button, -1);
      }
      if (event.key === "Home") {
        event.preventDefault();
        const first = qs("[data-mode]");
        setMode(first.dataset.mode);
        first.focus();
      }
      if (event.key === "End") {
        event.preventDefault();
        const buttons = qsa("[data-mode]");
        const last = buttons[buttons.length - 1];
        setMode(last.dataset.mode);
        last.focus();
      }
    });
  });
  qsa("[data-review-filter]").forEach((button) => {
    button.addEventListener("click", () => setReviewFilter(button.dataset.reviewFilter, true));
    button.addEventListener("keydown", (event) => {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveReviewFilterFocus(button, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveReviewFilterFocus(button, -1);
      }
      if (event.key === "Home") {
        event.preventDefault();
        const first = qs("[data-review-filter]");
        setReviewFilter(first.dataset.reviewFilter, true);
        first.focus();
      }
      if (event.key === "End") {
        event.preventDefault();
        const buttons = qsa("[data-review-filter]");
        const last = buttons[buttons.length - 1];
        setReviewFilter(last.dataset.reviewFilter, true);
        last.focus();
      }
    });
  });
  qsa("[data-receipt-diff-filter]").forEach((button) => {
    button.addEventListener("click", () => setReceiptDiffFilter(button.dataset.receiptDiffFilter, true));
    button.addEventListener("keydown", (event) => {
      if (event.key === "ArrowRight" || event.key === "ArrowDown") {
        event.preventDefault();
        moveReceiptDiffFilterFocus(button, 1);
      }
      if (event.key === "ArrowLeft" || event.key === "ArrowUp") {
        event.preventDefault();
        moveReceiptDiffFilterFocus(button, -1);
      }
      if (event.key === "Home") {
        event.preventDefault();
        const first = qs("[data-receipt-diff-filter]");
        setReceiptDiffFilter(first.dataset.receiptDiffFilter, true);
        first.focus();
      }
      if (event.key === "End") {
        event.preventDefault();
        const buttons = qsa("[data-receipt-diff-filter]");
        const last = buttons[buttons.length - 1];
        setReceiptDiffFilter(last.dataset.receiptDiffFilter, true);
        last.focus();
      }
    });
  });
  qsa("[data-action]").forEach((button) => {
    button.addEventListener("click", () => runAction(button.dataset.action));
  });
  document.addEventListener("change", (event) => {
    const input = event.target;
    if (!(input instanceof HTMLInputElement)) {
      return;
    }
    if (input.dataset.receiptCheck) {
      const row = receiptChecklistRows().find((item) => item.id === input.dataset.receiptCheck);
      if (row && row.available) {
        state.receiptChecklist[row.id] = input.checked;
        renderReceiptChecklist();
        focusReceiptCheck(row.id);
        renderReceiptSchema();
        renderReceiptPreview();
        const status = input.checked ? "recorded" : "pending";
        assistiveStatus(`${row.label} ${status}. ${receiptChecklistSummary().recorded} receipt checklist items recorded.`);
        recordEvent("Receipt checklist changed", `${row.id}=${status}`);
        safeWriteState();
      }
    }
    if (input.dataset.component) {
      const component = components.find((item) => item.id === input.dataset.component);
      if (component) {
        component.selected = input.checked;
        renderComponentStack();
        renderComponentTable(qs("#component-search").value);
        focusComponentToggle(component.id);
        renderPlan();
        assistiveStatus(`${component.name} ${input.checked ? "selected" : "cleared"}. ${componentSummaryText()}.`);
        recordEvent("Component selection changed", `${component.id}=${input.checked ? "selected" : "cleared"}`);
        safeWriteState();
      }
    }
  });
  qs("#component-search").addEventListener("input", (event) => {
    renderComponentTable(event.target.value);
  });
  qs("#evidence-search").addEventListener("input", (event) => {
    renderEvidence(event.target.value);
    renderReceiptPreview();
    safeWriteState();
  });
  qs("#blocker-search").addEventListener("input", (event) => {
    state.blockerFilter = normalizeBlockerFilter(event.target.value);
    renderProductionBlockers(state.blockerFilter);
    renderReceiptPreview();
    safeWriteState();
  });
  qs("#profile-select").addEventListener("change", (event) => {
    state.profile = event.target.value;
    qs("#step-profile").textContent = event.target.value;
    qs("#inspector-title").textContent = event.target.value;
    renderProfileScopeControl();
    renderPlan();
    recordEvent("Profile changed", state.profile);
    safeWriteState();
  });
  qs("#prefix-input").addEventListener("input", (event) => {
    state.prefix = event.target.value.trim() || "~/.local";
    renderPlan();
    recordEvent("Prefix changed", state.prefix, state.prefixValid ? "info" : "blocked");
    safeWriteState();
  });
  qs("#detail-range").addEventListener("input", (event) => {
    state.evidenceDetail = Number(event.target.value);
    renderEvidenceDetailControl();
    renderReceiptPreview();
    safeWriteState();
  });
  const savedReceiptLabelInput = qs("#saved-receipt-label-input");
  savedReceiptLabelInput.addEventListener("focus", () => {
    const snapshot = selectedSavedReceipt();
    savedReceiptLabelInput.dataset.previousLabel = snapshot ? snapshot.label : "";
  });
  savedReceiptLabelInput.addEventListener("input", (event) => {
    if (!(event.target instanceof HTMLInputElement)) {
      return;
    }
    event.target.value = event.target.value.slice(0, SNAPSHOT_LABEL_MAX_LENGTH);
    assistiveStatus("Editing selected receipt label. Changes stay local to the test lane.");
  });
  savedReceiptLabelInput.addEventListener("keyup", (event) => {
    if (!(event.target instanceof HTMLInputElement) || event.key === "Tab" || event.key === "Shift") {
      return;
    }
    event.target.value = event.target.value.slice(0, SNAPSHOT_LABEL_MAX_LENGTH);
    if (event.target.value.trim()) {
      updateSelectedReceiptLabel(event.target.value);
    }
  });
  savedReceiptLabelInput.addEventListener("change", (event) => {
    if (!(event.target instanceof HTMLInputElement)) {
      return;
    }
    const previous = event.target.dataset.previousLabel || selectedSavedReceipt()?.label || "receipt";
    updateSelectedReceiptLabel(normalizeSnapshotLabel(event.target.value, previous));
    const snapshot = selectedSavedReceipt();
    event.target.value = snapshot ? snapshot.label : "";
    if (snapshot && snapshot.label !== previous) {
      recordEvent("Receipt snapshot relabeled", `${snapshot.id}=${snapshot.label}`);
    }
    event.target.dataset.previousLabel = snapshot ? snapshot.label : "";
  });
  qs("#palette-search").addEventListener("input", (event) => {
    state.paletteQuery = event.target.value.slice(0, 64);
    state.paletteSelection = commandPaletteVisibleRows()[0]?.key || "";
    renderCommandPalette();
    renderReceiptPreview();
    safeWriteState();
  });
  qs("#palette-search").addEventListener("keydown", (event) => {
    if (event.key === "ArrowDown" || event.key === "ArrowRight") {
      event.preventDefault();
      focusCommandPaletteSelection();
    }
    if (event.key === "Enter") {
      event.preventDefault();
      const selected = selectedCommandPaletteItem(commandPaletteVisibleRows());
      if (selected) {
        activateCommandPaletteItem(selected.key);
      }
    }
    if (event.key === "Escape") {
      event.preventDefault();
      state.paletteQuery = "";
      renderCommandPalette();
      renderReceiptPreview();
      safeWriteState();
      assistiveStatus("Command palette search cleared.");
    }
  });
  qs("#console-form").addEventListener("submit", (event) => {
    event.preventDefault();
    const input = qs("#console-input");
    runCommand(input.value);
    input.select();
  });
  qsa("[data-command]").forEach((button) => {
    button.addEventListener("click", () => {
      qs("#console-input").value = button.dataset.command;
      runCommand(button.dataset.command);
    });
  });
}

applyStoredState();
applyUrlStateOverrides();
qs("#profile-select").value = state.profile;
qs("#prefix-input").value = state.prefix;
qs("#detail-range").value = String(state.evidenceDetail);
qs("#evidence-search").value = state.evidenceFilter;
qs("#blocker-search").value = state.blockerFilter;
qs("#console-input").value = state.consoleLastCommand === "empty command" ? "" : state.consoleLastCommand;
qs("#palette-search").value = state.paletteQuery;
qs("#step-profile").textContent = state.profile;
qs("#inspector-title").textContent = state.profile;
renderComponentStack();
renderComponentTable();
renderEvidence(state.evidenceFilter);
renderQualityGates();
renderEvidenceMatrix();
renderAccessibilityAudit();
renderQaRunbook();
renderEngineBinding();
renderVisualBaseline();
renderReleaseAcceptance();
renderReadinessCompare();
renderEvidenceIntake();
renderTraceabilityMatrix();
renderReviewChecks();
renderMigrationMap();
renderPromotionGate();
renderProductionBlockers(state.blockerFilter);
renderEventTrail();
setMode(state.mode);
setConsoleStatus(state.consoleStatus, state.consoleMessage);
renderPlan();
setTab(state.activeTab);
setProgress(state.progress);
wireEvents();
wireBrandEmblem();
wireVisualIdentityAsset();
