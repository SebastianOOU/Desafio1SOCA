#include <LiquidCrystal.h>
void amplitud_onda();
int amplitud = 0;
int *valores_ondas = new int[500];
int contador = 0;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

int datos_ondas = 0;

void setup()
{
    lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
    Serial.begin(9600);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(A1, INPUT);

    // Print a message to the LCD.
    lcd_1.print("hello world!");
}

void loop()
{
    int opcion = digitalRead(7);
    int opcion2 = digitalRead(8);
    datos_ondas = analogRead(A1);
    Serial.println(datos_ondas);


    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting
    // begins with 0):
    if (opcion == 0){
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Capturando");
        lcd_1.setCursor(8, 1);
        lcd_1.print("datos...");
        while(true){
            datos_ondas = analogRead(A1);
            int opcion2 = digitalRead(8);
            amplitud_onda();
            contador += 1;
            Serial.println(datos_ondas);

            if (opcion2 == 0){
                float mayor = 0;
                for (int i = 0;  i < contador; i++){

                    if (valores_ondas[i] > mayor){
                        mayor = valores_ondas[i];

                    }
                }
                mayor = mayor / 100;
                lcd_1.clear();
                lcd_1.print("Amplitud:");
                lcd_1.print(mayor);lcd_1.print("V");
                delete[] valores_ondas;
                contador = 0;
                break;
            }

        }
    }

}

void amplitud_onda(){

    valores_ondas[contador] = datos_ondas;


}
