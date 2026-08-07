import paho.mqtt.client as mqtt
from database import save_data

latest_data = {
    "status": "SAFE",
    "temp": 0,
    "hum": 0,
    "vib": 0,
    "gas": 1
}

BROKER = "10.62.176.181"
TOPIC = "industrial/safety"


def on_connect(client, userdata, flags, rc):

    if rc == 0:

        print("Connected to MQTT Broker")

        client.subscribe(TOPIC)

        print("Subscribed to:", TOPIC)

    else:

        print("Connection Failed:", rc)


def on_message(client, userdata, msg):

    global latest_data

    data = msg.payload.decode().strip()

    print("\n==============================")
    print("MQTT Received :", data)

    try:

        arr = data.split(",")

        for item in arr:

            key, value = item.split(":", 1)

            key = key.strip()
            value = value.strip()

            if key == "STATUS":
                latest_data["status"] = value

            elif key == "TEMP":
                latest_data["temp"] = int(value)

            elif key == "HUM":
                latest_data["hum"] = int(value)

            elif key == "VIB":
                latest_data["vib"] = int(value)

            elif key == "GAS":
                latest_data["gas"] = int(value)

        print("Updated Data :", latest_data)

        # Save into database
        save_data(latest_data)

        print("Data Stored Successfully")

    except Exception as e:

        print("Parser Error")
        print(e)


client = mqtt.Client()

client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, 1883, 60)

client.loop_start()