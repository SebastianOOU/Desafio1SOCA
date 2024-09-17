int calcular_tipo_triangular_senoidal(int valores_ondas[]){
  /*La función recibe valores globales (contador).
    Recibe un arreglo dinamico.
    Retorna valores (1,2 o 0) segun sea el caso.*/
    int cont1 = 0;
    int cont2 = 0;
    bool opcion1 =false, opcion2 = false, opcion3 = false;

    for (int i = 0; i < contador; i++){

        if (valores_ondas[i] >= 0 && valores_ondas[i - 1] < 0){
            if (opcion2){
                opcion3 = true;//True para segunda cresta.
                opcion2 = false;
            }else{
                opcion1 = true;//True para primer cresta.
            }
        }

        if(opcion1 && valores_ondas[i] < 0){
            opcion1 = false;
            opcion2 = true;
        }
        if(opcion3 && valores_ondas[i] < 0){
            opcion3 = false;
            break;
        }
        if (opcion1){
            cont1++;
        }
        if (opcion3){
            cont2++;
        }

    }

    int a = 0;
    int b = cont1 - cont2;
    if (cont1 == cont2){//Verifica si es Triangular.
        a = 1;
    }
    if(b != 0){//Verifica si es Senoidal.
        a = 2;
    }
    return a;
}
