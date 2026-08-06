import paho.mqtt.client as mqtt

latest_data = {
    "status": "SAFE",
    "temp": 0,
    "hum": 0,
    "vib": 0
}

BROKER = "10.167.33.179"
TOPIC = "industrial/safety"


def on_message(client, userdata, msg):
    global latest_data

    data = msg.payload.decode()

    try:
        arr = data.split(",")

        for item in arr:
            key, value = item.split(":")

            if key == "STATUS":
                latest_data["status"] = value

            elif key == "TEMP":
                latest_data["temp"] = int(value)

            elif key == "HUM":
                latest_data["hum"] = int(value)

            elif key == "VIB":
                latest_data["vib"] = int(value)

    except Exception as e:
        print(e)


client = mqtt.Client()

client.on_message = on_message

client.connect(BROKER, 1883)

client.subscribe(TOPIC)

client.loop_start()
