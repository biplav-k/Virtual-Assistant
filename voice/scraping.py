import requests, bs4
import os
import time
import speech_recognition as sr
import playsound
from commands import *
from gtts import gTTS
import sys

iteration = 0
history_path = "../files/decks/history.txt"
definitions = []
the_word = sys.argv[1]

def speak(text,num_of_iter):
    tts = gTTS(text=text, lang="en")
    filename = "voice" + str(num_of_iter)+".mp3"
    tts.save(filename)
    playsound.playsound(filename)

def get_audio():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        audio = r.listen(source)
        said = ""

        try:
            said = r.recognize_google(audio, language='en')
            print(said)
        except Exception as e:
            print("Exception: "+ str(e))
    return said

#Saves the word and its definition
def save_word(word, definition):
    with open(history_path, "a") as writer:
        writer.write("\n\n# " + word + "\n")
        for line in definitions:
            writer.write("- " + line + "\n")

## Uncomment these lines to enable the Voice Assistant
# speak("What are you looking for",1)
# the_word = get_audio()

#The website we want to inspect

res = requests.get("https://www.dictionary.com/browse/" + the_word)

#The while loop prevent the program to exit automatically, if a definition can't be found
while(res.status_code == 404):
    the_word = input("Can't find the definition at www.dictionary.com, try it again or press ctrl+c to exit!")
    res = requests.get("https://www.dictionary.com/browse/" + the_word)

soup = bs4.BeautifulSoup(res.text, "html.parser")
elements = soup.select("div") #returns a list of dictionaries of each div


for item in elements:
    if "value" in item.attrs.keys():
        definitions.append(item.getText())

#Prints the first two definitions if available
#if len(definitions) > 1:
#    print(definitions[0])
#    print(definitions[1])
#else:
#    print(definitions[0])

#search_browser(the_word)
print("Do you want to save the word?")
choice = input("Press 'y'(yes) or 'n'(no) \n")
if choice == "y":
    with open(history_path, "a") as writer:
        save_word(the_word, definitions)
        print(f"Word: {the_word} saved!")
elif choice == "n":
    print("Didn't saved!")
else:
    print("invalid input")


