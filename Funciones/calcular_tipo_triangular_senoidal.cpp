void calcular_tipo_triangular_senoidal(int valores_ondas[], int *ptr_dato){
    /*La funcion recibe valores globales (contador).
  Recibe un arreglo dinamico y un puntero.
  */
    int cont1 = 0;
    int cont2 = 0;

    bool opcion1 =false, opcion2 = false, opcion3 = false;

    for (int i = 0; i < contador; i++){

        if (valores_ondas[i] >= 0 && valores_ondas[i - 1] < 0){
            if (opcion2){
                opcion3 = true;
                opcion2 = false;

            }else{
                opcion1 = true;
            }
        }
        if(opcion1 && valores_ondas[i] < 0){
            opcion1 = false;
            opcion2 = true;
        }
        if(opcion3 && valores_ondas[i] < 0){
            break;
        }
        if (opcion1){
            cont1++;
        }
        if (opcion3){
            cont2++;
        }
    }
    bool cuadrada = es_onda_cuadrada(valores_ondas, contador);
    definir_tipo_onda(ptr_dato, cont1, cont2, cuadrada);
}
