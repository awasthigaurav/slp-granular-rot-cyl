#include <stdio.h>
#include <math.h>

long i,j,ts,ich,Nch,im,jm,irun,Nrun;
long k,km;
double x,y,r,d,dlt,Lx,Ly,Lz,R,pi,phii;
double dxs,dys,th,xs,ys,ym,th,st,ct,xp,yp,vxp,vyp;
double txi,tyi,tzi,txyi,vxi,vyi,vzi;
double psii,md,mdsd,mdi,uxi,uyi,uzi;
double vxx,vxy,vyx,vyy;
double sxp,syp,sxyp,uxp,uyp,uzp,sm,tm,s1,s2;
double vx[400][400],vy[400][400],vz[400][400];
double ux[400][400],uy[400][400],uz[400][400];
double tx[400][400],ty[400][400],tz[400][400],txy[400][400];
double phi[400][400],ymin[400],ymax[400],om[400][400];
FILE *inp,*out;
double theta, vtheta[400][400];
int main( )
{
  pi=atan(1.0)*4;
  inp=fopen("Nrun","r");
  fscanf(inp,"%li\n",&Nrun);
  fclose(inp);
  inp=fopen("R","r");
  fscanf(inp,"%lf\n",&R);
  fclose(inp);
  Lx=2*R;
  Ly=2*R;
  Lz=1;
  dlt=0.1;
  im=Lx/dlt;jm=Ly/dlt;
  km=im*jm;
  
  for (i=1;i<=im;++i){
    for (j=1;j<=jm;++j){
      phi[i][j]=vx[i][j]=vy[i][j]=vz[i][j]=0;
      ux[i][j]=uy[i][j]=uz[i][j]=0;
      tx[i][j]=ty[i][j]=tz[i][j]=txy[i][j]=0;
    }
  }
  inp=fopen("cva.dat","r");
  for (irun=1;irun<=Nrun;++irun){
    for (k=1;k<=km;++k){
      fscanf(inp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x,&y,&phii,&vxi,&vyi,&vzi,&uxi,&uyi,&uzi,&txi,&tyi,&tzi,&txyi);
      i=trunc((x+R)/dlt)+1;j=trunc((y+R)/dlt)+1;
      phi[i][j]=phi[i][j]+phii/Nrun;
      vx[i][j]=vx[i][j]+vxi/Nrun;
      vy[i][j]=vy[i][j]+vyi/Nrun;
      vz[i][j]=vz[i][j]+vzi/Nrun;
      ux[i][j]=ux[i][j]+uxi/Nrun;
      uy[i][j]=uy[i][j]+uyi/Nrun;
      uz[i][j]=uz[i][j]+uzi/Nrun;
      tx[i][j]=tx[i][j]+txi/Nrun;
      ty[i][j]=ty[i][j]+tyi/Nrun;
      tz[i][j]=tz[i][j]+tzi/Nrun;
      txy[i][j]=txy[i][j]+txyi/Nrun;
      r=sqrt(x*x+y*y);
      om[i][j]=(-vx[i][j]*y+vy[i][j]*x)/r/r;
    }
  }
  fclose(inp);
  
  out=fopen("avv.dat","w");
  for (i=1;i<=im;++i){
    for (j=1;j<=jm;++j){
      x=(i-0.5)*dlt-R;y=(j-0.5)*dlt-R;
      if (vx[i][j]<0&&vx[i][j+1]>0) ymin[i]=y-dlt*vx[i][j]/(vx[i][j+1]-vx[i][j]);
      if (phi[i][j]>0.4&&phi[i][j+1]<0.4) ymax[i]=y+dlt*(0.4-phi[i][j])/(phi[i][j+1]-phi[i][j]);
      r=sqrt(x*x+y*y);
      theta = atan(y/x);
      if (x<0&&y<0){
      	theta = theta - 4*atan(1);
	}
      vtheta[i][j] = (-vx[i][j]*y+vy[i][j]*x)/r;
      fprintf(out,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", x,y,phi[i][j],vx[i][j],vy[i][j],r,om[i][j], theta, vtheta[i][j], y-ymin[i], ymax[i]);
     }
  }
  fclose(out);
  out=fopen("intf.dat","w");
  for (i=1;i<=im;++i){
    x=(i-0.5)*dlt-R;
    fprintf(out,"%lf %lf %lf\n",x,ymin[i],ymax[i]);
  }
  fclose(out);
  
  out=fopen("prf.dat","w");
  for (i=1;i<=im;++i){
    x=(i-0.5)*dlt-R;
    for (j=1;j<=jm;++j){
      y=(j-0.5)*dlt-R;
      r=sqrt(x*x+y*y);
      if (i%5==0&&r<R&&y<0&&y>ymin[i]&&x<0&&y<ymax[i]){
        fprintf(out,"%lf %lf %lf %lf\n",x,y-ymin[i],vx[i][j],vy[i][j]);
      } //there was a i%5==0 also as one of the conditions in the if block
    }
    fprintf(out,"\n");
  }
  fclose(out);  
}



