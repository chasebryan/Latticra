# Latticra Panel Test UI Lane

Status: isolated test development area

This lane is for production-quality Latticra Panel UI/GUI iteration without changing the guarded Rust Panel implementation in `installer/latticra-installer/src/ui.rs` or any future edge GUI implementation.

The `Review` tab tracks UI-lane checks, pending egui migration review, and blocked production-release claims separately from the installer readiness ledger. Its state filter supports local persistence and `review=` deep links for QA snapshots. Non-visual status and hidden control descriptions are part of the lane so screen-reader behavior can be tested before any migration.

The Review evidence matrix separates verified local UI proof from pending guarded Rust Panel migration, pending installer-engine binding, and blocked production-release artifacts. The same local-only matrix is included in the no-effect receipt preview so QA can audit production blockers without implying release evidence.

The Review visual baseline ledger makes desktop, mobile, receipt, focus, guarded-Panel compare, and release signoff screenshot gates selectable, keyboard navigable, replayable with `visual=` links, and receipt-bound without claiming production visual signoff.

The Review release acceptance audit combines local UI proof, receipt/handoff replay, accessibility, guarded Panel migration, installer-engine binding, production evidence, and release authority into selectable `acceptance=` gates. It keeps `can_promote=false` and production claims closed while making the remaining acceptance gap explicit.

The Review accessibility audit makes keyboard paths, focus behavior, ARIA/live-region coverage, and pending screen-reader or real-installer accessibility work visible before migration. Its selectable `a11y=` evidence queue exposes the selected assistive proof gap, supports keyboard and command-palette review, joins QA handoff replay, and stays receipt-bound without claiming production accessibility certification.

The Review installer engine binding matrix maps simulated plan, prefix, run monitor, receipt, error, and production execution surfaces to their future live installer event sources with `engine=` deep links, keyboard selection, and receipt-bound zero-authority status. Its selected-binding contract inspector exposes source surface, receipt mapping, live event gap, and authority boundary for the active row without mutating main or edge GUI code.

The Review migration drilldown makes prototype-to-guarded-Panel migration candidates selectable, keyboard navigable, replayable with `migration=` links, and receipt-bound without mutating the guarded Rust Panel.

The Review QA runbook turns desktop, mobile, keyboard, receipt replay, migration, and production-denial checks into selectable, keyboard navigable, `scenario=` deep-linked, receipt-bound local-only scenarios.

The Readiness promotion gate records the test-lane decision before any migration or release claim: local UI evidence can be verified, but promotion remains blocked until guarded Panel migration review, installer-engine binding, artifact integrity, SBOM, lifecycle transcripts, upgrade and rollback, and multi-VM evidence exist. The no-effect receipt includes the same `can_promote=false` summary with zero production claim authority.

Promotion gate rows are selectable, keyboard navigable, persisted locally, replayed with `gate=` deep links, and exposed in the no-effect receipt as selected remediation detail.

The Readiness production blocker drilldown turns missing artifact, signature, SBOM, lifecycle, upgrade, rollback, and VM evidence into selectable `blockerItem=` remediation rows with owners, next actions, receipt binding, QA handoff replay, and retained roving focus after pointer or keyboard selection while keeping release authority at zero.

The Readiness comparison ledger separates local UI proof from guarded Panel migration, installer-engine binding, release artifacts, lifecycle validation, and recovery matrix requirements. Rows are selectable, keyboard navigable, replayable with `compare=` links, mobile deep links scroll the selected row into view, included in QA handoff validation, and receipt-bound with production claim authority held at zero.

The Readiness release evidence intake queue separates local UI proof packets from guarded Panel migration packets, installer runtime packets, artifact/signature packets, lifecycle transcripts, and recovery validation packets. Rows are selectable, keyboard navigable, replayable with `intake=` links, mobile deep links scroll the selected packet into view, included in QA handoff validation, and receipt-bound with intake and production authority held at zero.

The Readiness traceability matrix connects blocker groups, intake packets, promotion gates, and acceptance gates into selectable `trace=` paths. Rows are selectable, keyboard navigable, replayable with mobile deep-link scroll, included in QA handoff validation, and receipt-bound with production, host-write, runtime, main GUI, and edge GUI authority held at zero.

The selected trace alignment inspector flags drift between the active trace and the current packet, promotion gate, acceptance gate, and blocker selections. Its local-only alignment rows are receipt-bound so QA can distinguish a deliberate review focus from a fully aligned release path.

The trace alignment action can align the local review context to the selected trace path without creating production evidence or changing main or edge GUI code. It updates only test-lane packet, gate, acceptance, and blocker selections, then records the local action in the no-effect event trail.

When a trace path is already aligned, the action changes to a `Context aligned` no-op state with an `aria-disabled` hint instead of recording duplicate events. The receipt carries the same alignment action state and label for QA replay.

Selectable audit ledgers now share retained post-render roving focus across saved receipts, promotion gates, readiness comparison, release evidence intake, readiness traceability, migration review, QA runbook, installer-engine binding, visual baselines, release acceptance, accessibility evidence, and production blockers so pointer selection can continue directly into arrow-key review.

The workspace mode radio group uses roving tabindex and arrow-key navigation in the test lane.

Component toggles include described checkbox controls, visible keyboard focus, selected-count feedback, and no-effect receipt binding.

The Console tab exposes allowlist state visibly and non-visually, returns focus to the command field after blocked commands, marks invalid command input, and records console status in the no-effect receipt preview.

The Console command palette searches allowlisted commands, workspace tabs, and selected QA/release audit surfaces with roving focus, local-only jump activation, receipt-bound selection state, and zero shell, host-write, main GUI, or edge GUI authority.

The Delivery receipt schema map includes field provenance, live/guarded/blocked status, summary counts, safe text rendering, and receipt-bound schema provenance so QA can inspect where each no-effect field comes from.

The Delivery receipt checklist is stateful, persisted locally, guarded by mode and prefix prerequisites, announced through assistive status, and bound into the no-effect receipt preview as recorded, pending, or blocked evidence.

The Evidence tab saves local no-effect receipt snapshots, keeps a selectable snapshot list, and compares saved event, checklist, schema, mode, and prefix state against the current preview.

Selected saved receipts expose a local JSON export preview and download link that embeds a `NOT PRODUCTION EVIDENCE` watermark plus zero host-write, main GUI, and edge GUI authority fields.

Saved receipt maintenance retains the latest 8 local no-effect snapshots, lets QA relabel the selected snapshot, and deletes only local test-lane state without mutating installer evidence or production GUI code.

Saved receipt diff detail compares stable saved and current receipt fields row by row, marks changed values, and embeds the same local-only comparison in the export preview.

The receipt diff filter supports all, changed, and same field views with local persistence, `diff=` QA deep links, and keyboard navigation.

The export preview includes a validation ledger for local-only schema, non-production watermark, zero authority fields, selected snapshot embedding, and diff filter binding before download.

The local export artifact also carries a deterministic test-lane integrity digest over the validated payload scope so QA can compare the preview and downloaded JSON without claiming production evidence.

The QA handoff surface turns the selected saved receipt into a local review URL plus manifest that preserves mode, prefix, filters, selected snapshot, and export digest while keeping production evidence and host-write authority at zero.

QA handoff validation shows reviewer-facing gates for route parameters, mode and prefix replay, filter replay, selected snapshot alignment, digest alignment, export validation status, and zero-authority local boundaries.

The QA handoff URL now carries `snapshot=` and `digest=` replay parameters. Reloading that link restores the selected saved receipt when the snapshot still exists in local test-lane state, while missing snapshots remain local-only and do not create production evidence.

The Replay Request strip separates incoming handoff state from the freshly generated link, showing requested snapshot, requested digest, local restore status, and whether the current no-effect digest matched or was refreshed.

Missing replay requests are explicit: the strip shows whether the requested snapshot is present in local test-lane state before any restored or refreshed digest is trusted.

The global QA replay strip summarizes active URL-requested state across tabs, mode, filters, selected gates, blocker items, snapshots, and digests, then binds that applied/ignored count into the no-effect receipt with production, main GUI, and edge GUI authority held at zero.

The right context inspector now mirrors selected promotion gate, production blocker, release acceptance, readiness trace, trace alignment, QA replay, and saved receipt context so reviewers retain orientation while moving across tabs, with the same local-only summary embedded in the receipt.

The operator focus dock keeps the selected tab, production blocker, release acceptance gate, readiness trace, trace alignment state, command palette target, saved receipt, and zero-authority boundary visible near the workspace top. On mobile it compresses into a denser snap-scrolling review strip so selected trace rows remain readable. Its buttons jump only within the isolated test lane and the same context is embedded in the no-effect receipt.

Files:

```text
docs/demos/latticra-panel-test-ui/index.html
docs/demos/latticra-panel-test-ui/styles.css
docs/demos/latticra-panel-test-ui/app.js
scripts/check-latticra-panel-test-ui.sh
docs/status/LATTICRA_PANEL_TEST_UI_LANE_STATUS.md
```

Run locally:

```text
open docs/demos/latticra-panel-test-ui/index.html
```

Validate:

```text
sh scripts/check-latticra-panel-test-ui.sh
python3 scripts/check_latticra_panel_ui_design.py
```

Boundary:

```text
test_ui_lane=1
main_rust_panel_mutation_required=0
edge_gui_mutation_required=0
host_write_authority=0
network_authority=0
runtime_enforcement_authority=0
production_installer_claim=0
```

Status record:

```text
docs/status/LATTICRA_PANEL_TEST_UI_LANE_STATUS.md
```
