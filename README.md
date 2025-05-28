# ⚠️Importante 
Esta tienda de electronica está destinada a hacer compras onlines nediante PayPal, y está destinada a usuarios no comerciales, la modificación del código es con fines éticos. El propietario de este código Steven Alcívar no se responsabiliza del mal uso de este cófigo.

## 🚀 Caracteristicas 
- Gestión de Productos a traves de c++.
- Base de datos para datos escenciales del historial en PostgreSQL y Python.
- Historial Completo automático mediante un archivo de texto (.txt).
- Pagos mediante Paypal y parámetros personalizados a través de python mediante el archivo 'config.py'.
- 
## 💻 Requisitos
- Windows 10 o superior (compatible con PostgreSQL y Python).
- Tener PostgreSQL instalado (Esto será útil para almacenar información escencial de historial, como datos personales y total) Además se aprovechará su generación de ID para generar el número de factura.
- Tener el interprete de python para mostrar el historial a traves de la terminal.
- Tener el compilador de C++.

## 🛠️Instalación
1. Clone el repositiorio con `git clone https://github.com/StevenAC369/Tienda-Online`
2. Cree su usuario en PostgrSQL y añada sus datos en el archvio config.py para la conexión con la base de datos
3. Acceda mediante la terminal al direcotio clonado `cd Tienda-Onlne`
4. Para instalar los modulos python es recomendable usar un entorno virtual del mismo en el repositiorio clonado.
5. Instale los modulos de python necesario con `pip install -r requirements.txt`
6. Una vez configurado todo lo anterior correctamente, puede compilar el programa y ejecutarlo sin problemas.
7. Puede crear la base de datos y la tabla a traves del programa, con la opcion 5, es recomendable que el programa se encargue de esto para evitar problemas.
