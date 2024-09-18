#include <LiquidCrystal.h>
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
//Funciones_programa.
float calcular_amplitud_onda(int []);
int calcular_frecuencia_onda(int []);
bool es_onda_cuadrada(int [], int);
int calcular_tipo_triangular_senoidal(int[]);
void guardar_datos(int [],int &);
void definir_tipo_onda(int*, int, int, bool);
void print_datos_onda(float, int, int);
void print_bienvenida();

int contador = 0;

void setup(){

    Serial.begin(9600);
    lcd_1.begin(16, 2);

    pinMode(7, INPUT_PULLUP);//Boton 1
    pinMode(8, INPUT_PULLUP);//Boton 2
    pinMode(A1, INPUT);//Entrada datos ondas

    print_bienvenida();
}

//MAIN
void loop(){

    int boton1 = digitalRead(7);

    int datos_ondas = analogRead(A1);
    Serial.println(datos_ondas);

    if (boton1 == 0){

        lcd_1.clear();
        lcd_1.setCursor(0, 0);lcd_1.print("Capturando");
        lcd_1.setCursor(8, 1);lcd_1.print("datos...");
        //Arreglo_dinamico guarda los valores de las ondas.
        int *valores_ondas = new int[600];

        while(true){

            if (contador > 600){

                lcd_1.clear();
                lcd_1.setCursor(0, 0);lcd_1.print("-----Alerta------");
                lcd_1.setCursor(2, 1);lcd_1.print("Llego a tope");
                delay(3000);

                delete[] valores_ondas;
                contador = 0;

                print_bienvenida();

                break;
            }

            guardar_datos(valores_ondas,datos_ondas);
            int boton2 = digitalRead(8);

            if (boton2 == 0){

                lcd_1.clear();
                lcd_1.setCursor(0, 0);lcd_1.print("Procesando");
                lcd_1.setCursor(8, 1);lcd_1.print("datos...");

                int dato = 0;
                int *ptr_dato = &dato;

                float amplitud = calcular_amplitud_onda(valores_ondas);
                int frecuencia = calcular_frecuencia_onda(valores_ondas);
                calcular_tipo_triangular_senoidal(valores_ondas,ptr_dato);
                print_datos_onda(amplitud,frecuencia,dato);

                delete[] valores_ondas;
                contador = 0;
                break;
            }
        }
    }
}

//FUNCIONES________________________________________________________________________

void guardar_datos(int valores_ondas[], int &datos_ondas){

    datos_ondas = analogRead(A1);

    valores_ondas[contador] = datos_ondas;
    contador += 1;

    Serial.println(datos_ondas);
}

int calcular_frecuencia_onda(int valores_ondas[]){
    /*La funcion recibe valores globales (contador).
  Recibe un arreglo dinamico.
  Retorna el valor de la frecuencia.*/
    int mayor = 0;
    int menor = 0;

    bool opcion1 = false, opcion2 = false;

    for (int i = 0; i < contador; i++){

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

float calcular_amplitud_onda(int valores_ondas[]){
    /*La funcion recibe valores globales (contador).
    Recibe un arreglo dinamico.
    Retorna un float del valor de amplitud.*/
    int mayor = 0;
    int menor = 0;

    for (int i = 0;  i < contador; i++){
        delay(5);

        if (mayor == 0){
            mayor = valores_ondas[i];

        }else{

            if (valores_ondas[i] > mayor){
                mayor = valores_ondas[i];
            }
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

bool es_onda_cuadrada(int muestras[], int num_muestras) {
    int valor_maximo = muestras[0];
    int valor_minimo = muestras[0];

    for (int i = 1; i < num_muestras; i++) {
        if (muestras[i] > valor_maximo) {
            valor_maximo = muestras[i];
        }
        if (muestras[i] < valor_minimo) {
            valor_minimo = muestras[i];
        }
    }

    for (int i = 0; i < num_muestras; i++) {
        if (muestras[i] != valor_maximo && muestras[i] != valor_minimo) {
            return false;
        }
    }
    return true;
}

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

void print_datos_onda(float operacion1, int operacion2, int operacion3){

    lcd_1.clear();
    lcd_1.setCursor(3, 0);
    lcd_1.print("Tipo onda:");
    lcd_1.setCursor(3, 1);

    if (operacion3 == 1){
        lcd_1.print("Triangular");
    }else if(operacion3 == 2) {
        lcd_1.setCursor(4, 1);
        lcd_1.print("Senoidal");
    }else if(operacion3 == 3){
        lcd_1.print("Cuadrada");
    }else{
        lcd_1.setCursor(2, 1);
        lcd_1.print("Desconocida");
    }
    delay(2500);

    lcd_1.clear();
    lcd_1.setCursor(3, 0);
    lcd_1.print("Amplitud:");
    lcd_1.setCursor(5, 1);
    lcd_1.print(operacion1);
    lcd_1.print("V");
    delay(2500);

    lcd_1.clear();
    lcd_1.setCursor(3, 0);
    lcd_1.print("Frecuencia:");
    lcd_1.setCursor(6, 1);
    lcd_1.print(operacion2);
    lcd_1.print(" Hz");
    delay(2500);

    print_bienvenida();
}

void print_bienvenida(){

    lcd_1.setCursor(1, 0);
    lcd_1.print("- wave  data -");
    lcd_1.setCursor(3, 1);
    lcd_1.print("Bienvenido");
}
