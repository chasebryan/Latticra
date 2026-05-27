# Latticra Panel UI Design Checkpoint

Status: design checkpoint
Date: 2026-05-27 CDT

This checkpoint records the current Latticra Panel workbench layout as the baseline design state.

Future changes are allowed, but they should preserve the current workbench identity unless a deliberate design migration updates this file and the checker.

Checker:

```text
scripts/check_latticra_panel_ui_design.py
```

CI workflow:

```text
.github/workflows/latticra-panel-installer.yml
```

The checker currently protects these design anchors:

```text
gui-workbench build identity
embedded panel image
texture loader
left navigation panel
right console panel
central workbench panel
dashboard tab
components tab
seal tab
authority tab
delivery tab
updater tab
evidence tab
procedure tab
fluid install button
right evidence panel
focused running monitor
bounded recent engine output
non-wrapping engine log scroll
running console quick-command restraint
v1.0.0 readability pass
bounded readable status chips
first-screen purpose and next-action copy
window size
minimum window size
maximized launch
README console section
README safety section
```

Change rule:

1. keep the checker passing for ordinary UI edits;
2. update this file and the checker for deliberate design migrations;
3. keep installer CI passing before merge.

Current posture:

```text
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0
user_local_prefix_only=1
```
