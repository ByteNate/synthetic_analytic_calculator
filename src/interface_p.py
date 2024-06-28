import tkinter as tk
from tkinter import messagebox
import subprocess

def calculate_indices():
    try:
        words = int(entry_words.get())
        morphemes = int(entry_morphemes.get())
        inflectional_morphemes = int(entry_inflectional_morphemes.get())
        function_words = int(entry_function_words.get())

        result = subprocess.run(
            ['./synthetic_index_p', str(words), str(morphemes), str(inflectional_morphemes), str(function_words)],
            capture_output=True,
            text=True
        )

        if result.returncode == 0:
            messagebox.showinfo("Results", result.stdout)
        else:
            messagebox.showerror("Error", "Failed to calculate indices.\n" + result.stderr)

    except ValueError:
        messagebox.showerror("Input Error", "Please enter valid integers.")

root = tk.Tk()
root.title("Synthetic and Analytic Index Calculator")

tk.Label(root, text="Number of Words:").grid(row=0)
tk.Label(root, text="Number of Morphemes:").grid(row=1)
tk.Label(root, text="Number of Inflectional Morphemes:").grid(row=2)
tk.Label(root, text="Number of Function Words:").grid(row=3)

entry_words = tk.Entry(root)
entry_morphemes = tk.Entry(root)
entry_inflectional_morphemes = tk.Entry(root)
entry_function_words = tk.Entry(root)

entry_words.grid(row=0, column=1)
entry_morphemes.grid(row=1, column=1)
entry_inflectional_morphemes.grid(row=2, column=1)
entry_function_words.grid(row=3, column=1)

tk.Button(root, text="Calculate", command=calculate_indices).grid(row=4, column=1)

root.mainloop()
