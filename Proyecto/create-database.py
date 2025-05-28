import psycopg2
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
import config as config  

def create_database():
    """Crear la base de datos y la tabla en PostgreSQL."""
    conn = psycopg2.connect(
        dbname="postgres",
        user=config.DB_USER,
        password=config.DB_PASSWORD,
        host=config.DB_HOST,
        port=config.DB_PORT
    )
    conn.autocommit = True
    cursor = conn.cursor()

    # Crear la base de datos
    cursor.execute(f"CREATE DATABASE {config.DB_NAME};")
    cursor.close()
    conn.close()
    print(f"Base de datos '{config.DB_NAME}' creada exitosamente.")

def create_table():
    """Crear la tabla en PostgreSQL."""
    conn = psycopg2.connect(
        dbname=config.DB_NAME,
        user=config.DB_USER,
        password=config.DB_PASSWORD,
        host=config.DB_HOST,
        port=config.DB_PORT
    )
    cursor = conn.cursor()

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS historial (
            id SERIAL PRIMARY KEY,
            cedula TEXT NOT NULL,
            fecha TEXT NOT NULL,
            hora TEXT NOT NULL,
            nombres TEXT NOT NULL,
            direccion TEXT NOT NULL,
            celular TEXT NOT NULL,
            total TEXT NOT NULL
        );
    """)

    conn.commit()
    cursor.close()
    conn.close()
    print("Tabla 'historial' creada correctamente.")

if __name__ == "__main__":
    try:
        create_database()
    except Exception as e:
        print(f"Error creando la base de datos: {e}")

    try:
        create_table()
    except Exception as e:
        print(f"Error creando la tabla: {e}")