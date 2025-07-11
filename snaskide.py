
import tkinter as tk
from tkinter import filedialog
import os
import subprocess

def run_code():
    code = text_editor.get("1.0", tk.END)
    
    # Create directory if it doesn't exist
    if not os.path.exists("C:/Snask"):
        os.makedirs("C:/Snask")
        
    with open("C:/Snask/main.py", "w") as f:
        f.write(code)
    
    # Run the code using the snask interpreter
    snask_dir = os.path.dirname(os.path.abspath(__file__))
    main_py_path = os.path.join(snask_dir, "main.py")
    subprocess.run(["python", main_py_path], cwd="C:/Snask")

# Create the main window
window = tk.Tk()
window.title("Snask IDE")

# Create a text editor widget
text_editor = tk.Text(window)
text_editor.pack()

# Create a "Run" button
run_button = tk.Button(window, text="Run", command=run_code)
run_button.pack()

# Start the Tkinter event loop
window.mainloop()
