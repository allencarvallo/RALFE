import speech_recognition as sr
from wit import Wit

r = sr.Recognizer()

access_token = "2YHFBJ6CMIGVD4V3PQPA4A6ZWTUYZHUF"

def record_audio() :
    with sr.Microphone() as source:
        audio = r.listen(source)
        voice_data = ''
        try:
            voice_data = r.recognize_google(audio)
        except sr.UnknownValueError:
            print('Sorry, I did not get that')
        except sr.RequestError:
            print("Sorry, speech service is down")
        return voice_data


print()
print('Ralfe here, Say something....')
voice_data = record_audio()
print(voice_data)

client = Wit(access_token)
resp = client.message(voice_data)

print()
print('Wit.ai response')
print()
print(resp)
print()

intent = resp['intents'][0]['name']
print("intent name : ",intent)
print()
confidence = resp['intents'][0]['confidence']
print("confidence value : ",confidence)
print()
entity_value = resp['entities']['person:person'][0]['value']
print("Entity name : ",entity_value)
print()
if intent == 'call_someone' and confidence >= 0.90 and entity_value == 'son' :
    print("Calling Son....")
    print()
