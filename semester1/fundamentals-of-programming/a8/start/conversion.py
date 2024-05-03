import pickle


def read_data_from_text_file(text_file_path):
    data = []
    with open(text_file_path, 'r') as file:
        for line in file:
            processed_line = line.strip()
            data.append(processed_line)

    print(data)

    return data


def write_data_to_binary_file(data, binary_file_path):
    with open(binary_file_path, 'wb') as binary_file:
        pickle.dump(data, binary_file)

# movie_textfile.txt, movie.pickle
# rental_textfile.txt, rental.pickle
# client_textfile.txt, client.pickle


text_file_path = 'client_textfile.txt'
binary_file_path = 'client.pickle'

data = read_data_from_text_file(text_file_path)
write_data_to_binary_file(data, binary_file_path)


text_file_path = 'movie_textfile.txt'
binary_file_path = 'movie.pickle'

data = read_data_from_text_file(text_file_path)
write_data_to_binary_file(data, binary_file_path)


text_file_path = 'rental_textfile.txt'
binary_file_path = 'rental.pickle'

data = read_data_from_text_file(text_file_path)
write_data_to_binary_file(data, binary_file_path)


print(f"Data from {text_file_path} has been read and written to {binary_file_path} in binary format.")
