float calcular_amplitud_onda(int valores_ondas[]){
  /*La funcion recibe valores globales (contador).
    Recibe un arreglo dinamico.
    Retorna un float del valor de amplitud.*/
    int mayor = 0;
    int menor = 0;

    for (int i = 0;  i < contador; i++){

        if (valores_ondas[i] > mayor){
            mayor = valores_ondas[i];

        }
        if (menor == 0){
            menor = valores_ondas[i];

        }else{

            if (valores_ondas[i] < menor){
                menor = valores_ondas[i];
            }
        }
    }
    float operacion = (mayor - menor)/2;
    operacion = operacion / 100;//Convertir en V.

    return operacion;
}


