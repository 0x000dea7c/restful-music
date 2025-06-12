import sqlite3
import os

def create_database():
    database_file = os.environ("RESTMUSIC_DATABASE_NAME")

    try:
        connection = sqlite3.connect(database_file)
        cursor = connection.cursor()

        cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
        uuid TEXT UNIQUE,
        username TEXT UNIQUE,
        password TEXT,
        email TEXT UNIQUE
        )
        """)

        connection.commit()
        print("Database and tables created successfully")
    except sqlite3.Error as error:
        print(f"SQLite error: {error}")
    except Exception as error:
        print(f"Error: {error}")

    connection.close()

if __name__ == "__main__":
    create_database()
