#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <mikenet/simulator.h>

#include "model.h"
#include "reading_model_recur50_randcon.c"

#include "simconfig.h" //sample 12
//#include "pretrain_simconfig.h" //sample 8

int debug = 0;

ExampleSet *examples;

typedef struct
{
  char ch;
  Real vector[PHO_FEATURES];
} Phoneme;

Phoneme phonemes[50];
int phocount = 0;

int symbol_hash[255];

int NUM_WORDS = 0;

char words[10000][15];
char words_pho[10000][15];
char words_pho2[10000][15];

void noise_connection(Connections *c, float n)
{
  int i, j;

  for (i = 0; i < c->to->numUnits; i++)
    for (j = 0; j < c->from->numUnits; j++)
    {
      c->weights[i][j] *= 1.0 +
                          n * gaussian_number();
    }
}

load_items(char *key)
{
  FILE *f;
  int i;
  char line[255];
  char *p;

  // printf("load_items....\r\n");

  f = fopen(key, "r");
  if (f == NULL)
    Error0("can't open key file\n");

  fgets(line, 255, f);
  i = 0;
  while (!feof(f))
  {
    p = strtok(line, " \t\n");
    strcpy(words[i], p);
    p = strtok(NULL, " \t\n");
    // p=strtok(NULL," \t\n");
    strcpy(words_pho[i], p);
    words_pho[i][PHO_SLOTS] = 0;
    p = strtok(NULL, " \t\n");
    //if (p && ((p[0] >= 'a' && p[0] <= 'z') || p[0] == '-'))
    if(p && p[0] >= 33 && p[0] <= 126)
      strcpy(words_pho2[i], p);
    else
      strcpy(words_pho2[i], "");
    words_pho2[i][PHO_SLOTS] = 0;
    i++;
    fgets(line, 255, f);
  }
  fclose(f);
  NUM_WORDS = i;
}

float nonword_error(Real *vec, char *t1, char *t2)
{
  float e1 = 0, e2 = 0, e, d1, d2;
  char c;
  int v, i, j;

  for (i = 0; i < PHO_SLOTS; i++)
  {
    v = symbol_hash[(int)t2[i]];
    if (v == -1)
    {
      fprintf(stderr, "(1)error on hash lookup, char %c\n",
              t2[i]);
      exit(0);
    }

    d1 = 0;
    d2 = 0;
    for (j = 0; j < PHO_FEATURES; j++)
    {
      e = vec[i * PHO_FEATURES + j] - phonemes[v].vector[j];
      d1 += e * e;
    }
    if ((t2[0] != 0) && (t2[i] != t1[i]))
    {
      v = symbol_hash[(int)t2[i]];
      if (v == -1)
      {
        fprintf(stderr, "(2)error on hash lookup, char %c\n",
                t2[i]);
        exit(0);
      }
      for (j = 0; j < PHO_FEATURES; j++)
      {
        e = vec[i * PHO_FEATURES + j] - phonemes[v].vector[j];
        d2 += e * e;
      }
    }
    else
      d2 = d1;
    e1 += d1;
    e2 += d2;
  }
  if (e1 < e2)
    return e1;
  else
    return e2;
}

load_phonemes()
{
  FILE *f;
  char line[255], *p;
  int i, x;

  // printf("load_phonemes....\r\n");

  f = fopen("../Model/eng_mapping", "r");
  if (f == NULL)
  {
    fprintf(stderr, "file\n");
    exit(1);
  }
  x = 0;
  fgets(line, 255, f);
  while (!feof(f))
  {
    p = strtok(line, " \t\n");
    if (p[0] == '-')
      p[0] = '-';
    phonemes[phocount].ch = p[0];
    symbol_hash[(int)(p[0])] = x++;
    for (i = 0; i < PHO_FEATURES; i++)
    {
      p = strtok(NULL, " \t\n");
      if (strcmp(p, "NaN") == 0)
        phonemes[phocount].vector[i] = -10;
      else
        phonemes[phocount].vector[i] = atof(p);
    }
    phocount++;
    fgets(line, 255, f);
  }
  fclose(f);
}

float euclid_distance(Real *x1, Real *x2)
{
  float d = 0, r;
  int i;
  for (i = 0; i < PHO_FEATURES; i++)
  {
    r = x1[i] - x2[i];
    d += r * r;
  }
  return d;
}

Real euclid(Real *v, char *out)
{
  int i, j;
  int nearest_item;
  float error = 0;
  float nearest_distance, d;

  for (i = 0; i < PHO_SLOTS; i++)
  {
    nearest_item = -1;
    for (j = 0; j < phocount; j++)
    {
      d = euclid_distance(&v[i * PHO_FEATURES], phonemes[j].vector);
      if ((nearest_item == -1) ||
          (d < nearest_distance))
      {
        nearest_item = j;
        nearest_distance = d;
      }
    }
    error += d;
    out[i] = phonemes[nearest_item].ch;
  }
  out[PHO_SLOTS] = 0;
  return nearest_distance;
}

int get_name(char *tag, char *name)
{
  char *p;
  p = strstr(tag, "Pho:");
  p += 5;
  p = strtok(p, " \t\n");
  strcpy(name, p);
}

float compute_ce_error(Group *g, Example *ex)
{
  float e = 0.0, e1;
  int i, j;
  Real out, target;

  for (i = 0; i < g->numUnits; i++)
  {

    out = g->outputs[SAMPLES - 1][i];
    target = get_value(ex->targets, g->index, SAMPLES - 1, i);

    // printf("out1 %f target %f\n", out, target);

    // out=CLIP(g->outputs[SAMPLES-1][i],LOGISTIC_MIN,LOGISTIC_MAX);
    // printf("out2 %f target %f\n", out, target);

    if (fabs(target) < 0.001) // close enought to zero
    {
      // can't be higher than 1-errorRadius
      // out = CLIP(out,LOGISTIC_MIN,(1.0-g->errorRadius));
      e1 = -log(1.0 - out);
      // printf("1 e1 %f \n", e1);
    }
    else if (fabs(target) > 0.999) // close enough to 1
    {
      // can't be lower than errorRadius
      // out = CLIP(out,g->errorRadius,LOGISTIC_MAX);
      e1 = -log(out);
      // printf("2 e1 %f \n", e1);
    }
    else
    {
      e1 = (log((target) / (out)) * (target) +
            log((1.0 - (target)) /
                (1.0 - (out))) *
                (1.0 - (target)));
      // printf("3 e1 %f \n", e1);
    }

    // e1 = fabs(semantics->outputs[SAMPLES-1][i] -
    //           get_value(ex->targets,semantics->index,SAMPLES-1,i));
    // e += e1*e1;
    e += e1;
  }
  return e;
}

int main(int argc, char *argv[])
{
  float noise = 0.0;
  float lesion = 0.0;
  int didconvert;
  char converted[10];
  int test_illegal = 0;
  int ill;
  Real dx;
  StatStruct *stats;
  char fn[255];
  int illegal = 0;
  int verbose = 0;
  int semantic = 0;
  char euclid_output[15], euclid_target[15], name[40];
  char thresh_output[15], thresh_target[15];
  Real dice, range;
  Example *ex;
  int i, count, j, save;
  // Real error;
  float error;
  Real dx_cutoff = 100000000.0;
  float threshold = 0.25;
  int thresh_wrong;
  int euclid_wrong, euclid_wrongs;
  int thresh_wrongs;
  int new_wrongs = 0, new_wrong;
  FILE *f;
  long seed = 555;
  char *patternFile = NULL, *weightFile = NULL, *keyFile = NULL;
  int impairphon = 0, impairsem = 0;
  float noiselevel = 1;
  int testreadingmodel = 0;
  int correct = 0;
  int con = 0;
  float sse_phon = 0;

  setbuf(stdout, NULL);
  /* set random number seed to process id */
  mikenet_set_seed(666);
  stats = get_stat_struct();

  for (i = 0; i < 255; i++)
    symbol_hash[i] = -1;

  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-seed") == 0)
    {
      seed = atol(argv[i + 1]);
      i++;
    }
    else if (strncmp(argv[i], "-weight", 5) == 0)
    {
      weightFile = argv[i + 1];
      i++;
    }
    else if (strncmp(argv[i], "-pat", 4) == 0)
    {
      patternFile = argv[i + 1];
      i++;
    }
    else if (strncmp(argv[i], "-key", 4) == 0)
    {
      keyFile = argv[i + 1];
      i++;
    }
    else if (strcmp(argv[i], "-ill") == 0)
    {
      test_illegal = 1;
    }
    else if (strncmp(argv[i], "-load", 5) == 0)
    {
      weightFile = argv[i + 1];
      i++;
    }
    else if (strncmp(argv[i], "-lesion", 5) == 0)
    {
      lesion = atof(argv[i + 1]);
      i++;
    }
    else if (strncmp(argv[i], "-noiselevel", 8) == 0)
    {
      noiselevel = atof(argv[i + 1]);
      i++;
    }
    else if (strcmp(argv[i], "-dx") == 0)
    {
      dx_cutoff = atof(argv[i + 1]);
      i++;
    }
    else if (strncmp(argv[i], "-thresh", 5) == 0)
    {
      threshold = atof(argv[i + 1]);
      i++;
    }
    else if (strncmp(argv[i], "-verbose", 5) == 0)
    {
      verbose = 1;
    }
    else if (strncmp(argv[i], "-semantic", 5) == 0)
    {
      semantic = 1;
    }
    else if (strncmp(argv[i], "-impairphon", 10) == 0)
    {
      impairphon = 1;
    }
    else if (strncmp(argv[i], "-impairsem", 10) == 0)
    {
      impairsem = 1;
    }
    else if (strncmp(argv[i], "-testreadingmodel", 10) == 0)
    {
      testreadingmodel = 1;
    }
#ifdef NUM_RECUR50_CONTEXT
    else if (strncmp(argv[i], "-contex", 5) == 0)
    {
      con = 1;
    }
#endif
    else
    {
      fprintf(stderr, "unknown option: %s\n", argv[i]);
      exit(-1);
    }
  }

  load_phonemes();
  if (keyFile == NULL)
    Error0("no key file specified");

  if (patternFile == NULL)
    Error0("no pattern file specified");

  load_items(keyFile);

  // test samples
  // printf("Samples: %d\n", SAMPLES);

  build_reading_model_recur50_randcon(SAMPLES);

  if (impairphon == 1)
  {
    /*    c[9]->weightNoiseType=MULTIPLICATIVE_NOISE;
    c[10]->weightNoiseType=MULTIPLICATIVE_NOISE;
    c[9]->weightNoise=noiselevel;
    c[10]->weightNoise=noiselevel;
    phonology->inputNoise=noiselevel;
    phonology->activationNoise=noiselevel;
    pho_cleanup->inputNoise=noiselevel;
    pho_cleanup->activationNoise=noiselevel;
    pho_cleanup->targetNoise=noiselevel; */
    phonology->clampNoise = noiselevel;
    phonology->targetNoise = noiselevel;
  }
  //  printf("%f\n",c[9]->weightNoise);
  // printf("%f\n",c[10]->weightNoise);
  // printf("%f\n",phonology->inputNoise);

  if (impairsem == 1)
  {
    /* add these lines if impairing semantics: */
    /*    c[3]->weightNoiseType=MULTIPLICATIVE_NOISE;
    c[4]->weightNoiseType=MULTIPLICATIVE_NOISE;
    semantics->inputNoise=noiselevel;
    semantics->activationNoise=noiselevel;
    semantics->targetNoise=noiselevel;
    sem_cleanup->inputNoise=noiselevel;
    sem_cleanup->activationNoise=noiselevel;
    sem_cleanup->targetNoise=noiselevel; */
    semantics->clampNoise = noiselevel;
    semantics->targetNoise = noiselevel;
  }

  if (weightFile == NULL)
    Error0("no weight file specified");

  if (strcmp(patternFile, "../Model/ps_randcon.pat") == 0 && testreadingmodel == 0)
    load_weights(ps, weightFile);
  if (strcmp(patternFile, "../Model/ps_randcon.pat") == 0 && testreadingmodel == 1)
    load_weights(reading, weightFile);
  if (strcmp(patternFile, "../Model/sp.pat") == 0 && testreadingmodel == 0)
    load_weights(sp, weightFile);
  if (strcmp(patternFile, "../Model/sp.pat") == 0 && testreadingmodel == 1)
    load_weights(reading, weightFile);

  if (strcmp(patternFile, "../Model/englishdict_randcon_awl_neworth.pat") == 0)
  {
    // printf("englishdict_randcon_awl_neworth: load weights\r\n");
    load_weights(reading, weightFile);
  }

  mikenet_set_seed(seed);

  /* load in our example set */
  examples = load_examples(patternFile, SAMPLES);

  if (examples->numExamples != NUM_WORDS)
    Error2("not enough words in examplefile; file has %d and needs %d",
           examples->numExamples, NUM_WORDS);

  error = 0.0;
  count = 0;
  save = 1;
  euclid_wrongs = 0;
  new_wrongs = 0;
  thresh_wrongs = 0;

  clear_stats(stats);
  strcpy(thresh_target, "");
  strcpy(euclid_target, "");
  illegal = 0;

  euclid_wrongs = 0;
  thresh_wrongs = 0;
  clear_stats(stats);

  /* loop for ITER number of times */
  for (i = 0; i < examples->numExamples; i++)
  {
    ex = &examples->examples[i];

    if (strcmp(patternFile, "../Model/ps_randcon.pat") == 0 && testreadingmodel == 0)
    {
      printf("ps test ");
      crbp_forward(ps, ex);
    }
    if (strcmp(patternFile, "../Model/ps_randcon.pat") == 0 && testreadingmodel == 1)
    {
      printf("ps test ");
      crbp_forward(reading, ex);
    }
    if (strcmp(patternFile, "../Model/sp.pat") == 0 && testreadingmodel == 0)
    {
      printf("sp test ");
      crbp_forward(sp, ex);
    }
    if (strcmp(patternFile, "../Model/sp.pat") == 0 && testreadingmodel == 1)
    {
      printf("sp test ");
      crbp_forward(reading, ex);
    }

    if (strcmp(patternFile, "../Model/englishdict_randcon_awl_neworth.pat") == 0)
    {
      printf("reading test ");
      crbp_forward(reading, ex);
    }
    push_item(error, stats);
    euclid_wrong = 0;
    get_name(ex->name, name);
    printf("%s\t", name);
    if ((strcmp(patternFile, "../Model/sp.pat") == 0 && !con) || (strcmp(patternFile, "../Model/englishdict_randcon_awl_neworth.pat") == 0 && !semantic))
    {

      euclid(phonology->outputs[SAMPLES - 1], euclid_output);
      sse_phon = compute_ce_error(phonology, ex);
      error = nonword_error(phonology->outputs[SAMPLES - 1], words_pho[i], words_pho2[i]);
      /* test by yaning */
      // printf("%.2f\t%s\t%s\t%s\t",error,euclid_output,words_pho[i],words_pho2[i]);
      if (strcmp(words_pho2[i], euclid_output) == 0)
      {
        printf("correct\t");
        correct = 1;
      }
      else
      {
        printf("incorrect\t");
        correct = 0;
      }
      // printf("%.2f\t%s\t%s\t%s\t%d\t",error,euclid_output,words_pho[i],words_pho2[i], correct);
      // printf("%6.8f\t%s\t%s\t%d\t",error, euclid_output, words_pho[i], correct);
      printf("%6.16f\t%s\t%s\t%d\t%6.16f\t", error, euclid_output, words_pho[i], correct, sse_phon);
      printf("\n");
    }
    /*     if (verbose){
  for(j=0;j<phonology->numUnits;j++)
   printf("%i\t%7.4f\t%7.4f\n",
    j,
    phonology->outputs[SAMPLES-2][j],
    ex->targets[phonology->index][SAMPLES-1][j]);
    } */

    if (strcmp(patternFile, "../Model/ps_randcon.pat") == 0 || (strcmp(patternFile, "../Model/englishdict_randcon_awl_neworth.pat") == 0 && semantic))
    {

      for (j = 0; j < semantics->numUnits; j++)
      {
        printf("%5.2f ", semantics->outputs[SAMPLES - 1][j]);
      }
      printf("\n");
    }
  }
  return 0;
}
