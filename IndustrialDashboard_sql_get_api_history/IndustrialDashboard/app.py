from flask import Flask, render_template, jsonify
from mqtt_client import latest_data
from database import get_last_100

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/data")
def data():
    return jsonify(latest_data)

@app.route("/history")
def history():
    return jsonify(get_last_100())

if __name__ == "__main__":
    app.run(debug=True, use_reloader=False)