import requests

url = "https://www.nseindia.com/api/reports?archives=%5B%7B%22name%22%3A%22F%26O%20-%20Bhavcopy%20(fo.zip)%22%2C%22type%22%3A%22archives%22%2C%22category%22%3A%22derivatives%22%2C%22section%22%3A%22equity%22%7D%5D&date=10-Apr-2021&type=equity&mode=single"
filename = "fo.zip"
print(filename)
response = requests.post(url)
print(response)
if response.status_code == 200:
    with open(filename, 'wb') as file:
        file.write(response.content)
    print(f"File '{filename}' downloaded successfully.")
else:
    print(f"Failed to download the file. HTTP status code: {response.status_code}")
