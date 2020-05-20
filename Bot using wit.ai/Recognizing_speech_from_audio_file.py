from dotenv import load_dotenv
import os
from wit import Wit

# cwd = os.getcwd()  # Get the current working directory (cwd)
# files = os.listdir(cwd)  # Get all the files in that directory
# print("Files in %r: %s" % (cwd, files))


load_dotenv()
access_token = os.getenv('SERVER_ACCESS_TOKEN')
client = Wit(access_token)
resp = None
with open('milk.wav', 'rb') as f:
  resp = client.speech(f, {'Content-Type': 'audio/wav'})
print()
print('Yay, got Wit.ai response: ' + str(resp))
print()
