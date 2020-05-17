from dotenv import load_dotenv
import os
from wit import Wit

load_dotenv()
access_token = os.getenv('SERVER_ACCESS_TOKEN')
client = Wit(access_token)
resp = client.message('Is it hot there?')
print()
print('Yay, got wit.ai response : ' + str(resp))
print()
print('Confidence = ', resp['entities']['intent'][0]['confidence'])
print()