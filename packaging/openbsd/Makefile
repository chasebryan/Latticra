# LOCAL-ONLY OpenBSD PORT DRAFT
# Upstream packaging experiment for Latticra.
# Source archive, portcheck, bulk build, and ports-tree review are unresolved.

COMMENT=	contract-first systems architecture and language project
DISTNAME=	latticra-0.0.0
CATEGORIES=	devel

HOMEPAGE=	https://github.com/Bryforge/Latticra
MAINTAINER=	Bryforge <noreply@example.invalid>

# Package payload license: AGPL-3.0-or-later AND CC-BY-4.0.
# Redistribution remains closed until source, checksum, notice, and port review evidence exists.
PERMIT_PACKAGE=	No

WANTLIB += c

do-build:
	${MKDIR} ${WRKSRC}/build
	cd ${WRKSRC} && sh scripts/test-latticra-no-effect-cli-status-surface.sh
	${CC} ${CFLAGS} -std=c99 -Wall -Wextra -Werror -pedantic ${WRKSRC}/src/latticra_cli.c -o ${WRKSRC}/build/latticra

do-install:
	${INSTALL_PROGRAM_DIR} ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/latticra
	${INSTALL_PROGRAM} ${WRKSRC}/build/latticra ${PREFIX}/bin/latticra
	${INSTALL_DATA} ${WRKSRC}/README.md ${PREFIX}/share/doc/latticra/README.md

.include <bsd.port.mk>
