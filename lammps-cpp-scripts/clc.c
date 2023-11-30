#include <stdio.h>
#include <math.h>

long i,j,ts,ich,Nch,tm,im,jm;
double x,y,d,dlt,vol,R,Lx,Ly,Lz,pi,rho,phi;
double cxi,cyi,czi,cxyi,sxi,syi,szi,sxyi;
double nc[400][400],m[400][400];
double vx[400][400],vy[400][400],vz[400][400];
double ux[400][400],uy[400][400],uz[400][400];
double tx[400][400],ty[400][400],tz[400][400],txy[400][400];

FILE *inp,*out;
int main( )
{
  pi=atan(1.0)*4;
  rho=2.5;
  inp=fopen("R","r");
  fscanf(inp,"%lf\n",&R);
  fclose(inp);
  Lz=1;
  dlt=0.1;
  Lx=2*R;Ly=2*R;
  im=Lx/dlt;jm=Ly/dlt;
  vol=dlt*dlt*Lz;
  d=0.1;

  inp=fopen("v.dat","r");
  fscanf(inp,"%*s %*s %*s %*s %*s %*s %*s %*s %*s\n");
  fscanf(inp,"%*s %*s %*s %*s\n");
  fscanf(inp,"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s\n");
  fscanf(inp,"%li %li %*f \n",&ts,&Nch);
  for (ich=1;ich<=Nch;++ich){
    fscanf(inp,"%li %lf %lf",&tm,&x,&y);
    i=trunc((x+R)/dlt)+1;j=trunc((y+R)/dlt)+1;
    fscanf(inp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &nc[i][j],&m[i][j],&vx[i][j],&vy[i][j],&vz[i][j],&ux[i][j],&uy[i][j],&uz[i][j], &cxi,&cyi,&czi,&cxyi,&sxi,&syi,&szi,&sxyi);
    tx[i][j]=(-cxi+sxi-m[i][j]*vx[i][j]*vx[i][j])*nc[i][j]/vol;
    ty[i][j]=(-cyi+syi-m[i][j]*vy[i][j]*vy[i][j])*nc[i][j]/vol;
    tz[i][j]=(-czi+szi-m[i][j]*vz[i][j]*vz[i][j])*nc[i][j]/vol;
    txy[i][j]=(-cxyi+sxyi-m[i][j]*vx[i][j]*vy[i][j])*nc[i][j]/vol;
    ux[i][j]=ux[i][j]-vx[i][j]*vx[i][j];
    uy[i][j]=uy[i][j]-vy[i][j]*vy[i][j];
    uz[i][j]=uz[i][j]-vz[i][j]*vz[i][j];
  }
  fclose(inp);
  
  out=fopen("va.dat","w");
  for (i=1;i<=im;++i){
    for (j=1;j<=jm;++j){
      x=(i-0.5)*dlt-R;y=(j-0.5)*dlt-R;
      phi=nc[i][j]*m[i][j]/rho/vol;
      fprintf(out,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", x,y,phi,vx[i][j],vy[i][j],vz[i][j],ux[i][j],uy[i][j],uz[i][j], tx[i][j],ty[i][j],tz[i][j],txy[i][j]);    }
  }
  fclose(out);
}
