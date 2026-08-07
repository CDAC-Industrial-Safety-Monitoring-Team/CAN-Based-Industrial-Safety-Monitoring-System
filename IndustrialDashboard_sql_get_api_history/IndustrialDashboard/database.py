import mysql.connector
from datetime import datetime

# MySQL Connection
db = mysql.connector.connect(
    host="localhost",
    user="shouri",
    password="sunbeam@123",
    database="industrial_safety"
)

cursor = db.cursor(dictionary=True)

print("Connected to MySQL Database")


def save_data(data):
    """
    Save one sensor record into MySQL
    """

    sql = """
    INSERT INTO sensor_data
    (timestamp, temp, hum, vib, gas, status)
    VALUES (%s,%s,%s,%s,%s,%s)
    """

    values = (
        datetime.now(),
        data["temp"],
        data["hum"],
        data["vib"],
        data["gas"],
        data["status"]
    )

    cursor.execute(sql, values)
    db.commit()


def get_last_100():

    cursor.execute("""
        SELECT *
        FROM sensor_data
        ORDER BY id DESC
        LIMIT 100
    """)

    return cursor.fetchall()