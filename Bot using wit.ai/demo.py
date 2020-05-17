from dotenv import load_dotenv
load_dotenv()
import os

server_access_token = os.getenv('SERVER_ACCESS_TOKEN')
print(server_access_token)