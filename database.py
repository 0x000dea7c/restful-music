import sqlite3
import os

def create_database():
    database_file = os.environ("RESTMUSIC_DATABASE_NAME")

    try:
        connection = sqlite3.connect(database_file)
        cursor = connection.cursor()

        cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
        uuid TEXT PRIMARY KEY,
        username TEXT UNIQUE,
        password TEXT,
        email TEXT UNIQUE
        )
        """)

        cursor.execute("""
        CREATE TABLE IF NOT EXISTS playlists (
        uuid TEXT PRIMARY KEY,
        user_uuid TEXT,
        name TEXT TEXT NOT NULL,
        description TEXT NOT NULL,

        FOREIGN KEY (user_uuid) REFERENCES users(uuid)
        )
        """)

        cursor.execute("""
        CREATE TABLE IF NOT EXISTS songs (
        uuid TEXT PRIMARY KEY,
        title TEXT NOT NULL,
        artist TEXT NOT NULL,
        album TEXT,
        release_date INTEGER,
        duration INTEGER
        )
        """)

        cursor.execute("""
        CREATE TABLE playlist_songs (
        playlist_uuid TEXT,
        song_uuid TEXT,
        order INTEGER,
        PRIMARY KEY (playlist_uuid, song_uuid),
        FOREIGN KEY (playlist_uuid) REFERENCES playlists(uuid),
        FOREIGN KEY (song_uuid) REFERENCES songs(uuid)
        );
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
