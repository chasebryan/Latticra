#!/usr/bin/env python3
from pathlib import Path

path = Path('README.md')
text = path.read_text()

section = '''## Latticra Panel installer

Latticra Panel is the graphical local installer and control panel for Latticra, Lat, LIR, and Latticra Seal.

Fedora prerequisites:

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

Run the installer from source:

```sh
make -C installer gui
```

Safe dry-run:

```sh
make -C installer dry-run
```

Guarded user-local install:

```sh
make -C installer local-example
make -C installer verify-local
```

Open after install:

```sh
export PATH="$HOME/.local/bin:$PATH"
latticra-panel
```

This installer is user-local only. It does not use root, modify the kernel, modify systemd, change SELinux, or use network authority.

Full installer notes are in [`installer/README.md`](installer/README.md).

'''

if section in text:
    raise SystemExit('README already contains the Latticra Panel installer section.')

marker = '## Status and strategy\n'
if marker not in text:
    raise SystemExit('Could not find insertion marker.')

text = text.replace(marker, section + marker, 1)
path.write_text(text)
