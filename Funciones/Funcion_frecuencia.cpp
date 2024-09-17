int calcular_frecuencia_onda(int valores_ondas[]){
  /*La funcion recibe valores globales (contador).
    Recibe un arreglo dinamico.
    Retorna el valor de la frecuencia.*/
    int mayor = 0;
    int menor = 0;

    bool opcion1 = false, opcion2 = false;

    for (int i = 0; i < contador;  i++){

        if (valores_ondas[i] < 0){
            opcion1 = true;
        }
        if (valores_ondas[i] > 0){
            opcion2 = true;
        }
    }

    if (opcion1 && opcion2){
        opcion1 = false;
        opcion2 = false;
    }

    int a = 0, b = 0, u = 0, z = 0;

    for (int y = 0; y < contador; y++){

        if(valores_ondas[y] < 0){
            if(valores_ondas[y + 1] > valores_ondas[y]){
                //Solo se debe cumplir 1 vez (en cierta cantidad de datos).
                if (a == 0){
                    menor++;
                    a = 1;
                }
            }else{
                a = 0;
            }
            if(valores_ondas[y + 1] < valores_ondas[y] && opcion1){
                //Solo se debe cumplir 1 vez (en cierta cantidad de datos).
                if(u == 0){
                    mayor++;
                    u = 1;
                }
            }else{
                u = 0;
            }
        }
        if (valores_ondas[y] > 0){
            if(valores_ondas[y + 1] < valores_ondas[y]){
                //Solo se debe cumplir 1 vez (en cierta cantidad de datos).
                if(b == 0){
                    mayor++;
                    b = 1;
                }
            }else{
                b = 0;
            }
            if (valores_ondas[y + 1] > valores_ondas[y] && opcion2){
                //Solo se debe cumplir 1 vez (en cierta cantidad de datos).
                if (z == 0){
                    menor++;
                    z = 1;
                }
            }else{
                z = 0;
            }
        }
    }
    int operacion = (mayor + menor) / 2;

    return operacion;
}
