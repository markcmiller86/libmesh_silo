!cccccccccccccccccccccccccccccccccccccccccccccccccccccccc -*- fortran -*-
!
!     SILO include file for Fortan applications.
!
! Programmer:   miller86 Wed Sep 21 09:25:31 PDT 2011
!
! WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
!    This file is generated automatically from C header files in the
!    SILO distribution.  Do not make changes to this file manually,
!    as those changes will disappear.
! WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
!
! This file was generated by the following commands...
!       mv silo.inc silo.inc~
!       cat silo.h silo_f.h | mkinc > silo.inc
!
!cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc


!...Functions.
      external dbaddcaopt, dbaddccmp, dbaddcopt, dbadddopt, dbaddiaopt
      external dbaddicmp, dbaddiopt, dbaddrcmp, dbaddregion
      external dbaddregiona, dbaddropt, dbcalcfl, dbclose, dbcreate
      external dberrno, dbfgetca, dbfreemrgtree, dbfreeobject
      external dbfreeoptlist, dbget2dstrlen, dbgetca, dbgetcksums
      external dbgetcompress, dbgetcurve, dbgetdepwarn, dbgethdfnms
      external dbgetovrwrt, dbgetqv1, dbinqca, dbinqfile, dbinqlen
      external dbmkdir, dbmkmrgtree, dbmkobject, dbmkoptlist, dbmkptr
      external dbopen, dbpmrgv, dbputca, dbputcsgm, dbputcsgv
      external dbputcsgzl, dbputcurve, dbputdefvars, dbputfl
      external dbputgrplmap, dbputmat, dbputmmat, dbputmmesh
      external dbputmrgtree, dbputmsp, dbputmvar, dbputpm, dbputpv1
      external dbputqm, dbputqv, dbputqv1, dbputum, dbputuv1, dbputzl
      external dbputzl2, dbrdvar, dbrdvarslice, dbregfopts, dbrmptr
      external dbset2dstrlen, dbsetcksums, dbsetcompress, dbsetcwr
      external dbsetdepwarn, dbsetdir, dbsetdirid, dbsethdfnms
      external dbsetovrwrt, dbshowerrors, dbunregafopts, dbunregfopts
      external dbwrite, dbwriteslice, dbwrtfl

      integer  dbaddcaopt, dbaddccmp, dbaddcopt, dbadddopt, dbaddiaopt
      integer  dbaddicmp, dbaddiopt, dbaddrcmp, dbaddregion
      integer  dbaddregiona, dbaddropt, dbcalcfl, dbclose, dbcreate
      integer  dberrno, dbfgetca, dbfreemrgtree, dbfreeobject
      integer  dbfreeoptlist, dbget2dstrlen, dbgetca, dbgetcksums
      integer  dbgetcompress, dbgetcurve, dbgetdepwarn, dbgethdfnms
      integer  dbgetovrwrt, dbgetqv1, dbinqca, dbinqfile, dbinqlen
      integer  dbmkdir, dbmkmrgtree, dbmkobject, dbmkoptlist, dbmkptr
      integer  dbopen, dbpmrgv, dbputca, dbputcsgm, dbputcsgv
      integer  dbputcsgzl, dbputcurve, dbputdefvars, dbputfl
      integer  dbputgrplmap, dbputmat, dbputmmat, dbputmmesh
      integer  dbputmrgtree, dbputmsp, dbputmvar, dbputpm, dbputpv1
      integer  dbputqm, dbputqv, dbputqv1, dbputum, dbputuv1, dbputzl
      integer  dbputzl2, dbrdvar, dbrdvarslice, dbregfopts, dbrmptr
      integer  dbset2dstrlen, dbsetcksums, dbsetcompress, dbsetcwr
      integer  dbsetdepwarn, dbsetdir, dbsetdirid, dbsethdfnms
      integer  dbsetovrwrt, dbshowerrors, dbunregafopts, dbunregfopts
      integer  dbwrite, dbwriteslice, dbwrtfl


!...Parameters.
      integer  DBCSG_ANGLE_PNLA, DBCSG_ANGLE_PPA, DBCSG_BOX_XYXY
      integer  DBCSG_BOX_XYZXYZ, DBCSG_CIRCLE_PR, DBCSG_COMPLIMENT
      integer  DBCSG_CONE_PNLA, DBCSG_CONE_PPA, DBCSG_CYLINDER_PNLR
      integer  DBCSG_CYLINDER_PPR, DBCSG_DIFF, DBCSG_ELLIPSE_PRR
      integer  DBCSG_ELLIPSOID_PRRR, DBCSG_HEX_6F, DBCSG_INNER
      integer  DBCSG_INTERSECT, DBCSG_LINE_G, DBCSG_LINE_PN
      integer  DBCSG_LINE_PP, DBCSG_LINE_X, DBCSG_LINE_Y, DBCSG_ON
      integer  DBCSG_OUTER, DBCSG_PLANE_G, DBCSG_PLANE_PN
      integer  DBCSG_PLANE_PPP, DBCSG_PLANE_X, DBCSG_PLANE_Y
      integer  DBCSG_PLANE_Z, DBCSG_POLYGON_KP, DBCSG_POLYHEDRON_KF
      integer  DBCSG_PRISM_5F, DBCSG_PYRAMID_5F, DBCSG_QUADRATIC_G
      integer  DBCSG_QUADRIC_G, DBCSG_QUAD_4P, DBCSG_SPHERE_PR
      integer  DBCSG_SWEEP, DBCSG_TET_4F, DBCSG_TRI_3P, DBCSG_UNION
      integer  DBCSG_XFORM, DBOPT_ALIGN, DBOPT_ALLOWMAT0
      integer  DBOPT_ASCII_LABEL, DBOPT_BASEINDEX, DBOPT_BLOCKORIGIN
      integer  DBOPT_BNDNAMES, DBOPT_CONSERVED, DBOPT_COORDSYS
      integer  DBOPT_CYCLE, DBOPT_DISJOINT_MODE, DBOPT_DTIME
      integer  DBOPT_EXTENSIVE, DBOPT_EXTENTS, DBOPT_EXTENTS_SIZE
      integer  DBOPT_FACETYPE, DBOPT_FIRST, DBOPT_GROUPINGNAMES
      integer  DBOPT_GROUPINGS, DBOPT_GROUPINGS_SIZE, DBOPT_GROUPNUM
      integer  DBOPT_GROUPORIGIN, DBOPT_H5_ALIGN_MIN, DBOPT_H5_ALIGN_VAL
      integer  DBOPT_H5_CACHE_NBYTES, DBOPT_H5_CACHE_NELMTS
      integer  DBOPT_H5_CACHE_POLICY, DBOPT_H5_CORE_ALLOC_INC
      integer  DBOPT_H5_CORE_NO_BACK_STORE, DBOPT_H5_DIRECT_BLOCK_SIZE
      integer  DBOPT_H5_DIRECT_BUF_SIZE, DBOPT_H5_DIRECT_MEM_ALIGN
      integer  DBOPT_H5_FAM_FILE_OPTS, DBOPT_H5_FAM_SIZE, DBOPT_H5_FIRST
      integer  DBOPT_H5_LAST, DBOPT_H5_LOG_BUF_SIZE, DBOPT_H5_LOG_NAME
      integer  DBOPT_H5_META_BLOCK_SIZE, DBOPT_H5_META_EXTENSION
      integer  DBOPT_H5_META_FILE_OPTS, DBOPT_H5_MPIO_COMM
      integer  DBOPT_H5_MPIO_INFO, DBOPT_H5_MPIP_NO_GPFS_HINTS
      integer  DBOPT_H5_RAW_EXTENSION, DBOPT_H5_RAW_FILE_OPTS
      integer  DBOPT_H5_SIEVE_BUF_SIZE, DBOPT_H5_SILO_BLOCK_COUNT
      integer  DBOPT_H5_SILO_BLOCK_SIZE, DBOPT_H5_SILO_LOG_STATS
      integer  DBOPT_H5_SILO_USE_DIRECT, DBOPT_H5_SMALL_RAW_SIZE
      integer  DBOPT_H5_USER_DRIVER_ID, DBOPT_H5_USER_DRIVER_INFO
      integer  DBOPT_H5_VFD, DBOPT_HAS_EXTERNAL_ZONES
      integer  DBOPT_HIDE_FROM_GUI, DBOPT_HI_OFFSET, DBOPT_LABEL
      integer  DBOPT_LAST, DBOPT_LLONGNZNUM, DBOPT_LO_OFFSET
      integer  DBOPT_MAJORORDER, DBOPT_MATCOLORS, DBOPT_MATCOUNTS
      integer  DBOPT_MATLISTS, DBOPT_MATNAME, DBOPT_MATNAMES
      integer  DBOPT_MATNOS, DBOPT_MB_BLOCK_NS, DBOPT_MB_BLOCK_TYPE
      integer  DBOPT_MB_EMPTY_COUNT, DBOPT_MB_EMPTY_LIST
      integer  DBOPT_MB_FILE_NS, DBOPT_MIXLENS, DBOPT_MMESH_NAME
      integer  DBOPT_MRGTREE_NAME, DBOPT_MRGV_ONAMES, DBOPT_MRGV_RNAMES
      integer  DBOPT_NGROUPS, DBOPT_NMAT, DBOPT_NMATNOS, DBOPT_NMATSPEC
      integer  DBOPT_NODENUM, DBOPT_NSPACE, DBOPT_ORIGIN
      integer  DBOPT_PHZONELIST, DBOPT_PLANAR, DBOPT_REFERENCE
      integer  DBOPT_REGION_PNAMES, DBOPT_REGNAMES, DBOPT_SPECCOLORS
      integer  DBOPT_SPECNAMES, DBOPT_TENSOR_RANK, DBOPT_TIME
      integer  DBOPT_TOPO_DIM, DBOPT_TV_CONNECTIVITY, DBOPT_UNITS
      integer  DBOPT_USESPECMF, DBOPT_XLABEL, DBOPT_XUNITS
      integer  DBOPT_XVARNAME, DBOPT_YLABEL, DBOPT_YUNITS
      integer  DBOPT_YVARNAME, DBOPT_ZLABEL, DBOPT_ZONECOUNTS
      integer  DBOPT_ZONENAMES, DBOPT_ZONENUM, DBOPT_ZUNITS
      integer  DBOPT_ZVARNAME, DB_ABORT, DB_ABUTTING, DB_ALL
      integer  DB_ALL_AND_DRVR, DB_APPEND, DB_AREA, DB_ARRAY
      integer  DB_BLOCKCENT, DB_BNDCENT, DB_CARTESIAN, DB_CHAR
      integer  DB_CLOBBER, DB_COLLINEAR, DB_COLMAJOR, DB_CRAY
      integer  DB_CSGMESH, DB_CSGVAR, DB_CSGZONELIST, DB_CURVE
      integer  DB_CURVILINEAR, DB_CYLINDRICAL, DB_DEBUG, DB_DEFVARS
      integer  DB_DIR, DB_DOUBLE, DB_EDGECENT, DB_EDGELIST, DB_F77NULL
      integer  DB_FACECENT, DB_FACELIST, DB_FILE_OPTS_H5_DEFAULT_CORE
      integer  DB_FILE_OPTS_H5_DEFAULT_DEFAULT
      integer  DB_FILE_OPTS_H5_DEFAULT_DIRECT
      integer  DB_FILE_OPTS_H5_DEFAULT_FAMILY
      integer  DB_FILE_OPTS_H5_DEFAULT_LOG, DB_FILE_OPTS_H5_DEFAULT_MPIO
      integer  DB_FILE_OPTS_H5_DEFAULT_MPIP
      integer  DB_FILE_OPTS_H5_DEFAULT_SEC2
      integer  DB_FILE_OPTS_H5_DEFAULT_SILO
      integer  DB_FILE_OPTS_H5_DEFAULT_SPLIT
      integer  DB_FILE_OPTS_H5_DEFAULT_STDIO, DB_FILE_OPTS_LAST
      integer  DB_FLOAT, DB_FLOATING, DB_FROMCWR, DB_GROUPELMAP
      integer  DB_H5VFD_CORE, DB_H5VFD_DEFAULT, DB_H5VFD_DIRECT
      integer  DB_H5VFD_FAMILY, DB_H5VFD_LOG, DB_H5VFD_MPIO
      integer  DB_H5VFD_MPIP, DB_H5VFD_SEC2, DB_H5VFD_SILO
      integer  DB_H5VFD_SPLIT, DB_H5VFD_STDIO, DB_HDF5, DB_HDF5X
      integer  DB_HDF5_CORE, DB_HDF5_CORE_OBSOLETE, DB_HDF5_DIRECT
      integer  DB_HDF5_FAMILY, DB_HDF5_LOG, DB_HDF5_MPIO, DB_HDF5_MPIOP
      integer  DB_HDF5_MPIOP_OBSOLETE, DB_HDF5_MPIO_OBSOLETE
      integer  DB_HDF5_MPIP, DB_HDF5_SEC2, DB_HDF5_SEC2_OBSOLETE
      integer  DB_HDF5_SILO, DB_HDF5_SPLIT, DB_HDF5_STDIO
      integer  DB_HDF5_STDIO_OBSOLETE, DB_INT, DB_INTEL
      integer  DB_INVALID_OBJECT, DB_LOCAL, DB_LONG, DB_LONG_LONG
      integer  DB_MATERIAL, DB_MATSPECIES, DB_MRGTREE, DB_MRGVAR
      integer  DB_MULTIBLOCKMESH, DB_MULTIBLOCKVAR, DB_MULTIMAT
      integer  DB_MULTIMATSPECIES, DB_MULTIMESH, DB_MULTIMESHADJ
      integer  DB_MULTIVAR, DB_NETCDF, DB_NFILES, DB_NFILTERS
      integer  DB_NOCLOBBER, DB_NODECENT, DB_NONCOLLINEAR, DB_NONE
      integer  DB_NOTCENT, DB_NOTYPE, DB_NUMERICAL, DB_OFF, DB_ON
      integer  DB_OTHER, DB_PDB, DB_PDBP, DB_PHZONELIST, DB_POINTMESH
      integer  DB_POINTVAR, DB_POSTORDER, DB_PREORDER, DB_QUADCURV
      integer  DB_QUADMESH, DB_QUADRECT, DB_QUADVAR, DB_QUAD_CURV
      integer  DB_QUAD_RECT, DB_READ, DB_RECTILINEAR, DB_RESUME
      integer  DB_ROWMAJOR, DB_RS6000, DB_SGI, DB_SHORT, DB_SPHERICAL
      integer  DB_SUN3, DB_SUN4, DB_SUSPEND, DB_TAURUS, DB_TOP
      integer  DB_UCDMESH, DB_UCDVAR, DB_UNKNOWN, DB_USERDEF
      integer  DB_VARIABLE, DB_VARTYPE_ARRAY, DB_VARTYPE_LABEL
      integer  DB_VARTYPE_MATERIAL, DB_VARTYPE_SCALAR
      integer  DB_VARTYPE_SPECIES, DB_VARTYPE_SYMTENSOR
      integer  DB_VARTYPE_TENSOR, DB_VARTYPE_VECTOR, DB_VOLUME
      integer  DB_ZONECENT, DB_ZONELIST, DB_ZONETYPE_BEAM
      integer  DB_ZONETYPE_HEX, DB_ZONETYPE_POLYGON
      integer  DB_ZONETYPE_POLYHEDRON, DB_ZONETYPE_PRISM
      integer  DB_ZONETYPE_PYRAMID, DB_ZONETYPE_QUAD, DB_ZONETYPE_TET
      integer  DB_ZONETYPE_TRIANGLE, SILO_VERS_MAJ, SILO_VERS_MIN
      integer  SILO_VERS_PAT, SILO_VERS_PRE
      character*12  DB_F77NULLSTRING

      parameter(SILO_VERS_MAJ=4)
      parameter(SILO_VERS_MIN=8)
      parameter(SILO_VERS_PAT=0)
      parameter(SILO_VERS_PRE=0)
      parameter(DB_NETCDF=0)
      parameter(DB_PDB=2)
      parameter(DB_TAURUS=3)
      parameter(DB_UNKNOWN=5)
      parameter(DB_DEBUG=6)
      parameter(DB_HDF5X=7)
      parameter(DB_PDBP=1)
      parameter(DB_HDF5_SEC2_OBSOLETE=256)
      parameter(DB_HDF5_STDIO_OBSOLETE=512)
      parameter(DB_HDF5_CORE_OBSOLETE=768)
      parameter(DB_HDF5_MPIO_OBSOLETE=1024)
      parameter(DB_HDF5_MPIOP_OBSOLETE=1280)
      parameter(DB_H5VFD_DEFAULT=0)
      parameter(DB_H5VFD_SEC2=1)
      parameter(DB_H5VFD_STDIO=2)
      parameter(DB_H5VFD_CORE=3)
      parameter(DB_H5VFD_LOG=4)
      parameter(DB_H5VFD_SPLIT=5)
      parameter(DB_H5VFD_DIRECT=6)
      parameter(DB_H5VFD_FAMILY=7)
      parameter(DB_H5VFD_MPIO=8)
      parameter(DB_H5VFD_MPIP=9)
      parameter(DB_H5VFD_SILO=10)
      parameter(DB_FILE_OPTS_H5_DEFAULT_DEFAULT=0)
      parameter(DB_FILE_OPTS_H5_DEFAULT_SEC2=1)
      parameter(DB_FILE_OPTS_H5_DEFAULT_STDIO=2)
      parameter(DB_FILE_OPTS_H5_DEFAULT_CORE=3)
      parameter(DB_FILE_OPTS_H5_DEFAULT_LOG=4)
      parameter(DB_FILE_OPTS_H5_DEFAULT_SPLIT=5)
      parameter(DB_FILE_OPTS_H5_DEFAULT_DIRECT=6)
      parameter(DB_FILE_OPTS_H5_DEFAULT_FAMILY=7)
      parameter(DB_FILE_OPTS_H5_DEFAULT_MPIO=8)
      parameter(DB_FILE_OPTS_H5_DEFAULT_MPIP=9)
      parameter(DB_FILE_OPTS_H5_DEFAULT_SILO=10)
      parameter(DB_FILE_OPTS_LAST=10)
      parameter(DB_HDF5=7)
      parameter(DB_HDF5_SEC2=2055)
      parameter(DB_HDF5_STDIO=4103)
      parameter(DB_HDF5_CORE=6151)
      parameter(DB_HDF5_LOG=8199)
      parameter(DB_HDF5_SPLIT=10247)
      parameter(DB_HDF5_DIRECT=12295)
      parameter(DB_HDF5_FAMILY=14343)
      parameter(DB_HDF5_MPIO=16391)
      parameter(DB_HDF5_MPIOP=18439)
      parameter(DB_HDF5_MPIP=18439)
      parameter(DB_HDF5_SILO=20487)
      parameter(DB_NFILES=256)
      parameter(DB_NFILTERS=32)
      parameter(DB_COLLINEAR=130)
      parameter(DB_NONCOLLINEAR=131)
      parameter(DB_QUAD_RECT=130)
      parameter(DB_QUAD_CURV=131)
      parameter(DB_INVALID_OBJECT=-1)
      parameter(DB_QUADRECT=130)
      parameter(DB_QUADCURV=131)
      parameter(DB_QUADMESH=500)
      parameter(DB_QUADVAR=501)
      parameter(DB_UCDMESH=510)
      parameter(DB_UCDVAR=511)
      parameter(DB_MULTIMESH=520)
      parameter(DB_MULTIVAR=521)
      parameter(DB_MULTIMAT=522)
      parameter(DB_MULTIMATSPECIES=523)
      parameter(DB_MULTIBLOCKMESH=520)
      parameter(DB_MULTIBLOCKVAR=521)
      parameter(DB_MULTIMESHADJ=524)
      parameter(DB_MATERIAL=530)
      parameter(DB_MATSPECIES=531)
      parameter(DB_FACELIST=550)
      parameter(DB_ZONELIST=551)
      parameter(DB_EDGELIST=552)
      parameter(DB_PHZONELIST=553)
      parameter(DB_CSGZONELIST=554)
      parameter(DB_CSGMESH=555)
      parameter(DB_CSGVAR=556)
      parameter(DB_CURVE=560)
      parameter(DB_DEFVARS=565)
      parameter(DB_POINTMESH=570)
      parameter(DB_POINTVAR=571)
      parameter(DB_ARRAY=580)
      parameter(DB_DIR=600)
      parameter(DB_VARIABLE=610)
      parameter(DB_MRGTREE=611)
      parameter(DB_GROUPELMAP=612)
      parameter(DB_MRGVAR=613)
      parameter(DB_USERDEF=700)
      parameter(DB_INT=16)
      parameter(DB_SHORT=17)
      parameter(DB_LONG=18)
      parameter(DB_FLOAT=19)
      parameter(DB_DOUBLE=20)
      parameter(DB_CHAR=21)
      parameter(DB_LONG_LONG=22)
      parameter(DB_NOTYPE=25)
      parameter(DB_CLOBBER=0)
      parameter(DB_NOCLOBBER=1)
      parameter(DB_READ=1)
      parameter(DB_APPEND=2)
      parameter(DB_LOCAL=0)
      parameter(DB_SUN3=10)
      parameter(DB_SUN4=11)
      parameter(DB_SGI=12)
      parameter(DB_RS6000=13)
      parameter(DB_CRAY=14)
      parameter(DB_INTEL=15)
      parameter(DBOPT_FIRST=260)
      parameter(DBOPT_ALIGN=260)
      parameter(DBOPT_COORDSYS=262)
      parameter(DBOPT_CYCLE=263)
      parameter(DBOPT_FACETYPE=264)
      parameter(DBOPT_HI_OFFSET=265)
      parameter(DBOPT_LO_OFFSET=266)
      parameter(DBOPT_LABEL=267)
      parameter(DBOPT_XLABEL=268)
      parameter(DBOPT_YLABEL=269)
      parameter(DBOPT_ZLABEL=270)
      parameter(DBOPT_MAJORORDER=271)
      parameter(DBOPT_NSPACE=272)
      parameter(DBOPT_ORIGIN=273)
      parameter(DBOPT_PLANAR=274)
      parameter(DBOPT_TIME=275)
      parameter(DBOPT_UNITS=276)
      parameter(DBOPT_XUNITS=277)
      parameter(DBOPT_YUNITS=278)
      parameter(DBOPT_ZUNITS=279)
      parameter(DBOPT_DTIME=280)
      parameter(DBOPT_USESPECMF=281)
      parameter(DBOPT_XVARNAME=282)
      parameter(DBOPT_YVARNAME=283)
      parameter(DBOPT_ZVARNAME=284)
      parameter(DBOPT_ASCII_LABEL=285)
      parameter(DBOPT_MATNOS=286)
      parameter(DBOPT_NMATNOS=287)
      parameter(DBOPT_MATNAME=288)
      parameter(DBOPT_NMAT=289)
      parameter(DBOPT_NMATSPEC=290)
      parameter(DBOPT_BASEINDEX=291)
      parameter(DBOPT_ZONENUM=292)
      parameter(DBOPT_NODENUM=293)
      parameter(DBOPT_BLOCKORIGIN=294)
      parameter(DBOPT_GROUPNUM=295)
      parameter(DBOPT_GROUPORIGIN=296)
      parameter(DBOPT_NGROUPS=297)
      parameter(DBOPT_MATNAMES=298)
      parameter(DBOPT_EXTENTS_SIZE=299)
      parameter(DBOPT_EXTENTS=300)
      parameter(DBOPT_MATCOUNTS=301)
      parameter(DBOPT_MATLISTS=302)
      parameter(DBOPT_MIXLENS=303)
      parameter(DBOPT_ZONECOUNTS=304)
      parameter(DBOPT_HAS_EXTERNAL_ZONES=305)
      parameter(DBOPT_PHZONELIST=306)
      parameter(DBOPT_MATCOLORS=307)
      parameter(DBOPT_BNDNAMES=308)
      parameter(DBOPT_REGNAMES=309)
      parameter(DBOPT_ZONENAMES=310)
      parameter(DBOPT_HIDE_FROM_GUI=311)
      parameter(DBOPT_TOPO_DIM=312)
      parameter(DBOPT_REFERENCE=313)
      parameter(DBOPT_GROUPINGS_SIZE=314)
      parameter(DBOPT_GROUPINGS=315)
      parameter(DBOPT_GROUPINGNAMES=316)
      parameter(DBOPT_ALLOWMAT0=317)
      parameter(DBOPT_MRGTREE_NAME=318)
      parameter(DBOPT_REGION_PNAMES=319)
      parameter(DBOPT_TENSOR_RANK=320)
      parameter(DBOPT_MMESH_NAME=321)
      parameter(DBOPT_TV_CONNECTIVITY=322)
      parameter(DBOPT_DISJOINT_MODE=323)
      parameter(DBOPT_MRGV_ONAMES=324)
      parameter(DBOPT_MRGV_RNAMES=325)
      parameter(DBOPT_SPECNAMES=326)
      parameter(DBOPT_SPECCOLORS=327)
      parameter(DBOPT_LLONGNZNUM=328)
      parameter(DBOPT_CONSERVED=329)
      parameter(DBOPT_EXTENSIVE=330)
      parameter(DBOPT_MB_FILE_NS=331)
      parameter(DBOPT_MB_BLOCK_NS=332)
      parameter(DBOPT_MB_BLOCK_TYPE=333)
      parameter(DBOPT_MB_EMPTY_LIST=334)
      parameter(DBOPT_MB_EMPTY_COUNT=335)
      parameter(DBOPT_LAST=499)
      parameter(DBOPT_H5_FIRST=500)
      parameter(DBOPT_H5_VFD=500)
      parameter(DBOPT_H5_RAW_FILE_OPTS=501)
      parameter(DBOPT_H5_RAW_EXTENSION=502)
      parameter(DBOPT_H5_META_FILE_OPTS=503)
      parameter(DBOPT_H5_META_EXTENSION=504)
      parameter(DBOPT_H5_CORE_ALLOC_INC=505)
      parameter(DBOPT_H5_CORE_NO_BACK_STORE=506)
      parameter(DBOPT_H5_META_BLOCK_SIZE=507)
      parameter(DBOPT_H5_SMALL_RAW_SIZE=508)
      parameter(DBOPT_H5_ALIGN_MIN=509)
      parameter(DBOPT_H5_ALIGN_VAL=510)
      parameter(DBOPT_H5_DIRECT_MEM_ALIGN=511)
      parameter(DBOPT_H5_DIRECT_BLOCK_SIZE=512)
      parameter(DBOPT_H5_DIRECT_BUF_SIZE=513)
      parameter(DBOPT_H5_LOG_NAME=514)
      parameter(DBOPT_H5_LOG_BUF_SIZE=515)
      parameter(DBOPT_H5_MPIO_COMM=516)
      parameter(DBOPT_H5_MPIO_INFO=517)
      parameter(DBOPT_H5_MPIP_NO_GPFS_HINTS=518)
      parameter(DBOPT_H5_SIEVE_BUF_SIZE=519)
      parameter(DBOPT_H5_CACHE_NELMTS=520)
      parameter(DBOPT_H5_CACHE_NBYTES=521)
      parameter(DBOPT_H5_CACHE_POLICY=522)
      parameter(DBOPT_H5_FAM_SIZE=523)
      parameter(DBOPT_H5_FAM_FILE_OPTS=524)
      parameter(DBOPT_H5_USER_DRIVER_ID=525)
      parameter(DBOPT_H5_USER_DRIVER_INFO=526)
      parameter(DBOPT_H5_SILO_BLOCK_SIZE=527)
      parameter(DBOPT_H5_SILO_BLOCK_COUNT=528)
      parameter(DBOPT_H5_SILO_LOG_STATS=529)
      parameter(DBOPT_H5_SILO_USE_DIRECT=530)
      parameter(DBOPT_H5_LAST=599)
      parameter(DB_TOP=0)
      parameter(DB_NONE=1)
      parameter(DB_ALL=2)
      parameter(DB_ABORT=3)
      parameter(DB_SUSPEND=4)
      parameter(DB_RESUME=5)
      parameter(DB_ALL_AND_DRVR=6)
      parameter(DB_ROWMAJOR=0)
      parameter(DB_COLMAJOR=1)
      parameter(DB_NOTCENT=0)
      parameter(DB_NODECENT=110)
      parameter(DB_ZONECENT=111)
      parameter(DB_FACECENT=112)
      parameter(DB_BNDCENT=113)
      parameter(DB_EDGECENT=114)
      parameter(DB_BLOCKCENT=115)
      parameter(DB_CARTESIAN=120)
      parameter(DB_CYLINDRICAL=121)
      parameter(DB_SPHERICAL=122)
      parameter(DB_NUMERICAL=123)
      parameter(DB_OTHER=124)
      parameter(DB_RECTILINEAR=100)
      parameter(DB_CURVILINEAR=101)
      parameter(DB_AREA=140)
      parameter(DB_VOLUME=141)
      parameter(DB_ON=1000)
      parameter(DB_OFF=-1000)
      parameter(DB_ABUTTING=142)
      parameter(DB_FLOATING=143)
      parameter(DB_VARTYPE_SCALAR=200)
      parameter(DB_VARTYPE_VECTOR=201)
      parameter(DB_VARTYPE_TENSOR=202)
      parameter(DB_VARTYPE_SYMTENSOR=203)
      parameter(DB_VARTYPE_ARRAY=204)
      parameter(DB_VARTYPE_MATERIAL=205)
      parameter(DB_VARTYPE_SPECIES=206)
      parameter(DB_VARTYPE_LABEL=207)
      parameter(DBCSG_QUADRIC_G=16777216)
      parameter(DBCSG_SPHERE_PR=33619968)
      parameter(DBCSG_ELLIPSOID_PRRR=33685504)
      parameter(DBCSG_PLANE_G=50331648)
      parameter(DBCSG_PLANE_X=50397184)
      parameter(DBCSG_PLANE_Y=50462720)
      parameter(DBCSG_PLANE_Z=50528256)
      parameter(DBCSG_PLANE_PN=50593792)
      parameter(DBCSG_PLANE_PPP=50659328)
      parameter(DBCSG_CYLINDER_PNLR=67108864)
      parameter(DBCSG_CYLINDER_PPR=67174400)
      parameter(DBCSG_BOX_XYZXYZ=83886080)
      parameter(DBCSG_CONE_PNLA=100663296)
      parameter(DBCSG_CONE_PPA=100728832)
      parameter(DBCSG_POLYHEDRON_KF=117440512)
      parameter(DBCSG_HEX_6F=117506048)
      parameter(DBCSG_TET_4F=117571584)
      parameter(DBCSG_PYRAMID_5F=117637120)
      parameter(DBCSG_PRISM_5F=117702656)
      parameter(DBCSG_QUADRATIC_G=134217728)
      parameter(DBCSG_CIRCLE_PR=150994944)
      parameter(DBCSG_ELLIPSE_PRR=151060480)
      parameter(DBCSG_LINE_G=167772160)
      parameter(DBCSG_LINE_X=167837696)
      parameter(DBCSG_LINE_Y=167903232)
      parameter(DBCSG_LINE_PN=167968768)
      parameter(DBCSG_LINE_PP=168034304)
      parameter(DBCSG_BOX_XYXY=184549376)
      parameter(DBCSG_ANGLE_PNLA=201326592)
      parameter(DBCSG_ANGLE_PPA=201392128)
      parameter(DBCSG_POLYGON_KP=218103808)
      parameter(DBCSG_TRI_3P=218169344)
      parameter(DBCSG_QUAD_4P=218234880)
      parameter(DBCSG_INNER=2130706432)
      parameter(DBCSG_OUTER=2130771968)
      parameter(DBCSG_ON=2130837504)
      parameter(DBCSG_UNION=2130903040)
      parameter(DBCSG_INTERSECT=2130968576)
      parameter(DBCSG_DIFF=2131034112)
      parameter(DBCSG_COMPLIMENT=2131099648)
      parameter(DBCSG_XFORM=2131165184)
      parameter(DBCSG_SWEEP=2131230720)
      parameter(DB_PREORDER=1)
      parameter(DB_POSTORDER=2)
      parameter(DB_FROMCWR=4)
      parameter(DB_F77NULL=(-99))
      parameter(DB_ZONETYPE_BEAM=10)
      parameter(DB_ZONETYPE_POLYGON=20)
      parameter(DB_ZONETYPE_TRIANGLE=23)
      parameter(DB_ZONETYPE_QUAD=24)
      parameter(DB_ZONETYPE_POLYHEDRON=30)
      parameter(DB_ZONETYPE_TET=34)
      parameter(DB_ZONETYPE_PYRAMID=35)
      parameter(DB_ZONETYPE_PRISM=36)
      parameter(DB_ZONETYPE_HEX=38)
      parameter(DB_F77NULLSTRING="NULLSTRING")


! End.