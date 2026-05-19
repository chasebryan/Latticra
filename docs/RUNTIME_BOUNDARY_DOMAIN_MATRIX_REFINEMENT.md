# Runtime Boundary Domain Matrix Refinement

Status: initial companion implementation.

This record documents the RBDM companion slice.

Tracked files:

```text
include/latticra/runtime_boundary_domain_matrix.h
src/runtime_boundary_domain_matrix.c
src/runtime_boundary_domain_matrix_eval.c
tests/runtime_boundary_domain_matrix_refinement.c
scripts/test-runtime-boundary-domain-matrix-refinement.sh
.github/workflows/runtime-boundary-domain-matrix-refinement.yml
```

Matrix cells:

```text
declarative
operational
future-gated
blocked
invalid
unknown
```

Validation:

```sh
sh scripts/test-runtime-boundary-domain-matrix-refinement.sh
sh scripts/test-runtime-boundary.sh
```
