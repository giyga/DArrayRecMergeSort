#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//ARREGLO DINÁMICO
typedef struct { //Definición de las propiedades del arreglo dinámico
    size_t capacidad;
    size_t tamElem;
    int* Elems;
} dArray;
dArray inicArr(size_t tamElem, int capacidad){ //Instanciar un arreglo dinámico dArray
    return (dArray){ //Por qué el nombre dArray tiene que ir entre paréntesis?
      .capacidad = capacidad,
      .tamElem = tamElem,
      .Elems = (int*)malloc(capacidad * tamElem) //Que sea int
    };
    
}
void meterElem(dArray* D, size_t tamArr, int pos, int elem){ //Añadirle elementos sin importar el índice
        if (pos >= 0 && pos < tamArr){
            *(D->Elems + pos) = elem; 
    }
        else{ //Reescalar arreglo si el índice solicitado es superior a la capacidad actual del arreglo
            D->Elems = (int*)realloc(D->Elems, (pos + 1) * D->tamElem);
            D->capacidad = pos + 1; //Importante poner el ya que capacidad ha de contar los valores a partir de 1 en vez de 0 como los iteradores
            *(D->Elems + pos) = elem;
        }
}
void sacarElem(dArray* D, size_t tamArr, int pos){
    if (pos >= 0 && pos <= tamArr){
        for(int i = pos; i < tamArr; i++){
            *(D->Elems + i) = *(D->Elems + i + 1);
        }
        D->capacidad--;
        D->Elems = (int*)realloc(D->Elems, D->capacidad * D->tamElem);
    }
}

//FUNCIÓN MERGE SORT
void Ordenar(int* Arr, int tamArr, int n){ //OJO: n como argumento SIEMPRE debe valer 1
    if(n >= ceil(tamArr/2.00)){//Ultima iteración recursiva
        int Arr1[n];
        int Arr2[tamArr - n];
        int lonArr1 = sizeof(Arr1) / sizeof(Arr1[0]);
        int lonArr2 = sizeof(Arr2) / sizeof(Arr2[0]);
        for(int i = 0; i < lonArr1; i++) {
            Arr1[i] = Arr[i];
            if(lonArr1 + i <= tamArr - 1) {
                Arr2[i] = Arr[lonArr1 + i];}
        }
        //Fusionamos por última vez
        int h = 0; //índice arr1
        int k = 0; //índice arr2

        for(int j = 0; j < tamArr; j++){
            if (Arr1[h] < Arr2[k]){
                Arr[j] = Arr1[h];
                if(h == lonArr1 - 1) Arr1[h] = Arr2[lonArr2 - 1] + 1;
                else h++;
            }
            else {
                Arr[j] = Arr2[k];
                if(k == lonArr2 - 1) Arr2[k] = Arr1[lonArr1 - 1] + 1;
                else k++;
        }
}

        printf("\nArreglo final: ");
        for(int k = 0; k < tamArr; k++) printf("%d ", Arr[k]);
    } 
    else{   
        int Arr1[n];
        int Arr2[n];
        int pos = 0;
        int lonArr1 = sizeof(Arr1) / sizeof(Arr1[0]);
        int lonArr2 = lonArr1;
        while(pos <= tamArr - 1 - n){ 
            for(int i = 0; i < n; i++){ //Llenar los arreglos para la fusión
                if(pos + i < tamArr - 1) Arr1[i] = Arr[pos + i];
                if(pos + i + n <= tamArr - 1) Arr2[i] = Arr[pos + i + n];
            }
            int h = 0;
            int k = 0;
            for(int j = 0; j < n*2; j++){ //Fusión
                if (Arr1[h] < Arr2[k]){
                    Arr[j + pos] = Arr1[h];
                    if(h == lonArr1 - 1) Arr1[h] = Arr2[lonArr2 - 1] + 1;
                    else h++;
                }
                else {
                    Arr[j + pos] = Arr2[k];
                    if(k == lonArr2 - 1) Arr2[k] = Arr1[lonArr1 - 1] + 1;
                    else k++;
                    }
                }
            pos = pos + (2*n);
        }
        printf("\nIteración: ");
        for(int i = 0; i < tamArr; i++) printf(" %d ", Arr[i]);
        Ordenar(Arr, tamArr, n * 2); //Llamada recursiva
    }
    
}

int main() {
    
    dArray Arr = inicArr(sizeof(int),1);
    int i = 0; //Por qué me da error de segmentación cuando le asigno 0 como valor?
    int nuevoElem = 0;
    bool repetido = false;
    for(;;){
        printf("Por favor digita un número entero y presiona ENTER \n(o digita 0 y ENTER para salir)\n");
        scanf("%d", &nuevoElem);
        if(nuevoElem == 0) break;
        for(int h = 0; h < Arr.capacidad; h++){
            if(Arr.Elems[h] == nuevoElem) {repetido = true;
                break;
            }
        }
        if(repetido){
            printf("por favor asegúrate de ingresar un número que no esté repetido\n");
        }
        else {meterElem(&Arr, Arr.capacidad, i, nuevoElem);
            i++;
        }
        repetido = false;
    }
    Ordenar(Arr.Elems, Arr.capacidad, 1);
    printf("\ncapacidad del arreglo: %d", (int)Arr.capacidad);
    free(Arr.Elems);
    
    return 0; //Ahora solo necesito una forma de evitar que el usuario pueda ingresar strings u otro tipo de dato
} 
