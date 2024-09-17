void print_datos_onda(float operacion1, int operacion2/*, int operacion3*/){

    lcd_1.clear();
    lcd_1.setCursor(3, 0);
    lcd_1.print("Tipo onda:");
    lcd_1.setCursor(5, 1);
    lcd_1.print(operacion1);
    lcd_1.print("V");
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
}
