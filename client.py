import requests

esp32_ip = "IP_DO_SEU_ESP32"

url = f"http://{esp32_ip}/setservos"

data = {
    "servo1": 90,
    "servo2": 45,
    "servo3": 135,
    "servo4": 0
}

response = requests.post(url, data=data)

if response.status_code == 200:
    print("Servos definidos com sucesso!")
else:
    print(f"Erro ao definir os servos: {response.status_code}")
