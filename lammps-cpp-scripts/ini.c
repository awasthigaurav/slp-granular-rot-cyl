#include <stdio.h>
#include <math.h>

long Nparts,i,j,p,N,Nl;
long ia,im,iq,ir,idum;
double am;
double r,th,dth,thp,R,pi,rat;
double x[500000],y[500000],z[500000];
double Lx,Ly,Lz,sp,rho,eps,d,deld;
double h0,h1,w1;
FILE *inp, *out;

double ran0(void) // generates random numbers using linear congruential generator algorithm
{ // idum is seed for the random number generator; ia, iq, ir, and im are parameters for the algorithm
  long k;
  double res;
  k=idum/iq;
  idum=ia*(idum-k*iq)-ir*k;
  if (idum < 0) idum=idum+im; // to ensure seed is positive
  res=2*am*idum-1; // am is a scaling factor
  return res; // returns the random number between -1 and 1
}

int main( )
{
  ia = 16807;
  im = 2147483647;
  am = 1.0/im;
  iq = 127773;
  ir = 2836;
  
  pi=atan(1.0)*4;
  inp=fopen("idum","r");
  fscanf(inp,"%li\n",&idum);
  fclose(inp);
  inp=fopen("R","r");
  fscanf(inp,"%lf\n",&R);
  fclose(inp);
  d=0.1;
  Lz=1;
  rho=2.5;
  
  eps=1e-6;
  
  deld=0.1*d;
  sp=d+deld+eps;
  Nparts=2000;
  
  thp=60*pi/180;
  rat=(pi+2*thp)/2/pi*0.62;
  N=trunc(4*R*R/d/d*rat);
  r=R-sp;dth=sp/r;th=-dth-thp;
  for (i=1;i<=N;++i){
    th=th+dth;
    if (th>pi+thp){
      r=r-sp;
      dth=sp/r;
      th=-thp;
    }
    x[i]=-r*cos(th);y[i]=-r*sin(th);z[i]=sp;
  }
  Nl=trunc(Lz/sp)-2;
  for (j=1;j<=Nl;++j){
    for (i=1;i<=N;++i){
      x[i+j*N]=x[i];
      y[i+j*N]=y[i];
      z[i+j*N]=sp*(j+1);
    }
  }
  
  Nparts=N*(Nl+1);
  out = fopen("pos0.data","w");
  fprintf(out,"LAMMPS data file via write_data, version 12 Dec 2018, timestep = %i\n",0);
  fprintf(out,"\n");
  fprintf(out,"%li atoms\n",Nparts);
  fprintf(out,"%i atom types\n",1);
  fprintf(out,"\n");
  fprintf(out,"%lf %lf xlo xhi\n",-R,R);
  fprintf(out,"%lf %lf ylo yhi\n",-R,R);
  fprintf(out,"%lf %lf zlo zhi\n",0.0,Lz);
  fprintf(out,"\n");
  fprintf(out,"Atoms # sphere\n");
  fprintf(out,"\n");
  for (i=1;i<=Nparts;++i){
    fprintf(out,"%li %i %f %f %f %f %f %i %i %i\n", i,1,d+ran0()*deld,rho,x[i],y[i],z[i],0,0,0);
  }
  fprintf(out,"\n");
  fprintf(out,"Velocities\n");
  fprintf(out,"\n");
  for (i=1;i<=Nparts;++i)
    fprintf(out,"%li %f %f %f %f %f %f\n",i,0.0,0.0,ran0()*0.1,0.0,0.0,0.0);
  fclose(out);
  
  out=fopen("idum","w");
  fprintf(out,"%li\n",idum);
  fclose(out);

}




