import xml_generator

import PySimpleGUI as sg
import os.path

sg.theme('Black')

# print(xml_generator.world.getchildren())

# First the window layout in 2 columns
file_list_column = [
    [sg.Text("Output xml name"),
     # sg.In(size=(25, 1), enable_events=True, key="-FOLDER-"),
     sg.FolderBrowse(), ],
    [sg.Listbox(values=[], enable_events=True, size=(40, 20), key="-ELEMENTS LIST-")],
]
# For now will only show the name of the file that was chosen
element_actions = [
    [sg.Text("Actions:")],
    [sg.Text(size=(40, 1), key="-TEXT-")],
    [sg.Image(key="-IMAGE-")],
]

# ----- Full layout -----
layout = [
    [sg.Column(file_list_column),
     sg.VSeperator(),
     sg.Column(element_actions), ]
]
window = sg.Window("Column Demo", layout)
# Run the Event Loop
while True:
    event, values = window.read()
    if event == "Exit" or event == sg.WIN_CLOSED:
        break
    # Folder name was filled in, make a list of files in the folder
    if event == "-FOLDER-":
        folder = values["-FOLDER-"]
        try:
            # Get list of files in folder
            file_list = os.listdir(folder)
        except:
            file_list = []
        fnames = [
            f
            for f in file_list
            if os.path.isfile(os.path.join(folder, f))
               and f.lower().endswith((".png", ".gif"))
        ]
        window["-FILE LIST-"].update(fnames)
    elif event == "-FILE LIST-":  # A file was chosen from the listbox
        try:
            filename = os.path.join(values["-FOLDER-"], values["-FILE LIST-"][0])
            window["-TEXT-"].update(filename)
            window["-IMAGE-"].update(filename=filename)
        except:
            pass
window.close()
