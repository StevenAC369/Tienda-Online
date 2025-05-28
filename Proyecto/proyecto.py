import sys
import os
import psycopg2
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
import config as config

if len(sys.argv) < 6:
    print("Error: No se recibieron suficientes argumentos.")
    sys.exit(1)
cedula = sys.argv[1]
nombres = sys.argv[2]
direccion = sys.argv[3]
celular = sys.argv[4]
fecha = sys.argv[5]
hora = sys.argv[6]
total = sys.argv[7]

conn = psycopg2.connect(
    dbname=config.DB_NAME,
    user=config.DB_USER,
    password=config.DB_PASSWORD,
    host=config.DB_HOST,
)
cursor = conn.cursor()

cursor.execute("INSERT INTO historial (cedula, fecha, hora, nombres, direccion, celular, total) VALUES (%s, %s, %s, %s, %s,%s,%s) RETURNING id", 
               (cedula, fecha, hora, nombres, direccion, celular, total))

factura_id = cursor.fetchone()[0]
n_factura = str(factura_id)

with open("Proyecto/historial_local.py", "a") as archivo:
    archivo.write("\nfactura_id = "+n_factura+"\nprint('''\033[36m------------------------------------------------------------------------------------------\n"
    "\033[32mFactura: "+n_factura+"''')")
conn.commit()
cursor.close()
conn.close()

print("Datos guardados correctamente en PostgreSQL.")