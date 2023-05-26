
/* 
Problema:		Sistema Lineal de Ecuaciones.
Analista:		Juan Carlos Moya Garcia (0090-12841)
Curso:			(0769) Introduccion a la programacion de Computadoras
Descripcion:	Solucion de Sistema lineal de Ecuaciones n x m, utilizando el Metodo de reduccion de Gauss-Jordan.
*/


#include<stdio.h>
#include <stdlib.h> //Necesaria por la utilidad de atof como convertidor de char a int

#define DATOS "datosMatriz.dat" //Definiendo el archivo de datos
#define LONGITUD 250 			//Definiendo el tamano de la base de datos de matriz

//Area de declaracion de arreglos
void imprimir(int filas, int columnas, double * );
void pivotear(int filas, int columnas, double *, double*, double*,int j);

void main(int arguments,  //Argumentos de la aplicacion
		  char *argumentsRow[]){  

	system("clear"); //Limpieza de pantalla

	FILE* datosMatriz = fopen(DATOS, "r"); //Apertura de archivo DATOS
	
	for (int i = 0; i < arguments; i++){} //Inicializando los argumentos
	
	int filas = atof(argumentsRow[1]);	  //Definicion de "n"
	int 		 columnas = filas + 1;	  //Definicion de "m"
	int 	   datos = filas*columnas;	  //Determinacion de cantidad de datos para matriz
	char 			  bufer[LONGITUD];	  //Arreglo temporal para los datos obtenidos
	double   matrizA[filas][columnas];	  //Matriz principal
	int                  contador = 0;
	double            tempA[LONGITUD];	  //Matriz temporal de contencion de datos
	
	while(!feof(datosMatriz)){			  //proceso de lectura de datos
		fscanf(datosMatriz,"%s",bufer);
		tempA[contador] = atof(bufer);
		contador++;
	}
	
	int contador1 = 0;					   //Llenado de matriz principal con los datos	
	for(int i = 0;i < filas; i++){
		for(int j = 0; j < columnas; j++){
			matrizA[i][j] = tempA[contador1];
			contador1++;
		}
	}
	
	// Impresion de la matriz inicial
	printf("\n   ------ Sistema lineal de ecuaciones ------\n"); 
	printf("   ------            [%d]x[%d]           ------\n", filas, (columnas-1));
	imprimir(filas,columnas,&matrizA[0][0]);
	printf("\n\n");
	
	//Desarrollo de Metodo reduccion de Gauss-jordan
	
	double pivoteaux = 0;
	double vectorPivote[columnas];
	double vectorPivoteaux[columnas];
	double n = 0;
    

    for(int j =0; j<columnas-1;j++)//Desarrollo de tecnica de pivote en metodo Gauss Jordan
    { 
    	pivotear(filas, columnas,&matrizA[0][0], &vectorPivote[0], &vectorPivoteaux[0], j); //Desarrollo de tecnica de pivote
    	
    	for(int i = 0; i<filas; i++) //este proceso es necesario para evitar que la columna de resultados se vea afecdtada
        {
			if (i != j && j < columnas-1){
         		n = matrizA[i][j];	
        	}
        		for(int k = 0; k < columnas; k++){
					matrizA[i][k] = (-1*n*vectorPivote[k]) + matrizA[i][k];
				}
					if(i == j ){ // proceso necesario para evitar alteraciones en la fila pivote
						for(int l = 0; l < columnas; l++){
						matrizA[i][l] = vectorPivoteaux[l];
							if(matrizA[i][l] == -0){
								matrizA[i][l] = 0;
							}			
						}	 	
					}		
    	}        		
    }
    
    // Impresion de Matriz solucionada
    printf("\n -------- Solucion Gauss Jordan --------\n");
    imprimir(filas,columnas,&matrizA[0][0]);
    printf("\n");
    
    // Impresion de Resultados finales	
    printf("\n   ------ Resultados finales ------\n\n");
    int m = 1;
    double tempVector[columnas];
    for(int i = 0; i<filas; i++){
    	tempVector[i] = matrizA[i][columnas-1];
    	printf("         x(%d) =\t%0.1lf,  \n", m, tempVector[i]);
    	m++;
    } printf("\n");
    
   
    for(int k = 0; k < columnas; k++){ //Limpiador de basura ....
	     vectorPivote[k] = 0;
	}
}			

//Proceso central de impresiones multiples
void imprimir(int filas, int columnas, double * matrizA){
	printf("\n\n");
	int contar = 0;
	printf("|");   
	for(int i = 0; i<filas*columnas; i++){		
		if(contar < columnas){
			printf(" %0.1lf,\t ",matrizA[i]);
			contar++;
		}
			else {	
				printf("|");
				contar = 0;
				printf("\n|");
				printf(" %0.1lf,\t ",matrizA[i]);
				contar++;
			}
	} printf("|");
}

//Desarrollo de proceso de pivoteo entre matriz
//Este tecnica fue encontrada en la red, y solo se modifico para obtener los datos de este proyecto
void pivotear(int filas, int columnas, double *matrizA, double *vectorPivote, double *vectorPivoteaux, int j)
{
	double pivoteaux = 0;
	double matrizTemporal[filas][columnas];
	int sumi = 0;
	//Copiamos los datos de la matrizA  a una matriz temporal porque al enviarla como apuntador esta se convierte en un vector.
	for (int  i =  0; i < filas; i++){
		for( int k = 0; k < columnas; k++){
			matrizTemporal[i][k] = matrizA[sumi];
			sumi ++;
		}
	}
	//Una vez copiados los datos en una matriz temporal operamos para obtener el pivote y su fila asociada
	for(int i = 0; i<filas;i++){
		if(i == j ){
		 	// Suponemos que el pivote esta en la posicion (i,j) y lo calculamos dividiendo el numero en esa posicion entre si mismo.
				pivoteaux = matrizTemporal[i][j];
			// En la matriz temporal realizamos la division de toda la fila donde se encuentra el pivote y la guardamos en la matriz temporal y en dos vectores que usaremos mas tarde.	
			for(int l = 0; l < columnas; l++){
				matrizTemporal[i][l] = matrizTemporal[i][l] / pivoteaux;
				vectorPivote[l] = matrizTemporal[i][l];
				vectorPivoteaux[l] = matrizTemporal[i][l];
			}		
		 }
	}
	//Luego pasamos los datos de la matriz temporal a nuestra matriz de trabajo MA.
	sumi = 0;
	for (int  i =  0; i < filas; i++){
		for( int k = 0; k < columnas; k++){
			matrizA[sumi] = matrizTemporal[i][k];
			sumi++;
		}
	}
}
