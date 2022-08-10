#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef unix
#include <unistd.h>
#endif

#include <mikenet/simulator.h>
#include "simconfig.h" //sample 12
#include "model.h"
#include "hearing.h"
#include "reading_recur50_randcon.h"
#include "train.h"

ExampleSet *reading_examples, *op_examples, *os_examples;
ExampleSet *hearing_examples,*speaking_examples;
ExampleSet *sem_examples,*phono_examples;

ExampleSet *reading_examples_awl, *op_examples_awl, *os_examples_awl;
ExampleSet *hearing_examples_awl,*speaking_examples_awl;
ExampleSet *sem_examples_awl,*phono_examples_awl;

int main(int argc,char *argv[])
{
  char cmd[255];
  Example *ex;
  float epsilon=0.05;
  int seed=1,first=1, index=0;
  int start=1,i,j;
  char  loadFile[255],fn[255];
  setbuf(stdout,NULL);
  int impairphon=0,impairsem=0;
  float noiselevel=1;
  char *weightFile=NULL;
  int iteration=1000;
  int rcount=0, hcount=0, scount=0;
  float rerr=0, herr=0, serr=0;
  float dice=0, dice1=0;
  
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

  /* load in the artificial word example sets - new orth */
  reading_examples_awl=load_examples("englishdict_randcon_awl_neworth.pat",TICKS);
  op_examples_awl=load_examples("op_randcon_awl_neworth.pat",TICKS);
  os_examples_awl=load_examples("os_randcon_awl_neworth.pat",TICKS);

  phono_examples_awl=load_examples("phono_awl.pat",TICKS);
  sem_examples_awl=load_examples("sem_awl.pat",TICKS);
  hearing_examples_awl=load_examples("ps_randcon_awl.pat",TICKS);
  speaking_examples_awl=load_examples("sp_awl.pat",TICKS);
  
  /* load in the english word example sets */
  reading_examples=load_examples("englishdict_randcon.pat",TICKS);
  phono_examples=load_examples("phono.pat",TICKS);
  sem_examples=load_examples("sem.pat",TICKS);
  hearing_examples=load_examples("ps_randcon.pat",TICKS);
  speaking_examples=load_examples("sp.pat",TICKS);
  
  /* load pretrained weights from sem<->phon net: */
  printf("loading pretrained weights ...\n");
  load_weights(reading,weightFile);
  
  for(j=0;j<ps->numConnections;j++) freeze_weights(ps->connections[j]);
  for(j=0;j<sp->numConnections;j++) freeze_weights(sp->connections[j]);
  for(j=0;j<phono->numConnections;j++) freeze_weights(phono->connections[j]);
  for(j=0;j<sem->numConnections;j++) freeze_weights(sem->connections[j]); 
  printf("prtrained_frozen!\n");
  
  for(j=0;j<reading->numConnections;j++) unfreeze_weights(reading->connections[j]); 
  printf("reading_unfreeze!\n");

     
  for(i=index;i<=iteration;i++)
    { 
    
      dice = mikenet_random();
      dice1 = mikenet_random();

      if (i % 400 == 0 ) {
	    	#ifdef OP 
	    	sprintf(fn,"English_Artificial_OP_Reading_Weight_v%d_t%d", seed, i);
      	    #elif OS
		    sprintf(fn,"English_Artificial_OS_Reading_Weight_v%d_t%d", seed, i);
	        #endif
	    	save_weights(reading,fn);
      }

      if (dice1 <= 0.3) {
      
        //printf("reading\n");
        ex=get_random_example(reading_examples);
        crbp_forward(reading,ex);
        crbp_compute_gradients(reading,ex);
        rerr+=compute_error(reading,ex);
        crbp_apply_deltas(reading);
        rcount++;
        
      }
      else {
      	#ifdef OP 
      	if (dice <= 0.75)
	  	{	 
        	ex=get_random_example(op_examples_awl);
        	//get_name(ex->name,name);
        	crbp_forward(reading,ex);
        	crbp_compute_gradients(reading,ex);
        	rerr+=compute_error(reading,ex);
        	crbp_apply_deltas(reading);
        	rcount++;
      	}
      	else {         
        	ex=get_random_example(os_examples_awl);
        	//get_name(ex->name,name);
        	crbp_forward(reading,ex);
        	crbp_compute_gradients(reading,ex);
        	rerr+=compute_error(reading,ex);
        	crbp_apply_deltas(reading);
        	rcount++;
      	}
      
      	#elif OS
      	if (dice <= 0.25)
	  	{ 
        	ex=get_random_example(op_examples_awl);
        	//get_name(ex->name,name);
        	crbp_forward(reading,ex);
        	crbp_compute_gradients(reading,ex);
        	rerr+=compute_error(reading,ex);
        	crbp_apply_deltas(reading);
        	rcount++;
      	}
      	else {         
        	ex=get_random_example(os_examples_awl);
        	//get_name(ex->name,name);
        	crbp_forward(reading,ex);
        	crbp_compute_gradients(reading,ex);
        	rerr+=compute_error(reading,ex);
        	crbp_apply_deltas(reading);
        	rcount++;
      	}
      	  
      	#endif
      }
	  if (i % 100 == 0)
	  {
	  	printf("time: %d example:%d avg_reading_err: %3.3f avg_hearing_err: %3.3f avg_speaking_err: %3.3f\n", i, ex->index,
		rerr/rcount, herr/hcount, serr/scount);
	  	herr=0.0;
	  	serr=0.0;
	  	rerr=0.0;
	  	hcount=0;
	  	scount=0;
	  	rcount=0;
	  }
    }
  return 0;
}
