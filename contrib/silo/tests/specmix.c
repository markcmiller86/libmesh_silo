/*
Copyright (c) 1994 - 2010, Lawrence Livermore National Security, LLC.
LLNL-CODE-425250.
All rights reserved.

This file is part of Silo. For details, see silo.llnl.gov.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the disclaimer below.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the disclaimer (as noted
     below) in the documentation and/or other materials provided with
     the distribution.
   * Neither the name of the LLNS/LLNL nor the names of its
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

THIS SOFTWARE  IS PROVIDED BY  THE COPYRIGHT HOLDERS  AND CONTRIBUTORS
"AS  IS" AND  ANY EXPRESS  OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT
LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A  PARTICULAR  PURPOSE ARE  DISCLAIMED.  IN  NO  EVENT SHALL  LAWRENCE
LIVERMORE  NATIONAL SECURITY, LLC,  THE U.S.  DEPARTMENT OF  ENERGY OR
CONTRIBUTORS BE LIABLE FOR  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR  CONSEQUENTIAL DAMAGES  (INCLUDING, BUT NOT  LIMITED TO,
PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS  OF USE,  DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER  IN CONTRACT, STRICT LIABILITY,  OR TORT (INCLUDING
NEGLIGENCE OR  OTHERWISE) ARISING IN  ANY WAY OUT  OF THE USE  OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This work was produced at Lawrence Livermore National Laboratory under
Contract  No.   DE-AC52-07NA27344 with  the  DOE.  Neither the  United
States Government  nor Lawrence  Livermore National Security,  LLC nor
any of  their employees,  makes any warranty,  express or  implied, or
assumes   any   liability   or   responsibility  for   the   accuracy,
completeness, or usefulness of any information, apparatus, product, or
process  disclosed, or  represents  that its  use  would not  infringe
privately-owned   rights.  Any  reference   herein  to   any  specific
commercial products,  process, or  services by trade  name, trademark,
manufacturer or otherwise does not necessarily constitute or imply its
endorsement,  recommendation,   or  favoring  by   the  United  States
Government or Lawrence Livermore National Security, LLC. The views and
opinions  of authors  expressed  herein do  not  necessarily state  or
reflect those  of the United  States Government or  Lawrence Livermore
National  Security, LLC,  and shall  not  be used  for advertising  or
product endorsement purposes.
*/
/*------------------------------------------------------------------------
 * specmix.c -- Species over mixed-material zones.
 *
 * Programmer:  Jeremy Meredith, Feb 17, 1999
 *
 *  This test case creates identical structured and unstructured problems.
 *  Each has several materials, including mixed zones, and material-species
 *  information distributed over these materials (note the mixed zones).
 *
 * Modifications:
 *
 *  Mark C. Miller, Thu Feb 11 09:56:05 PST 2010
 *  Added test for vars with 8 subcomponents.
 *   Mark C. Miller, Mon Feb  1 17:08:45 PST 2010
 *   Added stuff to output all silo data types.
 *-----------------------------------------------------------------------*/
#include <math.h>
#include <silo.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <std.c>

#define MAXVAR  4
#define MAXMAT  5
#define MAXSPEC 5

#define NEW(t,n)   (t*)calloc(n,sizeof(t))
#ifndef min
#define min(a,b)   ((a)<(b) ? (a) : (b))
#endif
#ifndef max
#define max(a,b)   ((a)>(b) ? (a) : (b))
#endif
#define lim(a,l,h) (max(min((a),(h)),(l)))
#define lim01(a)   (lim((a),0,1))

/* Structures for a 2-d problem domain: */

/* Struct: Node */
typedef struct {
  int   c;
  int   i,j;
  float x,y;
  float vars[MAXVAR];
} Node;

/* Struct: Zone */
typedef struct {
  float vars[MAXVAR];
  int   nmats;
  int   mats[MAXMAT+1];
  float matvf[MAXMAT+1];
  float specmf[MAXMAT+1][MAXSPEC];
  Node *n[2][2];  /* the four nodes at the corners of this zone*/
} Zone;

/* Struct: Mesh */
typedef struct {
  int nx;
  int ny;
  int zx;
  int zy;
  Node **node;
  Zone **zone;
} Mesh;
void Mesh_Create(Mesh*,int,int); /* constructor */

/* file-writing functions */
void writemesh_curv2d(DBfile*,int,int);
void writemesh_ucd2d(DBfile*,int,int);
int writematspec(DBfile*);

/* problem specifics */
enum ZVARS { ZV_P, ZV_D };
enum NVARS { NV_U, NV_V };
int nmat = 4;
int nspec[]={2,4,5,1};
int matnos[]={1,2,3,4};
char *matnames[]={"Top", "Lower right", "Bottom", "Left"};
char *specnames[]={"Brad","Kathleen","Mark","Hank","Eric",
                   "Jeremy","Cyrus","Sean","Dave","Randy",
                   "Gunther","Tom"};
char *speccolors[]={"Red","Green","Blue","Cyan","Magenta",
                   "Yellow","Black","Orange","Brown","Purple",
                   "White","Pink"};

Mesh mesh;

/*----------------------------------------------------------------------------
 * Constructor: Mesh_Create()
 *
 * Inputs:   mesh   (Mesh*): The mesh to construct
 *           zx_, zy_ (int): The x & y size of the mesh in zones
 *
 * Abstract: initialize and allocate space for the problem mesh
 *
 * Modifications:
 *---------------------------------------------------------------------------*/
void Mesh_Create(Mesh *mesh,int zx_,int zy_) {
  int x,y;
  int c;
  mesh->nx=zx_+1;
  mesh->ny=zy_+1;
  mesh->zx=zx_;
  mesh->zy=zy_;
  
  c=0;
  mesh->node=NEW(Node*,mesh->nx);
  for (x=0;x<mesh->nx;x++) {
    mesh->node[x]=NEW(Node,mesh->ny);
    for (y=0;y<mesh->ny;y++) {
      mesh->node[x][y].c=c++;
      mesh->node[x][y].i=x;
      mesh->node[x][y].j=y;
    }
  }
  
  mesh->zone=NEW(Zone*,mesh->zx);
  for (x=0;x<mesh->zx;x++) {
    mesh->zone[x]=NEW(Zone,mesh->zy);
    for (y=0;y<mesh->zy;y++) {
      mesh->zone[x][y].n[0][0]=&mesh->node[x][y];
      mesh->zone[x][y].n[1][0]=&mesh->node[x+1][y];
      mesh->zone[x][y].n[0][1]=&mesh->node[x][y+1];
      mesh->zone[x][y].n[1][1]=&mesh->node[x+1][y+1];
    }
  }
}


/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------
 *                              Main Program
 *----------------------------------------------------------------------------
 *----------------------------------------------------------------------------
 * Modifications:
 * 	Robb Matzke, 1999-04-09
 *	Added argument parsing to control the driver which is used.
 *
 *---------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
  int x,y;
  int m,s;
  int err, mixc;
  int i, driver=DB_PDB, reorder=0;
  char filename[64], *file_ext=".pdb";
  int show_all_errors = FALSE;
  DBfile *db;

  /* Parse command-line */
  for (i=1; i<argc; i++) {
      if (!strncmp(argv[i], "DB_PDB", 6)) {
	  driver = StringToDriver(argv[i]);
	  file_ext = ".pdb";
      } else if (!strncmp(argv[i], "DB_HDF5", 7)) {
          driver = StringToDriver(argv[i]);
	  file_ext = ".h5";
      } else if (!strcmp(argv[i], "reorder")) {
	  reorder = 1;
      } else if (!strcmp(argv[i], "show-all-errors")) {
          show_all_errors = 1;
      } else if (argv[i][0] != '\0') {
	  fprintf(stderr, "%s: ignored argument `%s'\n", argv[0], argv[i]);
      }
  }
    
  if (show_all_errors) DBShowErrors(DB_ALL_AND_DRVR, 0);

  Mesh_Create(&mesh,20,20);
  
  /* -=-=-=-=-=-=-=-=-=- */
  /*  Setup Coordinates  */
  /* -=-=-=-=-=-=-=-=-=- */
  printf("Creating the mesh\n");

  for (x=0;x<mesh.nx;x++) {
    for (y=0;y<mesh.ny;y++) {
      float xx = (x-10);
      float yy = ((xx-8.5)*xx*(xx+8.5))/40. + (y-10);
      mesh.node[x][y].x = xx*2+(yy*yy/50 - 3);
      mesh.node[x][y].y = yy;
    }
  }


  /* -=-=-=-=-=-=-=-=-=- */
  /*  Do Mesh Variables  */
  /* -=-=-=-=-=-=-=-=-=- */
  printf("Creating the variables\n");

  /* do zone vars */
  for (x=0;x<mesh.zx;x++) {
    for (y=0;y<mesh.zy;y++) {
      mesh.zone[x][y].vars[ZV_P] = sqrt((mesh.node[x][y].x*mesh.node[x][y].x) +
                                        (mesh.node[x][y].y*mesh.node[x][y].y));
      mesh.zone[x][y].vars[ZV_D] = 10. / (mesh.zone[x][y].vars[ZV_P]+5);
    }
  }

  /* do node vars */
  for (x=0;x<mesh.nx;x++) {
    for (y=0;y<mesh.ny;y++) {
      mesh.node[x][y].vars[NV_U] = mesh.node[x][y].x;
      mesh.node[x][y].vars[NV_V] = mesh.node[x][y].y;
    }
  }


  /* -=-=-=-=-=-=-=-=-=- */
  /*    Do Materials     */
  /* -=-=-=-=-=-=-=-=-=- */
  printf("Overlaying materials\n");


  /* initialize */
  for (x=0;x<mesh.zx;x++) {
    for (y=0;y<mesh.zy;y++) {
      mesh.zone[x][y].nmats=0;
    }
  }
	  
  /* do it */
  for (m=1; m<=nmat; m++) {
    for (x=0;x<mesh.zx;x++) {
      for (y=0;y<mesh.zy;y++) {
	float x00=mesh.zone[x][y].n[0][0]->x;
	float y00=mesh.zone[x][y].n[0][0]->y;
	float x10=mesh.zone[x][y].n[1][0]->x;
	float y10=mesh.zone[x][y].n[1][0]->y;
	float x01=mesh.zone[x][y].n[0][1]->x;
	float y01=mesh.zone[x][y].n[0][1]->y;
	float x11=mesh.zone[x][y].n[1][1]->x;
	float y11=mesh.zone[x][y].n[1][1]->y;

	int   i,j;
	int   c=0;
	float vf=0.;
	const int RES=40; /* subsampling resolution */

	/* Subsample the zone at RESxRES to    *
	 * get a more accurate volume fraction */
	for (i=0;i<=RES;i++) {
	  for (j=0;j<=RES;j++) {
	    float ii=(float)i/(float)RES;
	    float jj=(float)j/(float)RES;
	    float xc = (x00*ii + x10*(1.-ii))*jj + 
	               (x01*ii + x11*(1.-ii))*(1.-jj);
	    float yc = (y00*ii + y10*(1.-ii))*jj + 
                       (y01*ii + y11*(1.-ii))*(1.-jj);

	    switch (m) {
	    case 1:
	      if (xc>-15 && yc>2) vf++;
	      break;
	    case 2:
	      if (xc>-15 && yc<=2 && xc-5>yc) vf++;
	      break;
	    case 3:
	      if (xc>-15 && yc<=2 && xc-5<=yc) vf++;
	      break;
	    case 4:
	      if (xc<= -15) vf++;
	      break;
	    default:
	      break;
	    }

	    c++;
	  }
	}

	vf /= (float)c;

	mesh.zone[x][y].matvf[m]=vf;
	if (vf)
	  mesh.zone[x][y].nmats++;
      }
    }
  }
  
  /* check for errors in mat-assigning code! */
  err=0;
  for (x=0;x<mesh.zx;x++) {
    for (y=0;y<mesh.zy;y++) {
      float vf=0;
      for (m=1; m<=nmat; m++) {
	vf += mesh.zone[x][y].matvf[m];
      }
      if (vf<.99 || vf>1.01) {
	printf("Error in zone x=%d y=%d: vf = %f\n",x,y,vf);
	err++;
      }
    }
  }
  if (err) exit(err);


  /* -=-=-=-=-=-=-=-=-=- */
  /*  do species stuff!  */
  /* -=-=-=-=-=-=-=-=-=- */
  printf("Overlaying material species\n");


  err=0;
  for (m=1;m<=nmat;m++) {
    for (x=0;x<mesh.zx;x++) {
      for (y=0;y<mesh.zy;y++) {
	if (mesh.zone[x][y].matvf[m]>0.) {
	  float mftot=0.;
	  for (s=0; s<nspec[m-1]; s++) {
	    float x00=mesh.zone[x][y].n[0][0]->x;
	    float y00=mesh.zone[x][y].n[0][0]->y;
	    float x10=mesh.zone[x][y].n[1][0]->x;
	    float y10=mesh.zone[x][y].n[1][0]->y;
	    float x01=mesh.zone[x][y].n[0][1]->x;
	    float y01=mesh.zone[x][y].n[0][1]->y;
	    float x11=mesh.zone[x][y].n[1][1]->x;
	    float y11=mesh.zone[x][y].n[1][1]->y;
	    float xx=(x00+x10+x01+x11)/4.;
	    float yy=(y00+y10+y01+y11)/4.;
	    
	    float mf=0;
	    float g,g1,g2; /* gradient values */
	    switch (m) {
	    case 1:
	      g=lim01((xx+20.)/40.);
	      switch (s) {
	      case 0: mf=g;	      break;
	      case 1: mf=1.-g;	      break;
	      default: exit(-1);
	      }
	      break;
	    case 2:
	      g=lim01((yy+20.)/40.);
	      switch (s) {
	      case 0: mf=.2+g/2.;     break;
	      case 1: mf=.5-g/2.;     break;
	      case 2: mf=.2;	      break;
	      case 3: mf=.1;	      break;
	      default: exit(-1);
	      }
	      break;
	    case 3:
	      g1=lim01((xx-5+yy+40.)/80.);
	      g2=lim01((xx-5-yy+40.)/80.);
	      switch (s) {
	      case 0: mf=g1/2.;	      break;
	      case 1: mf=g2/4.;	      break;
	      case 2: mf=.5-g1/2.;    break;
	      case 3: mf=.25-g2/4.;   break;
	      case 4: mf=.25;	      break;
	      default: exit(-1);
	      }
	      break;
	    case 4:
	      switch (s) {
	      case 0: mf=1.0;	      break;
	      default: exit(-1);
	      }
	      break;
	    default:
		exit(-1);
	      break;
	    }
	    
	    mesh.zone[x][y].specmf[m][s] = mf;
	    mftot += mf;
	  }
	  if (mftot < .99 || mftot > 1.01) {
	    printf("Error in zone x=%d y=%d mat=%d: mf = %f\n",x,y,m,mftot);
	    err++;
	  }
	}
      }
    }
  }
  if (err) exit(err);


  /* -=-=-=-=-=-=-=-=-=- */
  /* write to silo files */
  /* -=-=-=-=-=-=-=-=-=- */

  sprintf(filename, "specmix_quad%s", file_ext);
  printf("Writing %s using curvilinear mesh.\n", filename);
  db=DBCreate(filename, DB_CLOBBER, DB_LOCAL, "Mixed zone species test", driver);
  mixc=writematspec(db);
  writemesh_curv2d(db,mixc,reorder);
  DBClose(db);

  sprintf(filename, "specmix_ucd%s", file_ext);
  printf("Writing %s using unstructured mesh.\n", filename);
  db=DBCreate(filename, DB_CLOBBER, DB_LOCAL, "Mixed zone species test", driver);
  mixc=writematspec(db);
  writemesh_ucd2d(db,mixc,reorder);
  DBClose(db);

  printf("Done!\n");

  for (x=0;x<mesh.nx;x++)
      free(mesh.node[x]);
  free(mesh.node);

  for (x=0;x<mesh.zx;x++)
    free(mesh.zone[x]);
  free(mesh.zone);

  CleanupDriverStuff();
  return 0;
}

/*----------------------------------------------------------------------------
 * Function: writemesh_curv2d()
 *
 * Inputs:   db (DBfile*): the Silo file handle
 *
 * Returns:  (void)
 *
 * Abstract: Write the mesh and variables stored in the global Mesh 
 *           to the Silo file as a quadmesh and quadvars
 *
 * Modifications:
 *---------------------------------------------------------------------------*/
void writemesh_curv2d(DBfile *db, int mixc, int reorder) {

  float f1[1000],f2[1000], fm[1000];
  int x,y,c;

  char  *coordnames[2];
  char  *varnames[6];
  void *varbufs[6];
  float *coord[2];
  int dims[2];

  char *cnvar, *czvar;
  short *snvar, *szvar;
  int *invar, *izvar;
  long *lnvar, *lzvar;
  long long *Lnvar, *Lzvar;
  float *fnvar, *fzvar;
  double *dnvar, *dzvar;

  int nnodes=mesh.nx*mesh.ny;
  int nzones=mesh.zx*mesh.zy;
  
  /* do mesh */
  c=0;
  for (x=0;x<mesh.nx;x++) {
    for (y=0;y<mesh.ny;y++) {
      f1[c]=mesh.node[x][y].x;
      f2[c]=mesh.node[x][y].y;
      c++;
    }
  }

  coordnames[0]=NEW(char,20);
  coordnames[1]=NEW(char,20);
  strcpy(coordnames[0],"x");
  strcpy(coordnames[1],"y");

  coord[0]=f1;
  coord[1]=f2;

  dims[0]=mesh.nx;
  dims[1]=mesh.ny;

  DBPutQuadmesh(db, "Mesh", coordnames, coord, dims, 2, 
		DB_FLOAT, DB_NONCOLLINEAR, NULL);
  free(coordnames[0]);
  free(coordnames[1]);

  /* do Node vars */

  cnvar = (char *)        malloc(sizeof(char)*nnodes); 
  snvar = (short *)       malloc(sizeof(short)*nnodes); 
  invar = (int *)         malloc(sizeof(int)*nnodes); 
  lnvar = (long *)        malloc(sizeof(long)*nnodes); 
  Lnvar = (long long *)   malloc(sizeof(long long)*nnodes); 
  fnvar = (float *)       malloc(sizeof(float)*nnodes); 
  dnvar = (double *)      malloc(sizeof(double)*nnodes); 
  c=0;
  for (x=0;x<mesh.nx;x++) {
    for (y=0;y<mesh.ny;y++) {
      f1[c]=mesh.node[x][y].vars[NV_U];
      f2[c]=mesh.node[x][y].vars[NV_V];
      cnvar[c] = (char)        (x<y?x:y);
      snvar[c] = (short)       (x<y?x:y);
      invar[c] = (int)         (x<y?x:y);
      lnvar[c] = (long)        (x<y?x:y);
      Lnvar[c] = (long long)   (x<y?x:y);
      fnvar[c] = (float)       (x<y?x:y);
      dnvar[c] = (double)      (x<y?x:y);
      c++;
    }
  }

  DBPutQuadvar1(db, "u", "Mesh", f1, dims, 2, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "v", "Mesh", f2, dims, 2, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "cnvar", "Mesh", cnvar, dims, 2, NULL, 0, DB_CHAR, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "snvar", "Mesh", snvar, dims, 2, NULL, 0, DB_SHORT, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "invar", "Mesh", invar, dims, 2, NULL, 0, DB_INT, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "lnvar", "Mesh", lnvar, dims, 2, NULL, 0, DB_LONG, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "Lnvar", "Mesh", Lnvar, dims, 2, NULL, 0, DB_LONG_LONG, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "fnvar", "Mesh", fnvar, dims, 2, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
  DBPutQuadvar1(db, "dnvar", "Mesh", dnvar, dims, 2, NULL, 0, DB_DOUBLE, DB_NODECENT, NULL);
  free(cnvar);
  free(snvar);
  free(invar);
  free(lnvar);
  free(Lnvar);
  free(fnvar);
  free(dnvar);

  /* test writing a quadvar with many components */
  varnames[0] = "u0";
  varnames[1] = "v0";
  varnames[2] = "u1";
  varnames[3] = "v1";
  varnames[4] = "u2";
  varnames[5] = "v2";
  varbufs[0] = f1;
  varbufs[1] = f2;
  varbufs[2] = f1;
  varbufs[3] = f2;
  varbufs[4] = f1;
  varbufs[5] = f2;
  DBPutQuadvar(db, "manyc", "Mesh", 6, varnames, varbufs, dims, 2, NULL, 0,
    DB_FLOAT, DB_NODECENT, NULL);

  /* do Zone vars */

  dims[0]--;
  dims[1]--;

  czvar = (char *)        malloc(sizeof(char)*nzones); 
  szvar = (short *)       malloc(sizeof(short)*nzones); 
  izvar = (int *)         malloc(sizeof(int)*nzones); 
  lzvar = (long *)        malloc(sizeof(long)*nzones); 
  Lzvar = (long long *)   malloc(sizeof(long long)*nzones); 
  fzvar = (float *)       malloc(sizeof(float)*nzones); 
  dzvar = (double *)      malloc(sizeof(double)*nzones); 
  c=0;
  for (x=0;x<mesh.zx;x++) {
    for (y=0;y<mesh.zy;y++) {
      f1[c]=mesh.zone[x][y].vars[ZV_P];
      f2[c]=mesh.zone[x][y].vars[ZV_D];
      czvar[c] = (char)        (x<y?x:y);
      szvar[c] = (short)       (x<y?x:y);
      izvar[c] = (int)         (x<y?x:y);
      lzvar[c] = (long)        (x<y?x:y);
      Lzvar[c] = (long long)   (x<y?x:y);
      fzvar[c] = (float)       (x<y?x:y);
      dzvar[c] = (double)      (x<y?x:y);
      c++;
    }
  }

  for (c=0; c<mixc; c++)
      fm[c] = 2.0/mixc*c;
  if (reorder)
  {
    float tmp=fm[mixc-1];
    fm[mixc-1]=fm[mixc-2];
    fm[mixc-2]=tmp;
  }

  DBPutQuadvar1(db, "p", "Mesh", f1, dims, 2, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "d", "Mesh", f2, dims, 2, fm, mixc, DB_FLOAT, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "czvar", "Mesh", czvar, dims, 2, NULL, 0, DB_CHAR, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "szvar", "Mesh", szvar, dims, 2, NULL, 0, DB_SHORT, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "izvar", "Mesh", izvar, dims, 2, NULL, 0, DB_INT, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "lzvar", "Mesh", lzvar, dims, 2, NULL, 0, DB_LONG, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "Lzvar", "Mesh", Lzvar, dims, 2, NULL, 0, DB_LONG_LONG, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "fzvar", "Mesh", fzvar, dims, 2, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL);
  DBPutQuadvar1(db, "dzvar", "Mesh", dzvar, dims, 2, NULL, 0, DB_DOUBLE, DB_ZONECENT, NULL);
  free(czvar);
  free(szvar);
  free(izvar);
  free(lzvar);
  free(Lzvar);
  free(fzvar);
  free(dzvar);
}

/*----------------------------------------------------------------------------
 * Function: writemesh_ucd2d()
 *
 * Inputs:   db (DBfile*): the Silo file handle
 *
 * Returns:  (void)
 *
 * Abstract: Write the mesh and variables stored in the global Mesh 
 *           to the Silo file as a UCDmesh and UCDvars
 *
 * Modifications:
 *---------------------------------------------------------------------------*/
void writemesh_ucd2d(DBfile *db, int mixc, int reorder) {

  int   nl[5000];
  float f1[1000],f2[1000], fm[1000];
  int x,y,c;
  float *coord[2];
  int dims[2];
  char *cnvar, *czvar;
  short *snvar, *szvar;
  int *invar, *izvar;
  long *lnvar, *lzvar;
  long long *Lnvar, *Lzvar;
  float *fnvar, *fzvar;
  double *dnvar, *dzvar;

  int lnodelist;
  int nnodes;
  int nzones;
  int shapesize[1];
  int shapecnt[1];

  /* do mesh */
  c=0;
  for (x=0;x<mesh.nx;x++) {
    for (y=0;y<mesh.ny;y++) {
      f1[c]=mesh.node[x][y].x;
      f2[c]=mesh.node[x][y].y;
      if (mesh.node[x][y].c != c) {
	printf("Node mismatch! mesh.c=%d c=%d\n",mesh.node[x][y].c,c);
	exit(-1);
      }
      c++;
    }
  }

  coord[0]=f1;
  coord[1]=f2;

  dims[0]=mesh.nx;
  dims[1]=mesh.ny;

  /* create the zonelist */
  c=0;
  for (x=0;x<mesh.zx;x++) {
    for (y=0;y<mesh.zy;y++) {
      nl[c++] = mesh.zone[x][y].n[0][0]->c;
      nl[c++] = mesh.zone[x][y].n[1][0]->c;
      nl[c++] = mesh.zone[x][y].n[1][1]->c;
      nl[c++] = mesh.zone[x][y].n[0][1]->c;
    }
  }
  lnodelist=c;

  nnodes=mesh.nx*mesh.ny;
  nzones=mesh.zx*mesh.zy;
  shapesize[0]=4;
  shapecnt[0]=nzones;

  DBSetDeprecateWarnings(0);
  DBPutZonelist(db,"Mesh_zonelist",nzones,2,nl,lnodelist,0,shapesize,shapecnt,1);
  DBSetDeprecateWarnings(3);
  DBPutUcdmesh (db,"Mesh",2,NULL,coord,nnodes,nzones,"Mesh_zonelist",NULL,DB_FLOAT,NULL);

  /* do Node vars */

  cnvar = (char *)        malloc(sizeof(char)*nnodes); 
  snvar = (short *)       malloc(sizeof(short)*nnodes); 
  invar = (int *)         malloc(sizeof(int)*nnodes); 
  lnvar = (long *)        malloc(sizeof(long)*nnodes); 
  Lnvar = (long long *)   malloc(sizeof(long long)*nnodes); 
  fnvar = (float *)       malloc(sizeof(float)*nnodes); 
  dnvar = (double *)      malloc(sizeof(double)*nnodes); 
  c=0;
  for (x=0;x<mesh.nx;x++) {
    for (y=0;y<mesh.ny;y++) {
      f1[c]=mesh.node[x][y].vars[NV_U];
      f2[c]=mesh.node[x][y].vars[NV_V];
      cnvar[c] = (char)        (x<y?x:y);
      snvar[c] = (short)       (x<y?x:y);
      invar[c] = (int)         (x<y?x:y);
      lnvar[c] = (long)        (x<y?x:y);
      Lnvar[c] = (long long)   (x<y?x:y);
      fnvar[c] = (float)       (x<y?x:y);
      dnvar[c] = (double)      (x<y?x:y);
      c++;
    }
  }

  
  {
    DBoptlist *opt = DBMakeOptlist(1);
    int val = DB_ON;

    DBAddOption(opt,DBOPT_USESPECMF,&val);
    DBPutUcdvar1(db, "u", "Mesh", f1, nnodes, NULL, 0, DB_FLOAT,
        DB_NODECENT, opt);
    DBPutUcdvar1(db, "v", "Mesh", f2, nnodes, NULL, 0, DB_FLOAT,
        DB_NODECENT, opt);
    DBPutUcdvar1(db, "u", "Mesh", f1, nnodes, NULL, 0, DB_FLOAT, DB_NODECENT, opt);
    DBPutUcdvar1(db, "v", "Mesh", f2, nnodes, NULL, 0, DB_FLOAT, DB_NODECENT, opt);
    DBPutUcdvar1(db, "cnvar", "Mesh", cnvar, nnodes, NULL, 0, DB_CHAR, DB_NODECENT, opt);
    DBPutUcdvar1(db, "snvar", "Mesh", snvar, nnodes, NULL, 0, DB_SHORT, DB_NODECENT, opt);
    DBPutUcdvar1(db, "invar", "Mesh", invar, nnodes, NULL, 0, DB_INT, DB_NODECENT, opt);
    DBPutUcdvar1(db, "lnvar", "Mesh", lnvar, nnodes, NULL, 0, DB_LONG, DB_NODECENT, opt);
    DBPutUcdvar1(db, "Lnvar", "Mesh", Lnvar, nnodes, NULL, 0, DB_LONG_LONG, DB_NODECENT, opt);
    DBPutUcdvar1(db, "fnvar", "Mesh", fnvar, nnodes, NULL, 0, DB_FLOAT, DB_NODECENT, opt);
    DBPutUcdvar1(db, "dnvar", "Mesh", dnvar, nnodes, NULL, 0, DB_DOUBLE, DB_NODECENT, opt);
    DBFreeOptlist(opt);
  }
  free(cnvar);
  free(snvar);
  free(invar);
  free(lnvar);
  free(Lnvar);
  free(fnvar);
  free(dnvar);

  /* do Zone vars */

  dims[0]--;
  dims[1]--;

  czvar = (char *)        malloc(sizeof(char)*nzones); 
  szvar = (short *)       malloc(sizeof(short)*nzones); 
  izvar = (int *)         malloc(sizeof(int)*nzones); 
  lzvar = (long *)        malloc(sizeof(long)*nzones); 
  Lzvar = (long long *)   malloc(sizeof(long long)*nzones); 
  fzvar = (float *)       malloc(sizeof(float)*nzones); 
  dzvar = (double *)      malloc(sizeof(double)*nzones); 
  c=0;
  for (x=0;x<mesh.zx;x++) {
    for (y=0;y<mesh.zy;y++) {
      f1[c]=mesh.zone[x][y].vars[ZV_P];
      f2[c]=mesh.zone[x][y].vars[ZV_D];
      czvar[c] = (char)        (x<y?x:y);
      szvar[c] = (short)       (x<y?x:y);
      izvar[c] = (int)         (x<y?x:y);
      lzvar[c] = (long)        (x<y?x:y);
      Lzvar[c] = (long long)   (x<y?x:y);
      fzvar[c] = (float)       (x<y?x:y);
      dzvar[c] = (double)      (x<y?x:y);
      c++;
    }
  }

  for (c=0; c<mixc; c++)
      fm[c] = 2.0/mixc*c;
  if (reorder)
  {
    float tmp=fm[mixc-1];
    fm[mixc-1]=fm[mixc-2];
    fm[mixc-2]=tmp;
  }

  DBPutUcdvar1(db, "p", "Mesh", f1, nzones, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "d", "Mesh", f2, nzones, fm, mixc, DB_FLOAT, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "czvar", "Mesh", czvar, nzones, NULL, 0, DB_CHAR, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "szvar", "Mesh", szvar, nzones, NULL, 0, DB_SHORT, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "izvar", "Mesh", izvar, nzones, NULL, 0, DB_INT, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "lzvar", "Mesh", lzvar, nzones, NULL, 0, DB_LONG, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "Lzvar", "Mesh", Lzvar, nzones, NULL, 0, DB_LONG_LONG, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "fzvar", "Mesh", fzvar, nzones, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL);
  DBPutUcdvar1(db, "dzvar", "Mesh", dzvar, nzones, NULL, 0, DB_DOUBLE, DB_ZONECENT, NULL);
  free(czvar);
  free(szvar);
  free(izvar);
  free(lzvar);
  free(Lzvar);
  free(fzvar);
  free(dzvar);
}


/*----------------------------------------------------------------------------
 * Function: writematspec
 *
 * Inputs:   db (DBfile*): the Silo file handle
 *
 * Returns:  (void)
 *
 * Abstract: Write the material and species info stored in the global Mesh 
 *           to the Silo file.  Handle mixed zones properly for both.
 *
 * Modifications:
 *    Sean Ahern, Wed Feb  6 16:32:35 PST 2002
 *    Added material names.
 *---------------------------------------------------------------------------*/
int
writematspec(DBfile *db)
{
    int     x, y, c;
    int     dims[2];
    int     matlist[1000];
    int     mix_mat[1000];
    int     mix_zone[1000];
    int     mix_next[1000];
    float   mix_vf[1000];
    int     mixc;
    int     mfc;
    int     speclist[1000];
    int     mixspeclist[1000];
    float   specmf[10000];
    DBoptlist      *optlist;

    dims[0] = mesh.zx;
    dims[1] = mesh.zy;

    /* do Materials */

    c = 0;
    mixc = 0;
    for (x = 0; x < mesh.zx; x++)
    {
        for (y = 0; y < mesh.zy; y++)
        {
            int     nmats = mesh.zone[x][y].nmats;
            if (nmats == 1)
            {
                /* clean zone */
                int     m = -1;
                int     i;
                for (i = 1; i <= nmat; i++)
                    if (mesh.zone[x][y].matvf[i] > 0)
                        m = i;
                if (m < 0)
                {
                    printf("Internal error!\n");
                    exit(-1);
                };
                matlist[c] = m;
                c++;
            } else
            {
                /* mixed zone */
                int     m = 0;
                matlist[c] = -mixc - 1;
                for (m = 1; m <= nmat && nmats > 0; m++)
                {
                    if (mesh.zone[x][y].matvf[m] > 0)
                    {
                        mix_mat[mixc] = m;
                        mix_vf[mixc] = mesh.zone[x][y].matvf[m];
                        mix_zone[mixc] = c + 1; /* 1-origin */
                        nmats--;
                        if (nmats)
                            mix_next[mixc] = mixc + 2; /* next + 1-origin */
                        else
                            mix_next[mixc] = 0;
                        mixc++;
                    }
                }
                c++;
            }
        }
    }

    optlist = DBMakeOptlist(10);
    DBAddOption(optlist, DBOPT_MATNAMES, matnames);

    DBPutMaterial(db, "Material", "Mesh", nmat, matnos, matlist, dims, 2,
                  mix_next, mix_mat, mix_zone, mix_vf, mixc, DB_FLOAT,
                  optlist);

    /* Okay! Now for the species! */

    c = 0;
    mixc = 0;
    mfc = 0;
    for (x = 0; x < mesh.zx; x++)
    {
        for (y = 0; y < mesh.zy; y++)
        {
            if (mesh.zone[x][y].nmats == 1)
            {
                int     m = -1;
                int     i, s;
                for (i = 1; i <= nmat; i++)
                    if (mesh.zone[x][y].matvf[i] > 0)
                        m = i;
                if (m < 0)
                {
                    printf("Internal error!\n");
                    exit(-1);
                };

                if (nspec[m - 1] == 1)
                {
                    speclist[c] = 0;   /* no mf for this mat: only 1 species */
                } else
                {
                    speclist[c] = mfc + 1; /* 1-origin */
                    for (s = 0; s < nspec[m - 1]; s++)
                    {
                        specmf[mfc] = mesh.zone[x][y].specmf[m][s];
                        mfc++;
                    }
                }
                c++;
            } else
            {
                int     m;
                speclist[c] = -mixc - 1;

                for (m = 1; m <= nmat; m++)
                {
                    if (mesh.zone[x][y].matvf[m] > 0)
                    {
                        if (nspec[m - 1] == 1)
                        {
                            mixspeclist[mixc] = 0; /* no mf for this mat:
                                                    * only 1 species */
                        } else
                        {
                            int     s;
                            mixspeclist[mixc] = mfc + 1; /* 1-origin */
                            for (s = 0; s < nspec[m - 1]; s++)
                            {
                                specmf[mfc] = mesh.zone[x][y].specmf[m][s];
                                mfc++;
                            }
                        }
                        mixc++;
                    }
                }
                c++;
            }
        }
    }

    DBClearOptlist(optlist);
    DBAddOption(optlist, DBOPT_SPECNAMES, specnames);
    DBAddOption(optlist, DBOPT_SPECCOLORS, speccolors);

    DBPutMatspecies(db, "Species", "Material", nmat, nspec, speclist, dims, 2,
                    mfc, specmf, mixspeclist, mixc, DB_FLOAT, optlist);

    DBFreeOptlist(optlist);

    return mixc;
}
