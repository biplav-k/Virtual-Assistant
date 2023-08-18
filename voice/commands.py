import webbrowser
#This function will be triggered if the word "definition" appears in the command
#There will also be another function, which opens a wikipedia document
def search_browser(word):
    base_url = "https://www.dictionary.com/browse/"
    webbrowser.open(base_url + word, new = 2)
