#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum { //enums de los tipos de pokemon
    Normal,
    Fire,
    Water,
    Electric,
    Grass,
    Ice,
    Fighting,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dragon,
    EMPTY_CELL,
} pokeType;

typedef struct {
    int r; 
    int g;
    int b;
} pixelColor; // en main: pixelColor pix= {100,0,100}; y acceder asi: pix.r

static const pixelColor colores[] = {
    [Normal]      = {170, 170, 153},
    [Fire]        = {236, 66, 38},
    [Water]       = {78, 154, 255},
    [Electric]    = {244, 205, 52},
    [Grass]       = {119, 204, 85},
    [Ice]         = {101, 204, 255},
    [Fighting]    = {187, 85, 68},
    [Poison]      = {170, 86, 153},
    [Ground]      = {222, 187, 85},
    [Flying]      = {136, 153, 255},
    [Psychic]     = {237, 84, 153},
    [Bug]         = {170, 187, 35},
    [Rock]        = {187, 170, 102},
    [Ghost]       = {102, 103, 188},
    [Dragon]      = {120, 103, 238},
    [EMPTY_CELL]  = {0, 0, 0},
};

typedef enum {//se definen los enums de errores
    ST_OK,
    TODO_MAL,
    ST_HELP,
    ST_ERR_INSUFFICIENT_ARGUMENTS,
    ST_ERR_TOO_MANY_ARGUMENTS,
    ST_ERR_NULL_PTR,
    ST_ERR_UNKNOWN_ARGUMENT,
    ST_ERR_INVALID_WIDTH,
    ST_ERR_INVALID_HEIGHT,
    ST_ERR_INVALID_SEED,
    ST_ERR_INVALID_N,
    ST_ERR_NO_MEM,
} status_t;

void print_err(status_t st) {//funcion para imprimir los errores 
    switch(st) {
    case ST_OK:
      printf("ST_OK\n");
      break;

    case TODO_MAL:
      printf("TODO_MAL\n");
      break;
    
    case ST_HELP:
      printf("ST_HELP\n");
      break;

    case ST_ERR_INSUFFICIENT_ARGUMENTS:
      printf("ST_ERR_INSUFFICIENT_ARGUMENTS\n");
      break;

    case ST_ERR_TOO_MANY_ARGUMENTS:
      printf("ST_ERR_TOO_MANY_ARGUMENTS\n");
      break;
    
    case ST_ERR_NULL_PTR:
      printf("ST_ERR_NULL_PTR\n");
      break;
    
    case ST_ERR_UNKNOWN_ARGUMENT:
      printf("ST_ERR_UNKNOWN_ARGUMENT\n");
      break;

    case ST_ERR_INVALID_WIDTH:
      printf("ST_ERR_INVALID_WIDTH\n");
      break;

    case ST_ERR_INVALID_HEIGHT:
      printf("ST_ERR_INVALID_HEIGHT\n");
      break;

    case ST_ERR_INVALID_SEED:
      printf("ST_ERR_INVALID_SEED\n");
      break;

    case ST_ERR_INVALID_N:
      printf("ST_ERR_INVALID_N\n");
      break;

    case ST_ERR_NO_MEM:
      printf("ST_ERR_NO_MEM\n");
      break;
    
    default:
      printf("NOSE_CUAL_ERROR_ES\n");
    }
}

typedef enum {
    ARG_HELP_LONG,
    ARG_HELP_SHORT,
    ARG_WIDTH_LONG,
    ARG_WIDTH_SHORT,
    ARG_HEIGHT_LONG,
    ARG_HEIGHT_SHORT,
    ARG_SEED_LONG,
    ARG_SEED_SHORT,
    ARG_N,
} arg_t;

static const char *valid_args[] = {
    [ARG_HELP_LONG] = "--help",
    [ARG_HELP_SHORT] = "-h",
    [ARG_WIDTH_LONG] = "--width",
    [ARG_WIDTH_SHORT] = "-w",
    [ARG_HEIGHT_LONG] = "--height",
    [ARG_HEIGHT_SHORT] = "-H",
    [ARG_SEED_LONG] = "--seed",
    [ARG_SEED_SHORT] = "-s",
    [ARG_N] = "-n",
};

void print_help() {
  printf("/////////////////////////\nDebes pasar los argumentos de la siguiente forma al correr la funcion en la linea de comando: ./tp1 --argumento1 valor1 --argumento2 valor2 --argumento3 valor3 \n/////////////////////////\nLos argumentos a disposicion son:\n/////////////////////////\n--help o -h: imprime este mensaje de ayuda, es el unico argumento que no se acompaña con un valor.\n/////////////////////////\n--width o -w: cantidad de pixeles de ancho de la grilla de pokemones. Solamente numeros enteros mayores a 1.\n/////////////////////////\n--height o -H: cantidad de pixeles de alto de la grilla de pokemones. Solamente numeros enteros mayores a 1. Además width*height<268,000,000 para que todas los pokemones ataquen en todas las rondas. Valores grandes pueden alentizar el programa considerablemente\n/////////////////////////\n--seed o -s: semilla para la funcion randomizada de posicionamiento de pokemones. numeros enteros por favor.\n/////////////////////////\n-n: intervalo de impresión de mensajes PPM, en turnos. Numeros naturales, o el numero -1 para imprimir solamente la primera y última generacion.\n/////////////////////////\nSe deben pasar si o si los argumentos de width, height, seed, y n, sea en su formato largo (ej. --width) o corto (ej. -w) acompañados cada cual por un valor. El argumento --help no es obligatorio, y en el caso de ser usado también es irrelevante si se pasaron los demás argumentos ya que no se correrá el programa y se imprimirá este mensaje nada mas.\nSuerte y éxitos.");
}

void print_matriz(int **matrizTipos,int width,int height){
    printf("\n\n\n\n\n");
    for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
        printf(" %d ",matrizTipos[i][j]);
      }
      printf("\n");
    }
    printf("\n\n\n\n\n");
}

void print_matriz_d(double **matrizTipos,int width,int height){
    printf("\n\n\n\n\n");
    for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
        printf(" %lf ",matrizTipos[i][j]);
      }
      printf("\n");
    }
    printf("\n\n\n\n\n");
}

status_t parse_arguments(int argc, char *argv[], int *width, int *height, int *seed, int *n)
{
   char *pend = NULL;
   int _width;
   int _height;
   int _seed;
   int _n;
   int arg;
   bool width_processed = false;
   bool height_processed = false;
   bool seed_processed = false;
   bool n_processed = false;

    if (argc < 9) { // "./tp1" + 4*2, deben ser 9, almenos que se haya pasado el argumento de --help.
        for (int i = 1; i < argc; ++i) { 
            if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
                print_help();
                return ST_HELP;
            }
        }
        return ST_ERR_INSUFFICIENT_ARGUMENTS;
    }

    if (argc > 10) {// puede o no estar además el --help o -h, además de los otros 9 que considero necesarios.
        return ST_ERR_TOO_MANY_ARGUMENTS;
    }

    if ((NULL == argv) || (NULL == width) || (NULL == height) || (NULL == seed) || (NULL == n)) {
        return ST_ERR_NULL_PTR;
    }
    
    if ((argc == 10 && ((!strcmp(argv[9],"--help")) || (!strcmp(argv[9],"-h")))) || (argc == 9 && ((!strcmp(argv[8],"--help")) || (!strcmp(argv[8],"-h"))))) { //considera caso especial donde se pasa --help o -h como último argumento
        print_help();
        return ST_HELP;
    }
    //ahora hay 9 o 10 args y ni --help ni -h son el último.
    for (int i = 1; i < argc - 1; ++i) { 
      
        for (arg = 0; arg < sizeof(valid_args) / sizeof(valid_args[0]); ++arg) {
            if (!strcmp(argv[i], valid_args[arg])) {
                break;
            }
        }
        switch (arg) 
        {
            case ARG_HELP_LONG:
            case ARG_HELP_SHORT:
                print_help();
                return ST_HELP;
            case ARG_WIDTH_LONG:
            case ARG_WIDTH_SHORT:
                i++;
                _width = strtod(argv[i], &pend);
                if (('\0' != *pend) || (_width<2)) {
                    return ST_ERR_INVALID_WIDTH;
                }
                width_processed = true;
                break;
            case ARG_HEIGHT_LONG:
            case ARG_HEIGHT_SHORT:
                i++;
                _height = strtod(argv[i], &pend);
                if (('\0' != *pend) || (_height<2)) {
                    return ST_ERR_INVALID_HEIGHT;
                }
                height_processed = true;
                break;
            case ARG_SEED_LONG:
            case ARG_SEED_SHORT:
                i++;
                _seed = strtod(argv[i], &pend);
                if ('\0' != *pend) {
                    return ST_ERR_INVALID_SEED;
                }
                seed_processed = true;
                break;
            case ARG_N:
                i++;
                _n = strtod(argv[i], &pend);
                if (('\0' != *pend) || (_n<-1) || (_n==0)) {
                    return ST_ERR_INVALID_N;
                }
                n_processed = true;
                break;
            default:
                return ST_ERR_UNKNOWN_ARGUMENT;
          }
    }

    if ((width_processed == false) || (height_processed == false) || (seed_processed == false) || (n_processed == false)) {
        return ST_ERR_INSUFFICIENT_ARGUMENTS;
    }

    *width = _width;
    *height = _height;
    *seed = _seed;
    *n = _n;
    
    return ST_OK;
}

void int_matrix_free(int ***matrix, int height, int width)
{
    if (NULL != matrix) {
        if (NULL != *matrix) {
            for (size_t i = 0; i < height; ++i) {
                free((*matrix)[i]);
                (*matrix)[i] = NULL;
            }
        }
        free(*matrix);
        *matrix = NULL;
    }
}

void double_matrix_free(double ***matrix, int height, int width)
{
    if (NULL != matrix) {
        if (NULL != *matrix) {
            for (size_t i = 0; i < height; ++i) {
                free((*matrix)[i]);
                (*matrix)[i] = NULL;
            }
        }
        free(*matrix);
        *matrix = NULL;
    }
}

int **crear_matriz_dinamica_de_ceros(int width, int height)
{
    int **matrix = NULL;

    matrix = (int **) calloc(height, sizeof(int *));
    if (NULL == matrix) {
        return NULL;
    }

    for (int i = 0; i < height; ++i) {
        matrix[i] = calloc(width, sizeof(int));
        if (NULL == matrix[i]) {
            int_matrix_free(&matrix, i, width);
            return NULL;
        }
    }

    return matrix;
}

double **crear_matriz_de_HP(int width, int height,double hp){
    
    double **matrix=NULL;
    
    matrix =(double **)calloc(height,sizeof(double *));
    if(NULL==matrix){
      return NULL;
    }
    for (int i = 0;i<height;i++){
        matrix[i] = calloc(width, sizeof(double));
        if (NULL == matrix[i]) {
            double_matrix_free(&matrix, i, width);
            return NULL;
        }
        for(int j=0;j<width;j++){
            matrix[i][j]=hp;
        }
    }
    return matrix;
}

static double multiplicador_de_ataque[15][15]= 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1},
  {1,0.5,0.5,1,2,2,1,1,1,1,1,2,0.5,1,0.5},
  {1,2,0.5,1,0.5,1,1,1,2,1,1,1,2,1,0.5},
  {1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5},
  {1,0.5,2,1,0.5,1,1,0.5,2,0.5,1,0.5,2,1,0.5},
  {1,1,0.5,1,2,0.5,1,1,2,2,1,1,1,1,2},
  {2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1},
  {1,1,1,1,2,1,1,0.5,0.5,1,1,2,0.5,0.5,1},
  {1,2,1,2,0.5,1,1,2,1,0,1,0.5,2,1,1},
  {1,1,1,0.5,2,1,2,1,1,1,1,2,0.5,1,1},
  {1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1},
  {1,0.5,1,1,2,1,0.5,2,1,0.5,2,1,1,0.5,1},
  {1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1},
  {0,1,1,1,1,1,1,1,1,1,0,1,1,2,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
};

void llenar_de_pokemones(int **grillapointer,int width, int height, int seed) {
    int i;
    int j;
    srand((unsigned)seed); 
    for (i=0;i<height;i++){
      for(j=0;j<width;j++){
        grillapointer[i][j]=rand()%16; //como hay 14 tipos, se tomara al numero 15 como representación de una celda vacía. Se especifica esto en los pokeType enums.
      }
    }
      
      
}

status_t una_ronda_de_ataques(int **grillatipos,double **grillahp,int width,int height,int seed,double hp,int extraseed) {
  //En mi version del automata celular una ronda se define como el ciclo de tiempo durante el cual cada celda logra atacar a cada uno de sus ocho (maximo) vecinos una sola vez. El orden de atacantes y defensores se determina con srand() y rand(), para lo cual armamos un array de todos los ataques posibles (incluyendo los ataques de los pokemones que se van de pista afuera de la grilla, para simplificar el procedimiento, y en estos casos se omite el ataque), y vamos achicando el array a los ataques restantes. Este procedimiento alentiza el automata al usar matrices grandes, pero a cambio nos da el placer de saber que es equitativo hacia cualquier pokemon, sea donde sea que nazca en la grilla. 
  
  int i;
  int x;
  srand(seed+extraseed);
  int cant_ataques=width*height*8;  //se da por sentado que se corre el programa en sistema de 32 o 64bits e int almacena 4 bytes. Con esto width y height pueden tener un máximo de 16000 aprox cada uno.
  int *ataques=NULL;
  ataques=(int*)malloc(cant_ataques*sizeof(int));
  if (NULL==ataques){
    return ST_ERR_NO_MEM;
  }
  for(i=0;i<cant_ataques;i++){
    ataques[i]=i;
  }

  int fil_atac;
  int col_atac;
  int direc_atac;
  int fil_def;
  int col_def;
  //voy usando los ataques dela lista de los ataques posibles, y eliminandolos a medida que se usan.
  for(i=cant_ataques;i>0;i--){
    x=rand()%i;
    fil_atac=ataques[x]/(8*width);//floor division de enteros
    col_atac=(ataques[x]%(8*height))/8;
    direc_atac=ataques[x]%8;//en qué direccion ataca el pokemon atacante (tiene 8 opciones)

    switch(direc_atac){
      case 0:
        fil_def=fil_atac-1;
        col_def=col_atac-1;
        break;
      case 1:
        fil_def=fil_atac-1;
        col_def=col_atac;
        break;
      case 2:
        fil_def=fil_atac-1;
        col_def=col_atac+1;
        break;
      case 3:
        fil_def=fil_atac;
        col_def=col_atac-1;
        break;
      case 4:
        fil_def=fil_atac;
        col_def=col_atac+1;
        break;
      case 5:
        fil_def=fil_atac+1;
        col_def=col_atac-1;
        break;
      case 6:
        fil_def=fil_atac+1;
        col_def=col_atac;
        break;
      case 7:
        fil_def=fil_atac+1;
        col_def=col_atac+1;
        break;
    }
    //if(defensor fuera de grilla o atacante esta vacío) {no atacar, pero sacar ataque de la lista}
    if((fil_def<0) || (fil_def>=height) || (col_def<0) || (col_def>=width) || (grillatipos[fil_atac][col_atac]==15)){
      ataques[x]=ataques[i-1];
      continue;
    }
    //if defensor esta vacio heredar sin ataque
    if(grillatipos[fil_def][col_def]==15){
      grillatipos[fil_def][col_def]=grillatipos[fil_atac][col_atac];
      grillahp[fil_def][col_def]=hp;
      ataques[x]=ataques[i-1];
      continue;
    }
    
    //ataque
    grillahp[fil_def][col_def]-=multiplicador_de_ataque[grillatipos[fil_atac][col_atac]][grillatipos[fil_def][col_def]];
    
    //heredar el tipo si muere el defensor y resetear hp
    if(grillahp[fil_def][col_def]<=0){
      grillatipos[fil_def][col_def]=grillatipos[fil_atac][col_atac];
      grillahp[fil_def][col_def]=hp;
    }
    
    ataques[x]=ataques[i-1];
  }
  free(ataques);
  return ST_OK;
}

void print_ppm_to_terminal(int **matrizTipos,int width,int height,int ronda_num){
    printf("\n\n\n\n\n");
    printf("PPM formato texto, ronda numero %d, prox línea:\n",ronda_num);
    printf("P3 %d %d 255",width,height);
    for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
        printf(" %d %d %d",colores[matrizTipos[i][j]].r,colores[matrizTipos[i][j]].g,colores[matrizTipos[i][j]].b);
      }
    }
    printf("\n\n\n\n\n");

}



int main(int argc, char *argv[]) {

  // argumentos a recibir, valores predeterminados y counters
  int width;
  int height;
  int seed;
  int n;
  int cant_rondas=10;
  double hp=2;
  int i;
  
  // parse args
  status_t st = parse_arguments(argc, argv, &width, &height, &seed, &n);
  if (ST_HELP == st) {
    return EXIT_SUCCESS;
  }
  else if (ST_OK != st) {
    print_err(st);
    return EXIT_FAILURE;
  } 
  
  // crear matriz vacía
  int **matrizTipos=NULL;
  matrizTipos=crear_matriz_dinamica_de_ceros(width,height);
  if (matrizTipos==NULL){
    print_err(ST_ERR_NO_MEM);
    return ST_ERR_NO_MEM;
  }
  
  
  // llenar la matriz con tipos de pokemones de manera random con seed
  
  llenar_de_pokemones(matrizTipos,width,height,seed);
  
  
  // construir matriz de health points
  double **matrizHP=NULL;
  matrizHP=crear_matriz_de_HP(width,height,hp);
  if (matrizHP==NULL){
    print_err(ST_ERR_NO_MEM);
    return ST_ERR_NO_MEM;
  }

  
  // se llevan a cabo las m rondas de ataques
  
  for(i=0;i<cant_rondas;i++){
    st=una_ronda_de_ataques(matrizTipos,matrizHP,width,height,seed,hp,i);
    if (ST_OK != st) {
      print_err(st);
      return st;
    } 
    
    if (i%n==0){
      print_ppm_to_terminal(matrizTipos,width,height,i);
    }
    
  }
  
  free(matrizTipos);
  free(matrizHP);
  return EXIT_SUCCESS;
}
