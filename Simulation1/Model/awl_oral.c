
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef unix
#include <unistd.h>
#endif

#include <mikenet/simulator.h>
#include "simconfig.h"

#include "model.h"
#include "hearing.h"
#include "reading_recur50_randcon.h"
#include "train.h"

ExampleSet *hearing_examples,*speaking_examples;
ExampleSet *sem_examples,*phono_examples;

int main(int argc,char *argv[])
{
  char cmd[255];
  int hcount=0,scount=0;
  float herr=0,serr=0,dice;
  Example *ex;
  float epsilon=0.05;
  int seed=1,first=1,index=0;
  int start=1,i,j;
  char fn[255];
  setbuf(stdout,NULL);
  int impairphon=0,impairsem=0;
  float noiselevel=1;
  char *weightFile=NULL;
  int iteration=1000;

  /* what are the command line arguments? */
  for(i=1;i<argc;i++)
  {
      if (strcmp(argv[i],"-seed")==0)
	{
	  seed=atoi(argv[i+1]);
	  i++;
	}
	  else if (strncmp(argv[i],"-trained_weight",14)==0)
	{
	  weightFile=argv[i+1];
	  printf("weightFile %s\n", weightFile);
	  i++;
	}
	  else if (strncmp(argv[i],"-trained_index",12)==0)
	{
	  index=atof(argv[i+1]);
	  i++;
	}
	  else if (strncmp(argv[i],"-iteration",12)==0)
	{
	  iteration=atof(argv[i+1]);
	  i++;
	}
      else if (strncmp(argv[i],"-epsilon",5)==0)
	{
	  epsilon=atof(argv[i+1]);
	  i++;
	}
      else
	{
	  fprintf(stderr,"unknown argument: %s\n",argv[i]);
	  exit(1);
	}
  }

  default_epsilon=epsilon;

  mikenet_set_seed(seed);

  build_reading_model_recur50_randcon(SAMPLES);


  /* load in our example set */
  
  phono_examples=load_examples("phono_awl.pat",TICKS);
  sem_examples=load_examples("sem_awl.pat",TICKS);
  hearing_examples=load_examples("ps_randcon_awl.pat",TICKS);
  speaking_examples=load_examples("sp_awl.pat",TICKS);
     
 

  /* load trained weights from sem<->phon net: */
  if (weightFile!=NULL) load_weights(reading,weightFile);
  
  
  for(i=index;i<=iteration;i++)
  {
      
    dice = mikenet_random();
    if (dice <=0.1)
	{
	  ex=get_random_example(phono_examples);
	  crbp_forward(phono,ex);
	  crbp_compute_gradients(phono,ex);
	  crbp_apply_deltas(phono);
	}
    else if (dice <= 0.5)
	{
	  ex=get_random_example(hearing_examples);
	  crbp_forward(ps,ex);
	  crbp_compute_gradients(ps,ex);
	  herr += compute_error(ps,ex);
	  crbp_apply_deltas(ps);
	  hcount++;
	}
    else if (dice <= 0.6)
	{
	  ex=get_random_example(sem_examples);
	  crbp_forward(sem,ex);
	  crbp_compute_gradients(sem,ex);
	  crbp_apply_deltas(sem);
	}
    else
	{
	  ex=get_random_example(speaking_examples);
	  crbp_forward(sp,ex);
	  crbp_compute_gradients(sp,ex);
	  serr+=compute_error(sp,ex);
	  crbp_apply_deltas(sp);
	  scount++;
	  
	}
    
    if (i % 100 == 0)
	{
	  printf("time: %d avg_hearing_err: %3.3f avg_speaking_err: %3.3f\n", i,
		herr/hcount, serr/scount);
	  herr=0.0;
	  serr=0.0;
	  hcount=0;
	  scount=0;
	}
      
  }
  
  //  save_weights
  if (iteration==500) {
	 sprintf(fn,"Oral_Weight_LP_v%d", seed);
	 save_weights(reading,fn);
	 
	 sprintf(fn,"PS_Weight_LP_v%d", seed);
	 save_weights(ps,fn);
	 
	 sprintf(fn,"SP_Weight_LP_v%d", seed);
	 save_weights(sp,fn);	 
	 
  } else if (iteration==1000){
     sprintf(fn,"Oral_Weight_MP_v%d", seed);
	 save_weights(reading,fn);
	 
	 sprintf(fn,"PS_Weight_MP_v%d", seed);
	 save_weights(ps,fn);
	 
	 sprintf(fn,"SP_Weight_MP_v%d", seed);
	 save_weights(sp,fn);
	 
  } else if (iteration==2000){
     sprintf(fn,"Oral_Weight_HP_v%d", seed);
	 save_weights(reading,fn);
	 
	 sprintf(fn,"PS_Weight_HP_v%d", seed);
	 save_weights(ps,fn);
	 
	 sprintf(fn,"SP_Weight_HP_v%d", seed);
	 save_weights(sp,fn);
	 
  } else{
     
  }
  
  
  return 0;
}
