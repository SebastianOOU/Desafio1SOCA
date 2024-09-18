void definir_tipo_onda(int* ptr_dato, int cont1, int cont2, bool cuadrada){

    int b = cont1 - cont2;

    if (cont1 == cont2){
        *ptr_dato = 1;
    }
    if(b == 1 || b == -1){
        *ptr_dato = 2;
    }
    if (cuadrada){
        *ptr_dato = 3;
    }
}
