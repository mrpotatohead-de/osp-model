/* to compile this, your MIKENET_DIR environment variable
   must be set to the appropriate directory.  putting this
   at the bottom of your .cshrc file will do the trick:

   setenv MIKENET_DIR ~mharm/mikenet/default/


   This demo program solves the xor problem.  

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "simconfig.h"

#ifdef unix
#include <unistd.h>
#endif

#include <mikenet/simulator.h>
#include "model.h"
#include "hearing.h"

Net *reading,*sp,*ps,*sem,*phono;
Group *phonology,*psh,*semantics,*sem_cleanup,*pho_cleanup,*bias,*sph;
Group *orthography, *osh, *oph;
Group *context, *csh;

Connections *c[100],*bias_semantics, *bias_phono, *bias_pho_cleanup, *bias_sem_cleanup, *bias_psh, *bias_sph;
Connections *bias_oph, *bias_osh;
Connections *pho_to_psh, *psh_to_sem, *sem_to_sem_cleanup, *sem_cleanup_to_sem;
Connections *sem_to_sph, *sph_to_pho, *pho_to_pho_cleanup, *pho_cleanup_to_pho;
Connections *o_to_oph, *o_to_osh, *oph_to_pho, *osh_to_sem;
Connections *con_to_csh, *csh_to_sem, *bias_csh;

int connection_count=0;

float random_number_range=RANDOM_NUMBER_RANGE;


void build_reading_model_recur50_randcon(int samples)
{

  int i,x;
  float range;

  range = random_number_range;

  default_errorRamp=RAMP_ERROR;

  default_tai=1;

  default_activationType=LOGISTIC_ACTIVATION; 
  default_errorComputation=CROSS_ENTROPY_ERROR;
  
  default_scaling=SCALE_NONE;
  //default_scaling=SCALE_PROB;

  /* build a network, with samples number of time samples */
  reading=create_net(samples);
  sp=create_net(samples);
  ps=create_net(samples);
  sem=create_net(samples);
  phono=create_net(samples);
  reading->integrationConstant=(float)SECONDS/(float)samples;
  sp->integrationConstant=(float)SECONDS/(float)samples;
  ps->integrationConstant=(float)SECONDS/(float)samples;
  sem->integrationConstant=(float)SECONDS/(float)samples;
  phono->integrationConstant=(float)SECONDS/(float)samples;

  phonology=init_group("Phono",PHO_FEATURES * PHO_SLOTS,samples);
  
  psh=init_group("psh",300,samples);
  sph=init_group("sph",300,samples);
    
  semantics=init_group("Semantics",SEM_FEATURES,samples);
  sem_cleanup=init_group("SemCleanup",50,samples);
  pho_cleanup=init_group("PhoCleanup",50,samples);
  bias=init_bias(1.0,samples);
  orthography=init_group("Ortho",ORTHO_FEATURES,samples);
  oph=init_group("oph",500,samples);
  osh=init_group("osh",500,samples);
  context= init_group("Con",4,samples);
  
  csh= init_group("csh",10,samples);
  
  /* now add our groups to the network object */
  bind_group_to_net(reading,phonology);
  bind_group_to_net(reading,psh);
  bind_group_to_net(reading,sph);
  bind_group_to_net(reading,semantics);
  bind_group_to_net(reading,sem_cleanup);
  bind_group_to_net(reading,pho_cleanup);
  bind_group_to_net(reading,bias);
  bind_group_to_net(reading,orthography);
  bind_group_to_net(reading,oph);
  bind_group_to_net(reading,osh);
  bind_group_to_net(reading,context);
  bind_group_to_net(reading,csh);

  bind_group_to_net(ps,phonology);
  bind_group_to_net(ps,psh);
  bind_group_to_net(ps,semantics);
  bind_group_to_net(ps,sem_cleanup);
  bind_group_to_net(ps,bias);
  bind_group_to_net(ps,context);
  bind_group_to_net(ps,csh);

  bind_group_to_net(phono,bias);
  bind_group_to_net(phono,phonology);
  bind_group_to_net(phono,pho_cleanup);

  bind_group_to_net(sem,bias);
  bind_group_to_net(sem,semantics);
  bind_group_to_net(sem,sem_cleanup);

  bind_group_to_net(sp,phonology);
  bind_group_to_net(sp,sph);
  bind_group_to_net(sp,semantics);
  bind_group_to_net(sp,pho_cleanup);
  bind_group_to_net(sp,bias);


  x=0;
  /* now connect our groups */
  c[x]=connect_groups(phonology,psh);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  pho_to_psh=c[x];
  x++;

  c[x]=connect_groups(context,csh);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  con_to_csh=c[x];
  x++;
  
  c[x]=connect_groups(psh,semantics);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  psh_to_sem=c[x];
  x++;

  c[x]=connect_groups(csh,semantics);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  csh_to_sem=c[x];
  x++;
  
  c[x]=connect_groups(semantics,sem_cleanup);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  bind_connection_to_net(sem,c[x]);
  sem_to_sem_cleanup=c[x];
  x++;
  
  c[x]=connect_groups(sem_cleanup,semantics);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  bind_connection_to_net(sem,c[x]);
  sem_cleanup_to_sem=c[x];
  x++;
  
  c[x]=connect_groups(bias,semantics);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  bind_connection_to_net(sem,c[x]);
  bias_semantics=c[x];
  x++;

  c[x]=connect_groups(bias,sem_cleanup);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  bind_connection_to_net(sem,c[x]);
  bias_sem_cleanup=c[x];
  x++;
  
  c[x]=connect_groups(bias,psh);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  bias_psh=c[x];
  x++;
  
  c[x]=connect_groups(bias,csh);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(ps,c[x]);
  bias_csh=c[x];
  x++;
   
  c[x]=connect_groups(semantics,sph);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  sem_to_sph=c[x];
  x++;

  c[x]=connect_groups(sph,phonology);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  sph_to_pho=c[x];
  x++;
  
  c[x]=connect_groups(phonology,pho_cleanup);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  bind_connection_to_net(phono,c[x]);
  pho_to_pho_cleanup=c[x];
  x++;

  c[x]=connect_groups(pho_cleanup,phonology);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  bind_connection_to_net(phono,c[x]);
  pho_cleanup_to_pho=c[x];
  x++;
 
  c[x]=connect_groups(bias,phonology);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  bind_connection_to_net(phono,c[x]); 
  bias_phono=c[x];
  x++;
  
  c[x]=connect_groups(bias,sph);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  bias_sph=c[x];
  x++;

  c[x]=connect_groups(bias,pho_cleanup);
  bind_connection_to_net(reading,c[x]);
  bind_connection_to_net(sp,c[x]);
  bind_connection_to_net(phono,c[x]);
  bias_pho_cleanup=c[x];
  x++;
 
  c[x]=connect_groups(orthography,oph);
  bind_connection_to_net(reading,c[x]);
  o_to_oph=c[x];
  x++;

  c[x]=connect_groups(orthography,osh);
  bind_connection_to_net(reading,c[x]);
  o_to_osh=c[x];
  x++;

  c[x]=connect_groups(oph,phonology);
  bind_connection_to_net(reading,c[x]);
  oph_to_pho=c[x];
  x++;
 
  c[x]=connect_groups(osh,semantics);
  bind_connection_to_net(reading,c[x]);
  osh_to_sem=c[x];
  x++;

  c[x]=connect_groups(bias,oph);
  bind_connection_to_net(reading,c[x]);
  bias_oph=c[x];
  x++;

  c[x]=connect_groups(bias,osh);
  bind_connection_to_net(reading,c[x]);
  bias_osh=c[x];
  x++;
  
  connection_count=x;


  for(i=0;i<reading->numConnections;i++)
    {
      c[i]=reading->connections[i];
      randomize_connections(c[i],1.0);
    }

  for(i=0;i<semantics->numUnits;i++)
    bias_semantics->weights[i][0]=-3.0;

  for(i=0;i<phonology->numUnits;i++)
    bias_phono->weights[i][0]=-3.0;

  return;
}
