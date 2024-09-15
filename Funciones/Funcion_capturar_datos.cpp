void guardar_datos(int valores_ondas[], int &datos_ondas){
    //Recibe un arreglo dinamico y un dato por referencia.
    datos_ondas = analogRead(A1);

    valores_ondas[contador] = datos_ondas;
    contador += 1;

    Serial.println(datos_ondas);
}
