import nltk
from nltk.tokenize import word_tokenize, sent_tokenize
import csv
import os

# Check if 'punkt' is already downloaded
try:
    nltk.data.find('tokenizers/punkt')
except LookupError:
    nltk.download('punkt')

def process_text(input_file):
    with open(input_file, 'r', encoding='utf-8') as file:
        input_text = file.read()
    
    sentences = sent_tokenize(input_text)
    processed_data = []

    for sentence in sentences:
        words = word_tokenize(sentence)
        num_words = len(words)
        morphemes = sum(len(word) for word in words)  # Simplified example
        inflectional_morphemes = sum(1 for word in words if word.endswith('s'))  # Dummy example
        function_words = sum(1 for word in words if word.lower() in ['the', 'is', 'in', 'and'])  # Example

        processed_data.append((sentence.replace('\n', ' '), num_words, morphemes, inflectional_morphemes, function_words))

    return processed_data

def save_to_csv(processed_data, csv_file):
    try:
        with open(csv_file, 'w', newline='', encoding='utf-8') as file:
            writer = csv.writer(file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
            writer.writerow(["Sentence", "Words", "Morphemes", "Inflectional Morphemes", "Function Words"])
            for data in processed_data:
                writer.writerow(data)
                print(f"Writing to CSV: {data}")
    except PermissionError:
        print(f"Permission denied: '{csv_file}'. Please close any open instances of the file and try again.")

# File paths
script_dir = os.path.dirname(os.path.abspath(__file__))
input_text_file = os.path.join(script_dir, 'input_text.txt')
input_csv = os.path.join(script_dir, 'input_data.csv')

# Preprocess the text
processed_data = process_text(input_text_file)

# Save the preprocessed data to a CSV file
save_to_csv(processed_data, input_csv)
print(f"Input CSV: {input_csv}")
