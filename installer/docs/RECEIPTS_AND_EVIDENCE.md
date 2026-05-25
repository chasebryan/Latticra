# Receipts and Evidence

The installer should leave behind evidence that is understandable to a human operator.

The current receipt includes:

- UTC timestamp
- selected profile
- install prefix
- dry-run status
- host mutation authority status
- network authority status
- component choices
- behavior choices
- component manifest path
- installer script measurement
- config measurement
- generated install plan

The reset receipt includes:

- UTC timestamp
- reset mode
- install prefix
- command wrapper, desktop entry, icon, and prefix actions
- removed, planned, preserved, and missing counts
- authority baseline

The measurement is SHA-256 when `sha256sum` or `shasum -a 256` is available. If neither exists, the script falls back to POSIX `cksum` and labels it clearly.

Receipts are not a substitute for cryptographic release signing. They are a development evidence trail.
