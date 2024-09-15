float calcular_amplitud_onda(int valores_ondas[]){
  /*La funcion recibe valores globales (contador).
    Recibe un arreglo dinamico.
    Retorna el valor de la frecuencia.*/
    int mayor = 0;
    int menor = 0;

    int a = 0;
    int b = 0;

    for (int y = 0; y < contador; y++){

        if(valores_ondas[y] < 0){
            if(valores_ondas[y + 1] > valores_ondas[y]){
                //Solo se debe cumplir 1 vez (en cierta cantidad de datos).
                if (a == 0){
                    mayor++;
                    a = 1;
                }
            }else{
                a = 0;
            }
        }
        if (valores_ondas[y] > 0){
            if(valores_ondas[y + 1] < valores_ondas[y]){
                //Solo se debe cumplir 1 vez (en cierta cantidad de datos).
                if(b == 0){
                    menor++;
                    b = 1;
                }
            }else{
                b = 0;
            }
        }
    }

    float operacion = (mayor + menor) / 2;//Calcula el numero de ciclos.
    return operacion;
}
