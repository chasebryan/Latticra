# LOCAL-ONLY FreeBSD PORT DRAFT
# Upstream packaging experiment for Latticra.
# Source archive, license, portlint, poudriere, and ports-tree review are unresolved.

PORTNAME=	latticra
DISTVERSION=	0.0.0
CATEGORIES=	devel

MAINTAINER=	noreply@example.invalid
COMMENT=	Contract-first systems architecture and language project
WWW=		https://github.com/Bryforge/Latticra

LICENSE=	LicenseRef-Latticra-TBD

USES=		compiler:c11

do-build:
	${MKDIR} ${WRKSRC}/build
	cd ${WRKSRC} && sh scripts/test-latticra-no-effect-cli-status-surface.sh
	${CC} ${CFLAGS} -std=c99 -Wall -Wextra -Werror -pedantic ${WRKSRC}/src/latticra_cli.c -o ${WRKSRC}/build/latticra

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/bin
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_PROGRAM} ${WRKSRC}/build/latticra ${STAGEDIR}${PREFIX}/bin/latticra
	${INSTALL_DATA} ${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}/README.md

.include <bsd.port.mk>
