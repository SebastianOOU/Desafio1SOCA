#include <LiquidCrystal.h>
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void guardar_datos();
float calcular_amplitud_onda();
void print_amplitud(float);

int *valores_ondas = new int[500];
int contador = 0;
int datos_ondas = 0;

void setup(){

    Serial.begin(9600);
    lcd_1.begin(16, 2);

    pinMode(7, INPUT_PULLUP);//Boton 1
    pinMode(8, INPUT_PULLUP);//Boton 2
    pinMode(A1, INPUT);//Entrada datos ondas

    lcd_1.setCursor(1, 0);
    lcd_1.print("- wave  data -");
    lcd_1.setCursor(3, 1);
    lcd_1.print("Bienvenido");
}

//MAIN
void loop(){

    int boton1 = digitalRead(7);
    datos_ondas = analogRead(A1);
    Serial.println(datos_ondas);

    if (boton1 == 0){

        lcd_1.clear();
        lcd_1.setCursor(0, 0);lcd_1.print("Capturando");
        lcd_1.setCursor(8, 1);lcd_1.print("datos...");

        while(true){

            guardar_datos();
            int boton2 = digitalRead(8);

            if (boton2 == 0){

                float amplitud = calcular_amplitud_onda();
                print_amplitud(amplitud);

                delete[] valores_ondas;
                contador = 0;
                break;
            }
        }
    }
}

void guardar_datos(){

    datos_ondas = analogRead(A1);

    valores_ondas[contador] = datos_ondas;
    contador += 1;

    Serial.println(datos_ondas);
}

float calcular_amplitud_onda(){

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
    operacion = operacion / 100;

    return operacion;
}

void print_amplitud(float operacion){

    lcd_1.clear();
    lcd_1.print("Amplitud:");
    lcd_1.print(operacion);
    lcd_1.print("V");
}
