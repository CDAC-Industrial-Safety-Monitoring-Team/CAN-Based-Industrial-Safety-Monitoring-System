from flask import Flask, render_template, jsonify
from mqtt_client import latest_data

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/data")
def data():
    return jsonify(latest_data)

if __name__ == "__main__":
    app.run(debug=True)