Autor: Diego Villarraza - Octubre 2020
## Introduccion 🚀

Esta aplicación fue creada para el trabajo final de la asignatura Desarrollo de Aplicaciones 3 para Iot de la carrera de Especialización de Internet de las Cosas de FIUBA.

## 
## Tabla de contenido
* [Descripción del Sistema](#descripción-del-sistema)
* [Descripción del Hardware](#descripcion-del-hardware)
* [Arquitectura del Sistema](#arquitectura-del-sistema)

## 
## Descripción del Sistema 📋
El sistema consta de tres partes las cuales se decriben a continuación:

 * Servidor MQTT

    Servidor Mosquitto corriendo de manera local en una raspberryPi4 que intercatua con dos Esp32.

 * Aplicacion On-line
 
    Esta aplicacion esta desarrollada en Node-Red en la cual se subscriben a los mensajes MQTT de los esp32 y se almacenan los datos en una base de datps sqlite. En el dashboard de node-red se muestran los valores de temperatura, humedad del dht y el estado del led incoprado en el esp32

 * Aplicacion Web

    Esta aplicacion es una SPA (aplicacion de una sola pagina) donde se utiliza Vue.js para el desarrollo del front-end y el back-end es una Api desarrollada con Laravel

## 
## Descripción del Hardware 📋
El hardware utilizando, el cual se muestra en la figura 1 consta de: 

 - Raspberry PI 4, donde corre el broker mqtt y las aplicaciones.

 - Dos ESP32 los cuales tienen conectado un sensor de temperatura y humedad DHT.


 ![arquitectura](Doc/DDA_Hardware.png)



## 
## Arquitectura del Sistema 📋
Los componentes del sistema son:
 * Servidor MQTT
 * Aplicación on-line para el almacenamiento de los datos
 * Aplciación Web



