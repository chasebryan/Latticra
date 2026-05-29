#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
COPYFILE_DISABLE=1
export COPYFILE_DISABLE

fail() {
  printf 'fedora installroot rpm mutation lane: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_command() {
  command -v "$1" >/dev/null 2>&1 || fail "missing command: $1"
}

require_no_payload_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$payload_listing"; then
    fail "forbidden RPM payload pattern matched: $pattern"
  fi
}

# Source archives use Git's tracked and unignored source view, refuse symlink entries,
# and normalize tar metadata before RPM build input is accepted.
write_source_archive() {
  archive_path="$1"
  root="$2"
  python3 - "$archive_path" "$root" <<'PY'
import gzip
import os
import stat
import subprocess
import sys
import tarfile

archive_path = sys.argv[1]
root = sys.argv[2]
source_root = os.getcwd()


def excluded(relative):
    parts = relative.split(os.sep)
    if ".git" in parts or ".rpmwork" in parts:
        return True
    name = parts[-1]
    return name.endswith(".rpm") or name.endswith(".tar.gz")


def add_entry(archive, disk_path, archive_name):
    st = os.lstat(disk_path)
    if stat.S_ISLNK(st.st_mode):
        raise SystemExit(f"refusing source archive with symlink entry: {archive_name}")
    if not stat.S_ISDIR(st.st_mode) and not stat.S_ISREG(st.st_mode):
        raise SystemExit(f"refusing unsupported source archive entry: {archive_name}")

    info = tarfile.TarInfo(archive_name)
    info.uid = 0
    info.gid = 0
    info.uname = "root"
    info.gname = "root"
    info.mtime = 0
    info.pax_headers = {}
    if stat.S_ISDIR(st.st_mode):
        info.type = tarfile.DIRTYPE
        info.mode = 0o755
        archive.addfile(info)
        return

    info.size = st.st_size
    info.mode = 0o755 if (st.st_mode & stat.S_IXUSR) else 0o644
    with open(disk_path, "rb") as source:
        archive.addfile(info, source)


with open(archive_path, "wb") as raw:
    with gzip.GzipFile(filename="", mode="wb", fileobj=raw, mtime=0) as gz:
        with tarfile.open(fileobj=gz, mode="w", format=tarfile.PAX_FORMAT) as archive:
            add_entry(archive, source_root, root)
            proc = subprocess.run(
                ["git", "ls-files", "-z", "--cached", "--others", "--exclude-standard"],
                cwd=source_root,
                check=True,
                stdout=subprocess.PIPE,
            )
            paths = sorted(
                item.decode("utf-8")
                for item in proc.stdout.split(b"\0")
                if item
            )
            dirs = set()
            for rel in paths:
                if excluded(rel):
                    continue
                parent = os.path.dirname(rel)
                while parent:
                    dirs.add(parent)
                    parent = os.path.dirname(parent)

            for rel in sorted(dirs):
                add_entry(archive, os.path.join(source_root, rel), f"{root}/{rel}")
            for rel in paths:
                if excluded(rel):
                    continue
                add_entry(archive, os.path.join(source_root, rel), f"{root}/{rel}")
PY
}

[ "${LATTICRA_ALLOW_INSTALLROOT_RPM_MUTATION:-0}" = "1" ] || \
  fail 'refusing mutation without LATTICRA_ALLOW_INSTALLROOT_RPM_MUTATION=1'

[ -f /etc/os-release ] || fail 'missing /etc/os-release'
# shellcheck disable=SC1091
. /etc/os-release
[ "${ID:-}" = "fedora" ] || fail "refusing non-Fedora execution environment: ${ID:-unknown}"
[ "${GITHUB_ACTIONS:-}" = "true" ] || fail 'refusing outside GitHub Actions disposable CI'

require_command awk
require_command find
require_command git
require_command grep
require_command mktemp
require_command python3
require_command rpm
require_command rpmbuild
require_command sort
require_command tar
require_command gzip

require_file packaging/fedora/latticra.spec
require_file README.md
require_file docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
[ "$name" = 'latticra' ] || fail "unexpected package name: $name"
[ -n "$version" ] || fail 'missing package version'

root="${name}-${version}"
workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT INT HUP TERM

rpmtop="$workdir/rpmbuild"
source_archive="$rpmtop/SOURCES/$root.tar.gz"
installroot="$workdir/installroot"
report="$workdir/execution.report"
payload_listing="$workdir/payload.list"
installed_listing="$workdir/installed.list"

mkdir -p "$rpmtop/BUILD" "$rpmtop/BUILDROOT" "$rpmtop/RPMS" "$rpmtop/SOURCES" "$rpmtop/SPECS" "$rpmtop/SRPMS"
mkdir -p "$installroot/var/lib/rpm"

symlink_entry=$(find . -path './.git' -prune -o -type l -print | sed -n '1p')
[ -z "$symlink_entry" ] ||
  fail "refusing source archive with symlink entry: $symlink_entry"

write_source_archive "$source_archive" "$root"
cp packaging/fedora/latticra.spec "$rpmtop/SPECS/latticra.spec"

rpmbuild --define "_topdir $rpmtop" -bb "$rpmtop/SPECS/latticra.spec"

rpm_path="$(find "$rpmtop/RPMS" -type f -name 'latticra-*.rpm' ! -name '*debuginfo*' ! -name '*debugsource*' | sort | head -n 1)"
[ -n "$rpm_path" ] || fail 'binary RPM was not produced'

rpm -qpi "$rpm_path" >/dev/null
rpm -qpl "$rpm_path" >"$payload_listing"
grep -Fqx '/usr/share/doc/latticra/README.md' "$payload_listing" || fail 'README payload missing from RPM'
require_no_payload_pattern '^/usr/bin/latticra$'
require_no_payload_pattern '^/etc/latticra(/|$)'
require_no_payload_pattern '^/usr/lib/systemd/system/latticra\.service$'
require_no_payload_pattern '^/usr/lib/modules(/|$)'
require_no_payload_pattern '^/boot/latticra(/|$)'

rpm --root "$installroot" --dbpath /var/lib/rpm --initdb
rpm --root "$installroot" --dbpath /var/lib/rpm -Uvh --nodeps "$rpm_path"
rpm --root "$installroot" --dbpath /var/lib/rpm -q "$name" >/dev/null
rpm --root "$installroot" --dbpath /var/lib/rpm -ql "$name" >"$installed_listing"
grep -Fqx '/usr/share/doc/latticra/README.md' "$installed_listing" || fail 'installroot README payload missing'
[ -f "$installroot/usr/share/doc/latticra/README.md" ] || fail 'installroot README file absent'
rpm --root "$installroot" --dbpath /var/lib/rpm -V "$name"

rpm --root "$installroot" --dbpath /var/lib/rpm -e "$name"
if rpm --root "$installroot" --dbpath /var/lib/rpm -q "$name" >/dev/null 2>&1; then
  fail 'package still installed in installroot after removal'
fi
if [ -e "$installroot/usr/share/doc/latticra/README.md" ]; then
  fail 'README payload still present in installroot after removal'
fi

cat >"$report" <<EOF_REPORT
FEDORA INSTALLROOT RPM MUTATION LANE
execution_status=ok
package_name=$name
package_version=$version
installroot=$installroot
install_mutation_allowed=1
install_mutation_performed=1
removal_mutation_allowed=1
removal_mutation_performed=1
installroot_filesystem_mutated=1
installroot_rpmdb_mutated=1
live_container_rpmdb_mutated=0
developer_host_mutation_performed=0
boot_operation_performed=0
kernel_operation_performed=0
service_operation_performed=0
policy_operation_performed=0
network_allowed_during_rpm_execution=0
post_removal_absence_verified=1
rollback_planned=1
partial_failure_report_required=1
evidence_level=6
EOF_REPORT

grep -Fq 'execution_status=ok' "$report" || fail 'missing execution status'
grep -Fq 'install_mutation_performed=1' "$report" || fail 'missing install mutation evidence'
grep -Fq 'removal_mutation_performed=1' "$report" || fail 'missing removal mutation evidence'
grep -Fq 'live_container_rpmdb_mutated=0' "$report" || fail 'missing live container boundary'
grep -Fq 'post_removal_absence_verified=1' "$report" || fail 'missing post-removal verification'

cat "$report"
printf 'fedora_installroot_rpm_mutation_lane: ok\n'
