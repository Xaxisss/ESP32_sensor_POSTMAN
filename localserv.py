from flask import Flask, request, jsonify

app = Flask(__name__)

# menginisialisasi Variabel untuk menyimpan data sensor terbaru
data_terbaru = {
    "temperature": None,
    "humidity": None
}



@app.route('/data', methods=['POST'])
def receive_data():
    dataNow = request.get_json()
    if not dataNow:
        return jsonify({"message": "Tidak ada data"}), 400

    temperature = dataNow.get('temperature')
    humidity = dataNow.get('humidity')

    if temperature is None or humidity is None:
        return jsonify({"message": "Data Invalid"}), 400

    
    data_terbaru['temperature'] = temperature# untuk Simpan data sensor terbaru
    data_terbaru['humidity'] = humidity

    print(f"Received temperature: {temperature}")
    print(f"Received humidity: {humidity}")

    return jsonify({"message": "Data diterima"}), 200

@app.route('/data', methods=['GET'])
def get_data():
    print("GET request received")
    if data_terbaru['temperature'] is None or data_terbaru['humidity'] is None:
        return jsonify({"message": "Tidak ada data"}), 404

    return jsonify(data_terbaru), 200
#mencoba membuat endpoint baru sebagai langkah debugging
@app.route('/test', methods=['GET'])
def test_get():
    return jsonify({"message": "GET request to /test successful"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)