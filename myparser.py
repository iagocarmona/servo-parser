import re
import requests

esp32_ip = "IP_DO_SEU_ESP32"

url = f"http://{esp32_ip}/setservos"

data = {}

if __name__ == "__main__":
    import sys

    with open(sys.argv[1]) as arq:
        code = arq.readlines()
        for line in code:
            pat = re.search(r"mover eixo ([123]) em (\d{1,3})", line)
            pat_garra = re.search(r"(abre|fecha) garra", line)
            if pat:
                data[f"servo{pat.group(1)}"] = int(pat.group(2))
            elif pat_garra:
                data["servo4"] = 0 if pat_garra.group(1) == "abre" else 180

            if len(data) == 4:
                print(data)
                # response = requests.post(url, data=data)

                # if response.status_code == 200:
                #     print("Servos definidos com sucesso!")
                # else:
                #     print(f"Erro ao definir os servos: {response.status_code}")

                data = {}
# data = {
#     "servo1": 90,
#     "servo2": 45,
#     "servo3": 135,
#     "servo4": 0
# }


# mover eixo [123] em \d{1,}
# (abre|fecha) garra
# fim repita
# repita \d{1,} vezes:
