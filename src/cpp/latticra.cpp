/* SPDX-License-Identifier: AGPL-3.0-or-later */
/*
 * Latticra unified driver (C++).
 * Provides the latticra CLI surface, delegating reports to the C implementation
 * and routing authority decisions through the constrained C++ authority layer.
 *
 * MVP target: runnable authority decision + receipt surface (with lat integration).
 * All non-none effects denied; receipt write is the bounded local visible effect.
 * This file is intentionally small and focused on dispatch + the authority MVP path.
 * It does not perform host mutation.
 */

#include "latticra/cpp/authority.hpp"
#include "latticra/lat_parser.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string_view>

extern "C" {
void latticra_cli_print_status(void);
void latticra_cli_print_version(void);
void latticra_cli_print_effect_status(void);
void latticra_cli_print_prevention_research(void);
void latticra_cli_print_prevention_boundary(void);
void latticra_cli_print_prevention_evidence(void);
void latticra_cli_print_prevention_gate(void);
void latticra_cli_print_prevention_fixtures(void);
int latticra_cli_print_prevention_method(const char *method_id);
}

namespace {

void print_usage() {
    std::fputs(
        "usage: latticra [--status|--version|--report|--effect-status|--authority <effect> [id]|--lat-authority <file> [effect]|--prevention-*]\n",
        stderr);
}

latticra::authority_effect map_effect(std::string_view s) {
    if (s == "none") return latticra::authority_effect::none;
    if (s == "read") return latticra::authority_effect::read;
    if (s == "local_mutation") return latticra::authority_effect::local_mutation;
    if (s == "host_mutation") return latticra::authority_effect::host_mutation;
    if (s == "network") return latticra::authority_effect::network;
    if (s == "hardware") return latticra::authority_effect::hardware;
    if (s == "boot") return latticra::authority_effect::boot;
    if (s == "recovery") return latticra::authority_effect::recovery;
    if (s == "external") return latticra::authority_effect::external;
    return latticra::authority_effect::unknown;
}

int run_authority_decision(const char *effect_c, const char *identity_c) {
    std::string_view effect = effect_c ? effect_c : "none";
    std::string_view identity = identity_c ? identity_c : "cli";

    latticra::authority_request req{};
    req.requested_effect = map_effect(effect);
    req.flags = latticra::authority_flags{};
    req.flags.no_effect = true;
    req.source_identity = identity;
    req.lat_result = nullptr;
    req.lir_module = nullptr;

    latticra::authority_audit_report report{};
    latticra::authority_status st = latticra::classify_effect_request(req, report);

    std::puts("LATTICRA AUTHORITY DECISION");
    std::printf("requested_effect=%.*s\n", static_cast<int>(effect.size()), effect.data());
    std::printf("source_identity=%.*s\n", static_cast<int>(identity.size()), identity.data());
    std::printf("classify_status=%s\n", latticra::authority_status_label(st));
    std::puts("--- authority report ---");

    std::array<char, 4096> buf{};
    /* leave terminator room */
    if (latticra::render_authority_audit_report(report, buf.data(), buf.size() - 1) == latticra::authority_status::ok) {
        std::puts(buf.data());
    } else {
        std::puts("(render failed; capacity or input)");
    }
    std::puts("--- end report ---");

    /* Write receipt - the visible user-local effect */
    std::system("mkdir -p artifacts/receipts 2>/dev/null || true");
    std::time_t now = std::time(nullptr);
    char path[256];
    std::snprintf(path, sizeof(path), "artifacts/receipts/authority-decision-%.*s.txt",
                  static_cast<int>(effect.size()), effect.data());
    /* simple non-crypto content hash for the rendered report (fnv-1a 32) */
    uint32_t h = 2166136261u;
    for (const char *p = buf.data(); *p; ++p) {
        h ^= static_cast<uint8_t>(*p);
        h *= 16777619u;
    }
    if (FILE *f = std::fopen(path, "w")) {
        std::fprintf(f, "LATTICRA_RECEIPT\n");
        std::fprintf(f, "type=authority_decision\n");
        std::fprintf(f, "effect=%.*s\n", static_cast<int>(effect.size()), effect.data());
        std::fprintf(f, "identity=%.*s\n", static_cast<int>(identity.size()), identity.data());
        std::fprintf(f, "status=%s\n", latticra::authority_status_label(st));
        std::fprintf(f, "timestamp=%ld\n", static_cast<long>(now));
        std::fprintf(f, "report_hash=0x%08x\n", h);
        std::fprintf(f, "host_mutation=0\n");
        std::fprintf(f, "runtime_authority=0\n");
        std::fprintf(f, "mode=guarded-no-effect\n");
        std::fputs("---report---\n", f);
        std::fputs(buf.data(), f);
        std::fputs("\n---end---\n", f);
        std::fclose(f);
        std::printf("receipt_written=%s\n", path);
    } else {
        std::puts("receipt_write=skipped (mkdir -p artifacts/receipts)");
    }

    std::puts("effect_performed=0");
    std::puts("host_mutation_performed=0");
    return (st == latticra::authority_status::ok) ? 0 : 1;
}

} // namespace

namespace {
int run_lat_authority(const char *path, const char *eff_str) {
    FILE *f = std::fopen(path, "rb");
    if (!f) {
        std::fprintf(stderr, "cannot open lat source: %s\n", path);
        return 2;
    }
    char src[4096];
    size_t n = std::fread(src, 1, sizeof(src)-1, f);
    std::fclose(f);
    src[n] = '\0';

    latticra_lat_parse_result_t res{};
    latticra_status_t pst = latticra_lat_parse_source(src, n, &res);
    if (pst != LATTICRA_STATUS_OK || res.error != LATTICRA_LAT_PARSE_OK) {
        std::puts("LAT_PARSE_FAILED");
        return 1;
    }

    latticra::authority_request req{};
    req.requested_effect = eff_str ? map_effect(eff_str) : latticra::authority_effect::none;
    req.flags.no_effect = res.no_effect != 0;
    req.flags.execution_allowed = res.execution_allowed != 0;
    req.flags.mutation_allowed = res.mutation_allowed != 0;
    req.flags.server_allowed = res.server_allowed != 0;
    req.flags.network_allowed = res.network_allowed != 0;
    req.flags.recovery_allowed = res.recovery_allowed != 0;
    req.flags.hardware_allowed = res.hardware_allowed != 0;
    req.source_identity = path;
    req.lat_result = &res;
    req.lir_module = nullptr;

    latticra::authority_audit_report rep{};
    latticra::authority_status st = latticra::classify_effect_request(req, rep);

    std::puts("LATTICRA LAT+AUTHORITY");
    std::printf("source=%s\n", path);
    std::printf("parse_ok=1\n");
    std::printf("classify=%s\n", latticra::authority_status_label(st));
    std::array<char, 2048> b{};
    latticra::render_authority_audit_report(rep, b.data(), b.size()-1);
    std::puts(b.data());

    /* also emit receipt for this path (local visible effect) */
    std::system("mkdir -p artifacts/receipts 2>/dev/null || true");
    char rpath[256];
    /* derive simple tag from path+effect */
    const char *base = std::strrchr(path, '/'); base = base ? base+1 : path;
    const char *effn = eff_str ? eff_str : "default";
    std::snprintf(rpath, sizeof(rpath), "artifacts/receipts/lat-authority-%s-%s.txt", base, effn);
    if (FILE *rf = std::fopen(rpath, "w")) {
        std::fprintf(rf, "LATTICRA_RECEIPT\nlat_source=%s\nclassify=%s\nhost_mutation=0\n", path, latticra::authority_status_label(st));
        std::fputs(b.data(), rf);
        std::fclose(rf);
        std::printf("lat_receipt_written=%s\n", rpath);
    }
    return (st == latticra::authority_status::ok) ? 0 : 1;
}
} // namespace

int main(int argc, char **argv) {
    if (argc == 2 && (std::strcmp(argv[1], "--status") == 0 || std::strcmp(argv[1], "--report") == 0)) {
        latticra_cli_print_status();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--version") == 0) {
        latticra_cli_print_version();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--effect-status") == 0) {
        latticra_cli_print_effect_status();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--prevention-research") == 0) {
        latticra_cli_print_prevention_research();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--prevention-boundary") == 0) {
        latticra_cli_print_prevention_boundary();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--prevention-evidence") == 0) {
        latticra_cli_print_prevention_evidence();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--prevention-gate") == 0) {
        latticra_cli_print_prevention_gate();
        return 0;
    }
    if (argc == 2 && std::strcmp(argv[1], "--prevention-fixtures") == 0) {
        latticra_cli_print_prevention_fixtures();
        return 0;
    }
    if (argc == 3 && std::strcmp(argv[1], "--prevention-method") == 0) {
        return latticra_cli_print_prevention_method(argv[2]);
    }
    if ((argc == 3 || argc == 4) && std::strcmp(argv[1], "--authority") == 0) {
        const char *eff = argv[2];
        const char *id = (argc == 4) ? argv[3] : nullptr;
        return run_authority_decision(eff, id);
    }
    if (argc == 3 && std::strcmp(argv[1], "--lat-authority") == 0) {
        return run_lat_authority(argv[2], nullptr);
    }
    if (argc == 4 && std::strcmp(argv[1], "--lat-authority") == 0) {
        return run_lat_authority(argv[2], argv[3]);
    }

    if (argc == 2 && (std::strcmp(argv[1], "--help") == 0 || std::strcmp(argv[1], "-h") == 0)) {
        print_usage();
        std::puts("authority effects: none read local_mutation host_mutation network hardware boot recovery external");
        std::puts("MVP: --authority <effect> [id]  |  --lat-authority <latfile> [effect]  (receipts under artifacts/receipts/)");
        return 0;
    }
    print_usage();
    return 2;
}
