# Latticra C ABI Boundary Policy

Status: Draft  
Layer: Security / ABI  
Applies to: C-facing entry points, C/C++ interop, platform shims, plugin-like surfaces if introduced.

## 1. Purpose

This document defines how Latticra exposes and consumes C ABI boundaries.

C ABI boundaries are necessary for platform control, bootstrapping, interop, and long-term stability. They are also dangerous if they carry implicit ownership, unchecked buffers, ambiguous errors, or hidden mutation.

Latticra treats every C ABI boundary as a security-relevant boundary.

## 2. Core rules

```text
No ownership crosses implicitly.
No lifetime crosses implicitly.
No mutation crosses without authorization.
No buffer crosses without length.
No result crosses without status.
No platform-specific behavior hides in generic ABI code.
```

## 3. Handles

Opaque handles are preferred over exposed implementation structures.

Example:

```c
typedef struct latticra_handle latticra_handle;
```

Rules:

- callers must not know the internal layout;
- handle creation and destruction must be explicit;
- null handle behavior must be defined;
- invalid handle behavior must be defined;
- handle ownership must be documented.

## 4. Status codes

C ABI functions must return explicit status codes unless there is a strong reason not to.

Example:

```c
typedef enum {
    LATTICRA_OK = 0,
    LATTICRA_ERR_DENIED,
    LATTICRA_ERR_INVALID_CONTRACT,
    LATTICRA_ERR_OUT_OF_RANGE,
    LATTICRA_ERR_UNSUPPORTED,
    LATTICRA_ERR_INTERNAL
} latticra_status;
```

Rules:

- never collapse all failures into one generic failure if policy decisions matter;
- distinguish denied, invalid, unsupported, and internal failures;
- avoid leaking sensitive details across public ABI;
- provide a safe diagnostic path where appropriate.

## 5. Buffers

All byte buffers must include an explicit length.

Example:

```c
typedef struct {
    const unsigned char* data;
    unsigned long length;
} latticra_bytes;
```

Rules:

- no buffer without length;
- no null data pointer unless length is zero and explicitly allowed;
- maximum allowed lengths should be defined for external input;
- buffer ownership must remain with the caller unless otherwise documented;
- mutable output buffers must include capacity and written length.

## 6. Strings

Strings crossing the ABI must be treated as byte buffers with encoding rules.

Rules:

- define UTF-8 or other encoding explicitly;
- define whether null termination is required;
- never assume null termination if length is provided;
- validate before converting to internal string types;
- reject or normalize invalid encoding according to the specific boundary contract.

## 7. Ownership

Ownership transfer must be explicit in the function name or documentation.

Preferred naming:

```text
create / destroy
borrow / view
copy
take
release
```

Rules:

- borrowed data may not outlive the call unless explicitly documented;
- created handles must have a corresponding destroy function;
- output allocations must specify who frees them and how;
- allocator crossing is forbidden unless an ABI allocator contract exists.

## 8. Mutation

Mutation must be intentional.

Rules:

- no mutation through `const`-violating casts;
- no hidden global mutation;
- no policy mutation through generic utility calls;
- mutation that affects authority must pass through an effect gate;
- mutation must produce audit evidence when it is security-relevant.

## 9. Example ABI shape

```c
typedef struct latticra_handle latticra_handle;

typedef enum {
    LATTICRA_OK = 0,
    LATTICRA_ERR_DENIED,
    LATTICRA_ERR_INVALID_CONTRACT,
    LATTICRA_ERR_OUT_OF_RANGE,
    LATTICRA_ERR_UNSUPPORTED,
    LATTICRA_ERR_INTERNAL
} latticra_status;

typedef struct {
    const unsigned char* data;
    unsigned long length;
} latticra_bytes;

latticra_status latticra_validate_contract(
    latticra_handle* handle,
    latticra_bytes input
);

latticra_status latticra_destroy(
    latticra_handle* handle
);
```

## 10. C++ implementation mapping

C ABI functions should be thin wrappers around restricted C++ authority logic.

Example conceptual mapping:

```text
C ABI call
  -> argument shape check
  -> safe view construction
  -> C++ validator / authority object
  -> typed result
  -> status code mapping
  -> audit record if security-relevant
```

C ABI wrappers should not contain complex policy logic unless unavoidable.

## 11. Audit requirements

Security-relevant ABI calls should produce audit records when they:

- validate contracts;
- deny requests;
- authorize effects;
- mutate policy state;
- execute platform effects;
- load external modules;
- alter runtime state;
- access sensitive platform data.

Audit records should not leak secrets through public output.

## 12. Review checklist

Before accepting a C ABI function:

- [ ] Does every pointer have a documented null rule?
- [ ] Does every buffer have a length?
- [ ] Does every mutable output have a capacity?
- [ ] Is ownership explicit?
- [ ] Is lifetime explicit?
- [ ] Are status codes precise enough?
- [ ] Are inputs validated before internal use?
- [ ] Does the function avoid hidden global mutation?
- [ ] Does privileged behavior pass through an effect gate?
- [ ] Does security-relevant behavior produce audit evidence?
- [ ] Is platform-specific behavior isolated?

## 13. Promotion rule

No ABI surface should be described as stable until:

- the function contract is documented;
- tests exist for invalid inputs;
- null and boundary behavior are tested;
- ownership and lifetime rules are documented;
- audit behavior is documented where relevant.
