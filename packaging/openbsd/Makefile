# LOCAL-ONLY OpenBSD PORT DRAFT
# Upstream packaging experiment for Latticra.
# Source archive, license, portcheck, bulk build, and ports-tree review are unresolved.

COMMENT=	contract-first systems architecture and language project
DISTNAME=	latticra-0.0.0
CATEGORIES=	devel

HOMEPAGE=	https://github.com/Bryforge/Latticra
MAINTAINER=	Bryforge <noreply@example.invalid>

# LicenseRef-Latticra-TBD pending formal package license review.
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
