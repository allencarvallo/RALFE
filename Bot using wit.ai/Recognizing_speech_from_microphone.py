from dotenv import load_dotenv
import os
from wit import Wit

load_dotenv()
access_token = os.getenv('SERVER_ACCESS_TOKEN')

import speech_recognition as sr 

r = sr.Recognizer()

with sr.Microphone() as source :
    print('Say Something')
    audio = r.listen(source)
    try :
        voice_data = r.recognize_wit(audio,access_token)
        print(voice_data)
    except sr.UnknownValueError :
        print('Sorry, I did not get that')
    except sr.RequestError :
        print('Key is not valid or no internet connection')

