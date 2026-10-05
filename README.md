### Getting started
# Compiling
Run "make".

# Running tests
Run "make test".

# Running the freq_count program
Compile with "make freq_count".
To run the program with a custom file, do "hash_table/freq_count " followed by the file to count the words.
To run the program with included file 10k-words.txt, run "make run_freq_count".

### Design decisions
# Error handling
Erros are handled by asserts / crashing if the inputs are invalid, otherwise returing a boolean if the function was successful or not.

# Hash table ownership
The hash table does not by default take ownership of the keys and values, however the user has the option of adding an on entry destroy function that will be ran at the beginning of the destruction of each entry. This essentially lets the user decide if the hash table should own the data or not.

# Linked list ownership
The linked list does not own the inserted data, so strings or void pointers would need to be freed on their own.
